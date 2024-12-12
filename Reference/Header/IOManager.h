#pragma once
#include "Base.hpp"
#include <commdlg.h>
#include <shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include <shlobj.h>

namespace Engine
{

	class ENGINE_DLL IOManager : public Base
	{
	private:
		IOManager(void) = default;
		~IOManager(void) = default;

	public:

		static std::wstring selectSaveFilePath(void);
		static std::wstring selectLoadFilePath(void);
		static std::wstring selectFolderPath(void);
		//static void setDefaultPath(std::wstring& path) { defaultPath = path; }
		static std::list<std::pair<std::wstring, std::wstring>> findAllFiles(const std::wstring& folderPath);

		static HRESULT load(const std::wstring& path, std::function<void(HANDLE)> function);
		static HRESULT save(const std::wstring& path, std::function<void(HANDLE)> function);


		template <typename T>	static HRESULT serialize(HANDLE hFile, const T& value)
		{
			static_assert(!std::is_same<T, char*>::value, "���ڿ��� ����� �� �����ϴ�.");
			if (!WriteFile(hFile, &value, sizeof(T), NULL, NULL))
				return E_FAIL;

			return S_OK;
		}
		template <>				static HRESULT serialize(HANDLE hFile, const std::string& value)
		{
			int length = (int)value.size();
			if (!WriteFile(hFile, &length, sizeof(int), NULL, NULL))
				return E_FAIL;
			if (!WriteFile(hFile, value.c_str(), length * sizeof(char), NULL, NULL))
				return E_FAIL;

			return S_OK;
		}
		template <>				static HRESULT serialize(HANDLE hFile, const std::wstring& value)
		{
			int length = (int)value.size();
			if (!WriteFile(hFile, &length, sizeof(int), NULL, NULL))
				return E_FAIL;
			if (!WriteFile(hFile, value.c_str(), length * sizeof(wchar_t), NULL, NULL))
				return E_FAIL;

			return S_OK;
		}

		template <typename T>	static HRESULT deserialize(HANDLE hFile, T& value)
		{
			static_assert(!std::is_same<T, char*>::value, "���ڿ��� ����� �� �����ϴ�.");
			DWORD readAmount = 0;
			if (!ReadFile(hFile, &value, sizeof(T), &readAmount, NULL))
				return E_FAIL;
			if (readAmount == 0) return E_FAIL;

			return S_OK;
		}
		template <>				static HRESULT deserialize(HANDLE hFile, std::string& value)
		{
			int length = 0;
			if (!ReadFile(hFile, &length, sizeof(int), NULL, NULL))
				return E_FAIL;

			if (length < 0) return E_FAIL;
			if (length == 0) return S_OK;

			value.resize(length);
			if (!ReadFile(hFile, &value[0], length * sizeof(char), NULL, NULL))
				return E_FAIL;

			return S_OK;
		}
		template <>				static HRESULT deserialize(HANDLE hFile, std::wstring& value)
		{
			int length = 0;
			if (!ReadFile(hFile, &length, sizeof(length), NULL, NULL))
				return E_FAIL;
			if (length < 0) return E_FAIL;
			if (length == 0) return S_OK;

			value.resize(length);
			if (!ReadFile(hFile, &value[0], length * sizeof(wchar_t), NULL, NULL))
				return E_FAIL;

			return S_OK;

			//#include <tchar.h> // tchar�� ���� ���
			//	TCHAR* buffer = new TCHAR[length + 1];  // �� ���� ������ �߰��� Ȯ��
			//	if (ReadFile(hFile, buffer, length * sizeof(TCHAR), NULL, NULL))
			//	{
			//		buffer[length] = _T('\0');
			//		value = std::to_string(*buffer); => std::string��
			// 	    CString value = buffer; => cstring��
			//	}
			//	delete[] buffer;
		}

	private:
		//static std::wstring defaultPath;
	};

}