/*****************************************************************************
 *
 *  PROJECT:     Sidal Application
 *               (https://github.com/MobinYengejehi/Sidal)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        Sidal/Sidal/src/App.jsx
 * 
 *  AUTHOR:      MobinYengejehi
 *  GITHUB:      https://github.com/MobinYengejehi
 *
 *****************************************************************************/

import { useState } from "react";

import C from "./CFunctions";

export default function App() {
    return (
        <div className="container">
            <h1 onClick={async e => {
                const result = await C.Login("");
                console.log("login result is : ", result);
                // C.SayHi("salam chetori in buttone !");
            }} >hi this is sidal!</h1>
        </div>
    )
}