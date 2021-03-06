#ifndef FIND_MODULE_H
#define FIND_MODULE_H

#include <omnetpp.h>


/**
 * @brief Provides method templates to find omnet modules.
 *
 * @ingroup baseUtils
 * @ingroup utils
 */
template<typename T = omnetpp::cModule*>
class FindModule
{
	public:
		/**
		 * @brief Returns a pointer to a sub module of the passed module with
		 * the type of this template.
		 *
		 * Returns NULL if no matching submodule could be found.
		 */
		static T findSubModule(omnetpp::cModule *top)
		{
			T ret;
			for (omnetpp::cModule::SubmoduleIterator i(top); !i.end(); i++)
			{
                omnetpp::cModule *sub = *i; 
				ret = dynamic_cast<T>(sub);
				if (ret!=NULL)
					return ret;
				ret = findSubModule(sub);
				if (ret!=NULL)
					return ret;
			}
			return NULL;
		}

		/**
		 * @brief Returns a pointer to the module with the type of this
		 * template.
		 *
		 * Returns NULL if no module of this type could be found.
		 */
		static T findGlobalModule() {return findSubModule(omnetpp::cSimulation::getActiveSimulation()->getSystemModule());}

		/**
		 * @brief Returns a pointer to the host module of the passed module.
		 *
		 * Assumes that every host module is a direct sub module of the
		 * simulation.
		 */
		static omnetpp::cModule* findHost(omnetpp::cModule *m) {
            omnetpp::cModule *parent = m->getParentModule();
            omnetpp::cModule *node = m;

			// all nodes should be a sub module of the simulation which has no parent module!!!
			while( parent->getParentModule() != NULL ){
			node = parent;
			parent = node->getParentModule();
			}

			return node;
		}
};

#endif
