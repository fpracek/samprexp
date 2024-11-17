//─────────────────────────────────────────────────────────────────────────────
//  SAM.PR - EXPLORER 2024 Fausto Pracek (fpracek@gmail.com)
//─────────────────────────────────────────────────────────────────────────────

// FILE: samprexp.h

void main();                                                                    // Entry point
void PutSamSprite();                                                            // Display Sam sprite on the screen
void InitVDP();                                                                 // VDP initialization
u8 GetControllerDirection();                                                    // Get controllers direction
bool CheckControllerTriggerButtonPressed();                                     // Get controller trigger button pressed
void SamMoveUp();                                                               // Move Sam to up
void SamMoveDown();                                                             // Move Sam to down
void SamMoveLeft();                                                             // Move Sam to left
void SamMoveRight();                                                            // Move Sam to right
void TimerReset();                                                              // Timer reset
void VSyncCallback();                                                           // TIMI hook callback
void DisplayGameScreen();  				                                        // Display map on screen
void LoadTiles();								                                // Put tiles into VRAM
void SetActiveSegment(u8 id);                                                   // Set current segment (0=restore previous segment)
void RoomChange(u8 direction);                                                  // Room change
void InitMaze(u8 rooms);                                                        // Init maze
void SetExplorerPosition(u8 room_id, u8 x, u8 y, u8 speed);                     // Set the explorer's position and speed
void RemoveSoftwareSprite(u8 id);                                               // Remove software sprite
void PutSoftwareSprite(u8 x, u8 y, u8 id);                                      // Display software sprite       
void VDP_InterruptHandler();                                                    // VBlank interrupt handler
void WaitVBlank();                                                              // Wait for V-Blank period
void LoadSoftwareSprites();                                                     // Load software sprites
void InitGhosts(u8 ghosts, u8 rooms);                                           // Initialize ghosts with random positions and speeds
int GetAdjacentRoom(int roomId, int direction);                                 // Get adiacent room
float Sqrt(u8 n);                                                               // Standard qrt function
float GetFabs(float x);                                                         // Standard fabs function
float GetCeil(float x);                                                         // Standard ceils function
void PrintRooms(u8 rooms);                      