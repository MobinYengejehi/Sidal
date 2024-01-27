/*****************************************************************************
 *
 *  PROJECT:     Sidal Application
 *               (https://github.com/MobinYengejehi/Sidal)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        Sidal/Sidal/src-tauri/src/App/Utilities.cpp
 *
 *  AUTHOR:      MobinYengejehi
 *  GITHUB:      https://github.com/MobinYengejehi
 *
 *****************************************************************************/

#include "Utilities.h"

void JsonParse(const std::string& document, Json::Value* root) {
	if (document.empty()) {
		return;
	}

	if (!root) {
		return;
	}
 
	Json::Reader reader;
	reader.parse(document, *root);
}

void JsonStringify(const Json::Value& root, std::string* document) {
	if (!document) {
		return;
	}

	Json::StreamWriterBuilder wBuilder;
	wBuilder["indentation"] = "";

	*document = Json::writeString(wBuilder, root);
}