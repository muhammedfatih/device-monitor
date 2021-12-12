#include "deviceManager.h"

deviceManager::deviceManager(){};

deviceManager::~deviceManager(){};

int deviceManager::add(string _name, int _port){
	int deviceIndex = devices.size();
	device newDevice(_name, _port);
	devices.push_back(newDevice);
	return deviceIndex;
}
void deviceManager::incrementReadData(){
	nrOfReadData++;
}

void deviceManager::incrementReceivedData(){
	nrOfReceivedData++;

}

int deviceManager::getNrOfReadData(){
	return nrOfReadData;
}

int deviceManager::getNrOfReceivedData(){
	return nrOfReceivedData;
}

int deviceManager::getNrOfData(){
	return getNrOfReadData() + getNrOfReceivedData();
}

int deviceManager::getNrOfDevices(){
	return devices.size();
}

device* deviceManager::get(int deviceIndex){
	return &(devices[deviceIndex]);
}

string deviceManager::print(){
	return "Read:" + to_string(getNrOfReadData()) + "/Received:" + to_string(getNrOfReceivedData()) + "/Devices:" + to_string(getNrOfDevices()) + "";
}