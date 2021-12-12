#pragma once
#include "device.h"
#include <vector>
#include <string>

using namespace std;

class deviceManager{
    private:
        vector<device> devices;
        int nrOfReadData;
        int nrOfReceivedData;
    public:
        deviceManager();
        ~deviceManager();
        int add(string _name, int _port);
        void incrementReadData();
        void incrementReceivedData();
        int getNrOfReadData();
        int getNrOfReceivedData();
        int getNrOfData();
        int getNrOfDevices();
        device* get(int deviceIndex);
        string print();
};