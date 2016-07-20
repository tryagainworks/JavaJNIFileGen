#include "clsfilesettings.h"

ClsFileSettings::ClsFileSettings()
{
    cout << "Single argument constructor called" << endl;
    JNI_H_Prefix="";
    JNI_H_Suffix="_JNI.h";
    JNI_CPP_Prefix="";
    JNI_CPP_Suffix="_JNI.cpp";
    CPP_H_Prefix="";
    CPP_H_Suffix="_CPP.h";
    CPP_CPP_Prefix="";
    CPP_CPP_Suffix="_CPP.cpp";
    PROFILE_BASE_PATH = "/media/linuxmintuser02/Development/MyApps/QTApps_Windows/GitHub/JavaJNIFileGenGitHub/JNIProfiles/";//D:\\JNIProfiles\\";
    GLOBAL_EXTN = "JTC";
    JAVAH_PATH = "/opt/java/64/jdk1.8.0_74/bin/javah";//D:\\Win_8_1\\PgmFls86\\jdk1.8.0_51\\bin\\javah.exe";
    vecStrResourceHeaderFiles.push_back("/media/linuxmintuser02/Development/MyApps/QTApps_Windows/GitHub/JavaJNIFileGenGitHub/Resource/clsCppToJni.h");
    vecStrResourceCPPFiles.push_back("/media/linuxmintuser02/Development/MyApps/QTApps_Windows/GitHub/JavaJNIFileGenGitHub/Resource/clsCppToJni.cpp");
    JNI_CPP_CONVERTER = "clsCppToJni";
    MYCLASS ="myClass";
    HEADER_FILE_FOLDER ="Include";
    CPP_FILE_FOLDER ="Src";
    //vecStrSrcHeaders.push_back();
    vecStrJniHeaders.push_back("../"+HEADER_FILE_FOLDER+"/clsCppToJni.h");
}

ClsFileSettings* ClsFileSettings::me()
{
    static ClsFileSettings objTemp;
    //obj = &objTemp;
    //return obj;
    return &objTemp;
}

//ClsFileSettings* ClsFileSettings::obj=0;
