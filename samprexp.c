//─────────────────────────────────────────────────────────────────────────────
//  SAM.PR - EXPLORER 2024 Fausto Pracek (fpracek@gmail.com)
//─────────────────────────────────────────────────────────────────────────────

// FILE: samprexp.c


// *** INCLUDES ***
#include "msxgl.h"
#include "bios.h"
#include "vdp.h"
#include "tile.h"
#include "samprexp.h"
#include "fonts.h"
#include "memory.h"
#include "pt3/pt3_player.h"
#include "ayfx/ayfx_player.h"
#include "pt3/pt3_notetable2.h"
#include "music.h"
#include "debug.h"
#include "math.h"



// *** DEFINES ***
#define NO_ROOM							-1
#define MAX_ROOMS 						100
#define MAX_GHOSTS 						5
#define WIDTH 							220
#define HEIGHT 							120
#define INFINITY 						9999

#define VDP_CMD_REGISTER_WRITE 			0x80 
#define VDP_ADDR 						0x99               

#define VRAM_LAYOUT_TABLE				0x1800
#define VRAM_COLOR_TABLE				0x2000
#define VRAM_PATTERN_TABLE				0x0000

#define SAM_SPEED						3

#define SAM_SPRITE_FRONT				0
#define SAM_SPRITE_REAR 				3
#define SAM_SPRITE_LEFT_W1				8
#define SAM_SPRITE_LEFT_W2				10
#define SAM_SPRITE_RIGHT_W1				9
#define SAM_SPRITE_RIGHT_W2				11
#define SAM_SPRITE_FRONT_W1				1	
#define SAM_SPRITE_FRONT_W2				2
#define SAM_SPRITE_REAR_W1				4
#define SAM_SPRITE_REAR_W2				5
#define SAM_SPRITE_RIGHT				6
#define SAM_SPRITE_LEFT 				7
#define SAM_SPRITE_LEFT_W3				12
#define SAM_SPRITE_RIGHT_W3				13

#define CONTROLLER_DIRECTION_NONE 		0
#define CONTROLLER_DIRECTION_UP 		1
#define CONTROLLER_DIRECTION_UP_RIGHT	2
#define CONTROLLER_DIRECTION_RIGHT		3
#define CONTROLLER_DIRECTION_RIGHT_DOWN 4
#define CONTROLLER_DIRECTION_DOWN		5
#define CONTROLLER_DIRECTION_DOWN_LEFT	6
#define CONTROLLER_DIRECTION_LEFT		7
#define CONTROLLER_DIRECTION_LEFT_UP	8

#define MAP_N_E_S_W						0
#define MAP_N_E_S						1
#define MAP_N_S_W						2
#define MAP_N_E_W						3
#define MAP_E_S_W						4
#define MAP_N_E							5
#define MAP_N_S						 	6
#define MAP_N_W						 	7
#define MAP_E_S						 	8
#define MAP_E_W							9
#define MAP_S_W							10
#define MAP_N							11
#define MAP_S							12
#define MAP_E							13
#define MAP_W							14

#define NORTH 							0
#define EAST 							1
#define SOUTH 							2
#define WEST 						    3

#define SPRITE_SIZE_HEIGHT			    32
#define SPRITE_SIZE_WIDTH			    8
#define SCREEN_WIDTH 				    256

#define MUMMY_SPRITE					0
#define MUMMY_SPRITE_SHAPE_LEFT_WK_1	2
#define MUMMY_SPRITE_SHAPE_LEFT_WK_2	4
#define MUMMY_SPRITE_SHAPE_RIGHT_WK_1	1
#define MUMMY_SPRITE_SHAPE_RIGHT_WK_2	3
#define MUMMY_SPRITE_SHAPE_FRONT_WK_1	6
#define MUMMY_SPRITE_SHAPE_FRONT_WK_2	7
#define MUMMY_SPRITE_SHAPE_REAR_WK_1	8
#define MUMMY_SPRITE_SHAPE_REAR_WK_2	9
// *** STRUCTURES ***
// Point
typedef struct {    
    u16 x;  			// X point
    u16 y;      		// Y point
} Point;

