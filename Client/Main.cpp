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
#include <iostream>
#include <experimental/filesystem> //non-standard https://msdn.microsoft.com/en-us/library/hh874694(v=vs.140).aspx
#include <functional>
#include <memory>
#include <string>

#include <Windows.h>


struct ExtraWorkData
{
	uint16_t game;
	uint16_t length;
	char buffer[1024];
};
typedef BOOL(__thiscall *ExtraWorkProc)(ExtraWorkData *extrawork);


struct FreeLibraryDeleter
{
	typedef HMODULE pointer;
	void operator() (HMODULE handle)
	{
		FreeLibrary(handle);
	}
};

class err
{
public:
	err::err(DWORD errcode)
	{
		err::dwMessageId = errcode;
	}

	LPSTR str()
	{
		if (err::count > 0)
			this->~err();

		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			err::dwMessageId,
			0,
			(LPSTR)(&(err::lpMsg)),
			0,
			NULL);

		err::count++;

		return err::lpMsg;
	}

	DWORD id()
	{
		return err::dwMessageId;
	}

	err::~err()
	{
		if (err::count > 0)
		{
			err::count--;
			LocalFree(err::lpMsg);
			err::lpMsg = nullptr;
		}
	}

private:
	unsigned int count = 0;
	DWORD dwMessageId;
	LPSTR lpMsg = nullptr;
};

//Example: Client IX86ExtraWork.dll 0x3 4
//         Program DLL Gametype Length
int main(int argc, char ** argv)
{
	ExtraWorkData extrawork = {};
	std::experimental::filesystem::path dllname;
	auto retErr = [](std::string errmsg_in)
	{
		if (errmsg_in.length() > 0)
			std::cerr << "Error: " << errmsg_in << std::endl;
		else
		{
			err error(GetLastError());
			std::cerr << "Error(" << error.id() << "): " << error.str() << std::endl;
		}

		return EXIT_FAILURE;
	};

	switch (argc)
	{
		case 1: //Default values if no arguments are passed
		{
			dllname = "IX86ExtraWork.dll";
			extrawork.game = 0x3; //StarCraft
			extrawork.length = 4;
			break;
		}
		case 4:
		{
			dllname = argv[1];
			extrawork.game = (uint16_t)std::stoi(argv[2], nullptr, 16);
			extrawork.length = (uint16_t)std::stoi(argv[3], nullptr, 10);
			break;
		}
		default:
		{
			return retErr("Invalid number of arguments");
		}
	}

	if (!std::experimental::filesystem::exists(dllname))
		return retErr(dllname.string() + " does not exist");

	if (!std::experimental::filesystem::is_regular_file(dllname))
		return retErr(dllname.string() + " is not a regular file");

	auto hLib = std::unique_ptr <HMODULE, FreeLibraryDeleter>(LoadLibraryW(dllname.wstring().c_str()));
	if (!hLib)
		return retErr("");

	auto lpfnExtraWork = reinterpret_cast<ExtraWorkProc>(GetProcAddress(hLib.get(), "ExtraWork"));
	if (!lpfnExtraWork)
		return retErr("");

	BOOL bReturn = lpfnExtraWork(&extrawork);

	//FIXME: GameType should remain constant, Length needs to be determined by the Client and not the DLL
	std::cout << "ExtraWork returned " << (bReturn ? "TRUE" : "FALSE") << std::endl;
	std::cout << "GameType: " << std::hex << std::showbase << extrawork.game << "\t\t" << "Length: " << std::dec << std::noshowbase << extrawork.length << std::endl;
	std::cout << "Buffer: " << extrawork.buffer << std::endl;

	return EXIT_SUCCESS;
}