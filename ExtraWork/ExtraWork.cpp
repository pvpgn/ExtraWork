/*
*	ExtraWork - Allows PvPGN clients to load this DLL and executes code for specific clients
*	Copyright (C) 2014  xboi209 (xboi209@gmail.com)
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <TlHelp32.h>
#include "ExtraWork.h"

BOOL __cdecl ExtraWork(EXTRAWORK inStruct);
void sexp();
void w3xp();
void d2xp();
BOOL CALLBACK enumWindowsProc(HWND hWnd, LPARAM lParam);

BOOL __cdecl ExtraWork(EXTRAWORK inStruct)
{
	game.pid = GetCurrentProcessId();
	game.handle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_DUP_HANDLE | PROCESS_QUERY_INFORMATION | PROCESS_SET_INFORMATION | PROCESS_SUSPEND_RESUME | PROCESS_TERMINATE | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, game.pid);
	EnumWindows((WNDENUMPROC)enumWindowsProc, NULL);
	GetClassName(game.hWnd, (LPTSTR)game.classname, 256/*number of characters, not bytes*/);

	//Check what the game is and call a function specifically for that game
	if (strcmp(game.classname, SEXP) == 0)
		sexp();
	else if (strcmp(game.classname, W3XP) == 0)
		w3xp();
	else if (strcmp(game.classname, D2XP) == 0)
		d2xp();
	else
		return FALSE;

	return TRUE;
}


void sexp()
{
	return;
}

void w3xp()
{
	return;
}

void d2xp()
{
	return;
}

BOOL CALLBACK enumWindowsProc(HWND hWnd, LPARAM lParam)
{
	DWORD tempPID;
	char className[256];

	GetWindowThreadProcessId(hWnd, &tempPID);

	if (tempPID == game.pid)
	{
		GetClassName(hWnd, className, 256/*number of characters, not bytes*/);

		for (int i = 0; i < classNameElementSize; ++i)
		{
			if (strcmp(classNames[i], className) == 0)
			{
				game.hWnd = hWnd;
				return FALSE;
			}
		}
	}

	return TRUE;
}