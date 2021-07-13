///////////////////////////////////////////
// Example how to access dll with the .lib and header file.
// 
// Need to be linked in properties
// 
///////////////////////////////////////////

#include <iostream>
#include "TestDll.h"

int main(void) {

	// Instance of Dll
	std::unique_ptr<TestDll> m_dllTest = std::make_unique<TestDll>();

	// Get the int value inside claa from dll
	std:: cout << m_dllTest->GetInt() << "\n";

	// Set a new value and show it
	m_dllTest->SetInt(42);
	std::cout << m_dllTest->GetInt() << "\n";

	// All done
	std::cout << "Done\n";
	std::cin.get();

	return EXIT_SUCCESS;
}