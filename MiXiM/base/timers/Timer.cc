#include "Timer.h"
#include "TimerCore.h"

using namespace omnetpp;

void Timer::init(cModule *parent)
{
	owner = parent;
	if (ct==NULL)
	{
		ct = dynamic_cast<TimerCore*>(cModuleType::get("TimerCore")->createScheduleInit("TimerCore",owner));
		ct->init(this);
	}
}

void Timer::checkCT() 
{
    if (ct == NULL)
        EV << "init() must be called before using Timer functions";
}
