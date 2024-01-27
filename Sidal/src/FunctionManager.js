/*****************************************************************************
 *
 *  PROJECT:     Sidal Application
 *               (https://github.com/MobinYengejehi/Sidal)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        Sidal/Sidal/src/FunctionManager.js
 * 
 *  AUTHOR:      MobinYengejehi
 *  GITHUB:      https://github.com/MobinYengejehi
 *
 *****************************************************************************/

export default class FunctionManager {
    static Functions = {};

    constructor() {}

    static Register(name, func) {
        if (typeof name != "string" || name.length < 1) {
            return;
        }

        if (typeof func != "function") {
            return;
        }

        if (this.Exists(name)) {
            return;
        }

        this.Functions[name] = func; 
    }

    static Unregister(name) {
        if (!this.Exists(name)) {
            return; 
        }

        delete this.Functions[name];
    }

    static Exists(name) {
        if (typeof name != "string" || name.length < 1) {
            return false;
        }

        return typeof this.Functions[name] == "function";
    }

    static Get(name) {
        if (!this.Exists(name)) {
            return null;
        }

        return this.Functions[name];
    }

    static Invoke(name, args = []) {
        if (!this.Exists(name)) {
            return;
        }

        if (!args instanceof Array) {
            args = [];
        }

        const func = this.Get(name);

        return func(...args);
    }

    static InvokeByJson(jsonDocument) {
        if (typeof jsonDocument != "string" || jsonDocument.length < 1) {
            return;
        }

        try{
            const data = JSON.parse(jsonDocument);

            const name = data[0];

            if (!this.Exists(name)) {
                return;
            }

            const func = this.Get(name);

            const args = data[1];
            
            if (!args instanceof Array) {
                args = [];
            }

            return func(...args);
        }
        catch {}
    }
    
    static StartInvokerListener() {
        window.__FUNCTION_MANAGER_INVOKE_JAVASCRIPT_FUNCTION__ = this.InvokeByJson.bind(this);
    }
};