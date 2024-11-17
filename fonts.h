//─────────────────────────────────────────────────────────────────────────────
//  SAM.PR 2024 - EXPLORER Fausto Pracek (fpracek@gmail.com)
//─────────────────────────────────────────────────────────────────────────────

// FILE: fonts.h
	
// *** FONTS DEFINITION ***
const unsigned char g_AlphabeticalFontPatterns_Patterns[] =
{
// Font header data
	0x8B, // Data size [x|y]
	0x8B, // Font size [x|y]
	0x20, // First character ASCII code (!)
	0x60, // Last character ASCII code (')
// Sprite[0]
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[1]
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x00, /* ........ */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[2]
	0x36, /* ..##.##. */ 
	0x36, /* ..##.##. */ 
	0x24, /* ..#..#.. */ 
	0x48, /* .#..#... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[3]
	0x6C, /* .##.##.. */ 
	0x6C, /* .##.##.. */ 
	0xFE, /* #######. */ 
	0xFE, /* #######. */ 
	0x6C, /* .##.##.. */ 
	0xFE, /* #######. */ 
	0xFE, /* #######. */ 
	0x6C, /* .##.##.. */ 
	0x6C, /* .##.##.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[4]
	0x18, /* ...##... */ 
	0x3E, /* ..#####. */ 
	0x7E, /* .######. */ 
	0x58, /* .#.##... */ 
	0x7C, /* .#####.. */ 
	0x3E, /* ..#####. */ 
	0x1A, /* ...##.#. */ 
	0x7E, /* .######. */ 
	0x7C, /* .#####.. */ 
	0x18, /* ...##... */ 
	0x00, /* ........ */ 
// Sprite[5]
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x18, /* ...##... */ 
	0x30, /* ..##.... */ 
	0x30, /* ..##.... */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[6]
	0x38, /* ..###... */ 
	0x7C, /* .#####.. */ 
	0x6C, /* .##.##.. */ 
	0x38, /* ..###... */ 
	0x3A, /* ..###.#. */ 
	0x6E, /* .##.###. */ 
	0x6C, /* .##.##.. */ 
	0x7E, /* .######. */ 
	0x3A, /* ..###.#. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[7]
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x10, /* ...#.... */ 
	0x20, /* ..#..... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[8]
	0x0C, /* ....##.. */ 
	0x1C, /* ...###.. */ 
	0x38, /* ..###... */ 
	0x30, /* ..##.... */ 
	0x30, /* ..##.... */ 
	0x30, /* ..##.... */ 
	0x38, /* ..###... */ 
	0x1C, /* ...###.. */ 
	0x0C, /* ....##.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[9]
	0x30, /* ..##.... */ 
	0x38, /* ..###... */ 
	0x1C, /* ...###.. */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x1C, /* ...###.. */ 
	0x38, /* ..###... */ 
	0x30, /* ..##.... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[10]
	0x00, /* ........ */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x3C, /* ..####.. */ 
	0x3C, /* ..####.. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[11]
	0x00, /* ........ */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[12]
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x40, /* .#...... */ 
	0x80, /* #....... */ 
// Sprite[13]
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[14]
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[15]
	0x06, /* .....##. */ 
	0x06, /* .....##. */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x18, /* ...##... */ 
	0x30, /* ..##.... */ 
	0x30, /* ..##.... */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[16]
	0x18, /* ...##... */ 
	0x3C, /* ..####.. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x3C, /* ..####.. */ 
	0x18, /* ...##... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[17]
	0x18, /* ...##... */ 
	0x38, /* ..###... */ 
	0x78, /* .####... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[18]
	0x3C, /* ..####.. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x06, /* .....##. */ 
	0x0C, /* ....##.. */ 
	0x18, /* ...##... */ 
	0x30, /* ..##.... */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[19]
	0x78, /* .####... */ 
	0x7C, /* .#####.. */ 
	0x0E, /* ....###. */ 
	0x1C, /* ...###.. */ 
	0x38, /* ..###... */ 
	0x1C, /* ...###.. */ 
	0x0E, /* ....###. */ 
	0x7C, /* .#####.. */ 
	0x78, /* .####... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[20]
	0x20, /* ..#..... */ 
	0x60, /* .##..... */ 
	0x6C, /* .##.##.. */ 
	0x6C, /* .##.##.. */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[21]
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x60, /* .##..... */ 
	0x7C, /* .#####.. */ 
	0x0E, /* ....###. */ 
	0x06, /* .....##. */ 
	0x66, /* .##..##. */ 
	0x7C, /* .#####.. */ 
	0x38, /* ..###... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[22]
	0x1E, /* ...####. */ 
	0x3E, /* ..#####. */ 
	0x70, /* .###.... */ 
	0x7C, /* .#####.. */ 
	0x6E, /* .##.###. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x3C, /* ..####.. */ 
	0x18, /* ...##... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[23]
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x06, /* .....##. */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x18, /* ...##... */ 
	0x38, /* ..###... */ 
	0x70, /* .###.... */ 
	0x60, /* .##..... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[24]
	0x3C, /* ..####.. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x3C, /* ..####.. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x3C, /* ..####.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[25]
	0x3C, /* ..####.. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x3E, /* ..#####. */ 
	0x06, /* .....##. */ 
	0x66, /* .##..##. */ 
	0x7C, /* .#####.. */ 
	0x38, /* ..###... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[26]
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[27]
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x40, /* .#...... */ 
	0x80, /* #....... */ 
// Sprite[28]
	0x04, /* .....#.. */ 
	0x0C, /* ....##.. */ 
	0x18, /* ...##... */ 
	0x30, /* ..##.... */ 
	0x60, /* .##..... */ 
	0x30, /* ..##.... */ 
	0x18, /* ...##... */ 
	0x0C, /* ....##.. */ 
	0x04, /* .....#.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[29]
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x00, /* ........ */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[30]
	0x20, /* ..#..... */ 
	0x30, /* ..##.... */ 
	0x18, /* ...##... */ 
	0x0C, /* ....##.. */ 
	0x06, /* .....##. */ 
	0x0C, /* ....##.. */ 
	0x18, /* ...##... */ 
	0x30, /* ..##.... */ 
	0x20, /* ..#..... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[31]
	0x3C, /* ..####.. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x0E, /* ....###. */ 
	0x1C, /* ...###.. */ 
	0x18, /* ...##... */ 
	0x00, /* ........ */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[32]
	0x38, /* ..###... */ 
	0x7C, /* .#####.. */ 
	0x66, /* .##..##. */ 
	0x06, /* .....##. */ 
	0x76, /* .###.##. */ 
	0x7E, /* .######. */ 
	0x4E, /* .#..###. */ 
	0x6E, /* .##.###. */ 
	0x3C, /* ..####.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[33]
	0x3C, /* ..####.. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[34]
	0x78, /* .####... */ 
	0x7C, /* .#####.. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x7C, /* .#####.. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x7C, /* .#####.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[35]
	0x18, /* ...##... */ 
	0x3C, /* ..####.. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x60, /* .##..... */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x3C, /* ..####.. */ 
	0x18, /* ...##... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[36]
	0x78, /* .####... */ 
	0x7C, /* .#####.. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x7C, /* .#####.. */ 
	0x78, /* .####... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[37]
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x78, /* .####... */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[38]
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x78, /* .####... */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[39]
	0x3C, /* ..####.. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x60, /* .##..... */ 
	0x6E, /* .##.###. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x3C, /* ..####.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[40]
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[41]
	0x3C, /* ..####.. */ 
	0x3C, /* ..####.. */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x3C, /* ..####.. */ 
	0x3C, /* ..####.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[42]
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x6C, /* .##.##.. */ 
	0x6C, /* .##.##.. */ 
	0x7C, /* .#####.. */ 
	0x38, /* ..###... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[43]
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x6C, /* .##.##.. */ 
	0x78, /* .####... */ 
	0x70, /* .###.... */ 
	0x78, /* .####... */ 
	0x6C, /* .##.##.. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[44]
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[45]
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[46]
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x76, /* .###.##. */ 
	0x76, /* .###.##. */ 
	0x7E, /* .######. */ 
	0x6E, /* .##.###. */ 
	0x6E, /* .##.###. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[47]
	0x3C, /* ..####.. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x3C, /* ..####.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[48]
	0x7C, /* .#####.. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x7C, /* .#####.. */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[49]
	0x3C, /* ..####.. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x6C, /* .##.##.. */ 
	0x7E, /* .######. */ 
	0x36, /* ..##.##. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[50]
	0x7C, /* .#####.. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x7C, /* .#####.. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[51]
	0x3E, /* ..#####. */ 
	0x7E, /* .######. */ 
	0x70, /* .###.... */ 
	0x78, /* .####... */ 
	0x3C, /* ..####.. */ 
	0x1E, /* ...####. */ 
	0x0E, /* ....###. */ 
	0x7E, /* .######. */ 
	0x7C, /* .#####.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[52]
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[53]
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x3C, /* ..####.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[54]
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x3C, /* ..####.. */ 
	0x3C, /* ..####.. */ 
	0x18, /* ...##... */ 
	0x18, /* ...##... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[55]
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x66, /* .##..##. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[56]
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x3C, /* ..####.. */ 
	0x18, /* ...##... */ 
	0x3C, /* ..####.. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[57]
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x66, /* .##..##. */ 
	0x3E, /* ..#####. */ 
	0x1E, /* ...####. */ 
	0x06, /* .....##. */ 
	0x06, /* .....##. */ 
	0x06, /* .....##. */ 
	0x06, /* .....##. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[58]
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x06, /* .....##. */ 
	0x0C, /* ....##.. */ 
	0x18, /* ...##... */ 
	0x30, /* ..##.... */ 
	0x60, /* .##..... */ 
	0x7E, /* .######. */ 
	0x7E, /* .######. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[59]
	0x3C, /* ..####.. */ 
	0x3C, /* ..####.. */ 
	0x30, /* ..##.... */ 
	0x30, /* ..##.... */ 
	0x30, /* ..##.... */ 
	0x30, /* ..##.... */ 
	0x30, /* ..##.... */ 
	0x3C, /* ..####.. */ 
	0x3C, /* ..####.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[60]
	0x60, /* .##..... */ 
	0x60, /* .##..... */ 
	0x30, /* ..##.... */ 
	0x30, /* ..##.... */ 
	0x18, /* ...##... */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x06, /* .....##. */ 
	0x06, /* .....##. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[61]
	0x3C, /* ..####.. */ 
	0x3C, /* ..####.. */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x0C, /* ....##.. */ 
	0x3C, /* ..####.. */ 
	0x3C, /* ..####.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[62]
	0x10, /* ...#.... */ 
	0x38, /* ..###... */ 
	0x7C, /* .#####.. */ 
	0x6C, /* .##.##.. */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[63]
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0xFF, /* ######## */ 
	0xFF, /* ######## */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[64]
	0x30, /* ..##.... */ 
	0x30, /* ..##.... */ 
	0x10, /* ...#.... */ 
	0x08, /* ....#... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 

};


