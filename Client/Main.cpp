/*
*	ExtraWork Client - Loads an ExtraWork DLL for information
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

#include <Windows.h>
#include <iostream>
#include <cstdlib>

using namespace std;

struct EXTRAWORK
{
	WORD GameType;
	WORD Length;
	char OutBuffer[1024];
};

typedef BOOL(__fastcall *ExtraWorkProc)(void *);

enum GameType
{
	Diablo2 = 0x1,
	Warcraft3 = 0x2,
	Starcraft = 0x3,
	WorldOfWarcraft = 0x4
};

//Example:	Client IX86ExtraWork.dll 0x3 4
//			Program DLL Gametype Length
int main(int argc, char ** argv)
{
	HINSTANCE		hLib;
	ExtraWorkProc	lpfnExtraWork;
	BOOL			bReturn;
	EXTRAWORK		ew;

	if (argc == 1)
	{
		argv[1] = "IX86ExtraWork.dll";
		argv[2] = "0x3";
		argv[3] = "4";
	}
	else if (argc != 1 && argc != 4)
	{
		cout << "Invalid number of arguments" << endl;
		return 0;
	}


	hLib = LoadLibrary(argv[1]);

	bool success = false;
	if (hLib)
	{
		lpfnExtraWork = (ExtraWorkProc)GetProcAddress(hLib, "ExtraWork");
		ew.GameType = (WORD)strtoul(argv[2], NULL, 16);
		ew.Length = atoi(argv[3]);
		*ew.OutBuffer = 0;

		if (lpfnExtraWork)
		{
			bReturn = (*lpfnExtraWork)(&ew);

			cout << "ExtraWork returned " << (bReturn ? "TRUE" : "FALSE") << endl;
			cout << "GameType: " << ew.GameType << "\t\t" << "Length: " << ew.Length << endl << endl;
			cout << "Message: " << ew.OutBuffer << endl;

			success = true;
		}
		FreeLibrary(hLib);
	}


	if (!success)
		cout << "Could not load " << argv[1] << endl;


	return 0;
}