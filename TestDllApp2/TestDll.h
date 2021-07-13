#ifndef __TESTDLL_H__
#define __TESTDLL_H__

// Needed if not linked in properies
#if !defined(LOGGER_API) && !defined(no_auto_link_stuff)
// Path to dll  may be needed if not in the same directory as the exe.
#pragma comment(lib, "TestDll.lib")
#endif

extern "C" class TestDll
{
public:
	__declspec(dllexport) TestDll();
	__declspec(dllexport) ~TestDll();
	__declspec(dllexport) int GetInt();
	__declspec(dllexport) virtual inline void SetInt(int);
};

#endif // !__TESTDLL_H__
