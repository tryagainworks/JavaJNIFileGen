
#ifndef CLSMYSTDLIB_H
#define CLSMYSTDLIB_H
#include <string>
//#include <jni.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <dirent.h>
#include <QDir>
#include <QFile>
#include <QFileInfo>

using namespace std;

#define UNLIMITED_LOOP -1

class clsMySTDLib {
private:

    string fnSplitString(const string& str, const char& chrSplit, vector<string>& vec_result, bool blnTrim, bool blnRemoveEmpty, int intTimes, int intRetrivePosition);
public:
    clsMySTDLib();
    clsMySTDLib(const clsMySTDLib& orig);

    void fnSplitString(const string& str, const char& chrSplit, vector<string>& vec_result, bool blnTrim=false, bool blnRemoveEmpty = false, int intTimes = UNLIMITED_LOOP);

    string fnSplitGetStringAtPos(const string& str, const char& chrSplit, bool blnTrim=false, bool blnRemoveEmpty = false, int intRetrivePosition = UNLIMITED_LOOP);

    int fnSplitGetStringCount(const string& str, const char& chrSplit, bool blnTrim=false, bool blnRemoveEmpty = false);

    void fnSplitTwoWordString(vector<string>& vec_main, vector<string>& vec_result_1, vector<string>& vec_result_2, const char& chrSplit,bool blnTrim=false);

    void fnLtrim(string &strVal);

    void fnRtrim(string &strVal);

    void fnTrim(string &strVal);

    std::string fnGetCurrDateTime();

    virtual ~clsMySTDLib();
    void fnReadDataFromFile(string &strPath,vector<string> &strValue);

    string fnCreateFile(const string &strPath, const string &strExtn, const bool blnAppendDateTime);
    string fnWriteDataToFile(vector<string> &strValue, const string &strPath,  const string &strExtn,  const bool blnAppendDateTime);
    string fnPrepareFileName(const string &strPath, const string &strExtn, const bool blnAppendDateTime);
    void fnGetAllFiles(vector<string> &strValue, const string &strPath);
    void fnUpdateDataToFile(vector<string> &strValue, const string &strPath);
    void fnWriteData(ofstream &fout, vector<string> &strValue);
    string fnGetFileName(const string &strFullPath);
private:

};

#endif /* CLSSTRINGFUNCTIONS_H */

