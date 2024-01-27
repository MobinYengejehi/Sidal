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
    
    FUNCTION_MANAGER_REGISTER(Login);
}

EXPORT_INTERNAL void application_cleanup() {
    curl_global_cleanup();
}