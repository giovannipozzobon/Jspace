#include <stdio.h>
#include <stdbool.h>
#include "global.h"
#include "pista1.h"
#include "api.h"



const unsigned char nameFileGfx[] = {12, 'g', 'r', 'a', 'p', 'h', 'i', 'c', 's', '.', 'g', 'f', 'x'};

int scroll_pointer = 0, room_active = 0;
unsigned char *ptr_room; // the room active
// map of screen
unsigned char map[1803];

void LoadResource()
{

	// Load graphics
	LoadGrafix(nameFileGfx);

}

bool Scroll()
{
    uint8_t i;

	if (scroll_pointer > (LENGTH_SCROLL- (SCREEN_HEIGHT- DASHBOARD_HEIGHT))) {
		scroll_pointer = 0;
		//go to next level
		//return true;
	}   


	ptr_room = (unsigned char *) &pista1[0];
	SetCurrentTileMap(ptr_room, 0, LENGTH_SCROLL - SCREEN_HEIGHT - scroll_pointer);
	DrawTileMap(0, 0, 320, SCREEN_HEIGHT - DASHBOARD_HEIGHT);

	scroll_pointer++;
	return false;
}

void Initialise()
{

	SetColor(0xf0, 7, 1, 1, 0);

	// sound of explosion
	ResetChannelSound(0);
	PlaySoundChannel(0, SOUND_PLAYER_HIT);
}

// Funzione principale
int main() {
	
    // Load resource file
	LoadResource();    

    while(1) {
        nop_delay(1000);
        Scroll();
    }

}