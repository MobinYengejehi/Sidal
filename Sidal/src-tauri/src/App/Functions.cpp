/*****************************************************************************
 *
 *  PROJECT:     Sidal Application
 *               (https://github.com/MobinYengejehi/Sidal)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        Sidal/Sidal/src-tauri/src/App/Functions.cpp
 *
 *  AUTHOR:      MobinYengejehi
 *  GITHUB:      https://github.com/MobinYengejehi
 *
 *****************************************************************************/

#include <iostream>

#include "Functions.h"

using FunctionManager::FunctionArguments;
using FunctionManager::FunctionResult;

void SayHi(FunctionArguments args, FunctionResult result) {
	std::cout << "hi to js from cpp : " << args << std::endl;

	result[0] = "this is a test string from cpp!";
}