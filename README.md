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

