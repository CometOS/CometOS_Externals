/* -*- mode:c++ -*- ********************************************************
 * file:        BaseWorldUtility.h
 *
 * author:      Tom Parker
 *
 * copyright:   (C) 2006 Parallel and Distributed Systems Group (PDS) at
 *              Technische Universiteit Delft, The Netherlands.
 *
 *              This program is free software; you can redistribute it
 *              and/or modify it under the terms of the GNU General Public
 *              License as published by the Free Software Foundation; either
 *              version 2 of the License, or (at your option) any later
 *              version.
 *              For further information see file COPYING
 *              in the top level directory
 ***************************************************************************
 * description: basic world utility class
 *              provides world-required values
 **************************************************************************/

#include "BaseWorldUtility.h"
#include "FindModule.h"
#include "BaseConnectionManager.h"

using namespace omnetpp;
Define_Module(BaseWorldUtility);

const double BaseWorldUtility::speedOfLight = 299792458.0; //metres per second

BaseWorldUtility::BaseWorldUtility():
		isInitialized(false)
{}

void BaseWorldUtility::initialize(int stage) {
	Blackboard::initialize(stage);

	if (stage == 0) {
        initializeIfNecessary();
	}
	else if(stage == 1) {
		//check if necessary modules are there
		//Connection Manager
		if(!FindModule<BaseConnectionManager*>::findGlobalModule()) {
			EV << "Could not find a connection manager module in the network!";
		}
	}
}

void BaseWorldUtility::initializeIfNecessary()
{
	if(isInitialized)
		return;

	use2DFlag = par("use2D");

	if (use2DFlag) {
		playgroundSize = Coord(par("playgroundSizeX"),
							   par("playgroundSizeY"));
	} else {
		playgroundSize = Coord(par("playgroundSizeX"),
							   par("playgroundSizeY"),
							   par("playgroundSizeZ"));
	}

	if(playgroundSize.getX() <= 0) {
		EV << "Playground size in X direction is invalid. Should be greater zero.";
	}
	if(playgroundSize.getY() <= 0) {
		EV << "Playground size in Y direction is invalid. Should be greater zero.";
	}
	if(!use2DFlag && playgroundSize.getZ() <= 0) {
		EV << "Playground size in Z direction is invalid. Should be greater zero.";
	}

	useTorusFlag = par("useTorus");

	airFrameId = 0;

	isInitialized = true;
}

Coord BaseWorldUtility::getRandomPosition()
{
	initializeIfNecessary();

    if (use2DFlag) {
        return Coord(uniform(0, playgroundSize.getX()),
                     uniform(0, playgroundSize.getY()));
    } else {
        return Coord(uniform(0, playgroundSize.getX()),
                     uniform(0, playgroundSize.getY()),
                     uniform(0, playgroundSize.getZ()));
    }
}


long BaseWorldUtility::getUniqueAirFrameId(){
    initializeIfNecessary();

    // if counter has done one complete cycle and will be set to a value it already had
    if (airFrameId == -1){
        // print a warning
        EV << "WARNING: AirFrameId-Counter has done one complete cycle."
        << " AirFrameIds are repeating now and may not be unique anymore." << std::endl;
    }

    return airFrameId++;
}
