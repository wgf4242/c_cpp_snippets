#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// enable cross compiling
#ifdef __linux__
#include <sys/mman.h>
#elif _WIN32 || _MINGW_
#include <windows.h>
#endif

//Declaration of Function pointer, which will be ussed to call the shellcode
typedef void (*fp) (void);

int getFileSize(FILE* filePointer)
{
	fseek(filePointer,0L, SEEK_END);
	int size = ftell(filePointer);
	fseek(filePointer,0L, SEEK_SET);
	return size;
}

int main(int argc, char const *argv[])
{
	if(argc == 2)
	{
		FILE* shellcode = fopen(argv[1],"rb");
		if(shellcode)
		{
			int len = getFileSize(shellcode);
			printf("Shellcode length: %d\n", len);
			char* buffer = NULL;
			//Allocate Memory to store shellcode
			#ifdef __linux__
			buffer = (char*) mmap (NULL, len+1, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
			#elif _WIN32 || _MINGW_
			buffer = (char*) VirtualAlloc(NULL, len+1, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			#endif
			if(buffer!=NULL)
			{
				fread(buffer, len+1, 1, shellcode);
				fclose(shellcode);
				fp shell = (fp) buffer;
				//Invoke Shellcode
				printf("Shellcode has been loaded at %p. Press any key to execute it...",buffer);
				getchar();
				shell();
				printf("Executing done! Unloading shellcode and cleaning up memory...\nx");
				#ifdef __linux__
				munmap(buffer, len+1);
				#elif _WIN32 || _MINGW_
				VirtualFree(buffer, 0, MEM_RELEASE);
				#endif
				return 0;
			}
			else
			{
				printf("Could not allocate memory for buffer! Process aborted...");
				return -1;
			}		
		}
		else
		{
			perror("Could not load shellcode from file!");
			return -1;
		}
	
	}
	else
	{
		printf("ERROR: No shellcode file specified!\nUse: %s <path_to_shellcode>", argv[0]);
		return -1;
	}
}