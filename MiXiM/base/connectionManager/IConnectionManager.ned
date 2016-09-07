package org.mixim.base.connectionManager;

moduleinterface IConnectionManager
{
    parameters:
        double pMax @unit(mW);
        double sat @unit(dBm);
        double alpha;
        double carrierFrequency @unit(Hz);
}

