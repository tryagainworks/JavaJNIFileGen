#ifndef CLSFILENAMEPROPERTIES_H
#define CLSFILENAMEPROPERTIES_H

#include <string>
#include <string>
#include <iostream>
#include <vector>


using namespace std;


class ClsFileSettings
{
private:
    //static ClsFileSettings* obj;
    ClsFileSettings();
public:
    static ClsFileSettings* me();
    string JNI_H_Prefix;
    string JNI_H_Suffix;
    string JNI_CPP_Prefix;
    string JNI_CPP_Suffix;
    string CPP_H_Prefix;
    string CPP_H_Suffix;
    string CPP_CPP_Prefix;
    string CPP_CPP_Suffix;
    string PROFILE_BASE_PATH;
    string GLOBAL_EXTN;
    string JAVAH_PATH;
    vector<string> vecStrResourceHeaderFiles;
    vector<string> vecStrResourceCPPFiles;
    vector<string> vecStrSrcHeaders;
    vector<string> vecStrJniHeaders;
    string JNI_CPP_CONVERTER;
    string MYCLASS;
    string HEADER_FILE_FOLDER;
    string CPP_FILE_FOLDER;

};

#endif // CLSFILENAMEPROPERTIES_H
