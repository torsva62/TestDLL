///////////////////////////////////////////
// Example of how to access dll without having the .lib-,
// .def- or header file of the dll.
// 
// The functions name and definition must be knowned.
// 
///////////////////////////////////////////

#include <iostream>
#include "Loader.h"

int main(void)
{
    // Create instance of Loader and the dll path + name
    std::unique_ptr<Loader> m_loader = std::make_unique<Loader>();
    std::string dllName = "TestDll.dll";

    // Loader handle shouldn exist now
    std::cout << "Before loading\nHandle to dll (" << dllName << ") exist: ";
    std::cout << m_loader->DllHandleExist(dllName) << "\n\n";

    // Load the dll
    if (!m_loader->LoadDll(dllName)) {
        std::cout << "Failed loading dll '" << dllName << "'\n";
        throw;
    }

    // Now the handle exist
    std::cout << "After loading\nHandle to dll (" << dllName << ") exist: ";
    std::cout << m_loader->DllHandleExist(dllName) << "\n\n";

    // And now get values from outside class
    std::cout << "-----\nAccess from outside class\nto get member from inside class\n------\n\n";

    // Get the GetInt() value from outside class
    auto ret = m_loader->ExcecuteDllFunc<int(void)>("GetVar");
    std::cout << "Value from function GetVar is: '" << ret << "'\n\n";

    // Set a new value and show it
    m_loader->ExcecuteDllFunc<void(int)>("SetVar", 42);
    std::cout << "Value after changing value in function SetInt is: '" <<
        m_loader->ExcecuteDllFunc<int(void)>("GetVar") << "'\n\n";

	std::cout << "\nDone!\n";
	std::cin.get();
    return EXIT_SUCCESS;
}