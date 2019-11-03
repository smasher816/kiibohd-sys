[![Latest release on crates.io](https://meritbadge.herokuapp.com/amethyst-console)](https://crates.io/crates/kiibohd-sys)
[![Documentation on docs.rs](https://docs.rs/amethyst-console/badge.svg)](https://docs.rs/kiibohd-sys)

# kiibohd-sys

Raw bindings to the kll keyboard macro engine (https://github.com/kiibohd/controller).

## Setup

Add this to your `Cargo.toml`

```toml
[dependencies]
kiibohd-sys = "0.1.0"
```

## Usage

Please look at the Testing files in the upstream [controller](https://github.com/kiibohd/controller) git repo.

Specifically `Lib/host.py`, `Scan/TestIn/interface.py`, `Output/TestOut/host.py`, and the `main.c`

```rust
use std::ffi::*;
use std::os::raw::*;

unsafe extern "C" fn print_callback(cmd: *const c_char, args: *const c_char) {
	let cmd = CStr::from_ptr(cmd);
	let args = CStr::from_ptr(args);
	println!(" > {:?} {:?}", cmd, args);
}

fn main() {
	unsafe {
		Host_register_callback(print_callback as *mut c_void);
		Host_callback_test();
	}
}
```

Example output:
```
 > "serial_write" "Test 1 "
 > "serial_write" "Test 2 "
 > "serial_write" "\r\n"
 > "serial_write" "Systick Millisecond: "
 > "serial_write" "0x0"
 > "serial_write" "\r\n"
```
 
### Contributing

This will fetch the source code, compile a host version of libkiibohd, and generate the rust bindings+docs.

```bash
### Build the library

$ make
````
