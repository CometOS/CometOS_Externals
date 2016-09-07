#ifndef GLOBAL_TIME_H
#define GLOBAL_TIME_H 1

#include <omnetpp.h>

using omnetpp::simtime_t;

/*
 * GlobalTime provides information about the local opinion of the global time value
 * Default implementation cheats and just uses simTime, but subclasses should do
 * proper network-wide synchronisation
 */

class GlobalTime: public omnetpp::cSimpleModule
{
	public:	
	    //Module_Class_Members(GlobalTime, cSimpleModule, 0);
		virtual const simtime_t currentGlobalTime() const {return omnetpp::cSimulation::getActiveSimulation()->getSimTime();}
};
#endif
