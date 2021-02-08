#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <TlHelp32.h>
#include <atlbase.h>
#include <atlconv.h>

using namespace std; 

int main()
{

    HANDLE hsnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hsnap == INVALID_HANDLE_VALUE) {
        printf("Handle not provided");
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(pe);

    if (!::Process32First(hsnap, &pe)) {
        printf("Process Enumeration Failed");
    }

    do {
        printf("Pid: % 6d[Executable Image : % ws]{ Parent Pid : % 6d } \n { Threads = % 6d } {Priority = % 6d} \n", 
            pe.th32ProcessID,
            pe.szExeFile,
            pe.th32ParentProcessID,
            pe.cntThreads,
            pe.pcPriClassBase);
    } while (::Process32Next(hsnap, &pe));
    
    int n = 3; 

    printf("[*] Choose any of the following\n ");
    printf("[1] Open a Process with Process Name \n");
    printf("[2] Terminate a Process with Process ID \n");
    printf("[3] Close the Process Enumeration Handle gracefully \n");
    cin >> n;

    switch (n) {
     

    case 1:
    {
        //WCHAR Pname[] = L"notepad";
        std::cout << "Enter the Name of Process you want to initiate\n";
        
        string p;
        string *Pname = &p; 
        cin >> p;
        cout << "Creating new Process...\n";

        STARTUPINFO s = { sizeof(s) };
        PROCESS_INFORMATION p;

        BOOL success = ::CreateProcess(nullptr, Pname, nullptr, nullptr, false, 0, nullptr, nullptr, &s, &p);

        if (!success) {
            printf("Process Creation Failed! %d\n", ::GetLastError());
        }

        else {
            int Pname_pid = p.dwProcessId;
            int Pname_tid = p.dwThreadId;
            printf("[+] Process Created\n");
            printf("[Pid: %6d] \t", Pname_pid);
            printf("[Tid: %6d] ", Pname_tid);

        }

        ::CloseHandle(p.hProcess);
        ::CloseHandle(p.hThread);
        break;
    }
    case 2:
    {
        std::cout << "Enter the Process ID to Terminate\n";

        int term_pid;
        cin >> term_pid;
        cout << "Terminating... \n" << term_pid;

        HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, term_pid);

        if (!::TerminateProcess(hprocess, 1)) {
            printf("\n[-] \n", GetLastError());
        }
        else
            printf("[+] Process Terminated \n");

        CloseHandle(hprocess);
        break;
    }
    case 3: 
    {
        printf("[*] Exiting...\n");
        ::CloseHandle(hsnap);
    }
    }
    return 0;
}

