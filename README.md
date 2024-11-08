# Snake Game 🐍

A classic Snake game implemented in C++ with **multithreading** for enhanced gameplay. This simple console game is fun to play and demonstrates essential programming concepts like game loops, input handling, and multithreading.

## Features
- **Classic Gameplay**: Control the snake, eat fruits, grow longer, and increase your score.
- **Multithreading**: The game utilizes a separate thread to handle background music or sound effects.
- **Wrap-around Walls**: The snake can pass through one wall and reappear on the opposite side.
- **Expandable Snake**: Each fruit the snake consumes will increase its length.
- **Simple Controls**: 
  - **`W`** - Move Up
  - **`S`** - Move Down
  - **`A`** - Move Left
  - **`D`** - Move Right
  - **`X`** - Exit Game

## How It Works
This Snake game is built in C++ and uses **multithreading** to play background sounds without interrupting gameplay. The main game loop handles the rendering, user input, and game logic in sequence, while a separate thread plays sounds to enhance the user experience.

### Multithreading Example
The `threaded()` function, which plays a sound, is run in a separate thread so it doesn’t block the main game loop:
```cpp
void threaded(){
    PlaySound(TEXT("JOLA.wav"), NULL, SND_SYNC);
}
