# CometOS Externals #

This repository contains external components to be used together with the CometOS framework that are not compatible with the BSD license.
Using components from this repository together with CometOS is allowed if you consider the license of the respective component.

## Getting started ##

The CometOS build environment will automatically recognize and report if a component of this repository is necessary for the respective build. In that case, check out this repository and provide the COMETOS_EXTERNALS_PATH, then rebuild.

    git clone https://github.com/CometOS/CometOS_Externals.git ~/cometos_externals
    echo 'export COMETOS_EXTERNALS_PATH=~/cometos_externals' >> ~/.bashrc
    source ~/.bashrc


## Components ##

### MiXiM ###

Used for OMNeT++ simulations of the IEEE 802.15.4 MAC and PHY Layer.

http://mixim.sourceforge.net/

Located at MiXiM/

Modified version of MiXiM in the version 2.1. Amonst others, this version of MiXiM runs under OMNeT++ version 5.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

### FNET ###

Used for supporting Ethernet on the FRDM K64F board. Slightly adapted to fit CometOS.
http://fnet.sourceforge.net/

Located at FNET/

We gladly welcome every attempt to adapt a current FNET version with a more permissive license (Apache Version 2.0) for the use with CometOS!

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License Version 3 
or later (the "LGPL").

As a special exception, the copyright holders of the FNET project give you
permission to link the FNET sources with independent modules to produce an
executable, regardless of the license terms of these independent modules,
and to copy and distribute the resulting executable under terms of your 
choice, provided that you also meet, for each linked independent module,
the terms and conditions of the license of that module.
An independent module is a module which is not derived from or based 
on this library. 
If you modify the FNET sources, you may extend this exception 
to your version of the FNET sources, but you are not obligated 
to do so. If you do not wish to do so, delete this
exception statement from your version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

You should have received a copy of the GNU General Public License
and the GNU Lesser General Public License along with this program.
If not, see <http://www.gnu.org/licenses/>.

### Hierarchical Finite State Machine ###

Used for the 6LoWPAN Ordered Forwarding component of CometOS.

Located at HFSM.h

Heavily based (partially just taken/adapted from) the QEP event processor
(Miro Samek, "Practical UML Statecharts in C/C++"), for which the GPLv3 applies.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.

For details see http://state-machine.com/qpc/index.html#licensing

### RS-232 ###
Abstraction layer for RS-232 for the "local" platform. Not required for RS-232 on hardware.
We gladly welcome every attempt to implement RS-232 support directly into CometOS!

Located at rs232/

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
