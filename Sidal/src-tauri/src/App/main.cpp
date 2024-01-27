/*****************************************************************************
 *
 *  PROJECT:     Sidal Application
 *               (https://github.com/MobinYengejehi/Sidal)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        Sidal/Sidal/src-tauri/src/App/main.cpp
 *
 *  AUTHOR:      MobinYengejehi
 *  GITHUB:      https://github.com/MobinYengejehi
 *
 *****************************************************************************/

#include <iostream>
#include <memory>
#include <string>

#include "main.h"
#include "FunctionManager.h"
#include "Functions.h"

#include "Utilities.h"

EXPORT_INTERNAL void application_init() {
    curl_global_init(CURL_GLOBAL_ALL);
    
    FUNCTION_MANAGER_REGISTER(SayHi);

    /*Json::Value root;

    root[0] = "PrintMe";

    FunctionManager::FunctionArgumentsType args;
    args[0] = 310;
    args[1] = 13313;

    root[1] = args;

    std::string document;
    JsonStringify(root, &document);

    FunctionManager::FunctionResultType result;
    FunctionManager::Invoke(document, &result);

    std::cout << "function result is : " << result << std::endl;*/
}

EXPORT_INTERNAL void application_cleanup() {
    curl_global_cleanup();
}

/*#include "json/json.h"
#include "curl/curl.h"

#define EXPORT extern "C"

std::string JsonStringify(Json::Value json) {
    Json::StreamWriterBuilder wBuilder;
    wBuilder["indentation"] = "";

    return Json::writeString(wBuilder, json);
}

Json::Value JsonParse(const std::string& document) {
    Json::Reader reader;

    Json::Value root;

    reader.parse(document, root);

    return root;
}

EXPORT void* CppAllocate(size_t size) {
    void* ptr = malloc(size);
    
    std::string result = "[cpp number is : '";
    result += std::to_string(size + 3130);
    result += "']";

    Json::Value root;
    root["name"] = "mobin";
    root["last_name"] = "yengejehi";
    root["age"] = 18;

    std::string document = JsonStringify(root);

    std::cout << "root is : " << document.data() << " | " << document.size() << std::endl;

    std::cout << "parse is : " << JsonParse(document) << std::endl;

    result += " | ";
    result += document;

    memcpy(((char*)ptr), result.data(), result.size());

    std::cout << "allocating ptr : " << ptr << std::endl;

    return ptr;
}

EXPORT void CppFree(void* ptr) {
    std::cout << "freeing ptr : " << ptr << std::endl;

    free(ptr);
}

EXPORT int GetCNumber() {
    return 31;
}*/

/*extern "C" const char* GetCppNumber(int x, int y) {
    std::cout << "streaming out! " << x << " | " << y << "\n";

    int result = x + y + 56930;

    std::cout << "result generated : " << result << std::endl;

    std::string text = "[cpp number : '";
    //text += std::to_string(result);
    //text += "']";

    std::cout << "string is : " << text << std::endl;

    std::cout << "size is : " << text.size() << std::endl;

    void* memBuffer = malloc(text.size());

    memcpy(memBuffer, (const void*)text.data(), text.size());

    return (const char*)memBuffer;
}

extern "C" void FreeMemory(void* memory) {
    free(memory);
}*/