// Structure to represent a ghost's position, speed, and room ID
typedef struct {
    Point position;
    u8 roomID;
    u8 speed;
} SpriteInfo;


// Room
typedef struct {
    u8 id;
    int doors[4];  // 0: north, 1: east, 2: south, 3: west
    u8 type;      // Room type (1 to 10)
} Room;

typedef struct {
	u8 current;
} Shape;

typedef struct {
	Point 	location;
	Shape	shape;
} SamSprite;

typedef struct {
	u8 vBlank;
	u8 seconds;
	u8 minutes;
	u8 houres;
} Timer;

typedef struct{
	u8 backgroundBuffer[SPRITE_SIZE_HEIGHT * SPRITE_SIZE_WIDTH];
	Point position; 
	Shape shape;
	u8 speed;
	u8 speedCounter;
} SoftwareSprite;

// *** VARIABLES ***
SamSprite 		g_Sam;
Timer 			g_Timer;
bool 			g_VBlank = false;	
u8 				g_6thFrameCount = 0;
u8				g_PreviousSegment=0;
Room 			g_Rooms[MAX_ROOMS];
u8				g_Connections[MAX_ROOMS][MAX_ROOMS]; 
u8 				g_RoomOccupancy[MAX_ROOMS] = {0}; 
SpriteInfo 		g_Explorer;
SpriteInfo 		g_Ghosts[MAX_GHOSTS];
u8				g_ExitRoom;
u8				g_ExitDirection;
u8				g_CurrentRoomId=0;
u8				g_RoomsCount=10;
u16				g_CurrentRoomIndex=0;
SoftwareSprite	g_Sprites[10];
u8	 			g_FireTileState=0;



// *** CONSTANTS ***
extern const c8 g_Tiles[]; 
extern const c8 g_Palette[];
extern const c8 g_Maps[15][160];
extern const c8 g_SamPrSprites[];
extern const c8 g_samSpritesColorsTop[];
extern const c8 g_samSpritesColorsBottom[];
extern const u8 g_SoftwareSprites[10][256];
const u8 g_EastWestDoorsTiles[4][2]={
	{40,41},
	{38,39},
	{32,33},
	{17,24}
};
const u8 g_NorthSouthDoorsTiles[4][2]={
	{36,37},
	{34,35},
	{30,31},
	{25,26}
};

