#pragma once
#include <string>
#include <vector>
#include "stringFunctions.h"
#include "../externals/simpleIni/CSimpleIni.h"

using namespace std;

class parameterManager{
    private:
        static parameterManager* instance;
        parameterManager();
        static char** argv;
        static int argc;
        static string configPath;
        static CSimpleIni configFile;
    public:
        static parameterManager* getInstance();
        static void set(int _argc, char** _argv, string _configPath);
        static string get(string key, string defaultValue);
        static int get(string key, int defaultValue);
};