#include <stdlib.h>
#include <stdbool.h>
#include "sprite.h"
#include "api.h"

volatile Missile missile_enemies[NUM_ENEMIES];
volatile Missile missile_player = {ID_MISSILE,0,0,IMAGE_MISSILE,0};
volatile Sprite enemies[NUM_ENEMIES];
volatile Sprite player = {ID_PLAYER, FIRST_POS_X_PLAYER,FIRST_POS_Y_PLAYER, IMAGE_PLAYER};
volatile uint8_t count_missile_enemies;

int enemyMovements[NR_SPACESHIP_ARRAY][2] = { // array for SPACESHIP_ARRAY
	{-1, 0}, // Enemy 1 moves left 
	{0, -1}, // Enemy 2 moves up
	{1, 0},   // Enemy 3 moves rigth
	{0, 1}   // Enemy 4 moves down
};


int path_ghost[NR_GHOST][10][2]= 
{
	{{20, 20}, {50, 50}, {120, 120}, {100, 200}, {300, 50}, {55, 128}, {260, 67}, {107, 45}, {88, 5}, {250, 102}},
	{{190, 190}, {191, 191}, {192, 192}, {193, 193}, {194, 194}, {195, 195}, {196, 196}, {197, 197}, {198, 198}, {199, 199}},
	{{300, 100}, {200, 106}, {305, 23}, {59, 200}, {90, 4}, {134, 55}, {230, 189}, {111, 111}, {270, 167}, {78, 134}},
	{{10, 60}, {61, 01}, {12, 12}, {163, 163}, {64, 200}, {200, 165}, {166, 97}, {107, 207}, {18, 18}, {69, 69}},
	{{10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}}

}; //path



void spriteCommonInfo (Sprite *enemy, int index){
	int rnd;
	
	enemy->id=index+SHIFT_ID_ENEMIES; // Add 2 because 0 e 1 are player and player's missile
	rnd=rand() % (SCREEN_WIDTH);
	if (rnd > SCREEN_WIDTH-DISTANCE_HIT_SPRITE) rnd-=20;
	enemy->x = rnd;
	rnd=rand() % (SCREEN_HEIGHT);
	if (rnd > SCREEN_HEIGHT-DASHBOARD_HEIGHT-DISTANCE_HIT_SPRITE) rnd-=20;
	enemy->y = rnd;
	enemy->count_down_fire = (rand() % SCREEN_WIDTH)*100;
	enemy->count_down_fire_orig = enemy->count_down_fire;

}

void create_spaceship(Sprite *sprite, int index){
	spriteCommonInfo (sprite, index);
    sprite->type = SPACESHIP; 
    sprite->ptr_mov= rand()%150;
    sprite->image = IMAGE_ENEMY;
	sprite->visible=true; // make enemy visible
	DrawSprite(sprite->id, sprite->x, sprite->y, sprite->image);
};

void create_aircraft(Sprite *sprite, int index, uint8_t delay){
	spriteCommonInfo (sprite, index);
    sprite->type = AIRCRAFT; 
    sprite->delay=delay;
	sprite->count_delay=delay;
    sprite->image = IMAGE_ENEMY;
	sprite->visible=true; // make enemy visible   
	DrawSprite(sprite->id, sprite->x, sprite->y, sprite->image); 
};

void create_spaceship_array(Sprite *sprite, int index){
    uint8_t nr_array;

	spriteCommonInfo (sprite, index);
    if (index<4) 
        {nr_array=index;} 
    else 
        {nr_array=index/4;} // 4 is the size of movement array
    
    sprite->type = SPACESHIP_ARRAY;
    sprite->array=nr_array;
    sprite->image = IMAGE_ENEMY;
	sprite->visible=true; // make enemy visible
	DrawSprite(sprite->id, sprite->x, sprite->y, sprite->image);
    //sprintf(buffer," E.array: %1d  E.x: %1d  E.y: %1d", enemies[i].array, enemies[i].x, enemies[i].y); 
    //Gfx_WriteString (20,230,buffer);

};

