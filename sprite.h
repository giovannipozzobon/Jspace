#include <stdint.h>
#include <stdbool.h>
#include "global.h"


typedef struct {
	uint8_t id;
    int x, y;
    uint8_t image;
   	uint8_t nr_on_type; //number of sprite inside gruop of sprite of the type Use only by th enemy
	uint8_t type;
	uint8_t array;
	int delay; // wait X ciclies before move
	int count_delay; // wait X ciclies before move
	bool visible;
	uint8_t ptr_mov;
	uint8_t count_down_fire;// pointer of mov array (only for enemy SPACESHIP)
	uint8_t count_down_fire_orig;
} Sprite;

typedef struct {
	uint8_t id;
    int x, y; // When Y=0 Missile is deactived
    uint8_t image;
	uint8_t delay; // wait X ciclies before move
	bool visible;
	uint8_t count_down_fire;

} Missile;


void create_spaceship(Sprite *sprite, int index);

void create_aircraft(Sprite *sprite, int index, uint8_t delay);

void create_spaceship_array(Sprite *sprite, int index);

void create_ghost(Sprite *sprite, uint8_t nr_sprite_type_ghost, int index, uint8_t delay);

void moveEnemy(Sprite *enemy, Sprite *player);

void moveMissileEnemy();

int checkHitPlayer();
