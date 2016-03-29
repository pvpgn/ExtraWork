/*
*	This is free and unencumbered software released into the public domain.
*	Refer to <http://unlicense.org/> if you have not received a copy of UNLICENSE
*/
#include "extrawork.h"

#include <cstring>


BOOL __fastcall ExtraWork(ExtraWorkData *extrawork, int)
{
	if (extrawork == nullptr)
		return FALSE;

	switch (extrawork->game)
	{
	case 0x01:
	case 0x02:
	case 0x03:
	case 0x04:
		break;
	default:
		return FALSE;
	}

	extrawork->length = static_cast<std::uint16_t>(std::strlen(extrawork->buffer));

	return TRUE;
}