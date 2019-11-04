extern crate bindgen;

use std::env;
use std::path::PathBuf;

const ASAN: bool = false;

const HEADER: &str = "libkiibohd.h";
const SRC_DIR: &str = "controller";
const BUILD_DIR: &str = "libkiibohd";
const MODULES: &[&str] = &[
    "Debug/cli",
    "Debug/latency",
    "Debug/print",
    "Lib",
    "Macro/PartialMap",
    "Macro/PixelMap",
    "Output/HID-IO",
    "Output/Interface",
    "Output/TestOut",
    "Output/USB",
    "Scan/TestIn",
];

fn main() {
    // Tell cargo to tell rustc to link the libkiibohd.so shared library.
    println!("cargo:rustc-link-lib=kiibohd");
    println!("cargo:rustc-env=LD_LIBRARY_PATH={}", BUILD_DIR);
    println!("cargo:rustc-link-search={}", BUILD_DIR);

    if ASAN {
        println!("cargo:rustc-link-lib=asan");
        println!("cargo:rustc-link-lib=ubsan");
        println!("cargo:rustc-env=LD_PRELOAD=libasan.so:libubsan.so");
    }

    // Tell cargo to invalidate the built crate whenever the wrapper changes
    println!("cargo:rerun-if-changed={}", HEADER);

    // The input header we would like to generate bindings for.
    let mut builder = bindgen::Builder::default()
        .header(HEADER)
        .clang_arg(format!("-I{}", SRC_DIR))
        .clang_arg(format!("-I{}", BUILD_DIR))
        .clang_arg(format!("-L{}", BUILD_DIR));
    for module in MODULES {
        builder = builder.clang_arg(format!("-I{}/{}", SRC_DIR, module))
    }

    // Finish the builder and generate the bindings.
    let bindings = builder
        .generate()
        .expect("Unable to generate bindings");

    // Write the bindings to $OUT_DIR
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("kiibohd-bindings.rs"))
        .expect("Couldn't write bindings!");
}
