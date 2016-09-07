#ifndef HFSM_H_
#define HFSM_H_

/**
 * Hierarchical Finite State Machine
 *
 * @author Andreas Weigel, Florian Meier
 *
 * Heavily based (partially just taken/adapted from) the QEP event processor
 * (Miro Samek, "Practical UML Statecharts in C/C++"), for which the GPLv3 applies.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 *
 * For details see http://state-machine.com/qpc/index.html#licensing
 */

#include "palExec.h"
#include "cometosAssert.h"
#include "FSM.h"

namespace cometos {

/**
 * Template for implementing a finite state machine (FSM).
 */
template<typename C, typename E>
class HFSM {

public:
    typedef fsmReturnStatus (C::*state_t)(E& event);

protected:
	/**
	 * Created FSM is put into initial state
	 */
	HFSM(const state_t& initial) :
			state(initial),
			currOrigin(nullptr)
    {}

	fsmReturnStatus top(E& event) {
        return FSM_IGNORED;
    }

	/**
	 * Execute the ENTRY event of the initial state.
	 */
	void run() {
	    E initEvent(FSMEvent::INIT_SIGNAL);
	    E entryEvent(FSMEvent::ENTRY_SIGNAL);

        // call first initial transition, without dispatching entry/exit signals
        fsmReturnStatus r = execute(state, initEvent);
        ASSERT(r == FSM_TRANSITION);

        state_t t = &HFSM::top;

        do {
            E invalidEvent(FSMEvent::EMPTY_SIGNAL);
            state_t path[MAX_NEST_DEPTH];
            int8_t entryPathIdx =0;

            path[0] = state;
            execute(state, invalidEvent);

            while (state != t) {
                // from the state the last initial transition has left us in,
                // we go upwards the hierarchy to the top state;
                path[++entryPathIdx] = state;
                execute(state, invalidEvent);
            }
            ASSERT(entryPathIdx < MAX_NEST_DEPTH);

            // set state back to what it was after init transition
            state = path[0];

            // retrace the path from outer to inner state, calling the entry action for this transition
            do {
                execute(state, entryEvent);
            } while( (--entryPathIdx) > 0);

            t = path[0];

        } while (execute(state, initEvent) == FSM_TRANSITION);
        state = t;
	}

