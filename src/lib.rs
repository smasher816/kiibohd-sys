#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![allow(safe_packed_borrows)]

include!(concat!(env!("OUT_DIR"), "/kiibohd-bindings.rs"));

#[cfg(test)]
mod tests {
    use super::*;
    use std::ffi::*;
    use std::os::raw::*;

    unsafe extern "C" fn print_callback(cmd: *const c_char, args: *const c_char) {
        let cmd = CStr::from_ptr(cmd);
        let args = CStr::from_ptr(args);
        println!(" > {:?} {:?}", cmd, args);
    }

    #[test]
    fn size_defines_test() {
        println!("");
        let _var_uint_t = dbg!(StateWordSize_define);
        let _index_uint_t = dbg!(IndexWordSize_define);
        let _state_uint_t = dbg!(ScheduleStateSize_define);
    }

    #[test]
    fn callback_test() {
        unsafe {
            Host_register_callback(print_callback as *mut c_void);
            Host_callback_test();
        }
    }
}
