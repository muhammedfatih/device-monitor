#include "parameterManager.h"

parameterManager* parameterManager::instance = 0;
int parameterManager::argc = 0;
char** parameterManager::argv = NULL;
string parameterManager::configPath = "";
CSimpleIni parameterManager::configFile;

parameterManager* parameterManager::getInstance()
{
    if (instance == 0)
        instance = new parameterManager();
    return instance;
}

parameterManager::parameterManager(){}

void parameterManager::set(int _argc, char** _argv, string _configPath){
    argc = _argc;
    argv = _argv;
	configPath = get("configPath", _configPath);
	configFile.LoadFile(configPath.c_str());
}

string parameterManager::get(string key, string defaultValue){
	bool isKeyFound = false;
	string returnValue = defaultValue;
	string extendedKey = "--" + key + "=";
	for (int i = 0; i < argc; i++)
	{
		string currentParam = argv[i];
		if (startsWith(currentParam, extendedKey)) {
			returnValue = currentParam;
			replace(returnValue, extendedKey, "");
			isKeyFound = true;
			break;
		}
	}
	return !isKeyFound ? 
		configFile.GetValue("parameters", key.c_str(), defaultValue.c_str()):
		returnValue;
}

int parameterManager::get(string key, int defaultValue){
	bool isKeyFound = false;
	int returnValue = defaultValue;
	string extendedKey = "--" + key + "=";
	for (int i = 0; i < argc; i++)
	{
		string currentParam = argv[i];
		if (startsWith(currentParam, extendedKey)) {
            string tempValue = currentParam;
			replace(tempValue, extendedKey, "");
			try{
            	returnValue = atoi(tempValue.c_str());
				isKeyFound = true;
			}catch(...){
			}
			break;
		}
	}
	return !isKeyFound ? 
		atoi(configFile.GetValue("parameters", key.c_str(), to_string(defaultValue).c_str())):
		returnValue;
}