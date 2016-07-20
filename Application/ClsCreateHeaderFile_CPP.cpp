#include "MyLib/clsmystdlib.h"




#include "ClsCreateHeaderFile_CPP.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <qdebug.h>

clsGenFiles::clsGenFiles()
{
}

clsGenFiles::~clsGenFiles()
{
}

bool clsGenFiles::fnGenerageJNIHeaderFile(const string& strCmdLine)
{
	cout << strCmdLine << "\n";
	qDebug()<<strCmdLine.c_str();

	try
	{
		system(strCmdLine.c_str());
		return true;
	}
	catch (int e)
	{
		printf("Error when executing the strCommandLine. Error number = %d\n", e);
	}
}

bool clsGenFiles::fnRemoveCommentedCode(const string& strFilePath, vector<string> &vecStrFileContent)
{

	ifstream fin;
	string strFileLine;

	char c,d;
	//escape flag
	bool DOUBLESLASH_Comment = 0, ASTERISK_SLASH_Comment = 0, flag = 0;

#define NOT_COMMENT (!DOUBLESLASH_Comment && !ASTERISK_SLASH_Comment)

	fin.open(strFilePath.c_str());

	/* single quotes / double quotes */
	int s_QUOTED = 0, d_QUOTED = 0;

	while (fin.get(c))
	{
		switch (c)
		{
		case '\\':
		{
			if (NOT_COMMENT)
			{
				if (flag == 1)
					flag = 0;
				else
					flag = 1;
			}
		}
		break;

		case '\'':
		{
			if (NOT_COMMENT && !d_QUOTED)
			{
				if (!flag)
				{
					s_QUOTED++;
				}
			}
		}
		break;

		case '"':
		{
			if (NOT_COMMENT && !flag)
			{
				if (!s_QUOTED)
				{
					d_QUOTED++;
				}
			}
		}
		break;

		case '/':
		{
			if (NOT_COMMENT && !d_QUOTED)
			{
				fin.get(d);
				if (d == '*')
				{
					ASTERISK_SLASH_Comment = 1;
				}
				else if (d == '/')
				{
					DOUBLESLASH_Comment = 1;
				}
				else
				{
					if (!fin.eof())
					{
						fin.unget();
						//ungetc(d, input);
					}
				}
			}
		}
		break;

		case '*':
		{
			if (ASTERISK_SLASH_Comment)
			{
				fin.get(d);
				if (d == '/')
				{
					fin.get(c);
					if (fin.eof())
						return 0;

					ASTERISK_SLASH_Comment = 0;
				}
				else
				{
					fin.get(d);
					if (!fin.eof())
					{
						fin.unget();
						//ungetc(d, input);
					}
				}
			}
		}
		break;

		case '\n':
		{
			if (DOUBLESLASH_Comment)
			{
				DOUBLESLASH_Comment = 0;
			}
		}
		break;
		}

		if (NOT_COMMENT && c != '\\') flag = 0;
		if (d_QUOTED == 2) d_QUOTED = 0;
		if (s_QUOTED == 2) s_QUOTED = 0;

		if (NOT_COMMENT)
		{
			if(c!='\n')
				strFileLine+=c;
			else
			{
				if(strFileLine.length()>0)
				{
					vecStrFileContent.push_back(strFileLine);
					strFileLine.clear();
				}
			}
		}
	}
	fin.close();
	return true;
}

