#include "FileManager.h"

/* Loads */
void LoadCharacters()
{
    LoadSurvivors();
    LoadKillers();
}

/* Loads the survivors name from its file */
void LoadSurvivors()
{
    FILE* file = fopen(ASSETS_PATH"characters/Survivors.txt", "r");
    
    if (file == NULL)
    {
        printf("Error: Unable to open the Survivors file.\n");
        return;
    }

    // update if a new survivor is added to the game
    // 884 = max number of characters in the file
    char* survivorsFile = malloc(884 * sizeof(char));

    if (survivorsFile == NULL)
    {
        printf("Error: Unable to allocate memory for the survivors file.\n");
        return;
    }

    int i = 0;
    while (fgets(survivorsFile, MAX_LINES_CHARACTERS, file))
    {
        char* before = strtok(survivorsFile, ":");
        char* after = strtok(NULL, ":");

        strcpy_s(characters.survivorsId[i], MAX_LINES_CHARACTERS, before);
        strcpy_s(characters.survivorsName[i], MAX_LINES_CHARACTERS, after);
        i++;
    }

    free(survivorsFile);
    fclose(file);
}

/*
* Get the survivor's portrait with his id
* @param survivorId The id of the survivor
* @return Return a Texture2D of the survivor's portrait
*/
Texture2D GetSurvivorImage(const char* survivorId)
{
    char* srcImg = "";
    strcpy(srcImg, ASSETS_PATH "images/survivors/");
    strcat(srcImg, survivorId);
    strcat(srcImg, ".png");

    Image img = LoadImage(srcImg);
    ImageResize(&img, img.width / 5, img.height / 5);

    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);

    return texture;
}

/*
* Get the survivor's name with his id
* @param survivorId The id of the survivor
* @return Return a string with the survivor's name
*/
char* GetSurvivorName(const char* survivorId)
{
    int i = 0;

    while (strcmp(survivorId, characters.survivorsId[i]) != 0)
        i++;

    if (i == MAX_SURVIVORS)
        return "Error";

    return characters.survivorsName[i];
}

/* Loads the killers name from its file */
void LoadKillers()
{
    FILE* file = fopen(ASSETS_PATH"characters/Killers.txt", "r");

    if (file == NULL)
    {
        printf("Error: Unable to open the Killers file.\n");
        return;
    }

    // update if a new killer is added to the game
    // 799 = max number of characters in the file
    char* killersFile = malloc(799 * sizeof(char));

    if (killersFile == NULL)
    {
        printf("Error: Unable to allocate memory for the killers file.\n");
        return;
    }

    int i = 0;
    while (fgets(killersFile, MAX_LINES_CHARACTERS, file))
    {
        char* before = strtok(killersFile, ":");
        char* after = strtok(NULL, ":");

        strcpy_s(characters.killersId[i], MAX_LINES_CHARACTERS, before);
        strcpy_s(characters.killersName[i], MAX_LINES_CHARACTERS, after);
        i++;
    }

    free(killersFile);
    fclose(file);
}

/*
* Get the killer's portrait with his id
* @param killerId The id of the killer
* @return Return a Texture2D of the killer's portrait
*/
Texture2D GetKillerImage(const char* killerId)
{
    char* srcImg = "";
    strcpy(srcImg, ASSETS_PATH"images/killers/");
    strcat(srcImg, killerId);
    strcat(srcImg, ".png");

    Image img = LoadImage(srcImg);
    ImageResize(&img, img.width / 5, img.height / 5);

    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);

    return texture;
}

/*
* Get the killer's name with his id
* @param killerId The id of the killer
* @return Return a string with the killer's name
*/
char* GetKillerName(const char* killerId)
{
    int i = 0;

    while (strcmp(killerId, characters.killersId[i]) != 0)
        i++;

    if (i == MAX_KILLERS)
        return "Error";

    return characters.killersName[i];
}

/*
* Prints in the terminal all the survivors with their id and name
*/
void PrintSurvivors()
{
    for (size_t i = 0; i < MAX_SURVIVORS; i++)
    {
        printf("%s : %s", characters.survivorsId[i], characters.survivorsName[i]);
    }
}

