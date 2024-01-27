/*****************************************************************************
 *
 *  PROJECT:     Sidal Application
 *               (https://github.com/MobinYengejehi/Sidal)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        Sidal/Sidal/src-tauri/src/App/Utilities.h
 *
 *  AUTHOR:      MobinYengejehi
 *  GITHUB:      https://github.com/MobinYengejehi
 *
 *****************************************************************************/

#pragma once

#ifndef UTILITIES_HEADER
#define UTILITIES_HEADER

#include "json/json.h"

void JsonParse(const std::string& document, Json::Value* root);
void JsonStringify(const Json::Value& root, std::string* document);

#endif