/*
*	This is free and unencumbered software released into the public domain.
*	Refer to <http://unlicense.org/> if you have not received a copy of UNLICENSE
*/
#ifndef EXTRAWORK_H
#define EXTRAWORK_H


//Remove the need for Windows.h
using BOOL = int;
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
	std::uint16_t game;
	/*	
	*	0x01: Diablo II
	*	0x02: Warcraft III
	*	0x03: StarCraft
	*	0x04: World of Warcraft
	*/
	std::uint16_t length;
	char buffer[1024];
};

BOOL __fastcall ExtraWork(ExtraWorkData *extrawork, int unused);

#endif