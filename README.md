# ⛵ Missionaries and Cannibals — C++ Console Game

A terminal-based implementation of the classic **Missionaries and Cannibals** river-crossing puzzle, developed as a **Programming Fundamentals (PF) course project**.

---

## 📖 Problem Statement

Three missionaries and three cannibals need to cross a river using a single boat that can carry **at most 2 people**. At no point — on either bank or in the boat — can cannibals outnumber missionaries (otherwise the missionaries get eaten). Move all six people to the right bank to win.

---

## 🎮 How to Play

### Controls
At each turn, you will be prompted to enter how many **Missionaries (M)** and **Cannibals (C)** to move on the boat:

```
Move from left to right (M C): 1 1
```

- Enter two space-separated integers: `M C`
- Valid values: `0 1`, `1 0`, `0 2`, `2 0`, `1 1`
- Enter `q` at any prompt to quit

### Rules
| Rule | Description |
|------|-------------|
| Boat capacity | Carries 1 or 2 people per trip |
| Safety constraint | Missionaries must never be outnumbered by cannibals on either bank |
| Win condition | All 6 people safely on the right bank |

---

## ✅ Example Solution (11 Moves)

| Move # | Action | Left Bank | Right Bank | Boat |
|--------|--------|-----------|------------|------|
| Start  | —      | 3M 3C     | —          | Left |
| 1      | → 0M 2C | 3M 1C   | 2C         | Right |
| 2      | ← 0M 1C | 3M 2C   | 1C         | Left |
| 3      | → 0M 2C | 3M 0C   | 3C         | Right |
| 4      | ← 0M 1C | 3M 1C   | 2C         | Left |
| 5      | → 2M 0C | 1M 1C   | 2M 2C      | Right |
| 6      | ← 1M 1C | 2M 2C   | 1M 1C      | Left |
| 7      | → 2M 0C | 0M 2C   | 3M 1C      | Right |
| 8      | ← 0M 1C | 0M 3C   | 3M 0C      | Left |
| 9      | → 0M 2C | 0M 1C   | 3M 2C      | Right |
| 10     | ← 0M 1C | 0M 2C   | 3M 1C      | Left |
| 11     | → 0M 2C | (empty) | 3M 3C      | Right ✅ |

---

## ⚙️ Functions Overview

| Function | Description |
|----------|-------------|
| `main()` | Game loop — handles input, validation, move execution, and win check |
| `displayState()` | Prints the current state of both banks and the boat |
| `readMove()` | Reads player input; handles `q` for quit and bad input gracefully |
| `isValidMove()` | Checks boat capacity (1–2 people) and availability on the source bank |
| `isSideSafe()` | Validates one bank: missionaries ≥ cannibals (or 0 missionaries) |
| `bothSidesSafe()` | Calls `isSideSafe` for both banks |
| `performMove()` | Transfers people across the river and flips the boat side |
| `checkWin()` | Returns `true` when all 6 people are on the right bank |

---

## 🔨 Build & Run

### Prerequisites
- A C++ compiler: `g++` (GCC), `clang++`, or MSVC
- Any OS: Windows, Linux, or macOS

### Compile
```bash
g++ -o missionaries main.cpp
```

### Run
```bash
./missionaries          # Linux / macOS
missionaries.exe        # Windows
```

---

## 🧠 Concepts Demonstrated

- **Functions & Prototypes** — modular design with well-separated responsibilities
- **Pass by Reference** — state is updated cleanly via `int&` and `bool&` parameters
- **Input Validation** — handles non-integer input, out-of-range values, and quit signals
- **Game State Management** — temporary move simulation before committing changes
- **Control Flow** — `while` loop, `continue` for invalid moves, `break` on win/quit

---

## 📸 Sample Output

```
=======================================
  Missionaries and Cannibals Game
=======================================
Rules:
 - Move all 6 people to the right bank.
 - The boat can carry 1 or 2 people.
 - On either bank, missionaries must never be outnumbered by cannibals.
 - Enter 'q' at any prompt to quit.
=======================================

--- Current State ---
Left bank:  M M M C C C
Right bank: (empty)
Boat is on the left bank.
----------------------
Move from left to right (M C): 0 2

🎉 Congratulations! You won the game in 11 moves.
```

---

## 👤 Author

**M.Sami-Ullah Yousaf**  
Programming Fundamentals — Course Project  
**University OF Management and Technology**  
**2024**

---

## 📄 License

This project is for educational purposes only.
