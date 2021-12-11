#include "socketManager.h"

socketManager::socketManager(int _port){
    port = _port;
	isConnected = false;
}

bool socketManager::connect(){	
    int opt = 1;
	int addrlen = sizeof(server);
    std::string message;
	char errorBuffer[ 256 ];

    socketDesc = socket(AF_INET, SOCK_STREAM, 0);
    if(socketDesc == -1){
		strerror_r( errno, errorBuffer, 256 );
		perror(errorBuffer);
		return false;
	}

    if(setsockopt(socketDesc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
		strerror_r( errno, errorBuffer, 256 );
		perror(errorBuffer);
		return false;
	}

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;

    if(::bind(socketDesc, (struct sockaddr *)&server, sizeof(server)) < 0){
		strerror_r( errno, errorBuffer, 256 );
		perror(errorBuffer);
		return false;
	}
	
	if(listen(socketDesc, parameterManager::get("socketBacklog", 3)) < 0){
		strerror_r( errno, errorBuffer, 256 );
		perror(errorBuffer);
		return false;
	}
	
	isConnected = true;
    return true;
}

bool socketManager::getConnection(){
	int addrlen = sizeof(server);
	int newSocket = accept(socketDesc, (struct sockaddr *)&server, (socklen_t*)&addrlen);
	if(newSocket>0){
		acceptedSocket = newSocket;
		return true;
	}
	return false;
}

void socketManager::disConnect(){
	close(socketDesc);
	isConnected = false;
}

bool socketManager::hasConnection(){
	return isConnected;
}

std::string socketManager::read(){
	int bytes=1024;
    std::string output(bytes, 0);
	int addrlen = sizeof(server);
	char errorBuffer[ 256 ];

    if (::read(acceptedSocket, &output[0], bytes-1)<0) {
		strerror_r( errno, errorBuffer, 256 );
		perror(errorBuffer);
		return "";
    }
    return output;
}

bool socketManager::write(string message){
	int addrlen = sizeof(server);
	return send(acceptedSocket, message.c_str(), strlen(message.c_str()), 0) != -1;
}

bool socketManager::write(int message){
	return write(to_string(message));
}