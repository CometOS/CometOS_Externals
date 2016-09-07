/* -*- mode:c++ -*- ********************************************************
 * file:        NicEntryDebug.cc
 *
 * author:      Daniel Willkomm
 *
 * copyright:   (C) 2005 Telecommunication Networks Group (TKN) at
 *              Technische Universitaet Berlin, Germany.
 *
 *              This program is free software; you can redistribute it
 *              and/or modify it under the terms of the GNU General Public
 *              License as published by the Free Software Foundation; either
 *              version 2 of the License, or (at your option) any later
 *              version.
 *              For further information see file COPYING
 *              in the top level directory
 ***************************************************************************
 * part of:     framework implementation developed by tkn
 * description: Class to store information about a nic for the
 *              ConnectionManager module
 **************************************************************************/

#include "NicEntryDebug.h"
#include "ChannelAccess.h"

#include <cassert>

using namespace omnetpp;

#ifndef nicEV
//#define nicEV (ev.isDisabled()||!coreDebug) ? ev : ev << "NicEntry: "
#define nicEV EV << "NicEntry: " 
#endif

void NicEntryDebug::connectTo(NicEntry* other) {
	nicEV<<"connecting nic #"<<nicId<< " and #"<<other->nicId<<endl;

	NicEntryDebug* otherNic = (NicEntryDebug*) other;

	omnetpp::cGate *localoutgate = requestOutGate();
	localoutgate->connectTo(otherNic->requestInGate());
	outConns[other] = localoutgate->getPathStartGate();
}


void NicEntryDebug::disconnectFrom(NicEntry* other) {
	nicEV<<"disconnecting nic #"<<nicId<< " and #"<<other->nicId<<endl;

	NicEntryDebug* otherNic = (NicEntryDebug*) other;

	//search the connection in the outConns list
	GateList::iterator p = outConns.find(other);
	//no need to check whether entry is valid; is already check by ConnectionManager isConnected
	//get the hostGate
	//order is phyGate->nicGate->hostGate
	omnetpp::cGate* hostGate = p->second->getNextGate()->getNextGate();

	// release local out gate
	freeOutGates.push_back(hostGate);

	// release remote in gate
	otherNic->freeInGates.push_back(hostGate->getNextGate());

	//reset gates
	//hostGate->getNextGate()->connectTo(0);
	hostGate->disconnect();

	//delete the connection
	outConns.erase(p);
}


omnetpp::cGate* NicEntryDebug::requestInGate(void) {
	// gate of the host
	omnetpp::cGate *hostGate;

	if (!freeInGates.empty()) {
		hostGate = freeInGates.back();
		freeInGates.pop_back();
	} else {
		char gateName[20];

		// we will have one more in gate
		++inCnt;

		//get a unique name for the gate (composed of the nic module id and a counter)
		sprintf(gateName, "in%d-%d", nicId, inCnt);

		// create a new gate for the host module
		nicPtr->getParentModule()->addGate(gateName, omnetpp::cGate::INPUT);
		hostGate = nicPtr->getParentModule()->gate(gateName);

		// gate of the nic
		omnetpp::cGate *nicGate;

		// create a new gate for the nic module
		nicPtr->addGate(gateName, omnetpp::cGate::INPUT);
		nicGate = nicPtr->gate(gateName);

		// connect the hist gate with the nic gate
		hostGate->connectTo(nicGate);

		// pointer to the phy module
		ChannelAccess* phyModule;
		// gate of the phy module
		omnetpp::cGate *phyGate;

		// to avoid unnecessary dynamic_casting we check for a "phy"-named submodule first
		if ((phyModule = static_cast<ChannelAccess *> (nicPtr->getSubmodule("phy"))) == NULL)
			phyModule = FindModule<ChannelAccess*>::findSubModule(nicPtr);
		assert(phyModule != 0);

		// create a new gate for the phy module
		phyModule->addGate(gateName, omnetpp::cGate::INPUT);
		phyGate = phyModule->gate(gateName);

		// connect the nic gate (the gate of the compound module) to
		// a "real" gate -- the gate of the phy module
		nicGate->connectTo(phyGate);
	}

	return hostGate;
}

omnetpp::cGate* NicEntryDebug::requestOutGate(void) {
	// gate of the host
	omnetpp::cGate *hostGate;

	if (!freeOutGates.empty()) {
		hostGate = freeOutGates.back();
		freeOutGates.pop_back();
	} else {
		char gateName[20];

		// we will have one more out gate
		++outCnt;

		//get a unique name for the gate (composed of the nic module id and a counter)
		sprintf(gateName, "out%d-%d", nicId, outCnt);

		// create a new gate for the host module
		nicPtr->getParentModule()->addGate(gateName, omnetpp::cGate::OUTPUT);
		hostGate = nicPtr->getParentModule()->gate(gateName);

		// gate of the nic
		omnetpp::cGate *nicGate;
		// create a new gate for the nic module
		nicPtr->addGate(gateName, omnetpp::cGate::OUTPUT);
		nicGate = nicPtr->gate(gateName);

		// connect the hist gate with the nic gate
		nicGate->connectTo(hostGate);

		// pointer to the phy module
		ChannelAccess* phyModule;
		// gate of the phy module
		omnetpp::cGate *phyGate;

		// to avoid unnecessary dynamic_casting we check for a "phy"-named submodule first
		if ((phyModule = static_cast<ChannelAccess *> (nicPtr->getSubmodule("phy"))) == NULL)
			phyModule = FindModule<ChannelAccess*>::findSubModule(nicPtr);
		assert(phyModule != 0);

		// create a new gate for the phy module
		phyModule->addGate(gateName, omnetpp::cGate::OUTPUT);
		phyGate = phyModule->gate(gateName);

		// connect the nic gate (the gate of the compound module) to
		// a "real" gate -- the gate of the phy module
		phyGate->connectTo(nicGate);
	}

	return hostGate;
}
