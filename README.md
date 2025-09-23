# so_long

_A small 2D game written in C using MiniLibX, part of the 42 curriculum “so_long” project._

---

## Table of Contents

1. [Project Overview](#project-overview)  
2. [Features](#features)  
3. [Installation & Requirements](#installation--requirements)  
4. [Usage](#usage)  
5. [Controls](#controls)  
6. [Map Format & Validation Rules](#map-format--validation-rules)  
7. [Compilation & Building](#compilation--building)  
8. [Design Decisions & Implementation Notes](#design-decisions--implementation-notes)  
9. [Known Limitations & Future Improvements](#known-limitations--future-improvements)  

---

## Project Overview

so_long is a simple 2D game where the player navigates a map, collects necessary items, and exits through an exit point once all items are gathered. The game uses the MiniLibX (mlx) library for rendering, handles user input, and ensures map validity (walls, collectibles, exit, etc.).

Primary goals:

- Understand graphics rendering using mlx.  
- Manage user input and event handling (keyboard, window close).  
- Work with map parsing, validation, and state updates.  
- Maintain movement count or other metrics visible to the player.  

(This aligns with the 42 “so_long” project specification.

---

## Features

- Read and parse maps from `.ber` files.  
- Validate that maps are properly formed (correct dimensions, enclosed by walls, correct number of player start, collectibles, exit).  
- Render tiles / sprites for walls, floor, player, collectible, exit.  
- Respond to player movement: W/A/S/D (or arrow keys), prevent moving through walls.  
- Track and display the number of moves made.  
- Clean shutdown: close window via ESC key or window close button.  

---

## Installation & Requirements

Make sure you have:

- A Unix-like system (Linux or macOS; Linux recommended).  
- `cc` or another compatible C compiler.  
- MiniLibX library installed (with X11 support for Linux / appropriate setup for macOS).  
- Development tools — `make`, standard C build tools.  

Optionally:

- Libraries / dependencies for MiniLibX (X11, Xext, etc.) if you compile from source.  

---

## Usage

1. Clone the repository:

   ```bash
   git clone https://github.com/HoferJPaul/so_long.git
   cd so_long
   ```

2. Ensure required images / textures are present in `textures/` (walls, floor, player, collectible, exit).

3. Place map `.ber` files in `maps/` (or specify path when launching).

4. Build:

   ```bash
   make
   ```

5. Run:

   ```bash
   ./so_long maps/example1.ber
   ```

   Replace `maps/example1.ber` with the map you want to play.

---

## Controls

| Input             | Action                                                         |
|-------------------|----------------------------------------------------------------|
| **W / Up Arrow**    | Move up                                                        |
| **A / Left Arrow**  | Move left                                                      |
| **S / Down Arrow**  | Move down                                                      |
| **D / Right Arrow** | Move right                                                     |
| **ESC**             | Exit / close the game window                                   |
| **Window Close Button** | Also exit cleanly                                         |

---

## Map Format & Validation Rules

The `.ber` map files must obey specific rules:

1. **Rectangular shape** — every line must have the same length.  
2. **Enclosed by walls** — the outer border (first and last line, first and last characters of each line) must be walls.  
3. **Valid characters** — typically:  
   - `1` for wall  
   - `0` for floor / empty space  
   - `P` for player start (exactly 1)  
   - `E` for exit (at least 1)  
   - `C` for collectibles (at least 1)  
4. Must contain exactly one player start (`P`).  
5. Must have at least one exit (`E`) and one collectible (`C`).  
6. No invalid characters or unknown symbols.  

If any of the rules are broken, the program should exit with an error message and free any allocated resources.

---

## Compilation & Building

- The `Makefile` handles building all needed object files and linking.  
- Example commands:

  ```bash
  make all      # default, build executable
  make clean    # remove object files
  make fclean   # remove object files and executable
  make re       # fclean then all
  ```

- Compiler flags: use `-Wall -Wextra -Werror` (or similar) to enforce good coding practices.  

---

## Design Decisions & Implementation Notes

- **Map representation**: store the map in a 2D array (or array of strings). This simplifies indexing and collision detection.  
- **Rendering**: draw tile-by-tile in a loop, mapping map character to texture and placing using mlx functions.  
- **Movement & state**: when the player moves, check target tile — if wall, block; if collectible, increment collected count; if exit and all collectibles collected, end game.  
- **Tracking moves**: increment counter each valid movement and display somewhere (e.g. command line or in the window, depending on spec).  
- **Error handling & resource management**: ensure for map parsing failures or texture loading failures, the program cleans up (frees memory, closes window).  

---

## Known Limitations & Future Improvements

- **Graphics enhancements**: smoother animations or transitions, animated sprites.  
- **Dynamic tile sizes and scaling**: make tile size configurable or adapt to window size.  
- **Additional map features**: enemies, hazards, moving platforms.  
- **Level support**: multiple levels, with progression.  
- **UI improvements**: display move count within the window, perhaps a simple UI overlay.  
- **Performance**: optimize rendering to avoid redrawing unchanged parts every frame (if needed for larger maps).  