// *** FUNCTIONS ***
void PrintRooms(u8 rooms) {
    for (int i = 0; i < rooms; i++) {
        DEBUG_PRINT("Room ID: %d\n", g_Rooms[i].id);
        DEBUG_PRINT("Type: %d\n", g_Rooms[i].type);
        DEBUG_PRINT("Doors: North: %d, East: %d, South: %d, West: %d\n", g_Rooms[i].doors[0], g_Rooms[i].doors[1], g_Rooms[i].doors[2], g_Rooms[i].doors[3]);
        for (int j = 0; j < 4; j++) {
            if (g_Rooms[i].doors[j] == 255) {
                DEBUG_PRINT("This room has the exit door in direction %d!\n", j);
            }
        }
        DEBUG_PRINT("\n");
    }
}
// Standard sqrt function
float GetSqrt(u8 n) {
    
    
    float guess = n / 2.0;
    float epsilon = 0.000001;  

    
    while (1) {
        float better_guess = (guess + n / guess) / 2.0;
        if (GetFabs(guess - better_guess) < epsilon) {
            break;
        }
        guess = better_guess;
    }

    return guess;
}
// Standard fabs function
float GetFabs(float x) {
    if (x < 0) {
        return -x;  
    }
    return x;
}
// Standard ceil function
float GetCeil(float x) {
    int int_part = (int)x; 
    if (x > int_part) {
        return int_part + 1;  
    }
    return int_part;  
}
// Initialize the maze with rooms, random types, and random connections
void InitMaze(u8 rooms) {
	int grid_size = (int)GetCeil(GetSqrt(rooms));
    for (int i = 0; i < rooms; i++) {
        g_Rooms[i].id = i;
        g_Rooms[i].type = (Math_GetRandomRange8(0,9)) + 1;
        for (int j = 0; j < 4; j++) {
            g_Rooms[i].doors[j] = -1; // Initialize doors to -1 (no door)
        }
    }
    
    // Create doors and avoid adjacent rooms of the same type
    for (int i = 0; i < rooms; i++) {
        int neighbors[4] = {-1, -1, -1, -1}; // Neighboring rooms

        // Assign neighboring rooms
        if (i >= grid_size) neighbors[0] = i - grid_size;          // North
        if (i < rooms - grid_size) neighbors[2] = i + grid_size; // South
        if (i % grid_size != 0) neighbors[3] = i - 1; // West
        if (i % grid_size != grid_size - 1) neighbors[1] = i + 1; // East

        // Assign doors
        for (int j = 0; j < 4; j++) {
            if (neighbors[j] != -1 && neighbors[j] <rooms) {
                g_Rooms[i].doors[j] = neighbors[j];
                g_Rooms[neighbors[j]].doors[(j + 2) % 4] = i; // Connect back door to current room
                if (g_Rooms[neighbors[j]].type == g_Rooms[i].type) {
                    g_Rooms[neighbors[j]].type = (g_Rooms[i].type % 10) + 1;
                }
            }
        }
    }
    

	
    // Assign exit door
    int exit_index, exit_position; 
	do 	{ 
		exit_index = Math_GetRandomRange8(0,rooms);
		exit_position = Math_GetRandomRange8(0,4);
	} while (g_Rooms[exit_index].doors[exit_position] != -1); // Ensure no overlap with existing doors 
	g_Rooms[exit_index].doors[exit_position] = 255;

}
// Get adiacent room
int GetAdjacentRoom(int room_id, int direction) { 
	return g_Rooms[room_id].doors[direction];
}
// Set the explorer's position and speed
void SetExplorerPosition(u8 roomID, u8 x, u8 y, u8 speed) {
    g_Explorer.roomID = roomID;
    g_Explorer.position.x = x;
    g_Explorer.position.y = y;
    g_Explorer.speed = speed;
}
// Initialize ghosts with random positions and speeds
void InitGhosts(u8 ghosts, u8 rooms) {
    for (int i = 0; i < ghosts; i++) {
        g_Ghosts[i].roomID = Math_GetRandomRange8(0,rooms);
        g_Ghosts[i].position.x = Math_GetRandomRange8(0,WIDTH);
        g_Ghosts[i].position.y = Math_GetRandomRange8(0,HEIGHT);
        g_Ghosts[i].speed = 1 + Math_GetRandomRange8(0,3); // Random speed between 1 and 3 steps
        g_RoomOccupancy[g_Ghosts[i].roomID]++; // Mark room as occupied by a ghost
    }
}
// Load software sprites
void LoadSoftwareSprites(){
	SetActiveSegment(4);
	
	for(u8 i = 0; i < 10; ++i)
	{
		VDP_CommandHMMC(g_SoftwareSprites[i], i * 16, 212, 16, 32);
	}
	SetActiveSegment(0);
}
// Display software sprite
void PutSoftwareSprite(u8 x, u8 y, u8 id)
{
	g_Sprites[id].position.x=x;
	g_Sprites[id].position.y=y;
	VDP_CommandHMMM(g_Sprites[id].position.x, g_Sprites[id].position.y, 240, 212, 16, 32);
	//g_Sprites[id].shape.current=0;
	VDP_CommandLMMM(g_Sprites[id].shape.current*16, 212, x, y, 16, 32, VDP_OP_TIMP);
}
// Remove software sprite
void RemoveSoftwareSprite(u8 id)
{
	VDP_CommandHMMM(240, 212 , g_Sprites[id].position.x, g_Sprites[id].position.y, 16 , 32);
}
// Timer reset
void TimerReset(){
	g_Timer.vBlank=0;
	g_Timer.seconds=0;
	g_Timer.minutes=0;
	g_Timer.houres=0;
}
// Display Sam sprite on the screen
void PutSamSprite(){
	SetActiveSegment(3);
	VDP_LoadSpritePattern(g_SamPrSprites+g_Sam.shape.current*4*32*2,0,16*4*2);
	
	for(u8 i=0;i<4;i++){
		VDP_SetSpriteExUniColor(i,g_Sam.location.x,g_Sam.location.y,i*4,g_samSpritesColorsTop[i]);
		VDP_SetSpriteExUniColor(i+4,g_Sam.location.x,g_Sam.location.y+16,(i+4)*4,g_samSpritesColorsBottom[i]);
	}
	SetActiveSegment(0);
}
// Screen initialization
void InitVDP(){
	VDP_SetMode(VDP_MODE_SCREEN5);
	VDP_SetColor(2);
	VDP_SetLayoutTable(VDP_G4_ADDR_NT);
	
	
	VDP_SetSpriteAttributeTable(0x17A00);
	VDP_SetSpritePatternTable(0x17000);
	//VDP_RegWrite(5, 0xD0);
	VDP_EnableSprite(TRUE);
	VDP_SetSpriteFlag(VDP_SPRITE_SIZE_16);
	VDP_ClearVRAM();
	//VDP_RegWrite(5, 0xC0);  
    //VDP_RegWrite(6, 0xD0);  
    //VDP_SetColorTable(0x1A000-0x200);
	//Print_SetTextFont(g_AlphabeticalFontPatterns_Patterns, 1);
}
// Get controller trigger button pressed
bool CheckControllerTriggerButtonPressed(){
	if(Bios_GetJoystickTrigger(0)||Bios_GetJoystickTrigger(1)||Bios_GetJoystickTrigger(2)){
		return TRUE;
	}
	return FALSE;
}
// Get controllers direction
u8 GetControllerDirection(){
	u8 inputControllerDirection=Bios_GetJoystickDirection(0);
	if(inputControllerDirection==0){
		inputControllerDirection=Bios_GetJoystickDirection(1);
	}
	if(inputControllerDirection==0){
		inputControllerDirection=Bios_GetJoystickDirection(2);
	}
	return inputControllerDirection;
}
// Room change
void RoomChange(u8 direction){
	DEBUG_LOGNUM("FROM ROOM:",g_CurrentRoomId);
	g_CurrentRoomId=GetAdjacentRoom(g_CurrentRoomId,direction);
	DEBUG_LOGNUM("TO ROOM:",g_CurrentRoomId);
	if(g_CurrentRoomId==255){
		// End game
	}
	DisplayGameScreen();
	switch(direction){
		case NORTH:
			g_Sam.location.y=107;
			break;
		case SOUTH:
			if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]>=0){
				g_Sam.location.y=26;
			}
			else{
				g_Sam.location.y=51;
			}
			break;
		case EAST:
			g_Sam.location.x=18;
			break;
		case WEST:
			g_Sam.location.x=219;
			break;
	}
	PutSamSprite();
}
// Move Sam to up
void SamMoveUp(){
	if(g_Sam.shape.current!=SAM_SPRITE_REAR_W1 && g_Sam.shape.current!=SAM_SPRITE_REAR_W2){
		g_Sam.shape.current=SAM_SPRITE_REAR_W1;
	}
	if(g_Sam.shape.current!=SAM_SPRITE_REAR_W2){
		g_Sam.shape.current=SAM_SPRITE_REAR_W2;
	}
	else{
		g_Sam.shape.current=SAM_SPRITE_REAR_W1;
	}
	
	g_Sam.location.y-=SAM_SPEED;
	if(g_Sam.location.y<=50){
		if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]<0 || g_Sam.location.x<115 || g_Sam.location.x>125){
			g_Sam.shape.current!=SAM_SPRITE_REAR;
			g_Sam.location.y+=SAM_SPEED;
			return;
		}
	}
	if(g_Sam.location.y<=25){
		if(g_Sam.location.x>=115 && g_Sam.location.x<=125){
			PutSamSprite();
			RoomChange(NORTH);
			return;
		}
		else{
			g_Sam.location.y+=SAM_SPEED;
			return;
		}
	}
	PutSamSprite();
	
}
// Move Sam to down
void SamMoveDown(){
	if(g_Sam.shape.current!=SAM_SPRITE_FRONT_W1 && g_Sam.shape.current!=SAM_SPRITE_FRONT_W2){
		g_Sam.shape.current=SAM_SPRITE_FRONT_W1;
	}
	if(g_Sam.shape.current!=SAM_SPRITE_FRONT_W2){
		g_Sam.shape.current=SAM_SPRITE_FRONT_W2;
	}
	else{
		g_Sam.shape.current=SAM_SPRITE_FRONT_W1;
	}
	
	g_Sam.location.y+=SAM_SPEED;
	if(g_Sam.location.y>=105){
		if(g_Rooms[g_CurrentRoomIndex].doors[SOUTH]<0 || g_Sam.location.x<115 || g_Sam.location.x>125){
			g_Sam.shape.current=SAM_SPRITE_FRONT;
			g_Sam.location.y-=SAM_SPEED;
			//PutSamSprite();
			return;
		}
	}
	if(g_Sam.location.y>=108){
		if(g_Sam.location.x>=115 && g_Sam.location.x<=125){
			PutSamSprite();
			RoomChange(SOUTH);
			return;
		}
		else{
			g_Sam.location.y-=SAM_SPEED;
			return;
		}
	}
	PutSamSprite();
}
// Move Sam to left
void SamMoveLeft(){
	if(g_Sam.location.y<=50){
		return;
	}
	if((g_Sam.shape.current!=SAM_SPRITE_LEFT_W1 && g_Sam.shape.current!=SAM_SPRITE_LEFT_W2 && g_Sam.shape.current!=SAM_SPRITE_LEFT_W3)){
		g_Sam.shape.current=SAM_SPRITE_LEFT_W1;
	}
	switch(g_Sam.shape.current){
		case SAM_SPRITE_LEFT_W1:
			g_Sam.shape.current=SAM_SPRITE_LEFT_W3;
			break;
		case SAM_SPRITE_LEFT_W3:
			g_Sam.shape.current=SAM_SPRITE_LEFT_W2;
			break;
		case SAM_SPRITE_LEFT_W2:
			g_Sam.shape.current=SAM_SPRITE_LEFT_W1;
			break;
	}

	g_Sam.location.x-=SAM_SPEED;
	if(g_Sam.location.x<=20){
		if(g_Rooms[g_CurrentRoomIndex].doors[WEST]<0 || g_Sam.location.y<60||g_Sam.location.y>65){
			g_Sam.shape.current=SAM_SPRITE_LEFT;
			g_Sam.location.x+=SAM_SPEED;
			return;
		}
		
	}
	if(g_Sam.location.x<=17){
		PutSamSprite();
		RoomChange(WEST);
		return;
	}
	PutSamSprite();
	
}
// Move Sam to right
void SamMoveRight(){
	if(g_Sam.location.y<=50){
		return;
	}
	if((g_Sam.shape.current!=SAM_SPRITE_RIGHT_W1 && g_Sam.shape.current!=SAM_SPRITE_RIGHT_W2 && g_Sam.shape.current!=SAM_SPRITE_RIGHT_W3)){
		g_Sam.shape.current=SAM_SPRITE_RIGHT_W1;
	}
	
	switch(g_Sam.shape.current){
		case SAM_SPRITE_RIGHT_W1:
			g_Sam.shape.current=SAM_SPRITE_RIGHT_W3;
			break;
		case SAM_SPRITE_RIGHT_W3:
			g_Sam.shape.current=SAM_SPRITE_RIGHT_W2;
			break;
		case SAM_SPRITE_RIGHT_W2:
			g_Sam.shape.current=SAM_SPRITE_RIGHT_W1;
			break;
	}

	g_Sam.location.x+=SAM_SPEED;
	if(g_Sam.location.x>=220){
		if(g_Rooms[g_CurrentRoomIndex].doors[EAST]<0 || g_Sam.location.y<60||g_Sam.location.y>65){
			g_Sam.shape.current=SAM_SPRITE_RIGHT;
			g_Sam.location.x-=SAM_SPEED;
			return;
		}
		
	}
	if(g_Sam.location.x>=223){
		PutSamSprite();
		RoomChange(EAST);
		return;
	}
	PutSamSprite();
}
// Wait for V-Blank period
void WaitVBlank(){
    while(!g_VBlank) {}
    g_VBlank = false;
}
// TIMI hook callback
void VSyncCallback()
{
	g_VBlank = true;

	g_6thFrameCount++;
	if (g_6thFrameCount == 6)
		g_6thFrameCount = 0;

	if (g_6thFrameCount)
	{
		g_Timer.vBlank++;
		if(g_Timer.vBlank==60){
			g_Timer.vBlank=0;
			if (g_Timer.seconds==59){
				g_Timer.seconds=0;
				if (g_Timer.minutes==59){
					g_Timer.minutes=0;
					g_Timer.houres++;
				}
				else{
					g_Timer.minutes++;
				}
			}
			else{
				g_Timer.seconds++;
			}

		}
		//PT3_Decode();	 // Update data to write to the PSG regiters from the music
		//ayFX_Update();	 // Overwrite PSG registers data for the SFX
		//PT3_UpdatePSG(); // Update PSG registers
	}
	
}
// Set current segment (0=restore previous segment)
void SetActiveSegment(u8 id){
	if(id==0){
		SET_BANK_SEGMENT(1, g_PreviousSegment); 
	}
	else{
		g_PreviousSegment = GET_BANK_SEGMENT(1);   
		SET_BANK_SEGMENT(1, id); 
	}
}
// Put tiles into VRAM
void LoadTiles(){
	SetActiveSegment(2);		
	VDP_SetPalette(g_Palette);
	SetActiveSegment(0);
	Tile_SelectBank(0);
	Tile_SetDrawPage(0);
	SetActiveSegment(2);		
	Tile_LoadBank(0, g_Tiles, 58);
	SetActiveSegment(0);
}
// Get current room array index
u16 GetCurrenRoomArrayIndex(){
	for(u16 i=0;i<g_RoomsCount;i++){
		if(g_Rooms[i].id==g_CurrentRoomId){
			return i;
		}
	}
	return 0;
}
// Display map on screen
void DisplayGameScreen() {

	VDP_EnableVBlank(FALSE);

	u8 roomTypes[10][2] = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},
        {0, 2},
        {1, 3},
        {2, 0},
        {3, 1},
        {0, 3},
        {1, 0}
    };

	u8 roomMapNumber=0;
	g_CurrentRoomIndex=GetCurrenRoomArrayIndex();

	// N_E_S_W
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]>=0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]>=0){
		roomMapNumber=0;
	}
	// N_E_S
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]>=0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]<0){
		roomMapNumber=1;
	}
	// N_S_W
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]<0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]>=0){
		roomMapNumber=2;
	}
	// N_E_W
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]>=0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]>=0){
		roomMapNumber=3;
	}
	// E_S_W
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]>=0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]>=0){
		roomMapNumber=4;
	}
	// N_E
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]>=0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]<0){
		roomMapNumber=5;
	}
	// N_S
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]<0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]<0){
		roomMapNumber=6;
	}
	// N_W
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]<0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]>=0){
		roomMapNumber=7;
	}
	// E_S
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]>=0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]<0){
		roomMapNumber=8;
	}
	// E_W
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]>=0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]>=0){
		roomMapNumber=9;
	}
	// S_W
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]<0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]>=0){
		roomMapNumber=10;
	}
	// N
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]<0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]<0){
		roomMapNumber=11;
	}
	// S
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]<0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]>=0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]<0){
		roomMapNumber=12;
	}
	// E
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]>=0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]<0){
		roomMapNumber=13;
	}
	// W
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[EAST]<0 && g_Rooms[g_CurrentRoomIndex].doors[SOUTH]<0 && g_Rooms[g_CurrentRoomIndex].doors[WEST]>=0){
		roomMapNumber=14;
	}
	
	//DEBUG_LOGNUM("ROOM TYPE:",roomType);
	
	

	u8 eastTile=255;
	if(g_Rooms[g_CurrentRoomIndex].doors[EAST]>0){
		eastTile=roomTypes[g_Rooms[g_CurrentRoomIndex].type][0];
	} 
	u8 westTile=255;
	if(g_Rooms[g_CurrentRoomIndex].doors[WEST]>0){
		westTile=roomTypes[g_Rooms[g_CurrentRoomIndex].type][1];
	} 
	u8 northTile=255;
	if(g_Rooms[g_CurrentRoomIndex].doors[NORTH]>0){
		northTile=roomTypes[g_Rooms[g_CurrentRoomIndex].type][1];
	} 
	u8 southTile=255;
	if(g_Rooms[g_CurrentRoomIndex].doors[SOUTH]>0){
		southTile=roomTypes[g_Rooms[g_CurrentRoomIndex].type][0];
	} 
	SetActiveSegment(2);
	Tile_DrawMapChunk(0,0,g_Maps[roomMapNumber],16,10);
	SetActiveSegment(0);

	
	if(northTile!=255){
		Tile_DrawTile(7,0,g_NorthSouthDoorsTiles[northTile][0]);
		Tile_DrawTile(8,0,g_NorthSouthDoorsTiles[northTile][1]);
	}
	if(southTile!=255){
		Tile_DrawTile(7,9,g_NorthSouthDoorsTiles[southTile][0]);
		Tile_DrawTile(8,9,g_NorthSouthDoorsTiles[southTile][1]);
	}
	//if(westTile!=255){
	//	Tile_DrawTile(0,4,g_EastWestDoorsTiles[westTile][0]);
	//	Tile_DrawTile(0,5,g_EastWestDoorsTiles[westTile][1]);
	//}
	//if(eastTile!=255){
	//	Tile_DrawTile(15,4,g_EastWestDoorsTiles[eastTile][0]);
	//	Tile_DrawTile(15,5,g_EastWestDoorsTiles[eastTile][1]);
	//}
	
	
	VDP_EnableVBlank(TRUE);
	
	
}
// Entry point
void main()
{
	DEBUG_INIT();
	

	Bios_SetHookCallback(H_TIMI, VSyncCallback);
	InitVDP();
	VDP_EnableVBlank(TRUE);
	LoadTiles();
	
	g_Sam.location.x=100;
	g_Sam.location.y=100;
	g_Sam.shape.current=SAM_SPRITE_FRONT;
	
	u8 count = 0;
	InitMaze(g_RoomsCount);
	PrintRooms(g_RoomsCount);
	g_CurrentRoomId=0;
	DisplayGameScreen();
	LoadSoftwareSprites();
	PutSamSprite();
	TimerReset();
	g_FireTileState=1;
	g_Sprites[MUMMY_SPRITE].shape.current=100;
	g_Sprites[MUMMY_SPRITE].speed=10;
	g_Sprites[MUMMY_SPRITE].speedCounter=g_Sprites[MUMMY_SPRITE].speed;
	for(;;){
		WaitVBlank();
		if(g_FireTileState!=0 && g_Timer.vBlank%1==0){
			g_Sprites[MUMMY_SPRITE].speedCounter--;
			if(g_Sprites[MUMMY_SPRITE].speedCounter==0){
				g_Sprites[MUMMY_SPRITE].speedCounter=g_Sprites[MUMMY_SPRITE].speed;
				if(g_Sprites[MUMMY_SPRITE].shape.current!=100){
					RemoveSoftwareSprite(MUMMY_SPRITE);
					
				}
				else{
					g_Sprites[MUMMY_SPRITE].shape.current=MUMMY_SPRITE_SHAPE_REAR_WK_2;
					g_Sprites[MUMMY_SPRITE].position.x=30;
					g_Sprites[MUMMY_SPRITE].position.y=70;
				}
				g_Sprites[MUMMY_SPRITE].position.y-=2;
				switch(g_Sprites[MUMMY_SPRITE].shape.current){
					case MUMMY_SPRITE_SHAPE_REAR_WK_1:
						g_Sprites[MUMMY_SPRITE].shape.current=MUMMY_SPRITE_SHAPE_REAR_WK_2;
						break;
					case MUMMY_SPRITE_SHAPE_REAR_WK_2:
						g_Sprites[MUMMY_SPRITE].shape.current=MUMMY_SPRITE_SHAPE_REAR_WK_1;
						break;
					
				}
				PutSoftwareSprite(g_Sprites[MUMMY_SPRITE].position.x,g_Sprites[MUMMY_SPRITE].position.y,MUMMY_SPRITE);
			}
			
		}
	

		if(g_FireTileState!=0 && g_Timer.vBlank%10==0){
			if(g_FireTileState==1){
				g_FireTileState=2;
				Tile_DrawTile(3,8,29);
				Tile_DrawTile(3,2,14);
				Tile_DrawTile(12,2,15);
				Tile_DrawTile(12,8,4);
			}
			else{
				Tile_DrawTile(3,8,4);
				g_FireTileState=1;
				Tile_DrawTile(3,2,15);
				Tile_DrawTile(12,2,14);
				Tile_DrawTile(12,8,29);
			}
			
		}
		
		if(g_Timer.vBlank%4==0){
			u8 controllerDirection=GetControllerDirection();
			if(controllerDirection!=CONTROLLER_DIRECTION_NONE){
				TimerReset();
				switch(controllerDirection){
					case CONTROLLER_DIRECTION_UP:
						SamMoveUp();
						break;

					case CONTROLLER_DIRECTION_RIGHT:
						SamMoveRight();
						break;

					case CONTROLLER_DIRECTION_DOWN:
						SamMoveDown();
						break;

					case CONTROLLER_DIRECTION_LEFT:
						SamMoveLeft();
						break;
			
				}
				
			}
			else {
				if (g_Sam.shape.current==SAM_SPRITE_FRONT_W1 || g_Sam.shape.current==SAM_SPRITE_FRONT_W2){
					g_Sam.shape.current=SAM_SPRITE_FRONT;
					PutSamSprite();
				}
				if (g_Sam.shape.current==SAM_SPRITE_REAR_W1 || g_Sam.shape.current==SAM_SPRITE_REAR_W2){
					g_Sam.shape.current=SAM_SPRITE_REAR;
					PutSamSprite();
				}
				if (g_Sam.shape.current==SAM_SPRITE_LEFT_W1 || g_Sam.shape.current==SAM_SPRITE_LEFT_W2 || g_Sam.shape.current==SAM_SPRITE_LEFT_W3){
					g_Sam.shape.current=SAM_SPRITE_LEFT;
					PutSamSprite();
				}
				if (g_Sam.shape.current==SAM_SPRITE_RIGHT_W1 || g_Sam.shape.current==SAM_SPRITE_RIGHT_W2 || g_Sam.shape.current==SAM_SPRITE_RIGHT_W3){
					g_Sam.shape.current=SAM_SPRITE_RIGHT;
					PutSamSprite();
				}

			}

		
		}
		

		Halt();
	}
		
	Bios_Exit(0);
}

