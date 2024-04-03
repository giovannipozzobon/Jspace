#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "api.h"
#include "quicksort.h"
#include "sprite.h"
#include "global.h"

const unsigned char nameFileGfx[] = {12, 'g', 'r', 'a', 'p', 'h', 'i', 'c', 's', '.', 'g', 'f', 'x'};
const unsigned char nameFileLog[] = {10, 'j', 's', 'p', 'a', 'c', 'e', '.', 'l', 'o', 'g'};

volatile unsigned char nameFileSplahsScreen[] = {9, 's', 'l', 'i', 'd', 'e', '0', '.', 'c', '0'};
volatile unsigned char nameFileSplahsPalette[] = {10, 's', 'l', 'i', 'd', 'e', '0', '.', 'p', 'a', 'l'};

volatile unsigned int score, enemy_destroyed, fire_enemy;
volatile int level, lifes_player;
volatile int Hit_Enemy = -1;
volatile int scroll_pointer = 0, room_active = 0;
unsigned char *ptr_room; // the room active
char buffer[41];
char bufferLog[51];
unsigned char *bufImg = (unsigned char *)0x7000;


// total of enemies in the actual level
int total_enemies_level;

// file name of levels
const unsigned char fileNameLevel[6][11] = {
	{10, 'l', 'e', 'v', 'e', 'l', '0', '.', 'b', 'i', 'n'},
	{10, 'l', 'e', 'v', 'e', 'l', '1', '.', 'b', 'i', 'n'},
	{10, 'l', 'e', 'v', 'e', 'l', '2', '.', 'b', 'i', 'n'},
	{10, 'l', 'e', 'v', 'e', 'l', '3', '.', 'b', 'i', 'n'},
	{10, 'l', 'e', 'v', 'e', 'l', '4', '.', 'b', 'i', 'n'},
	{10, 'l', 'e', 'v', 'e', 'l', '5', '.', 'b', 'i', 'n'},
};