void create_ghost(Sprite *sprite, uint8_t nr_sprite_type_ghost, int index, uint8_t delay){

    spriteCommonInfo (sprite, index);
	sprite->type = GHOST;
    sprite->array=0; 
    sprite->delay=delay*10; 
	sprite->count_delay=delay;
    sprite->nr_on_type=nr_sprite_type_ghost; 
    sprite->image = IMAGE_GHOST;
	sprite->visible=true; // make enemy visible
	DrawSprite(sprite->id, sprite->x, sprite->y, sprite->image);    
};



 void changeDirectionEnemyArray(Sprite *enemy){
	
	enemyMovements[enemy->array][0] = enemyMovements[enemy->array][0] * -1;
	enemyMovements[enemy->array][1] = enemyMovements[enemy->array][1] * -1;

}


void changeDirectionEnemy(int nr_enemies){
	
	enemyMovements[nr_enemies][0] = enemyMovements[nr_enemies][0] * -1;
	enemyMovements[nr_enemies][1] = enemyMovements[nr_enemies][1] * -1;

}


void moveMissile(Sprite *enemy){
    uint8_t count;

	count = enemy->id-SHIFT_ID_ENEMIES;
	if ((enemy->count_down_fire<=0) && (enemy->visible==true) && (missile_enemies[count].visible==false)) {
		
		//create the missile only if the enemy is not near the bottom border
		if (enemy->y < SCREEN_HEIGHT-DASHBOARD_HEIGHT) {
			missile_enemies[count].id=PLACEHOLDER_ENEMY+count;	
			missile_enemies[count].visible=true;
			missile_enemies[count].x = enemy->x;
			missile_enemies[count].y = enemy->y+HEIGHT_SPRITE_FROM_BARICENTRE;
			missile_enemies[count].image = IMAGE_FIRE_ENEMY;
			DrawSprite(missile_enemies[count].id, missile_enemies[count].x, missile_enemies[count].y, missile_enemies[count].image);
			enemy->count_down_fire = enemy->count_down_fire_orig;
			count_missile_enemies ++;
			
			//sprintf(buffer," Enemy Fires "); 
			//Gfx_WriteString (160,230,buffer);		
		}
	};
}

void moveMissileEnemy(){
	uint8_t  i;

	for (i = 0; i < NR_MAX_MISSILE_ENEMY; i++)
	{
		if (missile_enemies[i].visible==true) {
			missile_enemies[i].y+=VELOCITY_MISSILE;
			if (missile_enemies[i].y>=SCREEN_HEIGHT-DASHBOARD_HEIGHT-DASHBOARD_HEIGHT) 
			{
				missile_enemies[i].visible=false;	
				HideSprite(missile_enemies[i].id);
				count_missile_enemies --;
			}
			else 
				MoveSprite(missile_enemies[i].id, missile_enemies[i].x, missile_enemies[i].y);
		} 
		
	}
}


