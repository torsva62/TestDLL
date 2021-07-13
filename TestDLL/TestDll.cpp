#include "pch.h"
#include "TestDll.h"

TestDll::TestDll() :
	m_testInt(1337)
{}

TestDll::~TestDll() {}

int TestDll::GetInt() { return m_testInt; }

inline void TestDll::SetInt(int l_int) { m_testInt = l_int; }

API void SetVar(const int l_int) { return m_myDll.SetInt(l_int); }

API int GetVar() { return m_myDll.GetInt(); }