/*
* Prints in the terminal all the killers with their id and name
*/
void PrintKillers()
{
    for (size_t i = 0; i < MAX_KILLERS; i++)
    {
        printf("%s : %s", characters.killersId[i], characters.killersName[i]);
    }
}

/*
* Loads the Survivor and Killer Perks
*/
void LoadPerks()
{
    LoadSurvivorPerks();
    LoadKillerPerks();
}

/* Load the Survivors perks from its file  */
void LoadSurvivorPerks()
{
    FILE* file = fopen(ASSETS_PATH"perks/Survivor.txt", "r");

    if (file == NULL)
    {
        printf("Error: Unable to open the Perks Survivor file.\n");
        return;
    }

    // 2325 = max number of characters in the file
    char* survivorPerksFile = malloc(2325 * sizeof(char));

    if (survivorPerksFile == NULL)
    {
        printf("Error: Unable to allocate memory for the survivor perks file.\n");
        return;
    }

    int i = 0;
    while (fgets(survivorPerksFile, MAX_LINES_CHARACTERS, file))
    {
        strcpy_s(perks.survivorPerks[i], MAX_LINES_CHARACTERS, survivorPerksFile);
        i++;
    }

    free(survivorPerksFile);
    fclose(file);
}

/* Load the Killer Perks from its file */
void LoadKillerPerks()
{
    FILE* file = fopen(ASSETS_PATH"perks/Killer.txt", "r");

    if (file == NULL)
    {
        printf("Error: Unable to open the Perks Killer file.\n");
        return;
    }

    // 2217 = max number of characters in the file
    char* killerPerksFile = malloc(2217 * sizeof(char));

    if (killerPerksFile == NULL)
    {
        printf("Error: Unable to allocate memory for the killer perks file.\n");
        return;
    }

    int i = 0;
    while (fgets(killerPerksFile, MAX_LINES_CHARACTERS, file))
    {
        strcpy_s(perks.killerPerks[i], MAX_LINES_CHARACTERS, killerPerksFile);
        i++;
    }

    free(killerPerksFile);
    fclose(file);
}

/* 
* Return the name of a survivor perk with its index
* @param i The index of the survivor perk
* @return Returns the name of the survivor perk
*/
char* GetSurvivorPerk(int i)
{
    return perks.survivorPerks[i];
}

/*
* Return the name of a killer perk with its index
* @param i The index of the killer perk
* @return Returns the name of the killer perk
*/
char* GetKillerPerk(int i)
{
    return perks.killerPerks[i];
}

/* Load maps from the maps folder */
void LoadMaps()
{
    FILE* file = fopen(ASSETS_PATH"maps/Maps.txt", "r");

    if (file == NULL)
    {
        printf("Error: Unable to open the Maps file.\n");
        return;
    }

    // 812 = max number of characters in the file
    char* mapsFile = malloc(812 * sizeof(char));

    if (mapsFile == NULL)
    {
        printf("Error: Unable to allocate memory for the Maps file.\n");
        return;
    }

    int i = 0;
    while (fgets(mapsFile, MAX_LINES_CHARACTERS, file))
    {
        char* before = strtok(mapsFile, ":");
        char* after = strtok(NULL, ":");

        strcpy_s(maps.mapsId[i], MAX_LINES_CHARACTERS, before);
        strcpy_s(maps.mapsName[i], MAX_LINES_CHARACTERS, after);
        i++;
    }

    free(mapsFile);
    fclose(file);
}

/*
* Get the map's portrait with his id
* @param mapId The id of the map
* @return Return a Texture2D of the map's portrait
*/
Texture2D GetMapImage(const char* mapId)
{
    char srcImg[500];
    strcpy(srcImg, ASSETS_PATH "images/maps/");
    strcat(srcImg, mapId);
    strcat(srcImg, ".png");

    Image img = LoadImage(srcImg);
    ImageResize(&img, img.width / 5, img.height / 5);

    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);

    return texture;
}

/*
* Get the map's name with his id
* @param mapId The id of the map
* @return Return a string with the map's name
*/
char* GetMapName(const char* mapId)
{
    int i = 0;
    while (strcmp(mapId, maps.mapsId[i]) != 0)
        i++;

    if (i == MAX_SURVIVORS)
        return "Error";

    return maps.mapsName[i];
}