# 🌲 Timber Man — C++ Game Project

A fun arcade-style **tree chopping game** built using **C++** and the **SFML graphics library** 🎮
This project is part of our **academic curriculum** and focuses on game logic, graphics rendering, event handling, and real-time user interaction.

> **Objective**
>
> * Cut the tree 🌳
> * Avoid the branches ❌
> * Survive as long as you can ⏱️
> * Simple rules. Addictive gameplay. Pure fun.

⚠️ **Project Status:**
This game is **under active development** as part of learning and academic practice.

---

## 🎮 Game Concept

The player stands beside a tree and chops it while avoiding falling branches.
The game challenges the player with:

* Time pressure ⏳
* Random branch generation 🌲
* Moving obstacles (bee animation) 🐝
* Environmental animations (cloud system ☁️)
* Reaction-based controls 🎮

**Goal**:
Chop the tree repeatedly → score points → survive longer.

---

## 🚀 Features

* Real-time gameplay
* Keyboard-based controls
* Animated graphics 🖼️
* Score system
* Time pressure system
* Branch randomization system
* Bee obstacle system 🐝
* Cloud animation system ☁️
* RIP stone death indicator 🪦
* Smooth rendering using SFML

---

## 🧠 Core Gameplay Mechanics

| System          | Description                               |
| --------------- | ----------------------------------------- |
| Branch System   | Randomized branches fall from the tree    |
| Time System     | Countdown timer with shrinking time bar   |
| Player System   | Player moves left/right and chops         |
| Obstacle System | Bee moves dynamically across the screen   |
| Environment     | Animated clouds system                    |
| Death System    | RIP stone appears when player is squished |
| Scoring System  | Score increases on successful chops       |
| Input System    | Input gating using acceptInput logic      |
| State System    | paused / running game states              |

---

## 🎯 Controls

| Key             | Action               |
| --------------- | -------------------- |
| **Enter**       | Start / Restart game |
| **Left Arrow**  | Move left & chop     |
| **Right Arrow** | Move right & chop    |
| **Escape**      | Exit game            |

---

## 🧱 Technical Architecture

The game follows a **structured procedural game architecture**:

* Central game loop
* Delta-time based movement
* Event-driven input system
* Sprite-based rendering
* State-based logic (paused / running / dead)
* Modular systems (branches, clouds, bee, UI)
* Input gating system
* Real-time animation systems

---

## 🗂 Project Structure

```text
TimberMan/
│
├── fonts/          # Font files used in the game
├── graphics/       # Images & sprites
├── sounds/         # Sound effects (planned)
│
├── Timber.cpp      # Main source code
├── Timber.exe      # Executable file
└── README.md       # Project documentation
```

---

## ⚙️ How to Compile & Run

### 🛠️ Compile and Execute (Terminal)

```bash
g++ Timber.cpp -o Timber -lsfml-graphics -lsfml-window -lsfml-system && ./Timber
```

### ▶️ Direct Execution

```bash
Timber.exe
```

---

## 🧩 Code System Breakdown

### 1️⃣ Branch System

* Fixed-size branch array
* Position shifting logic
* Random generation using seeded randomness
* Side-based collision logic

Function:

```cpp
void updateBranches(int seed)
```

Purpose:

* Shift branches downward
* Generate new random branch
* Control randomness

---

### 2️⃣ Time System

* Delta-time based countdown
* Shrinking time bar
* Automatic pause on zero time
* Visual feedback system

---

### 3️⃣ Player System

* Sprite-based movement
* Left/Right positioning
* Axe alignment system
* Side-based logic
* Input gating system

---

### 4️⃣ Bee Obstacle System 🐝

* Random speed generation
* Random height generation
* Screen traversal
* Respawn logic
* Continuous animation

---

### 5️⃣ Cloud Animation System ☁️

* Multi-cloud system
* Independent cloud speeds
* Random height generation
* Looping animation
* Environmental depth effect

---

### 6️⃣ Death System 🪦

* Branch collision detection
* Player squish detection
* RIP stone sprite rendering
* Death state activation
* Visual feedback system

---

### 7️⃣ Game State System

```cpp
bool paused = true;
```

Handles:

* Start screen
* Pause logic
* Death state
* Input blocking
* UI message system

---

### 8️⃣ UI System

* Score rendering
* Message rendering
* Centered text system
* Font management
* Dynamic UI updates

---

## 🎯 Learning Outcomes

* Game loop implementation
* Real-time systems design
* Event handling
* Asset management
* Modular game logic
* Animation systems
* State management
* Input systems
* Time-based physics
* Structured C++ architecture

---

## 📚 Academic Purpose

This project was developed as part of our academic curriculum to strengthen:

* C++ programming concepts
* Game development fundamentals
* Library integration
* Real-world project structuring
* Software architecture
* Interactive system design

---

## 🧑‍💻 Author

**Developed by:** Uttam Patnaik
**Course:** Academic Project
**Domain:** Game Development / C++

---

## ⚠️ Limitations

* No physics-based branch falling
* No true collision physics
* No audio system yet
* No menu system
* No save system
* No difficulty scaling
* No animations for death

---

## 🔮 Planned Improvements

* Physics-based falling branches
* Player death animation
* Game over screen
* Restart button
* Sound effects
* Background music
* Difficulty scaling
* Progressive speed system
* UI animations
* Menu system
* Pause menu
* Settings menu
* Score persistence
* High-score system

---

## 📌 Version & Status

**Version:** 0.5-alpha
**Build Type:** Development
**Stage:** Prototype+
**Stability:** Experimental

---

🌲 **Timber Man — Chop. Dodge. Survive. Learn. Repeat.** 🎮
