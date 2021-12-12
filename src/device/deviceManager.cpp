#include "deviceManager.h"

deviceManager::deviceManager(){};

deviceManager::~deviceManager(){
	for (device* item : devices){
		item->~device();
	}
};

device deviceManager::add(string _name, int _port){
	device newDevice(_name, _port);
	devices.push_back(&newDevice);
	return newDevice;
}

int deviceManager::getNrOfReadData(){
	int sum = 0;
	for (device* item : devices){
		sum += item->getNrOfReadData();
	}
	return sum;
}

int deviceManager::getNrOfReceivedData(){
	int sum = 0;
	for (device* item : devices){
		sum += item->getNrOfReceivedData();
	}
	return sum;
}

int deviceManager::getNrOfData(){
	int sum = 0;
	for (device* item : devices){
		sum += item->getNrOfData();
	}
	return sum;
}

int deviceManager::getNrOfDevices(){
	return devices.size();
}

string deviceManager::print(){
	return to_string(getNrOfDevices());
	// return "[" + to_string(getNrOfReadData()) + "/" + to_string(getNrOfReceivedData()) + "/" + to_string(getNrOfDevices()) + "]";
}