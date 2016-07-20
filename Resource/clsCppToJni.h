/*
 * clsCppToJni.h
 *
 *  Created on: 05-May-2016
 *      Author: linuxmintuser02
 */

#ifndef CLSCPPTOJNI_H_
#define CLSCPPTOJNI_H_

#include "jni.h"
#include <vector>

class clsCppToJni {
public:
	clsCppToJni();
	virtual ~clsCppToJni();
	jdoubleArray fnGetJDoubleArray(JNIEnv *env, std::vector<double> vecDbl);
};

#endif /* CLSCPPTOJNI_H_ */
