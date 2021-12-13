# Device Monitor

## 1. Summary

This repository contains three applications. Main application is a server for

device monitoring. Other two applications are client scripts. One of them is a

script that provides message to this server application, and the second application

is a script that questions about statistics from that server.

### 1.1. device-monitor (server)

Device monitor is a server that interacts with clients and user. It 

keeps track of the clients and clients' messages, retriving data from those clients,

and also provide statistics to users instantly. This binary is written in C++ 14.

### 1.2. client(s)

Client script is created for POC purposes. It is a simple client implementation

for this device-monitor server.

### 1.3. stat

Stat script is created for POC purposes. It is simply questioning the instant

statistics from server.

## 2. Installation

Scripts are not requires any spesific installation. Only server application needs

to install.

### 2.1. Pre-requests

- g++ 12.0.5

- python3

### 2.2. Server Installation

To install server application, all you need to do is changing your directory

to repository folder and run the `make` command.

## 3. Usage

### 3.1. device-monitor

If you already run `make` command, you can start server with typing 

`./bin/device-monitor` to terminal.

### 3.2. Configurations

Server application has some configurations. You can run server application directly

with its default values, but if you want to change these values you can either pass

these configurations in running command or in the `config.ini` file.

Possible configurations are:

* listenThreadSleep (default 100ms): sets the sleep time for threads.

* receiveDataFrequency (default 10): sets the frequency for retriving data from 

clients. If the value is 10, it means server asks some sample informations from

clients every 10 iteration.

* serverPort (default 34220): is the port for initial communication for clients.

* portRangeMin (default 34222): is the minimum port continious communication for clients.

* portRangeMax (default 35220): is the maximum port continious communication for clients.

* statPort (default 34221): is the port for fetching statistics.

To change any of these configurations, from command line you can type:

```

./bin/device-monitor --statPort=37220 --serverPort=33220

```

or you can create / modify `config.ini` file. Sample `config.ini` file is as below:

```

[parameters]
serverPort=33220
statPort=37220

```

### 3.2. client

Client application is configurable. You need to pass a device name as argument

while starting its script.

```

python3 client.py device-name-1

```

### 3.3. stat

You can get instant statistics with stat script. To run this script, you can type:

```

python3 stat.py

```

# 4. How it works

## 4.1. Class Diagram

![Class Diagram](images/class-diagram.png?raw=true "Class Diagram")

## 4.2 Flow Chart 

![Flow Chart](images/flow-chart.png?raw=true "Flow Chart")

# 5. External Sources

In the server application, there is a CSimpleIni class. This class is used for

reading configuration ini file.

# 6. Possible Improvements

- Containerization

- Semafor implementation for deviceManager class

- Web frontend

- Persistent logging mechanism

- Better exception handling