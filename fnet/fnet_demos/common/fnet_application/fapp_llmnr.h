/**************************************************************************
* 
* Copyright 2014 by Andrey Butok. FNET Community.
*
***************************************************************************
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License Version 3 
* or later (the "LGPL").
*
* As a special exception, the copyright holders of the FNET project give you
* permission to link the FNET sources with independent modules to produce an
* executable, regardless of the license terms of these independent modules,
* and to copy and distribute the resulting executable under terms of your 
* choice, provided that you also meet, for each linked independent module,
* the terms and conditions of the license of that module.
* An independent module is a module which is not derived from or based 
* on this library. 
* If you modify the FNET sources, you may extend this exception 
* to your version of the FNET sources, but you are not obligated 
* to do so. If you do not wish to do so, delete this
* exception statement from your version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* You should have received a copy of the GNU General Public License
* and the GNU Lesser General Public License along with this program.
* If not, see <http://www.gnu.org/licenses/>.
*
**********************************************************************/ /*!
*
* @file fapp_llmnr.h
*
* @author Andrey Butok
*
* @brief FNET Shell Demo (LLMNR Server).
*
***************************************************************************/


/************************************************************************
*     Private Definitions.
*************************************************************************/
#ifndef _FAPP_LLMNR_H_

#define _FAPP_LLMNR_H_

#if FAPP_CFG_LLMNR_CMD && FNET_CFG_LLMNR

void fapp_llmnr_cmd( fnet_shell_desc_t desc, int argc, char ** argv );
void fapp_llmnr_info(fnet_shell_desc_t desc);
void fapp_llmnr_release(void);

#endif /* FAPP_CFG_LLMNR_CMD */

#endif /* _FAPP_LLMNR_H_ */