bool clsGenFiles::fnGetFunDtlsFromVectorLines(const string& strKeyWordIdentifier, const vector<string>& strWordsToRemove, clsFuncDtls& vec_all_fun_dtls, const vector<string>& vecStrFileContent, bool blnFuncArgWithName)
{
	string strLine;
	string strFullFunction;
	//ifstream fin;
	vector<string> strVecArgName, strVecArgType;
	vector<string> strVecMainResult;

	//cout << "File name  = " << strFilePath << endl;
	//fin.open(strFilePath.c_str());
	//Read line by line
	//while (getline(fin, strLine)) {
	for(int iCount=0; iCount<vecStrFileContent.size(); iCount++)
	{
		strLine = vecStrFileContent.at(iCount);
		//search for native or jniexport
		if (strLine.find(strKeyWordIdentifier) != strLine.npos)
		{
			strFullFunction.assign(strLine);
			//append the string till the ; reached
			while (strLine.find(";") == strLine.npos)
			{
				strLine = vecStrFileContent.at(++iCount);
				//getline(fin, strLine);
				strFullFunction.append(strLine);
			}
			//remove unwanted words
			//unsigned int intStartPos = 0;
			size_t intStartPos = 0,intEndPos=0;

			//Doing both ltrim and rtrim
			objMyStrFun.fnTrim(strFullFunction);

			//select each unwanted words to remove
			/*
			for (unsigned int i = 0; i < strWordsToRemove.size(); i++) {
			    intStartPos = strFullFunction.find(strWordsToRemove[i]);
			    if (intStartPos != strWordsToRemove[i].npos) {
			        strFullFunction.replace(intStartPos, strWordsToRemove[i].length(), " ");
			    }
			}
			*/
			for (unsigned int i = 0; i < strWordsToRemove.size(); i++)
			{
				intStartPos = strFullFunction.find(strWordsToRemove.at(i));
				if (intStartPos != strFullFunction.npos)
				{
					strFullFunction.replace(intStartPos, strWordsToRemove.at(i).length(), " ");
				}
			}
			//find the function arg begin pos
			intStartPos = strFullFunction.find("(");
			//split the words before function args begin
			strVecMainResult.clear();
			objMyStrFun.fnSplitString(strFullFunction.substr(0, intStartPos), ' ', strVecMainResult, true, true);

			//return type
			vec_all_fun_dtls.strFuncReturnType.push_back(strVecMainResult[0]);

			//function name added
			//obj.strFunctionName.push_back(objMyStrFun.fnSplitGetStringAtPos(strVecMainResult[1], '_', true, false, intFuncWordPos));
			vec_all_fun_dtls.strFunctionName.push_back(strVecMainResult[1]);

			//remove the open and close bracket
			strLine = strFullFunction.substr(intStartPos);
			intStartPos = strLine.find_first_of("(");
			intEndPos = strLine.find_last_of(")");

			strLine.assign(strLine.substr(intStartPos+1, intEndPos - intStartPos-1));

			strVecMainResult.clear();
			//split the args
			objMyStrFun.fnSplitString(strLine, ',', strVecMainResult, true, true);

			if (!blnFuncArgWithName)
			{
				vec_all_fun_dtls.strFuncArgDType.push_back(strVecMainResult);
			}
			else
			{
				strVecArgName.clear();
				strVecArgType.clear();
				objMyStrFun.fnSplitTwoWordString(strVecMainResult, strVecArgType, strVecArgName, ' ', true);
				vec_all_fun_dtls.strFuncArgDType.push_back(strVecArgType);
				vec_all_fun_dtls.strFuncArgName.push_back(strVecArgName);
			}
			strVecMainResult.clear();
		}
	}

	//fin.close();
	return true;
}

bool clsGenFiles::fnGetJniFunctionDetails(const string& strJavaClass, clsFuncDtls& vec_jni_fun_dtls, const string& strJNIHeaderFilePath)
{
	//(package workd + class word)+ jniexport+jnicall
	vector<string> vs;
	vs.push_back("JNIEXPORT");
	vs.push_back(" JNICALL ");
	vector<string> vecStrFileContent;

	fnRemoveCommentedCode(strJNIHeaderFilePath, vecStrFileContent);

	return fnGetFunDtlsFromVectorLines("JNIEXPORT", vs, vec_jni_fun_dtls, vecStrFileContent, false);
}

bool clsGenFiles::fnGetJavaFunctionDetails(clsFuncDtls& vec_java_fun_dtls, const string & strJNIJavaFilePath)
{
	vector<string> vs;
	vs.push_back("public ");
	vs.push_back("private ");
	vs.push_back("protected ");
	vs.push_back("native ");
	vector<string> vecStrFileContent;

	fnRemoveCommentedCode(strJNIJavaFilePath, vecStrFileContent);

	fnGetFunDtlsFromVectorLines(" native ", vs, vec_java_fun_dtls, vecStrFileContent, true);

	vector<string> vec_str_cpp_dtype;

	for (vector<vector<string> >::iterator itrMain = vec_java_fun_dtls.strFuncArgDType.begin(); itrMain != vec_java_fun_dtls.strFuncArgDType.end(); itrMain++)
	{
		for (vector<string>::iterator itrSub = (*itrMain).begin(); itrSub != (*itrMain).end(); itrSub++)
		{
			if (*itrSub == "String")
			{
				vec_str_cpp_dtype.push_back("string");
			}
			else if (*itrSub == "int")
			{
				vec_str_cpp_dtype.push_back("int");
			}
			else if (*itrSub == "float")
			{
				vec_str_cpp_dtype.push_back("float");
			}
			else if (*itrSub == "boolean")
			{
				vec_str_cpp_dtype.push_back("bool");
			}
			else
			{
				vec_str_cpp_dtype.push_back(*itrSub);
			}
		}
		vec_java_fun_dtls.strFuncArgDTypeCPP.push_back(vec_str_cpp_dtype);
		vec_str_cpp_dtype.clear();
	}

	for (vector<string>::iterator itrSub = vec_java_fun_dtls.strFuncReturnType.begin(); itrSub != vec_java_fun_dtls.strFuncReturnType.end(); itrSub++)
	{
		if (*itrSub == "String")
		{
			vec_java_fun_dtls.strFuncReturnTypeCPP.push_back("string");
		}
		else if (*itrSub == "int")
		{
			vec_java_fun_dtls.strFuncReturnTypeCPP.push_back("int");
		}
		else if (*itrSub == "float")
		{
			vec_java_fun_dtls.strFuncReturnTypeCPP.push_back("float");
		}
		else if (*itrSub == "boolean")
		{
			vec_java_fun_dtls.strFuncReturnTypeCPP.push_back("bool");
		}
		else
		{
			vec_java_fun_dtls.strFuncReturnTypeCPP.push_back(*itrSub);
		}
	}

	return true;
}

