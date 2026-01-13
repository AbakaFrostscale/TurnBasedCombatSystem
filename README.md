# Turn-Based Combat Prototype (C++)

## Overview

This project is a **logic-only, engine-agnostic turn-based combat system** written in modern C++.  
It is designed as a **portfolio piece** to demonstrate gameplay systems programming, clean architecture, and Unreal Engine–inspired coding conventions without relying on any engine-specific APIs.

The system simulates combat between two teams (Players vs Enemies), handling turn order, damage calculation, critical hits, team elimination, and combat resolution.

---

## Key Features

- **Turn-based combat loop**
- **Multiple combatants per team**
- **Team-based targeting logic**
- **Randomized damage ranges**
- **Critical hit system (5% chance)**
- **Mid-round victory condition checks**
- **Clean separation of responsibilities**
- **Engine-agnostic design (logic only)**

---

## Design Goals

- Demonstrate **gameplay logic over presentation**
- Follow **UE-style naming conventions** (`FCombatant`, `ETeam`, etc.)
- Keep the system **portable** and easy to integrate into any engine
- Emphasize **clarity, correctness, and maintainability**
- Avoid premature optimization or over-engineering

---

## Project Structure

[TurnBasedCombat.cpp](https://github.com/user-attachments/files/24581414/TurnBasedCombat.cpp)

This prototype is intentionally contained in a single file to keep the focus on logic flow and readability.  
In a full project, this would be split into headers, source files, and integrated with engine systems.

---

## How It Works

### Combat Flow

1. Combat begins while **both teams are alive**
2. Each living combatant takes a turn
3. A valid target is randomly selected from the opposing team
4. Damage is calculated using:
   - A random range per combatant
   - A 5% chance to deal double damage (critical hit)
5. Health is clamped to prevent underflow
6. Combat ends immediately if a team is wiped out

---

## Example Output

Player1 attacks Enemy3 for 12 damage!
Enemy1 attacks Player2 for 18 damage!
Player2 attacks Enemy1 for 30 damage!
Enemy3 attacks Player4 for 11 damage!

Player1 in Players - 100/100
Enemy1 in Enemies - 72/120
Player2 in Players - 82/100
Enemy2 in Enemies - 120/120
Player3 in Players - 100/100
Enemy3 in Enemies - 108/120
Player4 in Players - 89/100
Enemy4 in Enemies - 120/120


---


---

## Compilation

This project uses only the C++ standard library.

### Example (GCC / Clang)

```bash
g++ TurnBasedCombat.cpp -std=c++17 -o TurnBasedCombat
./TurnBasedCombat
```

---

## Optional: GitHub Tags / Topics

c++
gameplay-programming
turn-based-combat
game-systems
engine-agnostic
portfolio-project
unreal-engine-style


---

If you want, I can also:
- Tighten this further for **AAA gameplay programmer applications**
- Rewrite it for a **technical recruiter audience**
- Add a **design commentary section**
- Or help you split this into `.h/.cpp` for presentation polish

Just say the word.




