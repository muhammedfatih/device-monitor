#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "helpers/parameterManager.h"
#include "helpers/socketManager.h"
#include "device/deviceManager.h"
#include "device/device.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

void threadFunctionDevice(deviceManager& devices, int deviceIndex){
    int listenThreadSleep = parameterManager::get("listenThreadSleep", 100);
    int receiveDataFrequency = parameterManager::get("receiveDataFrequency", 10);
    int currentIteration = 0;
    device* connectedDevice = devices.get(deviceIndex);

    cout << connectedDevice->getId() << "is connected." << endl;
    do{
        if(currentIteration++ % receiveDataFrequency == 0){
            string receivedMessage = connectedDevice->receive();
            if(!receivedMessage.empty()){
                cout << connectedDevice->print(receivedMessage) << endl;
                devices.incrementReceivedData();
            }
        }

        string clientMessage = connectedDevice->read();
        if(!clientMessage.empty()){
            cout << connectedDevice->print(clientMessage) << endl;
            devices.incrementReadData();
        }

        sleep_for(milliseconds(listenThreadSleep));
    }while(true);
}

void threadFunctionListen(deviceManager& devices){
    int serverPort = parameterManager::get("serverPort", 34220);
    int listenThreadSleep = parameterManager::get("listenThreadSleep", 1000);
    int portRangeMin = parameterManager::get("portRangeMin", 34222);
    int portRangeMax = parameterManager::get("portRangeMax", 34320);
    int currentAvailablePort = portRangeMin;

    socketManager sm(serverPort);
    sm.connect();

    cout << "Listening..." << endl;
        do{
        if(sm.getConnection()){
            string newClientName = sm.read();
            if(!newClientName.empty()){
                if(currentAvailablePort > portRangeMax){
                    sm.write(-1);
                    continue;
                }
                if(sm.write(currentAvailablePort)){
                    int newClientPort = currentAvailablePort++;
                    int deviceIndex = devices.add(newClientName, newClientPort);
                    if(deviceIndex != -1){
                        if(fork() != 0){
                            thread threadDevice(
                                threadFunctionDevice,
                                ref (devices),
                                deviceIndex
                            );
                            threadDevice.join();
                        }
                    }else{
                        cout << "Error: client name should be unique." << endl;
                    }
                }
            }
        }
        sleep_for(milliseconds(listenThreadSleep));
    }while(true);
    sm.disConnect();
}

void threadFunctionStats(deviceManager& devices){
    int statPort = parameterManager::get("statPort", 34221);
    int listenThreadSleep = parameterManager::get("listenThreadSleep", 1000);
    socketManager sm(statPort);
    sm.connect();

    cout << "Listening statistic requests..." << endl;
    do{
        if(sm.getConnection()){
            string request = sm.read();
            if(!request.empty()){
                sm.write(devices.print());
                cout << devices.print() << endl; 
            }
        }
        sleep_for(milliseconds(listenThreadSleep));
    }while(true);

    sm.disConnect();
}

int main(int argc, char** argv){
    parameterManager::set(argc, argv, "./config.ini");

    deviceManager* devices;
    devices = (deviceManager*) mmap(NULL, sizeof *devices, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);

    if(fork() == 0){
        thread threadListen(threadFunctionListen, ref(*devices));
        threadListen.join();
    }else{
        thread threadStats(threadFunctionStats, ref(*devices));
        threadStats.join();
    }

    return 0;
}