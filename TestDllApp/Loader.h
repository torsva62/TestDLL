#ifndef __DLL_LOADER_H__
#define __DLL_LOADER_H__

#include <Windows.h>
#include <string>
#include <map>
#include <functional>

////////////////////////////////////
// Wrapper to access the dll and the
// functions inside.
// You have to know the functions definitions.
// 
// Use:
// Create instance of Loader and the dll path + name
// std::unique_ptr<Loader> m_loader = std::make_unique<Loader>();
// std::string dllName = "TestDll.dll";
// 
// Access a function inside dll:
// Definition of the function: int GetVar();
// auto ret = m_loader->ExcecuteDllFunc<int(void)>("GetVar");
// 
//  This wrapper stilll need a lot of work
////////////////////////////////////

class Loader
{
public:

	Loader() :
		m_dllHandle(nullptr)
	{}

	~Loader() { UnLoadDll(); }

	bool LoadDll(const std::string& l_dllPath)
	{
		m_dllName = l_dllPath;
		m_dllHandle = LoadLibraryA(m_dllName.c_str());

		if (nullptr == m_dllHandle)
		{
			// Failed loding dll
			return false;
		}

		// Success loading dll
		return true;
	}

	bool DllHandleExist(const std::string& l_dllName)
	{
		return (m_dllHandle != nullptr);
	}

	bool UnLoadDll()
	{
		if (m_dllHandle == nullptr) {
			// Handle of dll doesnt exist, nothing to free
			return true;
		}

		auto b = FreeLibrary(m_dllHandle);
		if (!b) {
			// Failed to free dll
			return false;
		}

		m_dllHandle = nullptr;

		// Managed to free dll
		return true;
	}

	template <typename T>
	std::function<T> GetDllFunction(const std::string& funcName)
	{
		auto it = m_map.find(funcName);
		if (it == m_map.end())
		{
			auto addr = GetProcAddress(m_dllHandle, funcName.c_str());
			if (!addr)
				return nullptr;
			m_map.insert(std::make_pair(funcName, addr));
			it = m_map.find(funcName);
		}

		return std::function<T>((T*)(it->second));
	}

	template <typename T, typename... Args>
	typename std::result_of<std::function<T>(Args...)>::type ExcecuteDllFunc(const std::string& funcName, Args&&... args)
	{
		auto f = GetDllFunction<T>(funcName);
		if (f == nullptr)
		{
			std::cerr << "\nERROR! \nCan not find this function '" + funcName + "'" +
				"\nLast error: " + std::to_string(GetLastError()) << "\n\n";
			throw;
		}

		return f(std::forward<Args>(args)...);
	}

private:
	HINSTANCE m_dllHandle;
	std::map<std::string, FARPROC> m_map;
	std::string m_dllName;
};

#endif // !__DLL_LOADER__
