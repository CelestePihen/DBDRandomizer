#pragma once

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define SCREEN_TITLE "DBD Randomizer"

#include <time.h>
#include <stdlib.h>
#include <raylib.h>

#include "../filemanager/FileManager.h"

enum Mode
{
	CHARACTERS,
	PERKS,
	MAPS
};

enum Role
{
	KILLER,
	SURVIVOR
};

void RunApplication();
void LoadFileManager();
void ManageInput(enum Role* role, enum Mode* mode, int* randomNumber, Texture2D* displayImage, char** displayName);
void Render(enum Role role, enum Mode mode, Texture2D displayImage, char* displayName);