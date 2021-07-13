#ifndef __TESTDLL_H__
#define __TESTDLL_H__

#ifdef TESTDLL_EXPORTS
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif // TESTDLL_EXPORTS

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	class API TestDll
	{
	public:
		TestDll();
		~TestDll();

		int GetInt();
		virtual inline void SetInt(int);
	private:
		int m_testInt;
	};

	TestDll m_myDll;

	// Outside class functions to access inside class
	API inline void SetVar(const int l_int);
	API int GetVar();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !__TESTDLL_H__
