/*
*	See UNLICENSE file for license details
*	Refer to <http://unlicense.org/> if you have not received a copy of UNLICENSE
*/
#if _WIN32 || _WIN64
	#if _WIN64
		#error "64-bit programs can not be used with 32-bit DLLs"
	#endif
#endif

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <experimental/filesystem> //non-standard https://msdn.microsoft.com/en-us/library/hh874694(v=vs.140).aspx
#include <memory>
#include <string>

#include <Windows.h>

struct EXTRAWORK
{
	uint16_t Game;
	uint16_t Length;
	char Buffer[1024];
};
typedef BOOL(__thiscall *ExtraWorkProc)(EXTRAWORK *inStruct);

//Example:	Client IX86ExtraWork.dll 0x3 4
//			Program DLL Gametype Length
int main(int argc, char ** argv)
{
	struct FreeLibraryDeleter{typedef HMODULE pointer;void operator()(HMODULE handle){FreeLibrary(handle);}};
	std::unique_ptr <HMODULE, FreeLibraryDeleter> hLib = nullptr;
	ExtraWorkProc	lpfnExtraWork = nullptr;
	BOOL			bReturn = FALSE;
	EXTRAWORK		ExtraWork = {};
	auto LocalFreeDeleter = [](LPSTR handle){LocalFree(handle);};
	std::unique_ptr <char[], decltype(LocalFreeDeleter)> errmsg(new char[sizeof(char*)], LocalFreeDeleter);
	std::tr2::sys::path dllname;

	switch (argc)
	{
		case 1: //Default values if no arguments are passed
		{
			dllname = "IX86ExtraWork.dll";
			ExtraWork.Game = 0x03; //StarCraft
			ExtraWork.Length = 4;
			break;
		}
		case 4:
		{
			dllname = argv[1];
			ExtraWork.Game = (uint16_t)std::strtoul(argv[2], NULL, 16);
			ExtraWork.Length = (uint16_t)std::atoi(argv[3]);
			break;
		}
		default:
		{
			std::cout << "Error: Invalid number of arguments" << std::endl;
			return EXIT_FAILURE;
		}
	}

	if (!std::tr2::sys::exists(dllname))
	{
		std::cout << "Error: " << dllname.string() << " does not exist" << std::endl;
		return EXIT_FAILURE;
	}

	if (!std::tr2::sys::is_regular_file(dllname))
	{
		std::cout << "Error: " << dllname.string() << " is not a regular file" << std::endl;
		return EXIT_FAILURE;
	}

	hLib = std::unique_ptr <HMODULE, FreeLibraryDeleter>(LoadLibraryW(dllname.wstring().c_str()));
	if (!hLib)
	{
		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), 0, (LPSTR)&errmsg, 0, NULL);
		std::cout << "Error(" << GetLastError() << "): " << errmsg.get() << std::endl;
		return EXIT_FAILURE;
	}

	lpfnExtraWork = (ExtraWorkProc)GetProcAddress(hLib.get(), "ExtraWork");
	if (!lpfnExtraWork)
	{
		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), 0, (LPSTR)&errmsg, 0, NULL);
		std::cout << "Error(" << GetLastError() << "): " << errmsg.get() << std::endl;
		return EXIT_FAILURE;
	}

	bReturn = (*lpfnExtraWork)(&ExtraWork);

	//FIXME: GameType should remain constant, Length needs to be determined by the Client and not the DLL
	std::cout << "ExtraWork returned " << (bReturn ? "TRUE" : "FALSE") << std::endl;
	std::cout << "GameType: " << ExtraWork.Game << "\t\t" << "Length: " << ExtraWork.Length << std::endl;
	std::cout << "Buffer: " << ExtraWork.Buffer << std::endl;

	return EXIT_SUCCESS;
}