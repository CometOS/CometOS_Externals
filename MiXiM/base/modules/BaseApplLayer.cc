/* -*- mode:c++ -*- *******************************************************
 * file:        BaseApplLayer.cc
 *
 * author:      Daniel Willkomm
 *
 * copyright:   (C) 2004 Telecommunication Networks Group (TKN) at
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
 * description: application layer: general class for the application layer
 *              subclass to create your own application layer
 ***************************************************************************/


#include "BaseApplLayer.h"
#include "PassedMessage.h"

using namespace omnetpp;
/**
 * First we have to initialize the module from which we derived ours,
 * in this case BaseLayer.
 *
 * Then we have to intialize the gates and - if necessary - some own
 * variables.
 **/
void BaseApplLayer::initialize(int stage)
{
    BaseLayer::initialize(stage);
    if(stage==0){
        headerLength= par("headerLength");
    }
}

/**
 * Send message down to lower layer
 **/
void BaseApplLayer::sendDelayedDown(cMessage *msg, simtime_t delay) {
    recordPacket(PassedMessage::OUTGOING, PassedMessage::LOWER_DATA, msg);
    sendDelayed(msg, delay, lowerGateOut);
}

void BaseApplLayer::handleSelfMsg(omnetpp::cMessage* msg) {
    EV << "BaseApplLayer: handleSelfMsg not redefined; delete msg\n";
    delete msg;
};

void BaseApplLayer::handleLowerMsg(omnetpp::cMessage* msg) {
    EV << "BaseApplLayer: handleLowerMsg not redefined; delete msg\n";
    delete msg;
};

void BaseApplLayer::handleLowerControl(omnetpp::cMessage* msg) {
    EV << "BaseApplLayer: handleLowerControl not redefined; delete msg\n";
    delete msg;
};

void BaseApplLayer::handleUpperMsg(omnetpp::cMessage *msg) {
    assert(false);
    EV << "Application has no upper layers!";
    delete msg;
}

void BaseApplLayer::handleUpperControl(omnetpp::cMessage *msg) {
    assert(false);
    EV << "Application has no upper layers!";
    delete msg;
}

