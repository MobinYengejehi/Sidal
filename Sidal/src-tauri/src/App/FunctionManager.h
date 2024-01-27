/*****************************************************************************
 *
 *  PROJECT:     Sidal Application
 *               (https://github.com/MobinYengejehi/Sidal)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        Sidal/Sidal/src-tauri/src/App/FunctionManager.h
 *
 *  AUTHOR:      MobinYengejehi
 *  GITHUB:      https://github.com/MobinYengejehi
 *
 *****************************************************************************/

#pragma once

#ifndef FUNCTION_MANAGER_HEADER
#define FUNCTION_MANAGER_HEADER

#include <string>

#include "json/json.h"

#include "Export.h"

#define FUNCTION_MANAGER_REGISTER(function) FunctionManager::Register(#function, function)
#define FUNCTION_MANAGER_GENERATE(function) void function(FunctionManager::FunctionArguments args, FunctionManager::FunctionResult result)

EXPORT_INTERNAL void* call_c_function(const char* data);
EXPORT_INTERNAL void  clear_c_function_results(void* result);

namespace FunctionManager {
	typedef Json::Value FunctionArgumentsType;
	typedef const FunctionArgumentsType& FunctionArguments;

	typedef Json::Value FunctionResultType;
	typedef FunctionResultType& FunctionResult;

	typedef void (*FunctionType)(FunctionArguments args, FunctionResult result);

	void Register(const std::string& name, FunctionType function);
	void Unregister(const std::string& name);

	bool Exists(const std::string& name);

	FunctionType Get(const std::string& name);
	
	void Invoke(const std::string& name, FunctionArguments args, FunctionResultType* result = NULL);
	void Invoke(const std::string& data, FunctionResultType* result = NULL);

	void InvokeJavascriptFunction(const std::string& name, FunctionArguments args);
}

#endif