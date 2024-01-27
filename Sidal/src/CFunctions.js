/*****************************************************************************
 *
 *  PROJECT:     Sidal Application
 *               (https://github.com/MobinYengejehi/Sidal)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        Sidal/Sidal/src/CFunctions.js
 * 
 *  AUTHOR:      MobinYengejehi
 *  GITHUB:      https://github.com/MobinYengejehi
 *
 *****************************************************************************/

import { invoke } from "@tauri-apps/api/tauri";

const C_FUNCTION_EXECUTOR_NAME = "CallCFunction";

export default new Proxy({}, {
    get(_, key) {
        return async (...args) => {
            const data = [key, args];

            const jsonDocument = JSON.stringify(data);

            const result = await invoke(C_FUNCTION_EXECUTOR_NAME, { jsonDocument });

            return (
                result ?
                (
                    (() => {
                        try {
                            return JSON.parse(result);
                        } catch {
                            return null;
                        }
                    })()
                ) :
                null
            );
        }
    }
});