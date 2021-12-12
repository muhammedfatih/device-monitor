CXX = g++ -std=c++14

# User can set VERBOSE variable to have all commands echoed to console for 
# debugging purposes.
ifdef VERBOSE
    Q =
else
    Q = @
endif

all: install

install: \
	clean \
	stringFunctions.o \
	parameterManager.o \
	socketManager.o \
	device.o \
	deviceManager.o \
	device-monitor.o
	$Qecho "Generating binary..."
	$Q$(CXX) -o ./bin/device-monitor \
		./obj/device-monitor.o \
		./obj/stringFunctions.o \
		./obj/parameterManager.o \
		./obj/socketManager.o \
		./obj/device.o \
		./obj/deviceManager.o

clean:
	$Qecho "Cleaning binary and object files..."
	$Qrm -rf ./bin
	$Qrm -rf ./obj
	$Qmkdir ./bin
	$Qmkdir ./obj

stringFunctions.o: \
	./src/helpers/stringFunctions.cpp \
	./src/helpers/stringFunctions.h
	$Qecho "Compiling stringFunctions..."
	$Q$(CXX) -c ./src/helpers/stringFunctions.cpp
	$Qmv stringFunctions.o ./obj/stringFunctions.o

parameterManager.o: \
	./src/helpers/parameterManager.cpp \
	./src/helpers/parameterManager.h
	$Qecho "Compiling parameterManager..."
	$Q$(CXX) -c ./src/helpers/parameterManager.cpp
	$Qmv parameterManager.o ./obj/parameterManager.o

socketManager.o: \
	./src/helpers/socketManager.cpp \
	./src/helpers/socketManager.h
	$Qecho "Compiling socketManager..."
	$Q$(CXX) -c ./src/helpers/socketManager.cpp
	$Qmv socketManager.o ./obj/socketManager.o

device.o: \
	./src/device/device.cpp \
	./src/device/device.h
	$Qecho "Compiling device..."
	$Q$(CXX) -c ./src/device/device.cpp
	$Qmv device.o ./obj/device.o

deviceManager.o: \
	./src/device/deviceManager.cpp \
	./src/device/deviceManager.h
	$Qecho "Compiling deviceManager..."
	$Q$(CXX) -c ./src/device/deviceManager.cpp
	$Qmv deviceManager.o ./obj/deviceManager.o

device-monitor.o:
	$Qecho "Compiling device-monitor..."
	$Q$(CXX) -c ./src/main.cpp -o ./obj/device-monitor.o