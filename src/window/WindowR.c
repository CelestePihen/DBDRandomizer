#include "WindowR.h"

/*
 Start the application
*/
void RunApplication()
{
    LoadFileManager();

    enum Mode mode = CHARACTERS;
    enum Role role = SURVIVOR;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetRandomSeed(time(NULL));

    // App starts with a random survivor then the user can change to killer or can change the mode
    int randomNumber = GetRandomValue(0, MAX_SURVIVORS - 1);
    Texture2D displayImage = GetSurvivorImage(characters.survivorsId[randomNumber]);
    char* displayName = GetSurvivorName(characters.survivorsId[randomNumber]);

    while (!WindowShouldClose())
    {
		ManageInput(&role, &mode, &randomNumber, &displayImage, &displayName);
        Render(role, mode, displayImage, displayName);
    }

    UnloadTexture(displayImage);
    CloseWindow();
}

/* Loads the Texts and Images related to the game */
void LoadFileManager()
{
    LoadCharacters();
    LoadPerks();
    LoadMaps();
}

/* Manages the Input that the user can interact with. He can change the Mode, the Role and get a new character/perk/map */
void ManageInput(enum Role* role, enum Mode* mode, int* randomNumber, Texture2D* displayImage, char** displayName)
{
    if (IsKeyPressed(KEY_R))
    {
        UnloadTexture(*displayImage);

        if (*mode == PERKS)
        {
            if (*role == SURVIVOR)
            {
                int oldRandomNumber = *randomNumber;
                *randomNumber = GetRandomValue(0, MAX_PERKS_SURVIVOR - 1);

                while (oldRandomNumber == *randomNumber)
                {
                    *randomNumber = GetRandomValue(0, MAX_PERKS_SURVIVOR - 1);
                }

                *displayName = GetSurvivorPerk(*randomNumber);

                // TODO: I don't want to download and rename all the perks images
                Image img = LoadImage(ASSETS_PATH"perks/Survivor.png");
                ImageResize(&img, img.width / 5, img.height / 5);

                Texture2D texture = LoadTextureFromImage(img);
                UnloadImage(img);

                *displayImage = texture;
            }
            else
            {
                int oldRandomNumber = *randomNumber;
                *randomNumber = GetRandomValue(0, MAX_PERKS_KILLER - 1);

                while (oldRandomNumber == *randomNumber)
                {
                    *randomNumber = GetRandomValue(0, MAX_PERKS_KILLER - 1);
                }

                *displayName = GetKillerPerk(*randomNumber);

                // TODO: I don't want to download and rename all the perks images
                Image img = LoadImage(ASSETS_PATH"perks/Killer.png");
                ImageResize(&img, img.width / 5, img.height / 5);

                Texture2D texture = LoadTextureFromImage(img);
                UnloadImage(img);

                *displayImage = texture;
            }
        }
        else if (*mode == CHARACTERS)
        {
            if (*role == SURVIVOR)
            {
                int oldRandomNumber = *randomNumber;
                *randomNumber = GetRandomValue(0, MAX_SURVIVORS - 1);

                while (oldRandomNumber == *randomNumber)
                {
                    *randomNumber = GetRandomValue(0, MAX_SURVIVORS - 1);
                }

                *displayImage = GetSurvivorImage(characters.survivorsId[*randomNumber]);
                *displayName = GetSurvivorName(characters.survivorsId[*randomNumber]);
            }
            else
            {
                int oldRandomNumber = *randomNumber;
                *randomNumber = GetRandomValue(0, MAX_KILLERS - 1);

                while (oldRandomNumber == *randomNumber)
                {
                    *randomNumber = GetRandomValue(0, MAX_KILLERS - 1);
                }

                *displayImage = GetKillerImage(characters.killersId[*randomNumber]);
                *displayName = GetKillerName(characters.killersId[*randomNumber]);
            }
        }
        else
        {
            int oldRandomNumber = *randomNumber;
            *randomNumber = GetRandomValue(0, MAX_MAPS - 1);

            while (oldRandomNumber == *randomNumber)
            {
                *randomNumber = GetRandomValue(0, MAX_MAPS - 1);
            }

            *displayName = GetMapName(maps.mapsId[*randomNumber]);
            *displayImage = GetMapImage(maps.mapsId[*randomNumber]);
        }
    }

    if (*mode != MAPS && IsKeyPressed(KEY_E))
    {
        if (*role == SURVIVOR)
        {
            *role = KILLER;
        }
        else
        {
            *role = SURVIVOR;
        }
    }

    if (IsKeyPressed(KEY_T))
    {
        if (*mode == CHARACTERS)
        {
            *mode = PERKS;
        }
        else if (*mode == PERKS)
        {
            *mode = MAPS;
        }
        else
        {
            *mode = CHARACTERS;
        }
    }
}

/* Renders the Texts and Image */
void Render(enum Role role, enum Mode mode, Texture2D displayImage, char* displayName)
{
    int widthText = 0;
    
    // Draw to screen
    BeginDrawing();

    ClearBackground(DARKGRAY);

    // Draw important variables
    // Role
    if (mode != MAPS)
    {
        if (role == SURVIVOR)
        {
            widthText = MeasureText("Rôle: Survivant", 20);
            DrawText("Rôle: Survivant", SCREEN_WIDTH / 2 - widthText / 2, 10, 20, WHITE);
        }
        else
        {
            widthText = MeasureText("Rôle: Tueur", 20);
            DrawText("Rôle: Tueur", SCREEN_WIDTH / 2 - widthText / 2, 10, 20, WHITE);
        }
    }

    // Mode
    if (mode == PERKS)
    {
        widthText = MeasureText("Mode: Perks", 20);
        DrawText("Mode: Perks", SCREEN_WIDTH / 2 - widthText / 2, 30, 20, WHITE);
    }
    else if (mode == CHARACTERS)
    {
        widthText = MeasureText("Mode: Personnages", 20);
        DrawText("Mode: Personnages", SCREEN_WIDTH / 2 - widthText / 2, 30, 20, WHITE);
    }
    else
    {
        widthText = MeasureText("Mode: Maps", 20);
        DrawText("Mode: Maps", SCREEN_WIDTH / 2 - widthText / 2, 30, 20, WHITE);
    }

    // Draw displayImage and displayName
    DrawTexture(displayImage, SCREEN_WIDTH / 2 - displayImage.width / 2, SCREEN_HEIGHT / 2 - displayImage.height / 2 - 20, WHITE);

    widthText = MeasureText(displayName, 20);
    DrawText(displayName, SCREEN_WIDTH / 2 - widthText / 2, SCREEN_HEIGHT / 2 + 100, 20, WHITE);

    // Draw hints
    widthText = MeasureText("Appuie sur R pour changer l'aléatoire.", 20);
    DrawText("Appuie sur R pour changer l'aléatoire.", SCREEN_WIDTH / 2 - widthText / 2, SCREEN_HEIGHT / 2 + 150, 20, WHITE);

    if (mode != MAPS)
    {
        widthText = MeasureText("Appuie sur E pour changer de camp.", 20);
        DrawText("Appuie sur E pour changer de camp.", SCREEN_WIDTH / 2 - widthText / 2, SCREEN_HEIGHT / 2 + 170, 20, WHITE);
    }

    widthText = MeasureText("Appuie sur T pour changer de mode.", 20);
    DrawText("Appuie sur T pour changer de mode.", SCREEN_WIDTH / 2 - widthText / 2, SCREEN_HEIGHT / 2 + 190, 20, WHITE);

    EndDrawing();
}