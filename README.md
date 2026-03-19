# 🌲 Timber Man — C++ / SFML Arcade Game

A fast-paced **arcade-style tree chopping game** built using **C++** and the **SFML multimedia library** 🎮.  
This project demonstrates real-time rendering, input handling, animation systems, sound integration, and gameplay logic.

This game is developed as part of an **academic learning project** to practice **game programming, system design, and multimedia development using C++**.

---

# 🎮 Game Objective

The player stands beside a tree and chops it repeatedly while avoiding falling branches.

Your goal is to:

• Chop the tree 🌳  
• Avoid getting crushed by branches ❌  
• Beat the timer ⏱️  
• Score as many points as possible 🎯  

---

# 🚀 Features

## 🎮 Gameplay Systems
• Real-time gameplay loop  
• Score tracking system  
• Random branch generation  
• Time pressure system  

## 🌍 Environment & Animation
• Animated cloud system (3 independent clouds) ☁️  
• Moving bee obstacle 🐝  
• Log launch animation when chopping 🪵  

## 🔊 Game Feedback (NEW)
• Chop sound effect  
• Death sound effect  
• Out-of-time sound effect  
• Visual death indicator (RIP stone) 🪦  

## 🎹 Controls & Input
• Keyboard-based player control  
• Input gating system (`acceptInput`) to prevent spam  

---

# 🎯 Controls

| Key | Action |
|-----|------|
| **Enter** | Start / Restart Game |
| **Left Arrow** | Move left & chop |
| **Right Arrow** | Move right & chop |
| **Close Window** | Exit game |

---

# 🧱 Technical Architecture

The project follows a **procedural real-time game architecture**:

• Central game loop  
• Delta-time based movement  
• Event-driven input handling  
• Sprite-based rendering  
• State-based logic (paused / running / dead)  
• Modular gameplay systems  
• Real-time animation systems  

---

# 🗂 Project Structure

```
TimberMan/
│
├── graphics/        # Sprites and textures
├── font/            # Font files
├── sound/           # Sound effects (chop, death, timeout)
│
├── Timber.cpp       # Main game source code
└── README.md        # Documentation
```

---

# ⚙️ Build & Run

### 🛠 Compile

```
g++ Timber.cpp -o Timber -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

### ▶ Run

```
./Timber
```

---

# 🧩 Code System Breakdown

## 1️⃣ Branch System 🌲

```cpp
const int NUM_BRANCHES = 6;
enum class Side { LEFT, RIGHT, NONE };
```

### Logic
• Branch positions shift downward each chop  
• New branches spawn randomly  
• Branches appear on LEFT / RIGHT / NONE  

### Function
```cpp
void updateBranches(int seed)
```

---

## 2️⃣ Time System ⏱️

### Components
• `Clock`  
• `dt (delta time)`  
• `timeRemaining`  
• `timeBarWidthPerSecond`  

### Functionality
• Timer decreases continuously  
• Time bar shrinks visually  
• Game pauses at zero  
• Sound plays when time runs out  

---

## 3️⃣ Player System 🎮

### Features
• Left/Right movement  
• Axe alignment  
• Score increment on chop  
• Time bonus per chop  

### Input System
```cpp
bool acceptInput;
```

Prevents multiple inputs per frame.

---

## 4️⃣ Log Animation System 🪵 (NEW)

### Features
• Log launches on every chop  
• Direction based on player side  
• Uses velocity (X & Y movement)  
• Resets after leaving screen  

### Variables
```cpp
bool logActive;
float logSpeedX;
float logSpeedY;
```

---

## 5️⃣ Bee Obstacle System 🐝

### Features
• Random speed  
• Random height spawn  
• Moves across screen  
• Respawns automatically  

---

## 6️⃣ Cloud System ☁️

### Features
• 3 independent clouds  
• Random speeds  
• Random spawn heights  
• Continuous looping animation  

---

## 7️⃣ Sound System 🔊 (NEW)

### Sounds Used

| Sound | Trigger |
|------|--------|
| `chop.wav` | When player chops |
| `death.wav` | When player dies |
| `out_of_time.wav` | When timer ends |

### Implementation
```cpp
SoundBuffer
Sound
```

---

## 8️⃣ Death System 🪦

### Trigger
• Branch collision with player side  

### Effects
• Player disappears  
• RIP gravestone appears  
• Game pauses  
• Death sound plays  
• "SQUISHED!!" message displayed  

---

## 9️⃣ Game State System

```cpp
bool paused;
bool acceptInput;
```

Handles:
• Start / restart  
• Pause logic  
• Death state  
• Input blocking  

---

## 🔟 UI System

### Components
• Score text  
• Message text  
• Timer bar  

### Features
• Real-time score updates  
• Centered messages  
• Dynamic time bar  

---

# 🎯 Learning Outcomes

• Game loop architecture  
• Real-time rendering  
• Delta-time mechanics  
• Sprite animation systems  
• Input management  
• Procedural randomness  
• Audio integration (NEW)  
• Event-driven programming  
• Game state management  

---

# 📚 Academic Purpose

This project was developed to practice:

• C++ programming  
• Multimedia integration (SFML)  
• Game development fundamentals  
• Real-time system design  
• Modular architecture  

---

# ⚠️ Current Limitations

• No advanced physics system  
• No menu UI  
• No difficulty scaling  
• No high score saving system  
• No background music  
• No animation transitions  

---

# 🔮 Planned Improvements

• High score system 💾  
• Difficulty scaling  
• Background music  
• Particle effects  
• UI animations  
• Menu system  
• Pause menu  
• Settings menu  

---

# 🧑‍💻 Author

**Developer:** Uttam Patnaik  
**Project Type:** Academic Game Project  
**Language:** C++  
**Library:** SFML  

---

# 📌 Version Information

**Version:** 0.6-alpha  
**Build Type:** Development  
**Stage:** Prototype+  
**Stability:** Experimental  

---

# 🌲 Timber Man

**Chop. Dodge. Survive. Improve. Repeat.** 🎮