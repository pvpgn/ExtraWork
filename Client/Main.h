struct EXTRAWORK
{
	WORD GameType;
	WORD Length;
	char OutBuffer[1024];
};

enum GameType
{
	Diablo2 = 0x1,
	Warcraft3 = 0x2,
	Starcraft = 0x3,
	WorldOfWarcraft = 0x4
};

typedef BOOL(__fastcall *ExtraWorkProc)(void *);