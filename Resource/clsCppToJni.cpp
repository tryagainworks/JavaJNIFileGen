/*
 * clsCppToJni.cpp
 *
 *  Created on: 05-May-2016
 *      Author: linuxmintuser02
 */

#include "../include/clsCppToJni.h"

clsCppToJni::clsCppToJni() {
	// TODO Auto-generated constructor stub

}

clsCppToJni::~clsCppToJni() {
	// TODO Auto-generated destructor stub
}

jdoubleArray clsCppToJni::fnGetJDoubleArray(JNIEnv *env,
		std::vector<double> vecDbl) {
	if(vecDbl.size()==0) return 0;
	jdouble outCArray[vecDbl.size()];

	for (int i = 0; i < vecDbl.size(); i++) {
		outCArray[i] = vecDbl[i];
	}

	jdoubleArray outJNIArray = env->NewDoubleArray((int) vecDbl.size());
	if (0 == outJNIArray)
		return 0;
	env->SetDoubleArrayRegion(outJNIArray, 0, (int) vecDbl.size(), outCArray);
	return outJNIArray;
}