// name and points of 10 top scores
unsigned char TopScoreName[NR_SCORE][NR_SUBJECTS] = {
	{15, 'n', 'a', 'm', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{15, 'n', 'a', 'm', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{15, 'n', 'a', 'm', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{15, 'n', 'a', 'm', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{15, 'n', 'a', 'm', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{15, 'n', 'a', 'm', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{15, 'n', 'a', 'm', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{15, 'n', 'a', 'm', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{15, 'n', 'a', 'm', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{15, 'n', 'a', 'm', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
};

unsigned int TopScorePoints[NR_SCORE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // points divide for 10
unsigned int TopScoreOrderedIndex[NR_SCORE];							// array of indexes of ordered score

// filename of points and name
const unsigned char nameFileNameScore[] = {9, 's', 'c', 'o', 'r', 'e', 'n', 'a', 'm', 'e'};
const unsigned char nameFilePointsScore[] = {10, 's', 'c', 'o', 'r', 'e', 'p', 'o', 'i', 'n', 't'};

char playerName[16] = {15, 'n', 'a', 'm', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

// Type and qty of enemy for every level
// the order is SPACESHIP, AIRCRAFT, SPACESHIP_ARRAY, GHOST

const uint8_t array_enemy_for_level[NR_OF_LEVEL][NR_TYPE_OF_ENEMY] = {

	{1, 1, 1, 1},
	{3, 3, 3, 0},
	{2, 3, 0, 4},
	{2, 3, 3, 2},
	{2, 3, 3, 2},	
	{3, 3, 2, 0}
};

// velocity of enimies
const uint8_t array_delay_enemies[NR_OF_LEVEL][2] = {
	{20, 3}, {10, 5}, {5, 5}, {10, 3}, {10, 5}, {15, 13}// nr loops to wait 
};

// map of screen
unsigned char map[1803];

// external reference of sprite
extern Missile missile_player;
extern Sprite enemies[];
extern Sprite player;
extern uint8_t count_missile_enemies;

// Funzione per verificare se un bit specifico è impostato in una variabile
uint8_t bit_check(uint8_t var, uint8_t pos)
{
	// Crea una maschera con un bit impostato nella posizione specificata
	uint8_t mask = 1 << pos;

	// Utilizza l'operatore AND bitwise per controllare il bit nella variabile
	if (var & mask)
	{
		return 1; // Il bit è impostato
	}
	else
	{
		return 0; // Il bit non è impostato
	}
}

void moveAllEnemies()
{
	int i;

	for (i = 0; i < total_enemies_level; i++)
	{
		// move the enemies
		moveEnemy(&enemies[i], &player);
		if (enemies[i].visible == true)
			MoveSprite(enemies[i].id, enemies[i].x, enemies[i].y);
	}
}

void LoadSplashScreen()
{
	int x, o;
	uint8_t y, c;

	c = 0;
	y = 0;
	x = 0;

	//	do {
	nameFileSplahsScreen[9] = c + 48; // write the value Ascii: 0 -> '0';
	LoadFile((int)bufImg, (unsigned char *)nameFileSplahsScreen);
	sprintf(buffer, "LoadSplashScreen: %s \n", nameFileSplahsScreen);
	WriteFile(LOG_FILE_CHANNEL, (int)&buffer, 50);
	o = 0;
	do
	{

		// SetColorNew(bufImg[o]);
		SetColor(0xf0, bufImg[o], 0, 0, 0);
		// SetColor(0xf0,buffer[o],0,0,0);  NeoSetColor(0,buffer[o],0,0,0);

		DrawPixel(x, y);
		x++;
		o++;
		if (x == SCREEN_WIDTH)
		{
			x = 0;
			y++;
		}

	} while ((y < SCREEN_HEIGHT) || (o < 0x8000));
	c++;

	//} while ((y<SCREEN_HEIGHT));
}

//Not used
void LoadPalette()
{
	uint16_t w;
	uint8_t b, result;

	result = LoadFile((int)bufImg, (unsigned char *)nameFileSplahsPalette);
	sprintf(buffer, "LoadPalette: %c %s \n", result, nameFileSplahsPalette);
	WriteFile(LOG_FILE_CHANNEL, (int)&buffer, 30);

	if (result != 0)
	{
		w = 0;
		for (b = 0; b <= 15; b++)
		{
			SetPalette(b, bufImg[w], bufImg[w + 1], bufImg[w + 2]);
			w += 3;
		}
		sprintf(buffer, "LoadPalette: file letto\n");
		WriteFile(LOG_FILE_CHANNEL, (int)&buffer, 23);
	}
}

void LoadResource()
{

	// Load graphics
	LoadGrafix(nameFileGfx);

	// load score point and name
	LoadFile((int)&TopScoreName, nameFileNameScore);
	LoadFile((int)&TopScorePoints, nameFilePointsScore);
}

bool checkFire(){
	uint8_t fire_button_A;
	fire_button_A = CheckJoypad();
	return bit_check(fire_button_A, 4);

}

void create_enemy()
{
	uint8_t i, nr_sprite_type_ghost = 0;

	// SPACESHIP
	for (i = 0; i < array_enemy_for_level[level - 1][0]; i++)
	{
		create_spaceship(&enemies[total_enemies_level], total_enemies_level);
		total_enemies_level++;
	};

	// AIRCRAFT
	for (i = 0; i < array_enemy_for_level[level - 1][1]; i++)
	{
		create_aircraft(&enemies[total_enemies_level], total_enemies_level, array_delay_enemies[level - 1][1]);
		total_enemies_level++;
	};

	// SPACESHIP_ARRAY
	for (i = 0; i < array_enemy_for_level[level - 1][2]; i++)
	{
		create_spaceship_array(&enemies[total_enemies_level], total_enemies_level);
		total_enemies_level++;
	};

	// GHOST
	for (i = 0; i < array_enemy_for_level[level - 1][3]; i++)
	{
		create_ghost(&enemies[total_enemies_level], nr_sprite_type_ghost, total_enemies_level, array_delay_enemies[level - 1][0]);
		nr_sprite_type_ghost++;
		total_enemies_level++;
	};
}

void Initialise()
{

	lifes_player = NR_LIFES_PLAYER;
	score = 0;
	level = 1;
	enemy_destroyed = 0;
	total_enemies_level = 0;
	Hit_Enemy = -1;
	fire_enemy = NR_TIME_FIRE_ENEMY;

	ptr_room = &map[((0))];

	// Fix the length of Buffer Log to 50 chars
	bufferLog[50] = 50;

	// length fixed string
	buffer[0] = 40;

	// write to log
	// sprintf(buffer,"Routine: Initialise \n");
	// WriteFile(LOG_FILE_CHANNEL,(int) &buffer,50);

	SetColor(0xf0, 7, 1, 1, 0);

	create_enemy();

	// Iniziative and draw the player
	// TODO: impostare anche il centro dello sprite
	DrawSprite(player.id, player.x, player.y, player.image);

	// Iniziative room
	room_active = 0;
	ptr_room = map;
	scroll_pointer = 0;

	// Load the first map
	LoadFile((int)&map, fileNameLevel[level - 1]);

	// sound of explosion
	ResetChannelSound(0);
	PlaySoundChannel(0, SOUND_PLAYER_HIT);
}

bool Scroll()
{

	if (scroll_pointer >= LENGTH_SCROLL) {
		scroll_pointer = 0;
		//go to next level
		return true;
	}
	
	ptr_room = &map[0];
	SetCurrentTileMap(ptr_room, 0, LENGTH_SCROLL - SCREEN_HEIGHT - scroll_pointer);
	DrawTileMap(0, 0, 320, SCREEN_HEIGHT - DASHBOARD_HEIGHT);

	scroll_pointer++;
	return false;
}

void moveMissilePlayer()
{
	missile_player.y -= VELOCITY_MISSILE;
	if (missile_player.y <= 0)
	{
		HideSprite(missile_player.id);
		missile_player.y = 0;
	}
	else
		MoveSprite(missile_player.id, missile_player.x, missile_player.y);
}

void checkHitEnemy()
{
	int i;
	// check hit Missile_player with Emenies
	for (i = 0; i < NUM_ENEMIES; i++)
	{
		if (enemies[i].visible == true)
			if (DistanceSprites(missile_player.id, enemies[i].id, DISTANCE_HIT_SPRITE))
			{
				// sprintf(buffer," Enemy %1d is Hit", enemies[i].id);
				// Gfx_WriteString (20,230,buffer);
				Hit_Enemy = i;
			};
	}
}

void enemy_explosion()
{

	// hide missile
	HideSprite(ID_MISSILE);
	ResetChannelSound(0);
	PlaySoundChannel(0, SOUND_ENEMY_DESTROY);
	// change image (explosion) sprite enemy
	DrawSprite(enemies[Hit_Enemy].id, enemies[Hit_Enemy].x, enemies[Hit_Enemy].y, IMAGE_EXPLOSION1);
	nop_delay(2000);
	DrawSprite(enemies[Hit_Enemy].id, enemies[Hit_Enemy].x, enemies[Hit_Enemy].y, IMAGE_EXPLOSION2);
	nop_delay(2000);
	DrawSprite(enemies[Hit_Enemy].id, enemies[Hit_Enemy].x, enemies[Hit_Enemy].y, IMAGE_EXPLOSION3);
	nop_delay(2000);
	HideSprite(enemies[Hit_Enemy].id);
	enemies[Hit_Enemy].visible = false;
	missile_player.y = 0;

	score += POINT_DESTROY_ENEMY;
	Hit_Enemy = -1;
	enemy_destroyed++;
}

void player_explosion()
{

	// sound of explosion
	ResetChannelSound(0);
	PlaySoundChannel(0, SOUND_PLAYER_HIT);

	// change image (explosion) sprite player
	DrawSprite(player.id, player.x, player.y, IMAGE_EXPLOSION1);
	nop_delay(2000);
	DrawSprite(player.id, player.x, player.y, IMAGE_EXPLOSION2);
	nop_delay(2000);
	DrawSprite(player.id, player.x, player.y, IMAGE_EXPLOSION3);
	nop_delay(2000);

	DrawSprite(player.id, player.x, player.y, player.image);

	lifes_player--;
}

void print_dashboard_info()
{

	// the first byte of buffer is the lentgh of string (fixed length string)
	sprintf(buffer + 1, " LIFES: %1d      SCORE: %1d     LEVEL: %1d", lifes_player, score, level);
	Gfx_WriteString(POS_DASHBOARD_INFO, SCREEN_HEIGHT - DASHBOARD_HEIGHT, buffer);
}

void checkPositionPlayer()
{
	// check the position.If it's out of screen or in the board
	if (player.y > SCREEN_HEIGHT - DASHBOARD_HEIGHT - HEIGHT_SPRITE_FROM_BARICENTRE)
		player.y--;
	if ((player.y - HEIGHT_SPRITE_FROM_BARICENTRE) < 0)
		player.y++;
	if (player.x > SCREEN_WIDTH - WIDTH_SPRITE_FROM_BARICENTRE)
		player.x--;
	if ((player.x - WIDTH_SPRITE_FROM_BARICENTRE) < 0)
		player.x++;
}

void nextLevel()
{
	uint8_t result;

	ClearKeyboardArray();
	clrscr();
	ResetSprite();
	gotoxy(16, 10);
	cputc(0x81);
	sprintf(buffer, "YOU PASS LEVEL %1d", level-1);
	puts(buffer);
	gotoxy(5, 20);
	cputc(143);
	puts("PRESS RETURN OR FIRE TO GO TO NEXT LEVEL");

	result = LoadFile((int)&map, fileNameLevel[level - 1]);

	nop_delay(DELAY_SCREEN);
	while ((cgetc() != 13) && (checkFire()==0)); 


	// sprintf(buffer,"Error: %1d", result);
	// Gfx_WriteString (260,230,buffer);
	enemy_destroyed = 0; // reset the number of enemies destroyed
	scroll_pointer = 0;	 // start again from the beginning
	total_enemies_level = 0;
	Hit_Enemy = -1;
	fire_enemy = NR_TIME_FIRE_ENEMY;
	ResetSprite();
	create_enemy();
	DrawSprite(player.id, player.x, player.y, player.image);
	SetColor(0xf0, 7, 1, 1, 0);
}

void insertName()
{
	uint8_t i, key;

	SetColor(0xff, 2, 1, 1, 0);
	DrawRectangle(10, 10, 300, 220);

	// ClearScreen();

	SetColor(0xf0, 2, 1, 1, 0);
	// print scores
	for (i = 0; i < NR_SCORE; i++)
	{
		sprintf(buffer + 1, " %s", TopScoreName[i]);
		Gfx_WriteString(10, 15 * i, buffer);
	}

	i = 0;
	buffer[0] = 1;
	key = (char)cgetc();
	while ((key != 13) && (i <= 15))
	{
		i++;
		key = (char)cgetc();
		sprintf(buffer + 1, "%c", key);
		Gfx_WriteString(10 + i * 7, 200, buffer);
	}

	/*
	gotoxy(10,10);
	for(i=0;i<NR_SCORE;i++){
		sprintf(buffer+1," NAMES: %s        SCORE: %s \n", TopScoreName[i], TopScorePoints[i]);
		puts (buffer);
	}


	gotoxy(200,10);
	key= (char) cgetc();
	while (key != 13){
		key= (char) cgetc();
		cputc(key);
	}
	*/
}

void title_screen()
{
	uint8_t key, t, i = 1;

	// Clear screen
	clrscr();
	// Draw frame
	for (t = 0; t <= 20; t++)
	{
		DrawImage(t * 16, 16, 0);
	};
	for (t = 0; t <= 20; t++)
	{
		DrawImage(t * 16, 200, 16);
	};

	// Draw Clouds
	//DrawImage(160,160,26); DrawImage(176,160,27);

	cputcxy(10, 10, 32);
	gotoxy(18, 9);
	cputc(134);
	puts("Neo6502  JSPACE2\n");
	nop_delay(DELAY_SCREEN);
	gotoxy(21, 10);
	cputc(143);
	puts("by @Jobond");
	gotoxy(8, 14);
	cputc(135);
	puts("Inserisci il tuo nome: ");
	gotoxy(31,14);
	key = cgetc();
	while ((key != 13) && (i < 15))
	{
		cputc(key);
		playerName[i] = key;
		key = cgetc();
		i++;
	}
	nop_delay(DELAY_SCREEN);
	cputc(0x81);
	gotoxy(20, 18);
	puts("Let's start!");
	cputc(0x87);
	gotoxy(16, 21);
	puts("PRESS RETURN OR FIRE");
	while ((cgetc() != 13) && (checkFire()==0)); 

	nop_delay(DELAY_SCREEN);
	clrscr();
}

bool game_over()
{
	uint8_t key,i;
	bool exit, stop =false;

	// Clear the array of keyboard
	ClearKeyboardArray();

	gotoxy(20, 2);
	puts("GAME OVER");
	nop_delay(DELAY_SCREEN);
	gotoxy(0, 5);
	puts(&playerName[1]);
	sprintf(buffer, " your score is: %3d", score);
	puts(buffer);
	// Score list
	for (i = 0; i < NR_SCORE + 1; i++)
	{
		write(TopScoreName[i - 1], 15);
		sprintf(buffer, "%3d", TopScorePoints[i - 1]);
		puts(buffer);
		gotoxy(0, 10 + i);
	} // TopScoreOrderedIndex TopScorePoints

	nop_delay(DELAY_SCREEN);
	cputc(0x81);
	gotoxy(40, 120);
	puts("Play again (y/n)?");
	nop_delay(DELAY_SCREEN);

	while(stop==false){
		key = cgetc();
		if ((key == 'n') || (key == 'N')) { exit =false; stop=true;};
		if ((key == 'y') || (key == 'Y')) { exit =true;  stop=true;};		
	}

	return exit;
}

void savePlayer_Score()
{
	int i;
	for (i = 0; i < 16; i++)
	{
		TopScoreName[NR_SCORE - 1][i] = playerName[i];
	}
	TopScorePoints[NR_SCORE - 1] = score;
}

bool playerWin()
{
	uint8_t key;
	int i;
	bool exit, stop=false;

	gotoxy(18, 2);
	cputc(0x81);
	puts("YOU FINISH THE GAME");
	nop_delay(DELAY_SCREEN);
	gotoxy(0, 5);
	cputc(0x87);
	sprintf(buffer, "%s your score is: %3d", &playerName[1], score);
	puts(buffer);
	gotoxy(0, 10);
	// Score list
	for (i = 0; i < NR_SCORE + 1; i++)
	{
		write(TopScoreName[i - 1], 15);
		sprintf(buffer, "%3d", TopScorePoints[i - 1]);
		puts(buffer);
		gotoxy(0, 10 + i);
	} // TopScoreOrderedIndex TopScorePoints

	// Clear the array of keyboard
	ClearKeyboardArray();
	puts(" ");
	cputc(0x81);
	gotoxy(40, 120);
	sprintf(buffer, "Play again (y/n)?");
	puts(buffer);
	nop_delay(DELAY_SCREEN);

	while(stop==false){
		key = cgetc();
		if ((key == 'n') || (key == 'N')) { exit =false; stop=true;};
		if ((key == 'y') || (key == 'Y')) { exit =true;  stop=true;};		
	}

	return exit;

}


bool playGame()
{
	uint8_t movement;
	bool exitWinner = false;

	while ((lifes_player > -1) && (exitWinner == false))
	{

		if (Scroll() == true) // change level if scroll returns true
		{
			level++;
			if (level > MAXLEVEL)
				exitWinner = true; // exit winner
			else nextLevel();
		}

		moveAllEnemies();
		if (count_missile_enemies > 0)
			moveMissileEnemy();

		if (missile_player.y != 0)
		{
			moveMissilePlayer();
			checkHitEnemy();
			if (Hit_Enemy > -1)
				enemy_explosion();
		}

		movement = CheckJoypad();

		if (bit_check(movement, 0))
		{
			player.x--;
		} // sprite_x =-1;
		if (bit_check(movement, 1))
		{
			player.x++;
		} // sprite_x =+1;
		if (bit_check(movement, 2))
		{
			player.y--;
		} // sprite_y =-1;
		if (bit_check(movement, 3))
		{
			player.y++;
		} // sprite_y =+1;
		if (bit_check(movement, 4))
		{
			missile_player.y = player.y - 8;
			missile_player.x = player.x;
			DrawSprite(missile_player.id, missile_player.x, missile_player.y, missile_player.image);
		} // Fire_A
		if (bit_check(movement, 5))
		{ // nothing for now
		} // Fire_B

		// ResetChannelSound(0);
		// PlaySoundChannel(0, SOUND_MOV_PLAYER);

		// check the position of player and then draw the sprite
		checkPositionPlayer();
		MoveSprite(player.id, player.x, player.y);

		if (checkHitPlayer())
			player_explosion();

		print_dashboard_info();

		nop_delay(DELAY_GAME);

	}

	return (exitWinner);
}

void clearScreenWriteScore()
{

	// save Player name and score
	savePlayer_Score();

	// Order the scores and save them
	quickSort(TopScorePoints, TopScoreOrderedIndex, 0, NR_SCORE - 1);
	//sortByIndex((TopScoreName[0][0]), TopScoreOrderedIndex);

	SaveFile((int)TopScoreName, sizeof(TopScoreName), nameFileNameScore);
	SaveFile((int)TopScorePoints, sizeof(TopScorePoints), nameFilePointsScore);

	// Reset Sprite and Clear Screen
	ResetSprite();
	clrscr();
}

void OpenSerialLog(){

	SetSpeed_ProtocolUART(SERIAL_SPEED);

}

int main(void)
{
	
	//Open the serial for log
	//OpenSerialLog();
	//WriteStringTolUART("Ciao");


	/*
	volatile unsigned char attendi = 0xff;
	volatile bool exitPrg = true;

	// Open Log File
	//OpenFile(LOG_FILE_CHANNEL, (int)&nameFileLog, 3);
	//neo_console_clear_screen();

	// Load resource file
	LoadResource();
	 
	 //Load Splash Screen
	 //ClearScreen();
	 //LoadPalette();
	 //LoadSplashScreen();

	title_screen();

	// Use current time as
	// seed for random generator
	srand(1);


	// Initialise the environment
	Initialise();

	while (exitPrg == true)
	{

		if (playGame())
		{
			clearScreenWriteScore();
			exitPrg=playerWin();
			if (exitPrg == true)
				//restart from the level 1
				Initialise();
		}	
		else
		{
			clearScreenWriteScore();
			exitPrg = game_over();
			if (exitPrg == true)
				//restart from the level 1
				Initialise();
		}
	}
*/
	// Clear the screen and return to basic
	clrscr();
	ReturnToBasic();

	return 0;
	

}