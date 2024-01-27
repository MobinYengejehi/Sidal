/*****************************************************************************
 *
 *  PROJECT:     Sidal Application
 *               (https://github.com/MobinYengejehi/Sidal)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        Sidal/Sidal/src-tauri/src/main.rs
 * 
 *  AUTHOR:      MobinYengejehi
 *  GITHUB:      https://github.com/MobinYengejehi
 *
 *****************************************************************************/

#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

use std::ffi::c_void;
use std::ffi::c_char;
use std::ffi::CString;
use std::ffi::CStr;

use tauri::window::Window;

static mut MainWindow : Option<Window> = None;

extern "C" {
    fn application_init() -> c_void;
    fn application_cleanup() -> c_void;

    fn call_c_function(data : *const c_char) -> *mut c_void;
    fn clear_c_function_results(data : *mut c_void) -> c_void;
}

#[tauri::command]
fn CallCFunction(jsonDocument : &str) -> String {
    let c_str = CString::new(jsonDocument).unwrap();
    let c_str_data : *const c_char = c_str.as_ptr() as *const c_char;

    let resultPtr : *mut c_void = unsafe { call_c_function(c_str_data) };

    let resultStr : &str = &unsafe { CStr::from_ptr(resultPtr as *const _) }.to_string_lossy();

    unsafe { clear_c_function_results(resultPtr) };

    return format!("{}", resultStr);
}

#[no_mangle]
pub extern "C" fn CallJavascriptFunction(jsonDocumentRaw : *const c_char) {
    let jsonDocument : &str = &unsafe { CStr::from_ptr(jsonDocumentRaw as *const _) }.to_string_lossy();

    unsafe {
        match &MainWindow {
            Some(window) => {
                window.eval("window.givemsg('hi this is a cpp msg')");
            },
            None => {}
        }
    }

    println!("json document is : {}", jsonDocument);
}

fn main() {
    unsafe { application_init() };

    tauri::Builder::default()
        .on_page_load(move | window, _ | {
            // window.eval("alert('hi this is rust!')");
            unsafe { MainWindow.insert(window) };
        })
        .invoke_handler(tauri::generate_handler![CallCFunction])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");

    unsafe { application_cleanup() };
}

/*use std::ffi::c_void;
use std::ffi::CStr;

extern "C" {
    fn CppAllocate(size : u32) -> *mut c_void;

    fn CppFree(ptr : *mut c_void);

    fn GetCNumber() -> i32;
}

#[tauri::command]
fn greet(name: &str) -> String {
    let s : String = String::from("slam chetori?");

    println!("rust str is : {}", s);

    let ptr : *mut c_void = unsafe { CppAllocate(100) };

    let cstr : &str = &unsafe { CStr::from_ptr(ptr as *const _) }.to_string_lossy();
    println!("cstring is : {}", cstr);

    unsafe { CppFree(ptr) };
    
    return format!("rust says 2: {} | numb : {} | and c str : {}", name, unsafe { GetCNumber() }, cstr);
}

fn main() {
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![greet])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
*/