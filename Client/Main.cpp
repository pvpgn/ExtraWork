/*
*	This is free and unencumbered software released into the public domain.
*	Refer to <http://unlicense.org/> if you have not received a copy of UNLICENSE
*/

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <experimental/filesystem> //non-standard https://msdn.microsoft.com/en-us/library/hh874694(v=vs.140).aspx
#include <memory>
#include <stdexcept>
#include <string>

#include <Windows.h>


struct ExtraWorkData
{
	std::uint16_t game;
	std::uint16_t length;
	char buffer[1024];
};

using ExtraWorkProc = BOOL __fastcall(ExtraWorkData *);


struct FreeLibraryDeleter
{
	using pointer = HMODULE;
	void operator() (HMODULE hLibModule)
	{
		::FreeLibrary(hLibModule);
	}
};


int main(int argc, char **argv)
{
	if (argc == 2 && 
		(std::string(argv[1]).compare("--help") == 0 || std::string(argv[1]).compare("-h") == 0))
	{
		std::cout << "Usage: " << argv[0] << " [<ExtraWork DLL file>] [--] [<TGA file>]" << std::endl;
		std::cout << "\t-h, --help\tdisplay this information and exit" << std::endl;
		std::cout << "\t-v, --version\tprint version number and exit" << std::endl << std::endl;
		std::cout << "Report bugs to: <https://github.com/pvpgn/ExtraWork/issues/>" << std::endl;
		std::cout << "ExtraWork home page: <https://github.com/pvpgn/ExtraWork/>" << std::endl;
		return EXIT_SUCCESS;
	}

	if (argc == 2 && 
		(std::string(argv[1]).compare("--version") == 0 || std::string(argv[1]).compare("-v") == 0))
	{
		std::cout << "ExtraWork 1.3" << std::endl;
		std::cout << "ExtraWork is released into the public domain as specified by UNLICENSE <http://unlicense.org>" << std::endl;
		std::cout << "This is free software: you are free to change and redistribute it." << std::endl;
		std::cout << "There is NO WARRANTY, to the extent permitted by law." << std::endl;
		return EXIT_SUCCESS;
	}

	if (argc != 3)
	{
		std::cerr << "Invalid number of arguments" << std::endl;
		return EXIT_FAILURE;
	}

	std::experimental::filesystem::path dllname(argv[1]);
	if (std::experimental::filesystem::exists(dllname) == false)
	{
		std::cerr << dllname.string() << " does not exist" << std::endl;
		return EXIT_FAILURE;
	}

	if (std::experimental::filesystem::is_regular_file(dllname) == false)
	{
		std::cerr << dllname.string() << " is not a regular file" << std::endl;
		return EXIT_FAILURE;
	}

	auto hLib = std::unique_ptr<HMODULE, FreeLibraryDeleter>(::LoadLibraryA(dllname.string().c_str()));
	if (hLib == nullptr)
	{
		std::cerr << "Could not load " << dllname.string() << " (" << ::GetLastError() << ")" << std::endl;
		return EXIT_FAILURE;
	}

	auto lpfnExtraWork = reinterpret_cast<ExtraWorkProc *>(::GetProcAddress(hLib.get(), "ExtraWork"));
	if (lpfnExtraWork == nullptr)
	{
		std::cerr << "Could not retrieve ExtraWork()'s address " << "(" << ::GetLastError() << ")" << std::endl;
		return EXIT_FAILURE;
	}

	ExtraWorkData extrawork = {};
	try
	{
		extrawork.game = static_cast<std::uint16_t>(std::stoi(std::string(argv[2]), nullptr, 16));
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << "std::invalid_argument: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (std::out_of_range& e)
	{
		std::cerr << "std::out_of_range: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	BOOL bReturn = lpfnExtraWork(&extrawork);

	std::cout << "ExtraWork() returned " << (bReturn ? "TRUE" : "FALSE") << std::endl;
	if (bReturn == TRUE)
	{
		std::cout << "Game: " << std::hex << std::showbase << extrawork.game << std::endl;
		std::cout << "Length: " << extrawork.length << std::endl;
		std::cout << "Buffer: " << extrawork.buffer << std::endl;
	}

	return EXIT_SUCCESS;
}