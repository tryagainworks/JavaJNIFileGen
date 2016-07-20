#ifndef CLSCREATEHEADERFILE_CPP_H
#define CLSCREATEHEADERFILE_CPP_H
#include "MyLib/clsmystdlib.h"
#include "clsfilesettings.h"

//#include <jni.h>
#include <cstdio>
#include <cstring> //C header file char[]
#include <cstdlib> //C header file
#include <string> //C++ string header file
#include <vector>
#include <iostream>
#include <fstream>
#include "boost/filesystem.hpp"

using namespace std;

class clsFuncDtls {
public:
    vector<string> strFuncReturnType;
    vector<string> strFuncReturnTypeCPP;
    vector<string> strFunctionName;
    vector<vector<string> > strFuncArgDType;
    vector<vector<string> > strFuncArgName;
    vector<vector<string> > strFuncArgDTypeCPP;
};

class clsGenFiles {
private:
    
    clsMySTDLib objMyStrFun;
    
    bool fnGenerageJNIHeaderFile(const string& strCommanLine);

    bool fnGetJniFunctionDetails(const string& strJavaClass, clsFuncDtls& vec_cls_fun, const string& strJNIHeaderFilePath);

    bool fnGetJavaFunctionDetails(clsFuncDtls& vec_java_fun_args, const string& strJNIJavaFilePath);

    bool fnGenJNISrcFile(const clsFuncDtls& vec_Jni_fun_dtls, const clsFuncDtls& vec_java_fun_dtls, const string& strJNISrcFilePath, const string &strJNIHeaderFile, const string &strCPPHFileName);

    bool fnGenCPPHeadFile(const clsFuncDtls& vec_Jni_fun_dtls, const clsFuncDtls& vec_java_fun_dtls, const string& strCPPHeadFilePath);
    
    bool fnGetFunDtlsFromVectorLines(const string& strKeyWordIdentifier, const vector<string>& strWordsToRemove, clsFuncDtls& vec_cls_fun, const vector<string>& vecStrFileContent, bool blnFuncArgWithName);

    bool fnGenCPPSrcFile(const clsFuncDtls &vec_Jni_fun_dtls, const clsFuncDtls &vec_java_fun_dtls, const string &strCPPSrcFilePath, const string &strCPPHeaderFile);

    bool fnRemoveCommentedCode(const string& strFilePath, vector<string> &strFileContent);
public:
    clsGenFiles();
    clsGenFiles(const clsGenFiles& orig);

    bool fnGenFiles
    (const vector<string> strValue);

    bool fnIsFileExist
    (string);

    bool fnOverWriteFile
    (string, string);

    bool fnCopyFileByRenameExisting
    (string, string);

    void fnTest
    ();

    bool fnGenerateJNIHeaderFile(const string&);

    virtual ~clsGenFiles();

};

#endif /* CLSCREATEHEADERFILE_CPP_H */

