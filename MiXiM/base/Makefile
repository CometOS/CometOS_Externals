#
# OMNeT++/OMNEST Makefile for libmiximbase
#
# This file was generated with the command:
#  opp_makemake -f --deep --make-lib -o miximbase -O out -L../../out/$(CONFIGNAME)/MiXiM/modules
#

# Name of target to be created (-o option)
TARGET = libmiximbase$(A_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -IconnectionManager \
    -Imessages \
    -Imodules \
    -IphyLayer \
    -Itimers \
    -Iutils

# Additional object and library files to link with
EXTRA_OBJS =

# Output directory
PROJECT_OUTPUT_DIR = ../../out
PROJECTRELATIVE_PATH = MiXiM/base
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/connectionManager/ChannelAccess.o \
    $O/connectionManager/BaseConnectionManager.o \
    $O/connectionManager/NicEntryDirect.o \
    $O/connectionManager/ConnectionManager.o \
    $O/connectionManager/NicEntryDebug.o \
    $O/modules/BaseApplLayer.o \
    $O/modules/BaseNetwLayer.o \
    $O/modules/BaseMobility.o \
    $O/modules/BaseUtility.o \
    $O/modules/BaseMacLayer.o \
    $O/modules/BaseLayer.o \
    $O/modules/Blackboard.o \
    $O/modules/TestApplLayer.o \
    $O/modules/BaseModule.o \
    $O/modules/BaseBattery.o \
    $O/modules/BaseArp.o \
    $O/modules/BatteryAccess.o \
    $O/modules/BaseWorldUtility.o \
    $O/phyLayer/ChannelInfo.o \
    $O/phyLayer/BaseDecider.o \
    $O/phyLayer/MappingBase.o \
    $O/phyLayer/Decider.o \
    $O/phyLayer/ChannelState.o \
    $O/phyLayer/Signal.o \
    $O/phyLayer/MappingUtils.o \
    $O/phyLayer/BasePhyLayer.o \
    $O/phyLayer/PhyUtils.o \
    $O/timers/FrameTimerGenerator.o \
    $O/timers/FrameTimer.o \
    $O/timers/RepeatTimerCore.o \
    $O/timers/Timer.o \
    $O/timers/RepeatTimer.o \
    $O/timers/TimerCore.o \
    $O/timers/GlobalTime.o \
    $O/utils/Coord.o \
    $O/utils/winsupport.o \
    $O/messages/ChannelSenseRequest_m.o \
    $O/messages/BorderMsg_m.o \
    $O/messages/MacPkt_m.o \
    $O/messages/ApplPkt_m.o \
    $O/messages/AirFrame_m.o \
    $O/messages/NetwPkt_m.o

# Message files
MSGFILES = \
    messages/ChannelSenseRequest.msg \
    messages/BorderMsg.msg \
    messages/MacPkt.msg \
    messages/ApplPkt.msg \
    messages/AirFrame.msg \
    messages/NetwPkt.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET)

$(TARGET) : $O/$(TARGET)
	$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	$(AR) $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS)

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f miximbase miximbase.exe libmiximbase.so libmiximbase.a libmiximbase.dll libmiximbase.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f connectionManager/*_m.cc connectionManager/*_m.h
	-rm -f messages/*_m.cc messages/*_m.h
	-rm -f modules/*_m.cc modules/*_m.h
	-rm -f phyLayer/*_m.cc phyLayer/*_m.h
	-rm -f timers/*_m.cc timers/*_m.h
	-rm -f utils/*_m.cc utils/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc connectionManager/*.cc messages/*.cc modules/*.cc phyLayer/*.cc timers/*.cc utils/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/connectionManager/BaseConnectionManager.o: connectionManager/BaseConnectionManager.cc
$O/connectionManager/ChannelAccess.o: connectionManager/ChannelAccess.cc
$O/connectionManager/ConnectionManager.o: connectionManager/ConnectionManager.cc
$O/connectionManager/NicEntryDirect.o: connectionManager/NicEntryDirect.cc
$O/connectionManager/NicEntryDebug.o: connectionManager/NicEntryDebug.cc
$O/messages/BorderMsg_m.o: messages/BorderMsg_m.cc
$O/messages/MacPkt_m.o: messages/MacPkt_m.cc
$O/messages/ApplPkt_m.o: messages/ApplPkt_m.cc
$O/messages/NetwPkt_m.o: messages/NetwPkt_m.cc
$O/messages/AirFrame_m.o: messages/AirFrame_m.cc
$O/messages/ChannelSenseRequest_m.o: messages/ChannelSenseRequest_m.cc
$O/modules/Blackboard.o: modules/Blackboard.cc
$O/modules/BaseWorldUtility.o: modules/BaseWorldUtility.cc
$O/modules/BaseLayer.o: modules/BaseLayer.cc
$O/modules/BaseModule.o: modules/BaseModule.cc
$O/modules/BaseUtility.o: modules/BaseUtility.cc
$O/modules/BatteryAccess.o: modules/BatteryAccess.cc
$O/modules/BaseNetwLayer.o: modules/BaseNetwLayer.cc
$O/modules/BaseBattery.o: modules/BaseBattery.cc
$O/modules/TestApplLayer.o: modules/TestApplLayer.cc
$O/modules/BaseApplLayer.o: modules/BaseApplLayer.cc
$O/modules/BaseMacLayer.o: modules/BaseMacLayer.cc
$O/modules/BaseArp.o: modules/BaseArp.cc
$O/modules/BaseMobility.o: modules/BaseMobility.cc
$O/phyLayer/ChannelState.o: phyLayer/ChannelState.cc
$O/phyLayer/MappingBase.o: phyLayer/MappingBase.cc
$O/phyLayer/PhyUtils.o: phyLayer/PhyUtils.cc
$O/phyLayer/Signal.o: phyLayer/Signal.cc
$O/phyLayer/ChannelInfo.o: phyLayer/ChannelInfo.cc
$O/phyLayer/Decider.o: phyLayer/Decider.cc
$O/phyLayer/BaseDecider.o: phyLayer/BaseDecider.cc
$O/phyLayer/BasePhyLayer.o: phyLayer/BasePhyLayer.cc
$O/phyLayer/MappingUtils.o: phyLayer/MappingUtils.cc
$O/timers/RepeatTimerCore.o: timers/RepeatTimerCore.cc
$O/timers/RepeatTimer.o: timers/RepeatTimer.cc
$O/timers/TimerCore.o: timers/TimerCore.cc
$O/timers/FrameTimerGenerator.o: timers/FrameTimerGenerator.cc
$O/timers/Timer.o: timers/Timer.cc
$O/timers/FrameTimer.o: timers/FrameTimer.cc
$O/timers/GlobalTime.o: timers/GlobalTime.cc
$O/utils/Coord.o: utils/Coord.cc
$O/utils/winsupport.o: utils/winsupport.cc

