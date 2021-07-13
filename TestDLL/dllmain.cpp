// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hModule,  // handle the DLL module
    DWORD  ul_reason_for_call,          // reason for calling function
    LPVOID lpReserved                   // Reserved
)
{
    // Perform actions based on the reason for calling.
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        break;
    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;
    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;
    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    }
    // Successful DLL_PROCESS_ATTACH.
    return TRUE;
}
