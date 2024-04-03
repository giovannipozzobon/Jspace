#include <stdint.h>


//Screen
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define DASHBOARD_HEIGHT 10
#define POS_DASHBOARD_INFO 	0
#define NR_ROOMS 1 // number of room
#define LENGTH_ROOM_TILES 90
#define LENGTH_TILE 16
#define LENGTH_ROOM LENGTH_ROOM_TILES * LENGTH_TILE+3  //16*40+3 // number of tile for a room + 3  
#define LENGTH_SCROLL LENGTH_ROOM_TILES*LENGTH_TILE  // number of effective pixel to scroll in the program for every room normally equal to height of scroll 
#define HEIGTH_SCROLL 240 // number of pixel for every room to scroll

//game
#define NUM_ENEMIES 15 // NR_GHOST + NR_SPACESHIP_ARRAY + NR_AIRCRAFT + NR_SPACESHIP number of total enemies                 // **** TO DELETE ****
#define NR_ENEMY_FOR_WIN 1
#define NR_LIFES_PLAYER 5
#define NR_TIME_FIRE_ENEMY 10 
#define NR_MAX_MISSILE_ENEMY 10
#define MAXLEVEL 6
#define NR_TYPE_OF_ENEMY 4
#define NR_OF_LEVEL 6
#define DELAY_GAME 500
#define DELAY_SCREEN 5000


//Sprite
#define IMAGE_ENEMY 3 // First Enemy image
#define IMAGE_GHOST 9 // First Enemy image
#define IMAGE_PLAYER 0 // Player image
#define FIRST_POS_X_PLAYER 160
#define FIRST_POS_Y_PLAYER 220
#define IMAGE_MISSILE 4 // Player image
#define IMAGE_FIRE_ENEMY 8 // Fire Enemy
#define IMAGE_EXPLOSION1 5 // Explosion imagxse 1
#define IMAGE_EXPLOSION2 6 // Explosion image 2
#define IMAGE_EXPLOSION3 7 // Explosion image 3
#define ID_PLAYER 0 // Player image
#define ID_MISSILE 1 // Player image
#define SPACESHIP 3 // Type of enemies
#define NR_SPACESHIP 3                                    
#define AIRCRAFT 20 // Type of enemies. AIRCRAFT goes for player
#define NR_AIRCRAFT 3                                       
#define SPACESHIP_ARRAY 30 // Type of enemies using the array
#define NR_SPACESHIP_ARRAY 4                                     
#define GHOST 40 // Type of enemies. Apper and disapper using array
#define NR_GHOST 5                                      
#define HEIGHT_SPRITE_FROM_BARICENTRE 8
#define WIDTH_SPRITE_FROM_BARICENTRE 8
#define VELOCITY_MISSILE 2 //nr pixel 
#define SHIFT_ID_ENEMIES 2
#define PLACEHOLDER_ENEMY 50
#define DISTANCE_HIT_SPRITE 8

//Sound
#define SOUND_ENEMY_DESTROY 22 
#define SOUND_MOV_PLAYER 7
#define SOUND_PLAYER_HIT  19
#define POINT_DESTROY_ENEMY 10

//Other
#define LOG_FILE_CHANNEL 1
#define SERIAL_SPEED 115200