bool clsGenFiles::fnGenJNISrcFile(const clsFuncDtls& vec_Jni_fun_dtls, const clsFuncDtls& vec_java_fun_dtls, const string& strJNISrcFilePath, const string& strJNIHeaderFile, const string &strCPPHFileName)
{
	ofstream fout;

    boost::filesystem::path rootPath (strJNISrcFilePath);

    boost::filesystem::path srcFolder= rootPath.parent_path();

    if(!boost::filesystem::exists(srcFolder)){
        boost::filesystem::create_directories(srcFolder);
    }

    fout.open(strJNISrcFilePath.c_str());

	fout << "#include <iostream>\n";
	fout << "#include <jni.h>\n";

    fout << "#include \"" << "../" << ClsFileSettings::me()->HEADER_FILE_FOLDER << "/" + strJNIHeaderFile + "\"\n";

    vector<string>::iterator itr;

    for(itr = ClsFileSettings::me()->vecStrJniHeaders.begin();itr != ClsFileSettings::me()->vecStrJniHeaders.end();itr++){
        fout << "#include \"" << *itr << "\"" << "\n\n";
    }

	fout << "using namespace std;\n\n";

	fout << strCPPHFileName << " objBL;\n\n";
    fout << ClsFileSettings::me()->JNI_CPP_CONVERTER <<" objConvert;\n\n";

	//cout << "size of vec_Jni_fun_dtls.strFunctionName = " << vec_Jni_fun_dtls.strFunctionName.size() << endl;
	for (unsigned int iCount = 0; iCount < vec_Jni_fun_dtls.strFunctionName.size(); iCount++)
	{

		fout << "JNIEXPORT ";

		fout << vec_Jni_fun_dtls.strFuncReturnType[iCount];

		fout << " JNICALL ";

		fout << vec_Jni_fun_dtls.strFunctionName[iCount];

		fout << "\n(";

		//cout << "vec_Jni_fun_dtls.strFuncArgDType[iCount] = " << vec_Jni_fun_dtls.strFuncArgDType[iCount].size() << endl;

		unsigned int intSize = vec_Jni_fun_dtls.strFuncArgDType[iCount].size();
		for (unsigned int jCount = 0; jCount < intSize; jCount++)
		{
			fout << (vec_Jni_fun_dtls.strFuncArgDType[iCount])[jCount];

			if (jCount >= 2)
			{
				fout << " ";
				fout << (vec_java_fun_dtls.strFuncArgName[iCount])[jCount - 2];
			}
			else if (jCount == 0)
			{
				fout << "env";
			}
			else if (jCount == 1)
			{
				fout << " obj";
			}

			(jCount != (intSize - 1)) ? fout << ", " : "";
		}

		fout << "){\n\n";
		fout << "return objConvert.fn"<<vec_Jni_fun_dtls.strFuncReturnType[iCount]<<"(";
        fout << "env, objBL."<<vec_Jni_fun_dtls.strFunctionName[iCount]<<"(env, ";

		intSize = vec_Jni_fun_dtls.strFuncArgDType[iCount].size();

		for (unsigned int jCount = 2; jCount < intSize; jCount++)
		{
			fout << (vec_java_fun_dtls.strFuncArgName[iCount])[jCount - 2];
			(jCount != (intSize - 1)) ? fout << ", " : "";
		}

		fout << "));\n\n";
		fout << "}\n\n";
	}

	fout.close();
	return true;
}

