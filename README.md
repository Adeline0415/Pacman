# Pacman Game

This is a classic Pacman game developed using C language and the Allegro 5 library. The game features smooth character movement, intelligent enemy ghosts, power-ups, and exciting gameplay.

## Features

- Component-based architecture for modular and maintainable code
- Smooth character movement and collision detection
- Intelligent pathfinding for enemy ghosts
- Power-ups and special abilities for Pacman
- Efficient graphics rendering and audio playback using Allegro 5
- Customizable game settings and difficulty levels
- Cross-platform compatibility
- Multiple game scenes including main menu, settings, gameplay, and win screen
- Customizable game settings such as volume control, music selection, and character selection
- Random movement strategy for red ghost (Blinky) to avoid walking back and forth
- Shortest path direction calculation for pink ghost to chase Pacman intelligently
- Scoring system and win condition when all pellets are eaten

## Installation

1. Clone the repository:

```
git clone https://github.com/Adeline0415/Pacman.git
```

2. Install the necessary dependencies:
   - Allegro 5 library

3. Compile the game:

```
cd pacman-game
make
```

4. Run the game:

```
./pacman
```

## Gameplay

- Use the arrow keys to move Pacman around the maze
- Collect all the pellets to advance to the next level
- Avoid the enemy ghosts or use power-ups to temporarily turn the tables
- Earn points by collecting pellets and defeating ghosts
- Strive for the highest score and beat your own records
- Customize game settings in the settings menu
- Enjoy the smooth gameplay and intelligent enemy behavior

## Code Structure

- `game.c`: Main game loop and game state management
- `pacman_obj.c`: Pacman character implementation and movement logic
- `ghost.c`: Enemy ghost implementation and AI behavior
- `map.c`: Game map representation and rendering
- `scene_game.c`: Main game scene and game logic
- `scene_menu.c`: Menu scene and user interface
- `scene_settings.c`: Settings scene for game customization
- `scene_win.c`: Win screen displayed when the player wins the game
- `ghost_red_move_script.c`: Movement script for the red ghost (Blinky)
- `ghost_pink_move_script.c`: Movement script for the pink ghost

## Contributing

Contributions are welcome! If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request.
