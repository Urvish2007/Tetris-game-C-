# 🎮 **Comprehensive Explanation of the Tetris Game Code**

## 📜 **Table of Contents**
1. 🔹 **Introduction**
2. 🔹 **Code Structure Overview**
3. 🔹 **Key Components**
   - 📌 Constants and Includes
   - 📌 Console Handling Utilities
   - 📌 Tetromino Class
   - 📌 TetrisGame Class
4. 🔹 **Game Logic and Mechanics**
   - ⚙️ Collision Detection
   - ⚙️ Piece Movement and Rotation
   - ⚙️ Line Clearing and Scoring
   - ⚙️ Game Speed and Levels
5. 🔹 **User Input Handling**
6. 🔹 **Rendering and Display**
7. 🔹 **Game Loop and Flow**
8. 🔹 **Conclusion**
9. 🔹 **Screenshots and Video Demo**

---

## 🎯 **1. Introduction**
This document provides a **detailed breakdown** of a **Tetris game** implemented in **C++** using the **Windows Console API**. The code includes:
- 🎲 **Tetromino shapes and rotations**
- 🛡️ **Collision detection**
- 🏆 **Scoring and level progression**
- 🎮 **User input handling**
- 🔄 **Game state management (pause, restart, game over)**

---

## 🏗 **2. Code Structure Overview**
The code is structured into:
- 📌 **Header Includes** (`<iostream>`, `<vector>`, `<Windows.h>`, etc.)
- 📌 **Constants** (grid size, key codes, colors)
- 📌 **Utility Functions** (console cursor, color settings)
- 📌 **Tetromino Class** (handles piece shapes, rotation, movement)
- 📌 **TetrisGame Class** (manages game state, logic, and rendering)
- 📌 **Main Function** (game loop and initialization)

---

## 🛠 **3. Key Components**

### 🔹 **3.1 Constants and Includes**
The code uses:
- 🖥️ **`<Windows.h>`** for console manipulation.
- 📋 **`<vector>`** for dynamic grid storage.
- 🎹 **`<conio.h>`** for keyboard input.
- ⏳ **`<chrono>`** for timing and game speed.

**Key Constants:**
- 📏 `WIDTH = 12`, `HEIGHT = 20` (grid size for gameplay).
- ⏱️ `STARTING_SPEED = 450`ms (initial fall speed of pieces).
- ⏩ `INCREASE_SPEED = 20`ms (speed increment per level).
- 🔥 `LINESPERLEVEL = 10` (lines required to level up).
- 🏆 `THSCORE = 1000` (score threshold for difficulty increase).
- 🔳 **Tetromino shapes** stored as 2D vectors.
- 🎨 **Color mappings** for different Tetromino types.

### 🔹 **3.2 Console Handling Utilities**
- ✏️ `setCursorPosition(x, y)`: Moves the console cursor.
- 🎨 `setConsoleColor(text, bg)`: Changes text and background color.
- 🔄 `resetConsoleColor()`: Resets to default (white on black).

### 🔹 **3.3 Tetromino Class**
**Responsibilities:**
- 🏗️ Stores **piece type** (I, O, T, etc.).
- 🔄 Handles **rotation** (90° clockwise).
- 📍 Manages **position (x, y)**.
- 🛑 Provides **collision detection**.

**Key Methods:**
- 🔍 `getShape()`: Returns the current shape (considering rotation).
- 🔄 `rotateMatrix()`: Rotates the piece.
- ⬅️➡️⬇️ `moveLeft()`, `moveRight()`, `moveDown()`: Adjust position.

### 🔹 **3.4 TetrisGame Class**
**Core Game Logic:**
- 🎨 **Grid Management** (storing placed blocks).
- 🎮 **Piece Movement** (left, right, down, rotation).
- 🛡️ **Collision Detection** (checks if a move is valid).
- 💥 **Line Clearing** (updates score and level).
- 🔄 **Game State** (pause, game over, restart).

**Key Methods:**
- ❌ `isCollision()`: Checks if a piece overlaps with the grid.
- 📍 `placePiece()`: Locks the piece in place.
- 🔥 `clearLines()`: Removes completed lines.
- ⬇️ `hardDrop()`: Instantly drops the piece.
- ⏳ `update()`: Handles automatic falling.
- 🎨 `draw()`: Renders the game state.

---

## ⚙️ **4. Game Logic and Mechanics**

### 🔹 **4.1 Collision Detection**
- 🚧 Checks if a piece **exceeds grid bounds**.
- 🔍 Detects **overlaps with placed blocks**.
- 🛠 Uses **temporary position checks** before applying moves.

### 🔹 **4.2 Piece Movement and Rotation**
- 🎮 **Arrow keys** control movement.
- 🔄 **Rotation** is applied using matrix transformation.
- ⏬ **Soft drop (Down key)** speeds up falling.
- 🚀 **Hard drop (Space)** instantly places the piece.

### 🔹 **4.3 Line Clearing and Scoring**
- 🏆 **Scoring**:
  - 🎯 **100 points per line × level**.
  - 📈 **Level increases** every 10 lines.
- ⏩ **Speed increases** with score (`fallSpeed` decreases).

### 🔹 **4.4 Game Speed and Levels**
- ⏳ **`STARTING_SPEED = 450ms`**, reduced by `INCREASE_SPEED = 20ms` per level.
- 🎚 **Level progression** (`LINESPERLEVEL = 10`).
- 🏆 **Difficulty increases** at `THSCORE = 1000` points.

---

## 🎮 **5. User Input Handling**
- ⬅️➡️ **Arrow Keys**: Move and rotate the piece.
- 🔽 **Space**: Hard drop.
- ⏸ **P**: Pause/resume.
- ❌ **1**: End game.
- 🔄 **2**: Restart game.
- 🚪 **ESC**: Quit.

---

## 🎨 **6. Rendering and Display**
- 🕹 **Grid** is drawn using ASCII characters (`#` for blocks).
- 🎨 **Colors** differentiate Tetromino types.
- 🔜 **Next Piece** is displayed beside the grid.
- 🚨 **Game Over** and **Pause** messages appear when triggered.

---

## 🔄 **7. Game Loop and Flow**
1. 🚀 **Initialize** game (grid, first piece).
2. 🔄 **Loop** until game over:
   - ⌨️ **Handle input** (movement, rotation).
   - 🔧 **Update** game state (falling, collisions).
   - 🖥 **Draw** the grid, score, and next piece.
3. ☠️ **Game Over**:
   - 🔄 Option to **restart** or **exit**.

---

## 🏁 **8. Conclusion**
This implementation covers:
- 🧩 **Core Tetris mechanics** (rotation, movement, scoring).
- 🎨 **Console-based rendering** (colors, cursor control).
- 🎮 **User interaction** (keyboard controls).
- 🛠 **Extensible structure** (easy to modify difficulty, add features).

---

## 📸 **9. Screenshots and Video Demo**
![Screenshot 2025-03-27 183457](https://github.com/user-attachments/assets/fb60eb0d-0d46-4440-b031-743465d9641f)


https://github.com/user-attachments/assets/213625ce-b974-4dc8-bb05-c2fd5909112a


(Add video link here)

