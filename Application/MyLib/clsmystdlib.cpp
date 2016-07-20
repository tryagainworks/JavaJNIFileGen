
#include "clsmystdlib.h"

clsMySTDLib::clsMySTDLib() {
}

clsMySTDLib::clsMySTDLib(const clsMySTDLib& orig) {
}

clsMySTDLib::~clsMySTDLib() {
}

void clsMySTDLib::fnLtrim(string& strVal) {
    size_t intPosition = 0;
    if ((intPosition = strVal.find_first_not_of(" \n\r\t")) == strVal.npos) {
        strVal = "";
    } else {
        strVal = strVal.substr(strVal.find_first_not_of(" \n\r\t"));
    }
}

void clsMySTDLib::fnRtrim(string& strVal) {
    size_t intPosition = 0;
    if ((intPosition = strVal.find_last_not_of(" \n\r\t")) == strVal.npos) {
        strVal = "";
    } else {
        strVal = strVal.substr(0, strVal.find_last_not_of(" \n\r\t") + 1);
    }
}

void clsMySTDLib::fnTrim(string &strVal) {
    fnLtrim(strVal);
    fnRtrim(strVal);
}

void clsMySTDLib::fnSplitTwoWordString(vector<string>& vec_main, vector<string>& vec_result_1, vector<string>& vec_result_2, const char& chrSplit, bool blnTrim) {
    string strValue;
    size_t intDelimPosition = 0;
    for (vector<string>::iterator irt = vec_main.begin(); irt != vec_main.end(); irt++) {
        strValue = *irt;
        fnTrim(strValue);
        intDelimPosition = strValue.find(chrSplit);
        
        strValue = strValue.substr(0, intDelimPosition);
        if (blnTrim) {
            fnTrim(strValue);
        }
        vec_result_1.push_back(strValue);

        strValue = *irt;
        
        strValue = strValue.substr(intDelimPosition);
        if (blnTrim) {
            fnTrim(strValue);
        }
        vec_result_2.push_back(strValue);
    }
}

void clsMySTDLib::fnSplitString(const string& str, const char& chrSplit, vector<string>& vec_result, bool blnTrim, bool blnRemoveEmpty, int intNoOfStrNeed) {
    fnSplitString(str, chrSplit, vec_result, blnTrim, blnRemoveEmpty, intNoOfStrNeed, UNLIMITED_LOOP);
    
}

string clsMySTDLib::fnSplitString(const string& str, const char& chrSplit, vector<string>& vec_result, bool blnTrim, bool blnRemoveEmpty, int intNoOfStrNeed, int intNthStr) {
    int intStart = 0;
    int intFound = 0;
    int intLoopedTimes = 0;
    string strValue;
    intFound = str.find(chrSplit, intStart);
    while ((intNoOfStrNeed == UNLIMITED_LOOP ? intLoopedTimes : intNoOfStrNeed) <= intLoopedTimes) {
        intLoopedTimes++;
        strValue = str.substr(intStart, (intFound - intStart));
        if (blnTrim) {
            fnTrim(strValue);
        }
        if (!blnRemoveEmpty || strValue.find_first_not_of(' ', 0) != strValue.npos) {
            if (intNthStr == UNLIMITED_LOOP) {
                vec_result.push_back(strValue);
            } else if (intNthStr == intLoopedTimes) {
                return strValue;
            }
        }
        if (intFound == str.npos) {
            break;
        }
        intStart = intFound + 1;
        intFound = str.find(chrSplit, intStart);
    }
}

string clsMySTDLib::fnSplitGetStringAtPos(const string& str, const char& chrSplit, bool blnTrim, bool blnRemoveEmpty, int intRetrivePosition) {
    vector<string> vec_result;
    return fnSplitString(str, chrSplit, vec_result, blnTrim, blnRemoveEmpty, UNLIMITED_LOOP, intRetrivePosition);
}

int clsMySTDLib::fnSplitGetStringCount(const string& str, const char& chrSplit, bool blnTrim, bool blnRemoveEmpty) {
    vector<string> vec_result;
    fnSplitString(str, chrSplit, vec_result, blnTrim, blnRemoveEmpty, UNLIMITED_LOOP, UNLIMITED_LOOP);
    return vec_result.size();
}

std::string clsMySTDLib::fnGetCurrDateTime(){
    std::string strCurTime;
    time_t t = time(0);
    char* chrTime = new char[50];
    struct tm* toLocalTime = localtime(&t);
    sprintf(chrTime,"%d_%d_%d_%d_%d_%d",toLocalTime->tm_mday,(toLocalTime->tm_mon)+1,(toLocalTime->tm_year)+1900,(toLocalTime->tm_hour)+1,(toLocalTime->tm_min)+1,(toLocalTime->tm_sec)+1);
    strCurTime.append(chrTime);
    delete[] chrTime;
    return strCurTime;
}

string clsMySTDLib::fnGetFileName(const string &strFullPath){
    string strFileName = strFullPath.substr(strFullPath.find_last_of("\\/")+1);
    return strFileName;
}

string clsMySTDLib::fnWriteDataToFile(vector<string> &strValue, const string &strPath, const string &strExtn, const bool blnAppendDateTime){
    ofstream fout;
    string strFileName=fnPrepareFileName(strPath,strExtn,blnAppendDateTime);
    fout.open(strFileName,ios::trunc);
    fnWriteData(fout,strValue);
    return fnGetFileName(strFileName);
}

void clsMySTDLib::fnWriteData(ofstream &fout, vector<string> &strValue){
    for(vector<string>::iterator itr = strValue.begin();itr!=strValue.end();itr++){
        fout << *itr << endl;
    }
    fout.close();
}

void clsMySTDLib::fnUpdateDataToFile(vector<string> &strValue, const string &strPath){
    ofstream fout;
    fout.open(strPath,ios::trunc);
    fnWriteData(fout,strValue);
}

void clsMySTDLib::fnReadDataFromFile(string &strPath,vector<string> &strValue){
    string str;
    ifstream fin;
    fin.open(strPath);
    while(getline(fin,str)){
        fnTrim(str);
        strValue.push_back(str);
    }
    fin.close();
}

string clsMySTDLib::fnPrepareFileName(const string &strPath,const string &strExtn, const bool blnAppendDateTime){
    string strVal = strPath;
    if(blnAppendDateTime){
        strVal.append("_");
        strVal.append(fnGetCurrDateTime());
    }
    strVal.append(".");
    strVal.append(strExtn);
    return strVal;
}

string clsMySTDLib::fnCreateFile(const string &strPath,const string &strExtn, const bool blnAppendDateTime){
    ofstream fout;
    string strFileName=fnPrepareFileName(strPath,strExtn,blnAppendDateTime);
    fout.open(strFileName,ios::trunc);
    fout.close();
    return fnGetFileName(strFileName);
}

void clsMySTDLib::fnGetAllFiles(vector<string> &strValue, const string &strPath){
    /*DIR *strDir;
    string strFile;
    strDir = opendir(strPath.c_str());
    strValue.clear();
    while(readdir(strDir)!=NULL){
        strFile = strDir->dd_dta.name;
        if(!(strFile=="." || strFile=="..")){
            strValue.push_back(strDir->dd_dta.name);
        }
    }*/
    QDir dir(QString::fromStdString(strPath));
    QStringList strLst= dir.entryList(QStringList("*.jTC"));
    for(QString str : strLst){
        strValue.push_back(str.toStdString());
    }
}