	void dispatch(E& event) {
	    // TODO I guess this could be made dramatically easier
	    E exitSignal(FSMEvent::EXIT_SIGNAL);
	    E emptySignal(FSMEvent::EMPTY_SIGNAL);
	    E entrySignal(FSMEvent::ENTRY_SIGNAL);
	    E initSignal(FSMEvent::INIT_SIGNAL);
	    state_t path[MAX_NEST_DEPTH];
	    state_t s; //< source of a potential transition
	    state_t t; //< old state if no transition; new state in case of transition;
	    fsmReturnStatus r;

	    t = state; // save current old state
	    currOrigin = state;

	    do {
	        // process event hierarchically, i.e., as long as the inner state does
	        // not handle the event, try to process it by its super state
	        s = state;
	        r = (((C*)this)->*s)(event);
	    } while (r == FSM_SUPER);

	    currOrigin = nullptr;

	    // check if a transition has to be handled
	    if (r == FSM_TRANSITION) {
	        int8_t epIdx = (int8_t) (-1); //< transition entry path index
	        int8_t ephIdx;                //< transition entry path helper index

	        path[0] = state; // target of the taken transition
	        path[1] = t;     // old state before taking transition

	        // exit the old state up the the state that was source of the transition
	        while(t != s) {
	            if (execute(t, exitSignal) == FSM_HANDLED) {
	                execute(t, emptySignal);
	            }
	            t = state; // update to next superstate
	        }

	        t = path[0]; // t is now target of the transition

	        if (s == t) { // self transition
	            execute(s, exitSignal);
	            epIdx = 0;                // enter target
	        } else {
	            execute(t, emptySignal);  // superstate of target
	            t = state;
	            if (s == t) {             // source == target->super
	                epIdx = 0;            // enter target
	            } else {
	                execute(s, emptySignal); // superstate of source
	                // check source->super == target->super
	                if (state == t) {
	                    execute(s, exitSignal); // exit source
	                    epIdx = 0;              // enter target
	                } else {
	                    // check source == super->target
	                    if (state == path[0]) {
	                        execute(s, exitSignal);
	                    } else {
	                        // check of possibilities; source == target->super->super..
	                        // store entry path along the way
	                        ephIdx = 0; // indicate that LCA not found
	                        epIdx = 1;  // enter target and its superstate
	                        path[1] = t; // save target of transition
	                        t = state;

	                        r = execute(path[1], emptySignal);
	                        while (r == FSM_SUPER) {
	                            path[++epIdx] = state; // store entry path

	                            // is curr super state the source?
	                            if (state == s) {
	                                ephIdx = 1; // indicate that LCA has been found

	                                ASSERT(epIdx < MAX_NEST_DEPTH);
	                                epIdx--;    // do not enter the source
	                                r = FSM_HANDLED;
	                            } else {
	                                // curr super state is not the source, go up
	                                r = execute(state, emptySignal);
	                            }
	                        }

	                        // has the LCA state been found?
	                        if (ephIdx == 0) {
	                            // LCA not found
	                            ASSERT(epIdx < MAX_NEST_DEPTH);

	                            execute(s, exitSignal);

	                            // check the rest of source->super == target->super->super..
	                            ephIdx = epIdx;

	                            // indicate LCA not found
	                            r = FSM_IGNORED;
	                            do {
	                                if (t == path[ephIdx]) {
	                                    r = FSM_HANDLED;      // indicate LCA found
	                                    epIdx = (ephIdx - 1); // do not enter LCA
	                                    ephIdx = -1;          // terminate loop
	                                } else {
	                                    --ephIdx;
	                                }
	                            } while(ephIdx >= 0);

	                            if (r != FSM_HANDLED) {
	                                // check each source->super->super..
	                                // for each target->super->super..
	                                r = FSM_IGNORED;

	                                do {

	                                    if (execute(t, exitSignal) == FSM_HANDLED) {
	                                        // if not handled, superstate is automatically set
	                                        execute(t, emptySignal);
	                                    }

	                                    t = state;      // set super state to t
	                                    ephIdx = epIdx;
	                                    do {
	                                        if (t == path[ephIdx]) { // is this the LCA?
	                                            // do not enter LCA
	                                            epIdx = ephIdx - 1;
	                                            ephIdx = -1; // break inner loop
	                                            r = FSM_HANDLED;
	                                        } else {
	                                            --ephIdx;
	                                        }
	                                    } while (ephIdx > 0);
	                                } while (r != FSM_HANDLED);
	                            }
	                        }
	                    }
	                }
	            }
	        }
            for (; epIdx >= 0; --epIdx) {
                execute(path[epIdx], entrySignal);
            }
            t = path[0];

            state = t;


            // very similar to the initialization function, equal parts
            // should be refactored into a function
            while (execute(t, initSignal) == FSM_TRANSITION) {
                epIdx = 0;
                path[0] = state;
                execute(state, emptySignal);
                while (state != t) {
                    path[++epIdx] = state;
                    execute(state, emptySignal);
                }

                state = path[0];

                ASSERT(epIdx < MAX_NEST_DEPTH);

                do {
                    execute(path[epIdx], entrySignal);
                } while( --epIdx >= 0);

                t = path[0];
            }
	    }

	    // in case of no transition, restore original state
	    // if a transition happened, t will hold the new state
	    state = t;

	}


	inline fsmReturnStatus superState(state_t super) {
	    state = super;
	    return FSM_SUPER;
	}

	inline fsmReturnStatus transition(state_t next) {
        palExec_atomicBegin();
		state = next;
        palExec_atomicEnd();
        return FSM_TRANSITION;
	}

	const state_t& getState() {
	    if (currOrigin != nullptr) {
            return currOrigin;
        } else {
            return state;
        }
	}

    bool setStateIfIdle(state_t idleState, state_t nextState) {
        palExec_atomicBegin(); 

        if(state != idleState) {
            palExec_atomicEnd();
            return false;
        }

        state = nextState;
        palExec_atomicEnd();
        return true;
    }

private:
    state_t state;
    state_t currOrigin;
    
    inline fsmReturnStatus execute(state_t s, E& e) {
        return (((C*)this)->*s)(e);
    }

    static const uint8_t MAX_NEST_DEPTH = 4;

};


} // namespace

#endif /* FSM_H_ */