bool clsGenFiles::fnGenCPPHeadFile(const clsFuncDtls& vec_Jni_fun_dtls, const clsFuncDtls& vec_java_fun_dtls, const string& strCPPHeadFilePath)
{
	ofstream fout;
	fout.open(strCPPHeadFilePath.c_str());
	fout << "#include <iostream>\n";
	fout << "#include <jni.h>\n";
	fout << "#include <string>\n";

    vector<string>::iterator itr;

    for(itr = ClsFileSettings::me()->vecStrSrcHeaders.begin();itr != ClsFileSettings::me()->vecStrSrcHeaders.end();itr++){
        fout << "#include \"" << *itr << "\"" << "\n\n";
    }

	fout << "using namespace std;\n\n";

	fout << "class Integer {};\n\n";
	fout << "class String {};\n\n";
	fout << "template<typename _Tp>\n";
	fout << "class List{};\n\n";
	fout << "template<typename _Tp>\n";
	fout << "class ArrayList{};\n\n";
	fout << "template<typename _Tp1,typename _Tp2>\n";
	fout << "class HashMap{};\n\n";

    fout << "class "<< ClsFileSettings::me()->MYCLASS <<"{\n\n";

	fout << "private:\n\n";

	fout << "public:\n\n";
	//cout << "size of vec_Jni_fun_dtls.strFunctionName = " << vec_Jni_fun_dtls.strFunctionName.size() << endl;
	for (unsigned int iCount = 0; iCount < vec_Jni_fun_dtls.strFunctionName.size(); iCount++)
	{

		fout << vec_java_fun_dtls.strFuncReturnTypeCPP[iCount] << " ";

		fout << vec_java_fun_dtls.strFunctionName[iCount];

		fout << "\n(";

		//cout << "vec_Jni_fun_dtls.strFuncArgDType[iCount] = " << vec_Jni_fun_dtls.strFuncArgDType[iCount].size() << endl;

		int intSize = vec_java_fun_dtls.strFuncArgDType[iCount].size();
		for (int jCount = 0; jCount < intSize; jCount++)
		{
			fout << (vec_java_fun_dtls.strFuncArgDTypeCPP[iCount])[jCount];
			fout << " ";
			fout << (vec_java_fun_dtls.strFuncArgName[iCount])[jCount];
			(jCount != (intSize - 1)) ? fout << ", " : "";
		}

		fout << ");\n\n";
	}

	fout << "};\n\n";

	fout.close();
	return true;
}

bool clsGenFiles::fnGenCPPSrcFile(const clsFuncDtls& vec_Jni_fun_dtls, const clsFuncDtls& vec_java_fun_dtls, const string& strCPPSrcFilePath, const string& strCPPHeaderFile)
{
	ofstream fout;
	fout.open(strCPPSrcFilePath.c_str());

    fout << "#include \"" << "../" << ClsFileSettings::me()->HEADER_FILE_FOLDER << "/" + strCPPHeaderFile + "\""<<endl <<endl;

	//cout << "size of vec_Jni_fun_dtls.strFunctionName = " << vec_Jni_fun_dtls.strFunctionName.size() << endl;
	for (unsigned int iCount = 0; iCount < vec_Jni_fun_dtls.strFunctionName.size(); iCount++)
	{

        fout << vec_java_fun_dtls.strFuncReturnTypeCPP[iCount] << " " << ClsFileSettings::me()->MYCLASS << "::" << vec_java_fun_dtls.strFunctionName[iCount];

		fout << "\n(";

		//cout << "vec_Jni_fun_dtls.strFuncArgDType[iCount] = " << vec_Jni_fun_dtls.strFuncArgDType[iCount].size() << endl;

		int intSize = vec_java_fun_dtls.strFuncArgDType[iCount].size();
		for (int jCount = 0; jCount < intSize; jCount++)
		{
			fout << (vec_java_fun_dtls.strFuncArgDTypeCPP[iCount])[jCount];
			fout << " ";
			fout << (vec_java_fun_dtls.strFuncArgName[iCount])[jCount];
			(jCount != (intSize - 1)) ? fout << ", " : "";
		}

		fout << "){\n";
		fout << "}\n\n";
	}

	fout.close();
	return true;
}

