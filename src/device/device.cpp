#include "device.h"

device::device(string _name, int _port) : sm(_port){
    name = _name;
    port = _port;

    sm.connect();
    sm.getConnection();
}

device::~device(){
    sm.disConnect();
}

string device::getId(){
    return name + "(" + to_string(port) + ")";
}

bool device::write(string msg){
    return sm.write(msg);
}

string device::read(){
    string data = sm.read();
    if(!data.empty()){
        readData.push_back(data);
        write("OK");
    }
    return data;
}

string device::receive(){
    write("GET");
    string data = sm.read();
    if(!data.empty()){
        receivedData.push_back(data);
        write("OK");
    }
    return data;
}

int device::getNrOfReadData(){
    return readData.size();
}

int device::getNrOfReceivedData(){
    return receivedData.size();
}

int device::getNrOfData(){
    return getNrOfReadData() + getNrOfReceivedData();
}

string device::print(string msg){
    return "[" + getId() + "-" 
        + to_string(getNrOfReadData()) + "/" + to_string(getNrOfReceivedData()) 
        + "]" + msg;
}