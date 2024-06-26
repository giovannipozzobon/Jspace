

void SetCursorPosition(uint8_t x_pos , uint8_t y_pos);


void ResetChannelSound(uint8_t nr_channel);


void PlaySoundChannel(uint8_t nr_channel, uint8_t sfx);

void Gfx_WriteString(uint8_t x_pos , uint8_t y_pos, char * str);

 
void DisplayDirectory();

void OpenFile(uint8_t channel, const unsigned char * fileName, uint8_t mode);

void CloseFile(uint8_t channel);

uint8_t WriteFile(uint8_t channel, int memory, int nrbyte);

uint8_t LoadFile( int memory, const unsigned char * fileName);

uint8_t SaveFile( int memory, int nrbyte , const unsigned char * fileName);

void DrawLine(int x1,int y1,int x2,int y2);

void DrawRectangle(int x1,int y1,int x2,int y2);

void DrawImage(int x,int y, uint8_t imageID);

uint8_t LoadGrafix(const unsigned char * file);

void DrawSprite(uint8_t id, int x, int y, uint8_t image);

void MoveSprite(uint8_t id, int x, int y);

uint8_t DistanceSprites(uint8_t id_sprite1, uint8_t id_sprite2, uint8_t distance) ;

void HideSprite(uint8_t id);

void ResetSprite();

uint8_t CheckJoypad();

int readTimer();

void waitXcycleclock(int cicli);

void ResetPalette();

void SetColor(uint8_t _and, uint8_t _xor, uint8_t solid, uint8_t dimension, uint8_t flip);

void SetCurrentTileMap(const unsigned char * addr, int x, int y);

void DrawTileMap(int x1, int y1, int x2, int y2);

unsigned int nop_delay(unsigned int delay) ;

void SetPalette(uint8_t color, uint8_t r, uint8_t g, uint8_t b);

void SetColorNew(uint8_t color);

void DrawPixel(int x,int y);

void ClearScreen();

uint8_t CheckKeyboardArray();

void ReturnToBasic();


// Get character from keyboard
int inkey();

int cgetc();


// Position cursor (API Group 2, Function 7)
void gotoxy(uint8_t sx, uint8_t sy);

// write to conole a string with lengh count
void write (const unsigned char* buf, unsigned count);

// Put a character
void cputc(char ch);

// Put a character at screen coord
void cputcxy(int sx, int sy, char ch);

// Clear screen
void clrscr();

void ClearKeyboardArray();
