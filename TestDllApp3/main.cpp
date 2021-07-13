#include <iostream>
#include <Windows.h>

///////////////////////////////////////////
// Example how to access dll without the .lib and header file.
// 
///////////////////////////////////////////

typedef int (__cdecl* GetInt)(void);
typedef int (__cdecl* SetInt)(int);

int main(void) {

    // Get the handle
    HINSTANCE dllHandle = nullptr;
    dllHandle = LoadLibrary(TEXT("TestDll.dll"));

    if (nullptr != dllHandle) {
        std::cout << "\nLoading dll handle: Sucess!\n\n";
    }
    else {
        // Handle isnt valid. Throw.
        std::cout << "\nLoading dll handle: Failed!\n\n";
        throw;
    }

    // Get pointer for GetVar function and show the value from function in dll
    GetInt ptrGet = nullptr;
    ptrGet = (GetInt)GetProcAddress(dllHandle, "GetVar");
    if (NULL != ptrGet) {
        std::cout << "Value from function: GetVar is: '" << ptrGet() << "'.\n\n";
    }
    else {
        std::cout << "Access to GetVar in dll failed!\n";
        std::cout << "Lasterror: " << GetLastError() << "\n";
    }

    // Get pointer for SetVar function, change the valu and show the new
    // value from GetVar function in dll
    SetInt ptrSet;
    ptrSet = (SetInt)(GetProcAddress(dllHandle, "SetVar"));
    if (NULL != ptrSet)
    {
       ptrSet(42);
       std::cout << "Access to SetVar in dll success!\n";
       std::cout << "New value is: '" << ptrGet() << "'\n";
    }
    else {
        std::cout << "Access to SetInt in dll failed!\n";
        std::cout << "Lasterror: " << GetLastError() << "\n";
    }

    // Check if dll handle still is valid.
    // Free the dll
    if (NULL != dllHandle) {
        std::cout << "\nFree dll handle: ";

        if (FreeLibrary(dllHandle))
            std::cout << "Succes!\n";
        else {
            std::cout << "Failed!\n";
            std::cout << "Lasterror: " << GetLastError() << "\n";
        }
    }

    // We are done. Exit
    std::cout << "\nDone!\n";
    std::cin.get();

    return EXIT_SUCCESS;
}
