#pragma once
#include <string>
#include <vector>
#include "../helpers/socketManager.h"

using namespace std;

class device{
    private:
        socketManager sm;
        string name;
        int port;
        vector<string> readData;
        vector<string> receivedData;
    public:
        device(string _name, int _port);
        ~device();
        string getId();
        bool write(string msg);
        string read();
        string receive();
        int getNrOfReadData();
        int getNrOfReceivedData();
        int getNrOfData();
        string print(string msg);
};