bool clsGenFiles::fnGenFiles
(const vector<string> strValue)
{

    string strDateTime = objMyStrFun.fnGetCurrDateTime();

	string a_strJavahEXEPath = strValue[0];
    string a_strOutputFolder = strValue[1] + "_" + strDateTime;
	string a_strClassPath = strValue[2];
	string a_strClass = strValue[3];
	string a_strJavaFile = strValue[4];
	string a_strJNI_H_File = strValue[5];
	string a_strJNI_CPP_File = strValue[6];
	string a_strCPP_H_File = strValue[7];
	string a_strCPP_CPP_File = strValue[8];

	string strJavaClass;
	string strJNIHeadFile;
	string strCommandLine;

	//strCommandLine.append("\"");

	strCommandLine.append("\"");
	strCommandLine.append(a_strJavahEXEPath);
	strCommandLine.append("\"");
	strCommandLine.append(" -jni -o ");

    strJNIHeadFile.append(a_strOutputFolder);
    strJNIHeadFile.append("/");
    strJNIHeadFile.append(ClsFileSettings::me()->HEADER_FILE_FOLDER);
	strJNIHeadFile.append("/");
	strJNIHeadFile.append(a_strJNI_H_File);

	strCommandLine.append("\"");
	strCommandLine.append(strJNIHeadFile);
	strCommandLine.append("\" -cp ");

	strCommandLine.append("\"");
	strCommandLine.append(a_strClassPath);
	strCommandLine.append("\" ");

	strCommandLine.append("\"");
	strCommandLine.append(a_strClass);
	//strCommandLine.append("\"\"");
	strCommandLine.append("\"");

	//Create JNI Header File
	fnGenerageJNIHeaderFile(strCommandLine);

	//Get JNI Header File Function details
	clsFuncDtls vec_jni_fun_dtls;
	try
	{

		fnGetJniFunctionDetails(strJavaClass, vec_jni_fun_dtls, strJNIHeadFile);
	}
	catch(int a)
	{
		cout << "clsFuncDtls jni";
	}


	//Get Java File Function details
	clsFuncDtls vec_java_fun_args;
	try
	{

		fnGetJavaFunctionDetails(vec_java_fun_args, a_strJavaFile);
	}
	catch(int a)
	{
		cout << "clsFuncDtls java";
	}

	//Create JNI Source File
	try
	{
        fnGenJNISrcFile(vec_jni_fun_dtls, vec_java_fun_args, a_strOutputFolder + "/" + ClsFileSettings::me()->CPP_FILE_FOLDER + "/" +  a_strJNI_CPP_File, a_strJNI_H_File,ClsFileSettings::me()->MYCLASS);
	}
	catch(int a)
	{
		cout << "fnGenJNISrcFile";
	}

	//Create CPP Header File
	//vector<vector<string> > vec_java_fun_args;
	try
	{
        fnGenCPPHeadFile(vec_jni_fun_dtls, vec_java_fun_args, a_strOutputFolder + "/" + ClsFileSettings::me()->HEADER_FILE_FOLDER + "/" +a_strCPP_H_File);
	}
	catch(int a)
	{
		cout << "fnGenCPPHeadFile";
	}

	//Create CPP Source File
	try
	{
		//vector<vector<string> > vec_java_fun_args;
        fnGenCPPSrcFile(vec_jni_fun_dtls, vec_java_fun_args, a_strOutputFolder + "/" + ClsFileSettings::me()->CPP_FILE_FOLDER + "/" +a_strCPP_CPP_File, a_strCPP_H_File);
	}
	catch(int a)
	{
		cout << "fnGenCPPHeadFile";
	}

    //Copy resource cpp and header files
    try
    {
        vector<string>::iterator itr;

        boost::filesystem::path pthSource, pthDest;

        for(itr = ClsFileSettings::me()->vecStrResourceHeaderFiles.begin();itr != ClsFileSettings::me()->vecStrResourceHeaderFiles.end();itr++){
            pthSource= *itr;
            pthDest = a_strOutputFolder + "/" + ClsFileSettings::me()->HEADER_FILE_FOLDER + "/" + pthSource.filename().generic_string();
            boost::filesystem::copy(pthSource,pthDest);
        }

        for(itr = ClsFileSettings::me()->vecStrResourceCPPFiles.begin();itr != ClsFileSettings::me()->vecStrResourceCPPFiles.end();itr++){
            pthSource = *itr;
            pthDest = a_strOutputFolder + "/" + ClsFileSettings::me()->CPP_FILE_FOLDER + "/" + pthSource.filename().generic_string();
            boost::filesystem::copy(pthSource,pthDest);
        }



    }
    catch(int a)
    {
        cout << "fnGenCPPHeadFile";
    }

	return true;
}
