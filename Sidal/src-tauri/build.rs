/*****************************************************************************
 *
 *  PROJECT:     Sidal Application
 *               (https://github.com/MobinYengejehi/Sidal)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        Sidal/Sidal/src-tauri/build.rs
 * 
 *  AUTHOR:      MobinYengejehi
 *  GITHUB:      https://github.com/MobinYengejehi
 *
 *****************************************************************************/

use std::{ fs, io };
use std::path::Path;
use std::ffi::OsStr;

extern crate walkdir;
use walkdir::WalkDir;

fn get_files_in_directory(path: &str) -> io::Result<Vec<String>> {
    let entries = fs::read_dir(path)?;

    let file_names : Vec<String> = entries
        .filter_map(| entry | {
            let path = entry.ok()?.path();

            if path.is_file() {
                return path.file_name()?.to_str().map(|s| s.to_owned());
            }else{
                return None;
            }
        })
        .collect();
    
    return Ok(file_names);
}

fn main() {
    let mut arch_type = "x64";

    if std::env::var("CARGO_CFG_TARGET_POINTER_WIDTH").unwrap() == "32".to_string() {
        arch_type = "x86";
    }

    let mut dlls_dir = ".\\dlls".to_string();
    let mut libs_dir = ".\\libs".to_string();
    let mut static_libs_dir = ".\\static_libs".to_string();

    dlls_dir.push_str(&("\\".to_string()));
    dlls_dir.push_str(&arch_type);

    libs_dir.push_str(&("\\".to_string()));
    libs_dir.push_str(&arch_type);

    static_libs_dir.push_str(&("\\".to_string()));
    static_libs_dir.push_str(&arch_type);

    match get_files_in_directory(&dlls_dir) {
        Ok(file_names) => {
            for file_name in file_names {
                let file_path = Path::new(&dlls_dir).join(&file_name);
                
                fs::copy(file_path, Path::new("./").join(&file_name));
            }
        }
        Err(e) => {}
    }

    println!("cargo:rustc-link-search=native={}", libs_dir);
    match get_files_in_directory(&libs_dir) {
        Ok(file_names) => {
            for file_name in file_names {
                let file_path = Path::new(&file_name);
                let file_name = file_path.file_stem().unwrap().to_str().unwrap();

                println!("cargo:rustc-link-lib={}", file_name);
            }
        }
        Err(e) => {}
    }

    println!("cargo:rustc-link-search=native={}", static_libs_dir);
    match get_files_in_directory(&static_libs_dir) {
        Ok(file_names) => {
            for file_name in file_names {
                let file_path = Path::new(&file_name);
                let file_name = file_path.file_stem().unwrap().to_str().unwrap();

                println!("cargo:rustc-link-lib=static={}", file_name);
            }
        }
        Err(e) => {}
    }

    tauri_build::build();

    print!("Building backend...");

    let mut c_builder = cc::Build::new();
    c_builder.cpp(true);

    let backend_dir = "./src/App/".to_string();
    
    for file in WalkDir::new(&backend_dir).into_iter().filter_map(|file| file.ok()) {
        if file.metadata().unwrap().is_file() {
            let ext = file.path().extension().and_then(OsStr::to_str);

            if ext == Some("c") || ext == Some("cpp") || ext == Some("cxx") {
                c_builder.file(file.path());
            }
        }
    }

    c_builder.compile("Backend.exe");
}