void moveEnemy(Sprite *enemy, Sprite *player) {

	uint8_t rnd;

	// countdown for enimies fire a missile
	enemy->count_down_fire--;

    // SPACESHIP is random
	if(enemy->type == SPACESHIP) {
		/*  ***** TODO A NEW KIND OF ENEMY *****
		seemes not work fine *TODO:rework the alghoritim
 		enemy->ptr_mov ++;
		enemy->x = sinusoid_values[enemy->ptr_mov][0];
		enemy->y = sinusoid_values[enemy->ptr_mov][1];
		*/ 
		rnd = (rand() % (4)) + 1; 
		if(rnd == 4) enemy->x-=1;
		if(rnd == 2) enemy->x+=1;
		if(rnd == 1) enemy->y-=1;
		if(rnd == 3) enemy->y+=1;

		// check the position.If it's out of screen or in the board
		if (enemy->y >= SCREEN_HEIGHT-DASHBOARD_HEIGHT-HEIGHT_SPRITE_FROM_BARICENTRE) enemy->y--;
		if (enemy->y <=0) enemy->y++;
		if (enemy->x >= SCREEN_WIDTH-WIDTH_SPRITE_FROM_BARICENTRE) enemy->x--;
		if (enemy->x <=0) enemy->x++;

	}

	// AIRCRAFT goes for player
	if(enemy->type == AIRCRAFT) {
		if(enemy->delay == 0) {
			if(enemy->x > player->x) enemy->x--;
			if(enemy->x < player->x) enemy->x++;
			if(enemy->y > player->y) enemy->y--;
			if(enemy->y < player->y) enemy->y++;
			enemy->delay = enemy->count_delay;
		}
		else enemy->delay--;

		// check the position.If it's out of screen or in the board
		/* this check should not be necessary because the enemy follows the player
		if (enemy->y >= SCREEN_HEIGHT-DASHBOARD_HEIGHT) enemy->y--;
		if (enemy->y <=0) enemy->y++;
		if (enemy->x >= SCREEN_WIDTH) enemy->x--;
		if (enemy->x <=0) enemy->x++;
		*/
    }
	
	// AIRCRAFT goes for array
	if(enemy->type == SPACESHIP_ARRAY) {
		if ((enemy->x >= SCREEN_WIDTH-WIDTH_SPRITE_FROM_BARICENTRE) || (enemy->x <= 8) 
				||(enemy->y >= SCREEN_HEIGHT-DASHBOARD_HEIGHT-HEIGHT_SPRITE_FROM_BARICENTRE) || (enemy->y<= HEIGHT_SPRITE_FROM_BARICENTRE)) {
				changeDirectionEnemyArray(enemy);
				//sprintf(buffer," E.im: %1d E.t: %1d  E.x: %1d  E.y: %1d ", enemy->image, enemy->type, enemy->x, enemy->y); 
				//Gfx_WriteString (20,230,buffer);
		}
		
		enemy->x += enemyMovements[enemy->array][0];
		enemy->y += enemyMovements[enemy->array][1];
		
		

	}
	
	if (enemy->type == GHOST){
		    // Muovi lo sprite lungo il percorso predefinito
		if(enemy->delay == 0) {
			enemy->x = path_ghost[enemy->nr_on_type][enemy->array][0];
			enemy->y = path_ghost[enemy->nr_on_type][enemy->array][1];
			enemy->array = (enemy->array + 1) % 10;  // Avanza al prossimo passo del percorso
			enemy->delay = enemy->count_delay*10;;
		}
		else enemy->delay--;
	}
    
    if (enemy->type != GHOST) moveMissile(enemy);
}

int checkHitPlayer(){
	int i;
	int Hit_Player=0;

	//check hit player with Emenies
	for (i = 0; i < NUM_ENEMIES; i++) {
		if (enemies[i].visible==true)
			if (DistanceSprites(player.id, enemies[i].id, DISTANCE_HIT_SPRITE)) {
				//sprintf(buffer," Player is Hit by En: %1d", enemies[i].id); 
				//Gfx_WriteString (20,230,buffer);
				//Hide the enemy hit
				enemies[i].visible = false;
				HideSprite(enemies[i].id);
				Hit_Player = 1;
			};
	}
	//check hit player with Emenies's fire
	for (i = 0; i < NR_MAX_MISSILE_ENEMY; i++) {
		if (missile_enemies[i].visible==true)
			if (DistanceSprites(player.id, missile_enemies[i].id, DISTANCE_HIT_SPRITE)) {
				//sprintf(buffer," Player is Hit by Fire: %1d", missile_enemies[i].id); 
				//Gfx_WriteString (20,230,buffer);
				//Hide the enemy hit
				missile_enemies[i].visible = false;
				HideSprite(missile_enemies[i].id);
				Hit_Player = 1;
			};
	}
	return Hit_Player;
}

