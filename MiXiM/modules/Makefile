#
# OMNeT++/OMNEST Makefile for libmiximmodules
#
# This file was generated with the command:
#  opp_makemake -f --deep --make-so -o miximmodules -O out -L../../out/$(CONFIGNAME)/MiXiM/base -lmiximbase
#

# Name of target to be created (-o option)
TARGET = libmiximmodules$(SHARED_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -IanalogueModel \
    -Iapplication \
    -IconnectionManager \
    -Imac \
    -Imessages \
    -Imobility \
    -Inetw \
    -Inic \
    -Inode \
    -Iphy \
    -Ipower \
    -Ipower/battery \
    -Itransport \
    -Iutility

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../out/$(CONFIGNAME)/MiXiM/base  -lmiximbase
LIBS += -Wl,-rpath,`abspath ../../out/$(CONFIGNAME)/MiXiM/base`

# Output directory
PROJECT_OUTPUT_DIR = ../../out
PROJECTRELATIVE_PATH = MiXiM/modules
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/analogueModel/LogNormalShadowing.o \
    $O/analogueModel/UWBIRIEEE802154APathlossModel.o \
    $O/analogueModel/JakesFading.o \
    $O/analogueModel/UWBIRStochasticPathlossModel.o \
    $O/analogueModel/SimplePathlossModel.o \
    $O/application/BurstApplLayer.o \
    $O/application/TestApplication.o \
    $O/application/SensorApplLayer.o \
    $O/application/BurstApplLayerBattery.o \
    $O/application/TrafficGen.o \
    $O/connectionManager/UnitDisk.o \
    $O/mac/UWBIRMac.o \
    $O/mac/CSMAMacLayer.o \
    $O/mac/Mac80211.o \
    $O/mac/AlohaMacLayer.o \
    $O/mac/csma.o \
    $O/mac/CSMA802154.o \
    $O/messages/AggrPkt.o \
    $O/messages/UWBIRMacPkt.o \
    $O/mobility/RectangleMobility.o \
    $O/mobility/CircleMobility.o \
    $O/mobility/TurtleMobility.o \
    $O/mobility/LineSegmentsMobilityBase.o \
    $O/mobility/TractorMobility.o \
    $O/mobility/ConstSpeedMobility.o \
    $O/mobility/ANSimMobility.o \
    $O/mobility/BonnMotionFileCache.o \
    $O/mobility/BonnMotionMobility.o \
    $O/mobility/MassMobility.o \
    $O/mobility/LinearMobility.o \
    $O/netw/DummyRoute.o \
    $O/netw/ArpHost.o \
    $O/phy/Decider80211Battery.o \
    $O/phy/Decider80211.o \
    $O/phy/PhyLayerUWBIR.o \
    $O/phy/SNRThresholdDecider.o \
    $O/phy/DeciderUWBIREDSyncOnAddress.o \
    $O/phy/DeciderUWBIRED.o \
    $O/phy/Decider802154Narrow.o \
    $O/phy/PhyLayerBattery.o \
    $O/phy/DeciderUWBIREDSync.o \
    $O/phy/PhyLayer.o \
    $O/power/battery/SimpleBattery.o \
    $O/power/battery/BatteryStats.o \
    $O/transport/Aggregation.o \
    $O/utility/phyPER.o \
    $O/utility/IEEE802154A.o \
    $O/utility/SimTracer.o \
    $O/messages/AggrPkt_m.o \
    $O/messages/UWBIRMacPkt_m.o \
    $O/messages/DummyRoutePkt_m.o \
    $O/messages/Mac80211Pkt_m.o \
    $O/messages/AirFrameUWBIR_m.o

# Message files
MSGFILES = \
    messages/AggrPkt.msg \
    messages/UWBIRMacPkt.msg \
    messages/DummyRoutePkt.msg \
    messages/Mac80211Pkt.msg \
    messages/AirFrameUWBIR.msg

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

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppenvir$D $(KERNEL_LIBS) $(SYS_LIBS)

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
	$(SHLIB_LD) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(LIBS) $(OMNETPP_LIBS) $(LDFLAGS)
	$(SHLIB_POSTPROCESS) $O/$(TARGET)

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
	-rm -f miximmodules miximmodules.exe libmiximmodules.so libmiximmodules.a libmiximmodules.dll libmiximmodules.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f analogueModel/*_m.cc analogueModel/*_m.h
	-rm -f application/*_m.cc application/*_m.h
	-rm -f connectionManager/*_m.cc connectionManager/*_m.h
	-rm -f mac/*_m.cc mac/*_m.h
	-rm -f messages/*_m.cc messages/*_m.h
	-rm -f mobility/*_m.cc mobility/*_m.h
	-rm -f netw/*_m.cc netw/*_m.h
	-rm -f nic/*_m.cc nic/*_m.h
	-rm -f node/*_m.cc node/*_m.h
	-rm -f phy/*_m.cc phy/*_m.h
	-rm -f power/*_m.cc power/*_m.h
	-rm -f power/battery/*_m.cc power/battery/*_m.h
	-rm -f transport/*_m.cc transport/*_m.h
	-rm -f utility/*_m.cc utility/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc analogueModel/*.cc application/*.cc connectionManager/*.cc mac/*.cc messages/*.cc mobility/*.cc netw/*.cc nic/*.cc node/*.cc phy/*.cc power/*.cc power/battery/*.cc transport/*.cc utility/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/analogueModel/LogNormalShadowing.o: analogueModel/LogNormalShadowing.cc \
	analogueModel/LogNormalShadowing.h
$O/analogueModel/UWBIRIEEE802154APathlossModel.o: analogueModel/UWBIRIEEE802154APathlossModel.cc \
	utility/SimpleTimeConstMapping.h \
	utility/IEEE802154A.h \
	analogueModel/UWBIRIEEE802154APathlossModel.h
$O/analogueModel/SimplePathlossModel.o: analogueModel/SimplePathlossModel.cc \
	analogueModel/SimplePathlossModel.h
$O/analogueModel/JakesFading.o: analogueModel/JakesFading.cc \
	analogueModel/JakesFading.h
$O/analogueModel/UWBIRStochasticPathlossModel.o: analogueModel/UWBIRStochasticPathlossModel.cc \
	analogueModel/UWBIRStochasticPathlossModel.h
$O/application/TrafficGen.o: application/TrafficGen.cc \
	application/TrafficGen.h \
	utility/Packet.h
$O/application/TestApplication.o: application/TestApplication.cc \
	application/TestApplication.h \
	messages/UWBIRMacPkt_m.h \
	phy/RadioUWBIR.h \
	mac/UWBIRMac.h \
	utility/SimpleTimeConstMapping.h \
	mac/AlohaMacLayer.h \
	phy/DeciderResultUWBIR.h \
	utility/IEEE802154A.h \
	utility/Packet.h \
	messages/UWBIRMacPkt.h \
	analogueModel/UWBIRIEEE802154APathlossModel.h
$O/application/BurstApplLayer.o: application/BurstApplLayer.cc \
	application/BurstApplLayer.h
$O/application/BurstApplLayerBattery.o: application/BurstApplLayerBattery.cc \
	application/BurstApplLayer.h \
	application/BurstApplLayerBattery.h
$O/application/SensorApplLayer.o: application/SensorApplLayer.cc \
	application/SensorApplLayer.h \
	utility/Packet.h
$O/connectionManager/UnitDisk.o: connectionManager/UnitDisk.cc \
	connectionManager/UnitDisk.h
$O/mac/csma.o: mac/csma.cc \
	mac/csma.h \
	utility/DroppedPacket.h \
	phy/DeciderResult802154Narrow.h
$O/mac/CSMA802154.o: mac/CSMA802154.cc \
	mac/CSMA802154.h \
	mac/csma.h \
	utility/DroppedPacket.h \
	phy/DeciderResult802154Narrow.h
$O/mac/UWBIRMac.o: mac/UWBIRMac.cc \
	messages/UWBIRMacPkt_m.h \
	phy/RadioUWBIR.h \
	mac/UWBIRMac.h \
	utility/SimpleTimeConstMapping.h \
	phy/DeciderResultUWBIR.h \
	utility/IEEE802154A.h \
	utility/Packet.h \
	messages/UWBIRMacPkt.h \
	analogueModel/UWBIRIEEE802154APathlossModel.h \
	phy/MacToUWBIRPhyControlInfo.h
$O/mac/CSMAMacLayer.o: mac/CSMAMacLayer.cc \
	mac/CSMAMacLayer.h
$O/mac/Mac80211.o: mac/Mac80211.cc \
	phy/DeciderResult80211.h \
	messages/Mac80211Pkt_m.h \
	mac/Mac80211.h \
	utility/Consts80211.h \
	phy/Decider80211.h
$O/mac/AlohaMacLayer.o: mac/AlohaMacLayer.cc \
	mac/UWBIRMac.h \
	phy/RadioUWBIR.h \
	messages/UWBIRMacPkt_m.h \
	utility/SimpleTimeConstMapping.h \
	mac/AlohaMacLayer.h \
	phy/DeciderResultUWBIR.h \
	utility/Packet.h \
	utility/IEEE802154A.h \
	messages/UWBIRMacPkt.h \
	analogueModel/UWBIRIEEE802154APathlossModel.h
$O/messages/DummyRoutePkt_m.o: messages/DummyRoutePkt_m.cc \
	messages/DummyRoutePkt_m.h
$O/messages/Mac80211Pkt_m.o: messages/Mac80211Pkt_m.cc \
	messages/Mac80211Pkt_m.h
$O/messages/UWBIRMacPkt.o: messages/UWBIRMacPkt.cc \
	messages/UWBIRMacPkt_m.h \
	messages/UWBIRMacPkt.h
$O/messages/AggrPkt_m.o: messages/AggrPkt_m.cc \
	messages/AggrPkt_m.h
$O/messages/UWBIRMacPkt_m.o: messages/UWBIRMacPkt_m.cc \
	messages/UWBIRMacPkt_m.h
$O/messages/AggrPkt.o: messages/AggrPkt.cc \
	messages/AggrPkt_m.h \
	messages/AggrPkt.h
$O/messages/AirFrameUWBIR_m.o: messages/AirFrameUWBIR_m.cc \
	messages/AirFrameUWBIR_m.h \
	utility/IEEE802154A.h
$O/mobility/MassMobility.o: mobility/MassMobility.cc \
	mobility/MassMobility.h
$O/mobility/TractorMobility.o: mobility/TractorMobility.cc \
	mobility/TractorMobility.h
$O/mobility/ANSimMobility.o: mobility/ANSimMobility.cc \
	mobility/LineSegmentsMobilityBase.h \
	mobility/ANSimMobility.h
$O/mobility/ConstSpeedMobility.o: mobility/ConstSpeedMobility.cc \
	mobility/ConstSpeedMobility.h
$O/mobility/RectangleMobility.o: mobility/RectangleMobility.cc \
	mobility/RectangleMobility.h
$O/mobility/BonnMotionFileCache.o: mobility/BonnMotionFileCache.cc \
	mobility/BonnMotionFileCache.h
$O/mobility/CircleMobility.o: mobility/CircleMobility.cc \
	mobility/CircleMobility.h
$O/mobility/BonnMotionMobility.o: mobility/BonnMotionMobility.cc \
	mobility/LineSegmentsMobilityBase.h \
	mobility/BonnMotionFileCache.h \
	mobility/BonnMotionMobility.h
$O/mobility/LinearMobility.o: mobility/LinearMobility.cc \
	mobility/LinearMobility.h
$O/mobility/TurtleMobility.o: mobility/TurtleMobility.cc \
	mobility/LineSegmentsMobilityBase.h \
	mobility/TurtleMobility.h
$O/mobility/LineSegmentsMobilityBase.o: mobility/LineSegmentsMobilityBase.cc \
	mobility/LineSegmentsMobilityBase.h
$O/netw/ArpHost.o: netw/ArpHost.cc \
	netw/ArpHost.h
$O/netw/DummyRoute.o: netw/DummyRoute.cc \
	utility/Packet.h \
	messages/DummyRoutePkt_m.h \
	utility/SimTracer.h \
	netw/DummyRoute.h
$O/phy/SNRThresholdDecider.o: phy/SNRThresholdDecider.cc \
	phy/SNRThresholdDecider.h
$O/phy/Decider802154Narrow.o: phy/Decider802154Narrow.cc \
	utility/Consts802154.h \
	phy/Decider802154Narrow.h \
	phy/DeciderResult802154Narrow.h
$O/phy/Decider80211Battery.o: phy/Decider80211Battery.cc \
	phy/Decider80211.h \
	utility/Consts80211.h \
	phy/Decider80211Battery.h
$O/phy/PhyLayer.o: phy/PhyLayer.cc \
	analogueModel/LogNormalShadowing.h \
	analogueModel/SimplePathlossModel.h \
	phy/PhyLayer.h \
	analogueModel/JakesFading.h \
	utility/Consts80211.h \
	phy/Decider802154Narrow.h \
	phy/Decider80211.h \
	phy/SNRThresholdDecider.h
$O/phy/PhyLayerUWBIR.o: phy/PhyLayerUWBIR.cc \
	messages/AirFrameUWBIR_m.h \
	phy/RadioUWBIR.h \
	utility/SimpleTimeConstMapping.h \
	phy/DeciderUWBIRED.h \
	utility/Consts80211.h \
	phy/Decider80211.h \
	utility/UWBIRPacket.h \
	analogueModel/UWBIRStochasticPathlossModel.h \
	messages/UWBIRMacPkt_m.h \
	mac/UWBIRMac.h \
	phy/DeciderUWBIREDSyncOnAddress.h \
	mac/AlohaMacLayer.h \
	phy/PhyLayerBattery.h \
	phy/PhyLayer.h \
	phy/DeciderResultUWBIR.h \
	utility/Packet.h \
	utility/IEEE802154A.h \
	messages/UWBIRMacPkt.h \
	phy/DeciderUWBIREDSync.h \
	phy/Decider80211Battery.h \
	phy/PhyLayerUWBIR.h \
	analogueModel/UWBIRIEEE802154APathlossModel.h \
	phy/MacToUWBIRPhyControlInfo.h
$O/phy/Decider80211.o: phy/Decider80211.cc \
	phy/DeciderResult80211.h \
	messages/Mac80211Pkt_m.h \
	utility/Consts80211.h \
	phy/Decider80211.h
$O/phy/DeciderUWBIREDSyncOnAddress.o: phy/DeciderUWBIREDSyncOnAddress.cc \
	phy/RadioUWBIR.h \
	utility/SimpleTimeConstMapping.h \
	phy/DeciderUWBIRED.h \
	utility/UWBIRPacket.h \
	messages/UWBIRMacPkt_m.h \
	mac/UWBIRMac.h \
	phy/DeciderUWBIREDSyncOnAddress.h \
	mac/AlohaMacLayer.h \
	phy/DeciderResultUWBIR.h \
	utility/IEEE802154A.h \
	utility/Packet.h \
	messages/UWBIRMacPkt.h \
	analogueModel/UWBIRIEEE802154APathlossModel.h
$O/phy/PhyLayerBattery.o: phy/PhyLayerBattery.cc \
	phy/PhyLayerBattery.h \
	phy/PhyLayer.h \
	utility/Consts80211.h \
	phy/Decider80211.h \
	phy/Decider80211Battery.h
$O/phy/DeciderUWBIRED.o: phy/DeciderUWBIRED.cc \
	messages/AirFrameUWBIR_m.h \
	phy/RadioUWBIR.h \
	utility/SimpleTimeConstMapping.h \
	phy/DeciderUWBIRED.h \
	utility/Consts80211.h \
	phy/Decider80211.h \
	utility/UWBIRPacket.h \
	analogueModel/UWBIRStochasticPathlossModel.h \
	mac/UWBIRMac.h \
	messages/UWBIRMacPkt_m.h \
	phy/DeciderUWBIREDSyncOnAddress.h \
	mac/AlohaMacLayer.h \
	phy/PhyLayerBattery.h \
	phy/PhyLayer.h \
	phy/DeciderResultUWBIR.h \
	utility/IEEE802154A.h \
	utility/Packet.h \
	phy/DeciderUWBIREDSync.h \
	messages/UWBIRMacPkt.h \
	phy/Decider80211Battery.h \
	phy/PhyLayerUWBIR.h \
	analogueModel/UWBIRIEEE802154APathlossModel.h
$O/phy/DeciderUWBIREDSync.o: phy/DeciderUWBIREDSync.cc \
	phy/RadioUWBIR.h \
	utility/SimpleTimeConstMapping.h \
	phy/DeciderUWBIRED.h \
	utility/UWBIRPacket.h \
	messages/UWBIRMacPkt_m.h \
	mac/UWBIRMac.h \
	mac/AlohaMacLayer.h \
	phy/DeciderResultUWBIR.h \
	utility/IEEE802154A.h \
	utility/Packet.h \
	phy/DeciderUWBIREDSync.h \
	messages/UWBIRMacPkt.h \
	analogueModel/UWBIRIEEE802154APathlossModel.h
$O/power/battery/BatteryStats.o: power/battery/BatteryStats.cc \
	power/battery/SimpleBattery.h \
	power/battery/BatteryStats.h \
	power/battery/DeviceEntry.h \
	power/battery/BatteryState.h
$O/power/battery/SimpleBattery.o: power/battery/SimpleBattery.cc \
	power/battery/BatteryStats.h \
	power/battery/SimpleBattery.h \
	power/battery/DeviceEntry.h \
	power/battery/BatteryState.h
$O/transport/Aggregation.o: transport/Aggregation.cc \
	messages/AggrPkt_m.h \
	transport/Aggregation.h \
	messages/AggrPkt.h
$O/utility/IEEE802154A.o: utility/IEEE802154A.cc \
	utility/IEEE802154A.h
$O/utility/phyPER.o: utility/phyPER.cc \
	utility/phyPER.h \
	utility/Packet.h \
	utility/UWBIRPacket.h
$O/utility/SimTracer.o: utility/SimTracer.cc \
	utility/Packet.h \
	utility/SimTracer.h

