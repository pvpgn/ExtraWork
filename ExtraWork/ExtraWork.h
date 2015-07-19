/*
*	See UNLICENSE file for license details
*	Refer to <http://unlicense.org/> if you have not received a copy of UNLICENSE
*/
#if _WIN32 || _WIN64
	#if _WIN64
		#error "64-bit DLLs can not be used in 32-bit programs"
	#endif
#endif

#define EXPORT extern "C" __declspec(dllexport)

//Remove the need for Windows.h
typedef	int BOOL;
#ifndef TRUE
	#define	TRUE 1
#endif
#ifndef FALSE
	#define	FALSE 0
#endif

#include <cstdint>

//refer to https://bnetdocs.org/?op=packet&pid=240
struct ExtraWorkData
{
	uint16_t game;
	/*	
	*	0x01: Diablo II
	*	0x02: Warcraft III
	*	0x03: StarCraft
	*	0x04: World of Warcraft
	*/
	uint16_t length;
	char buffer[1024];
};

EXPORT BOOL __fastcall ExtraWork(ExtraWorkData *extrawork, int unused);