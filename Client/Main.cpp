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

#include <Windows.h>

struct EXTRAWORK
{
	uint16_t GameType;
	uint16_t Length;
	char Buffer[1024];
};
typedef BOOL(__thiscall *ExtraWorkProc)(EXTRAWORK *inStruct);

//Example:	Client IX86ExtraWork.dll 0x3 4
//			Program DLL Gametype Length
int main(int argc, char ** argv)
{
	HINSTANCE		hLib;
	ExtraWorkProc	lpfnExtraWork;
	BOOL			bReturn;
	EXTRAWORK		ExtraWork;
	char			*dllname;

	if (argc != 1 && argc != 4)
	{
		std::cout << "Invalid number of arguments" << std::endl;
		return 1;
	}
	else if (argc == 1)	//Default values if no arguments are passed
	{
		dllname = "IX86ExtraWork.dll";
		ExtraWork.GameType = 0x3; //StarCraft
		ExtraWork.Length = 4;
	}
	else //3 arguments
	{
		dllname = argv[1];
		ExtraWork.GameType = (uint16_t)std::strtoul(argv[2], NULL, 16);
		ExtraWork.Length = std::atoi(argv[3]);
	}

	hLib = LoadLibrary(dllname);
	if (!hLib) 
	{
		std::cout << "LoadLibrary error" << std::endl;
		return 1;
	}

	lpfnExtraWork = (ExtraWorkProc)GetProcAddress(hLib, "ExtraWork");
	FreeLibrary(hLib);
	if (!lpfnExtraWork)
	{
		std::cout << "GetProcAddress error" << std::endl;
		return 1;
	}

	bReturn = (*lpfnExtraWork)(&ExtraWork);

	//FIXME: GameType should remain constant, Length needs to be determined by the Client and not the DLL
	std::cout << "ExtraWork returned " << (bReturn ? "TRUE" : "FALSE") << std::endl;
	std::cout << "GameType: " << ExtraWork.GameType << "\t\t" << "Length: " << ExtraWork.Length << std::endl;
	std::cout << "Buffer: " << ExtraWork.Buffer << std::endl;

	return 0;
}
