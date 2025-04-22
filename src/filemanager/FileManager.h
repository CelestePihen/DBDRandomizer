#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

// change if a new character, perk or map + their id is longer than 60 characters on a line
#define MAX_LINES_CHARACTERS 60

/* ------------------------   CHARACTERS   ------------------------ */

// change if a new character is added
#define MAX_SURVIVORS 45
#define MAX_KILLERS 38

typedef struct Characters
{
	char killersId[MAX_KILLERS][MAX_LINES_CHARACTERS];
	char killersName[MAX_KILLERS][MAX_LINES_CHARACTERS];

	char survivorsId[MAX_SURVIVORS][MAX_LINES_CHARACTERS];
	char survivorsName[MAX_SURVIVORS][MAX_LINES_CHARACTERS];
} Characters;

Characters characters;

void LoadCharacters();
void LoadSurvivors();
void LoadKillers();

Texture2D GetSurvivorImage(const char* survivorId);
char* GetSurvivorName(const char* survivorId);

Texture2D GetKillerImage(const char* killerId);
char* GetKillerName(const char* killerId);

void PrintSurvivors();
void PrintKillers();

/* ---------------------------   PERKS  ---------------------------- */

#define MAX_PERKS_KILLER 127
#define MAX_PERKS_SURVIVOR 149

typedef struct Perks
{
	char killerPerks[MAX_PERKS_KILLER][MAX_LINES_CHARACTERS];
	char survivorPerks[MAX_PERKS_SURVIVOR][MAX_LINES_CHARACTERS];
} Perks;

Perks perks;

void LoadPerks();
void LoadSurvivorPerks();
void LoadKillerPerks();

char* GetSurvivorPerk(int r);
char* GetKillerPerk(int r);

/* ---------------------------   MAPS  ---------------------------- */
#define MAX_MAPS 24

typedef struct Maps
{
	char mapsId[MAX_MAPS][MAX_LINES_CHARACTERS];
	char mapsName[MAX_MAPS][MAX_LINES_CHARACTERS];
} Maps;

Maps maps;

void LoadMaps();
Texture2D GetMapImage(const char* mapId);
char* GetMapName(const char* mapId);