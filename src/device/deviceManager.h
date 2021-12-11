#pragma once
#include "device.h"
#include <vector>
#include <string>

using namespace std;

class deviceManager{
    private:
        vector<device*> devices;
    public:
        deviceManager();
        ~deviceManager();
        device add(string _name, int _port);
        int getNrOfReadData();
        int getNrOfReceivedData();
        int getNrOfData();
        string print();
};