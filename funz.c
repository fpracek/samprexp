//─────────────────────────────────────────────────────────────────────────────
//  SAM.PR - EXPLORER 2024 Fausto Pracek (fpracek@gmail.com)
//─────────────────────────────────────────────────────────────────────────────

// FILE: samprexp_s6_b1.c
#include "msxgl.h"


#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define MAX_ROOMS 100  // Max number of rooms

extern typedef struct {
    int id;
    int doors[4];  // 0: north, 1: east, 2: south, 3: west
    int type;      // Room type (1 to 4)
} Room;

// Connect two rooms bidirectionally
void ConnectRooms(Room* maze, u8 room1, u8 room2, u8 direction1, u8 direction2) {
    maze[room1].doors[direction1] = room2;
    maze[room2].doors[direction2] = room1;
}

// Check if two rooms have the same type
u8 AreAdjacentRoomsSameType(Room* maze, u8 room1, u8 room2) {
    return maze[room1].type == maze[room2].type;
}

// Assign random types to rooms ensuring no adjacent rooms share the same type
void AssignRoomTypes(u8 num_rooms) {
    u8 roomTypes[4]={0,1,2,3};
    for (u8 i = 0; i < num_rooms; i++) {
        // Try to assign a random type different from adjacent rooms
        u8 type_assigned = 0;
        while (!type_assigned) {
            g_Maze[i].type = roomTypes[Math_GetRandomRange8(0, 3)];  // Assign a random type from 1 to 4
            type_assigned = 1;

            // Check adjacent rooms to ensure they don't share the same type
            for (u8 dir = 0; dir < 4; dir++) {
                u8 adj_room = g_Maze[i].doors[dir];
                if (adj_room != -1 && AreAdjacentRoomsSameType(maze, i, adj_room)) {
                    type_assigned = 0;
                    break;
                }
            }
        }
    }
}

// Create the maze
void CreateMaze(u8 num_rooms, u8 *exit_room) {
    // Initialize each room with an ID and no doors (-1)
    for (u8 i = 0; i < num_rooms; i++) {
        g_Maze[i].id = i;
        for (u8 j = 0; j < 4; j++) {
            maze[i].doors[j] = -1;  // No doors initially
        }
    }



    // Randomly connect rooms ensuring all rooms are reachable
    for (u8 i = 0; i < num_rooms - 1; i++) {
        u8 direction = Math_GetRandomRange8(0, 3); // Randomly select a direction for room i
        u8 opposite_direction = (direction + 2) % 4; // Opposite direction for the target room
        u8 target_room = i + 1 + (Math_GetRandomRange8(0, num_rooms - i - 2) ); // Select a random subsequent room

        // Connect the rooms if they are not already connected in that direction
        if (maze[i].doors[direction] == -1 && maze[target_room].doors[opposite_direction] == -1) {
            ConnectRooms(maze, i, target_room, direction, opposite_direction);
        }
    }

    // Add extra random connections to make the maze more complex
    for (u8 i = 0; i < num_rooms; i++) {
        u8 random_room = Math_GetRandomRange8(0, num_rooms - 1);
        u8 direction = Math_GetRandomRange8(0, 3);
        u8 opposite_direction = (direction + 2) % 4;

        // Connect rooms if there is no existing connection and they are not the same room
        if (maze[i].doors[direction] == -1 && maze[random_room].doors[opposite_direction] == -1 && i != random_room) {
            ConnectRooms(maze, i, random_room, direction, opposite_direction);
        }
    }

    // Assign random types to rooms while ensuring no adjacent rooms share the same type
    AssignRoomTypes(maze, num_rooms);

    // Set a random exit room
    *exit_room = Math_GetRandomRange8(0, num_rooms - 1);
    u8 exit_door = Math_GetRandomRange8(0, 3);
    maze[*exit_room].doors[exit_door] = -2;  // Mark the exit with -2
}

//// Function to pru8 the maze
//void print_maze(Room* maze, u8 num_rooms) {
//    if (!maze) return;
//    for (u8 i = 0; i < num_rooms; i++) {
//        printf("Room %d (Type %d): N=%d, E=%d, S=%d, O=%d\n", 
//            maze[i].id, 
//            maze[i].type, 
//            maze[i].doors[NORTH], 
//            maze[i].doors[EAST], 
//            maze[i].doors[SOUTH], 
//            maze[i].doors[WEST]);
//    }
//}
// Init maze
void InitMaze(u8 rooms) {

    u8 exit_room;

    // Create an array of rooms with a max size of MAX_ROOMS (static memory)
    Room maze[MAX_ROOMS];

    // Create the maze with a specific number of rooms
    CreateMaze(maze, rooms, &exit_room);

    //// Pru8 the maze
    //printf("Maze with exit in room %d\n", exit_room);
    //print_maze(maze, rooms);


}