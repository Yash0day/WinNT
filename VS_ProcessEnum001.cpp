// Process Enumeration using TOOL HELP functions
//

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

int main() {

	HANDLE hprocess = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hprocess == INVALID_HANDLE_VALUE) {
		printf("Handle not Valid!");
	}

	PROCESSENTRY32 pe; 
	pe.dwSize = sizeof(pe);  //defining the size of 'dwsize' in PROCESSENRTRY32 structure as the size of the structure. //

	if (!::Process32First(hprocess, &pe)) {
		printf("Error while enumerating the Process");
	}

	do
	 {
		printf("Pid: %6d [Executable Image: %ws] {Parent Pid: %6d} \n {Threads = %6d} {Priority = %6d} \n", 
			pe.th32ProcessID,
			pe.szExeFile,
			pe.th32ParentProcessID,
			pe.cntThreads,
			pe.pcPriClassBase);
	} while (::Process32Next(hprocess, &pe));

	::CloseHandle(hprocess);

	printf("Handle Closed!!!");
}
