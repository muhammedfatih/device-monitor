#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "helpers/parameterManager.h"
#include "helpers/socketManager.h"
#include "device/deviceManager.h"
#include "device/device.h"
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

void threadFunctionDevice(device& connectedDevice){
    int listenThreadSleep = parameterManager::get("listenThreadSleep", 100);
    int recieveDataFrequency = parameterManager::get("recieveDataFrequency", 10);
    int currentIteration = 0;

    do{
        if(currentIteration++ % recieveDataFrequency == 0){
            string receivedMessage = connectedDevice.receive();
            if(!receivedMessage.empty())
                cout << connectedDevice.print(receivedMessage) << endl;
        }

        string clientMessage = connectedDevice.read();
        if(!clientMessage.empty())
                cout << connectedDevice.print(clientMessage) << endl;

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
                    device newDevice = devices.add(newClientName, newClientPort);
                    pid_t pid = fork();
                    if(pid != 0){
                        thread threadDevice(threadFunctionDevice, ref(newDevice));
                        threadDevice.join();
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
    deviceManager devices;

    thread threadListen(threadFunctionListen, ref(devices));
    thread threadStats(threadFunctionStats, ref(devices));
    threadListen.join();
    threadStats.join();

    return 0;
}