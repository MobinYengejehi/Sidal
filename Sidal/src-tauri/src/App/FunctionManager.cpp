/*****************************************************************************
 *
 *  PROJECT:     Sidal Application
 *               (https://github.com/MobinYengejehi/Sidal)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        Sidal/Sidal/src-tauri/src/App/FunctionManager.cpp
 *
 *  AUTHOR:      MobinYengejehi
 *  GITHUB:      https://github.com/MobinYengejehi
 *
 *****************************************************************************/

#include <unordered_map>
#include <memory>

#include "FunctionManager.h"

#include "Utilities.h"

std::unordered_map<std::string, FunctionManager::FunctionType> Functions;

#include <iostream>

extern "C" {
	void CallJavascriptFunction(const char* jsonDocument);
	//CallJavascriptFunction("salam chetori khobi in cpp ie!");
}

EXPORT_INTERNAL void* call_c_function(const char* data) {
	FunctionManager::FunctionResultType result;
	FunctionManager::Invoke(data, &result);

	std::string jsonResult;
	JsonStringify(result, &jsonResult);

	if (jsonResult.empty()) {
		return NULL;
	}

	size_t size = jsonResult.size();

	void* resultPtr = malloc(size);
	memcpy(resultPtr, jsonResult.data(), size);
	
	return resultPtr;
}

EXPORT_INTERNAL void clear_c_function_results(void* result) {
	free(result);
}

void FunctionManager::Register(const std::string& name, FunctionType function) {
	if (Exists(name)) {
		return;
	}

	Functions[name] = function;
}

void FunctionManager::Unregister(const std::string& name) {
	if (!Exists(name)) {
		return;
	}

	Functions.erase(name);
}

bool FunctionManager::Exists(const std::string& name) {
	return Functions.find(name) != Functions.end();
}

FunctionManager::FunctionType FunctionManager::Get(const std::string& name) {
	if (name.empty()) {
		return NULL;
	}

	if (!Exists(name)) {
		return NULL;
	}

	return Functions.at(name);
}

void FunctionManager::Invoke(const std::string& name, FunctionArguments args, FunctionResultType* result) {
	FunctionType function = Get(name);

	if (!function) {
		return;
	}

	if (result) {
		function(args, *result);
		return;
	}

	FunctionResultType res = FunctionResultType(Json::arrayValue);

	function(args, res);
}

void FunctionManager::Invoke(const std::string& data, FunctionResultType* result) {
	if (data.empty()) {
		return;
	}

	Json::Value root;
	JsonParse(data, &root);

	if (root[0].isNull()) {
		return;
	}

	std::string name = root[0].asString();

	FunctionType function = Get(name);

	if (!function) {
		return;
	}

	FunctionArgumentsType args = FunctionArgumentsType(Json::arrayValue);

	if (root[1].isArray()) {
		args = root[1];
	}

	if (result) {
		function(args, *result);
		return;
	}

	FunctionResultType res = FunctionResultType(Json::arrayValue);

	function(args, res);
}