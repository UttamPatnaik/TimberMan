# 🌲 Timber Man — C++ Game Project

A fun arcade-style **tree chopping game** built using **C++** and the **SFML graphics library** 🎮  
This project is part of our **academic curriculum** and focuses on game logic, graphics rendering, event handling, and real-time user interaction.

> **Objective**  
> - Cut the tree 🌳  
> - Avoid the branches ❌  
> - Survive as long as you can ⏱️  
> - Simple rules. Addictive gameplay. Pure fun.

⚠️ **Project Status:**  
This game is **not fully complete** and is still under development as part of learning and academic practice.

---

## 🎮 Game Concept

The player stands beside a tree and chops it while avoiding falling branches.  
The game challenges the player with:

- Time pressure ⏳  
- Random branch generation 🌲  
- Moving obstacles (bee animation) 🐝  
- Reaction-based controls 🎮  

**Goal**:  
Chop the tree repeatedly → score points → survive longer.

---

## 🚀 Features

- Real-time gameplay
- Keyboard-based controls
- Sound effects 🎵
- Animated graphics 🖼️
- Score system
- Smooth rendering using SFML

---

## 🧠 Core Gameplay Mechanics

| System            | Description                                      |
|-------------------|--------------------------------------------------|
| Branch System     | Randomized branches fall from the tree           |
| Time System       | Countdown timer that limits survival time        |
| Player System     | Player moves left/right and chops                |
| Obstacle System   | Bee moves across screen dynamically              |
| Scoring System    | Score increases on successful chops              |
| Pause System      | Game starts on Enter key                         |
| UI System         | Text rendering for score and messages            |

---

## 🎯 Controls

| Key              | Action                     |
|------------------|----------------------------|
| **Enter**        | Start game                 |
| **Left Arrow**   | Move left & chop           |
| **Right Arrow**  | Move right & chop          |
| **Escape**       | Exit game                  |

---

## 🧱 Technical Architecture

The game follows a **modular procedural architecture**:

- Game Loop based system
- Frame-based updates
- Time-delta physics
- Event-driven input handling
- Sprite-based rendering
- State-based logic (paused / running)

---

## 🗂 Project Structure

```text
TimberMan/
│
├── fonts/          # Font files used in the game
├── graphics/       # Images & sprites
├── sounds/         # Sound effects
│
├── Timber.cpp      # Main source code
├── Timber.exe      # Executable file (click to run the game)
└── README.md       # Project documentation

⚙️ How to Compile & Run
🛠️ Compile and Execute using terminal:
Bashg++ Timber.cpp -o Timber -lsfml-graphics -lsfml-window -lsfml-system && ./Timber
▶️ Direct Execution
You can also run the game by simply double-clicking the executable file:
BashTimber.exe

🧩 Code System Breakdown
1️⃣ Branch System
C++const int NUM_BRANCHES = 6;
enum class Side { LEFT, RIGHT, NONE };

Branches stored in arrays
Positions updated using shifting logic
Random generation using rand() + seed
Each branch has: Position, Rotation, Side state

Function:
C++void updateBranches(int seed)
Purpose:

Shift branches down
Generate new random branch
Control randomness using time-based seed

2️⃣ Time System (Timer Bar)

Clock, delta time (dt), timeRemaining, timeBarWidthPerSecond
Shrinking time bar
Game pause when time reaches zero
Real-time countdown + visual feedback

3️⃣ Player System

Sprite-based movement
Position switching
Axe alignment
Side-based logic

4️⃣ Bee Obstacle System 🐝

Random speed generation
Random height generation
Screen traversal
Respawn logic
Dynamic animation

5️⃣ Game State System
C++bool paused = true;

Start screen
Pause logic
Timer freeze
Input gating
Message display system

6️⃣ UI System

Score rendering
Message rendering
Font management
Centered text logic
Dynamic UI updates


🎯 Learning Outcomes

Game loop implementation
Event handling
Asset management (fonts, graphics, sounds)
Real-time rendering
Memory handling in C++
Project structuring


📚 Academic Purpose
This project was developed as part of our academic curriculum to strengthen:

C++ programming concepts
Game development fundamentals
Library integration
Real-world project structuring


🧑‍💻 Author

Developed by: Uttam Patnaik
Course: Academic Project
Domain: Game Development / C++


⚠️ Limitations & Planned Improvements
Current Limitations:

Collision detection
Player death logic
Game over screen
Restart system
Branch collision physics
Falling animations
Sound effects system
Menu system
Difficulty scaling

Planned Improvements:

Branch collision detection
Player death animation
Game over screen
Restart button
Falling tree physics
Sound effects & background music
Difficulty scaling
Progressive speed
UI animations
Menu system
Pause menu


📌 Version & Status

Version: 0.4-alpha
Build Type: Development
Stage: Prototype
Stability: Experimental


🌲 Timber Man — Chop. Dodge. Survive. Learn. Repeat. 🎮
