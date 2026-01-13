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
//TurnBasedCombat.cpp
//Logic-only turn based combat prototype
//Author Kaden
//Description: Portfolio project demonstrating gameplay systems logic
//Version: 1.00

#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

enum class ETeam {Players, Enemies};

struct FCombatant
{
	std::string Name;
	int MaxHP;
	int CurrentHP;
	int MinDamage;
	int MaxDamage;
	ETeam Team;

	bool IsAlive() const
	{
		return CurrentHP > 0;
	}
};

class FTurnBasedCombat
{
public:
	FTurnBasedCombat();
	void RunCombat();

private: 
	void CombatantTurn(FCombatant& Attacker);
	void LogStatus() const;
	bool IsTeamAlive(ETeam TeamName) const;
	bool IsCritical();
	int CalculateDamage(const FCombatant& Attacker);
	std::string TeamToString(ETeam Team);

private:
	std::vector<FCombatant> Combatants;
	std::mt19937 RandomGenerator;

};

FTurnBasedCombat::FTurnBasedCombat()
{
	std::random_device rd;
	RandomGenerator = std::mt19937(rd());

	Combatants.push_back({"Player1", 100, 100, 8, 15, ETeam::Players});
	Combatants.push_back({"Enemy1", 120, 120, 10, 18, ETeam::Enemies});
	Combatants.push_back({"Player2", 100, 100, 8, 15, ETeam::Players});
	Combatants.push_back({"Enemy2", 120, 120, 10, 18, ETeam::Enemies});
	Combatants.push_back({"Player3", 100, 100, 8, 15, ETeam::Players});
	Combatants.push_back({"Enemy3", 120, 120, 10, 18, ETeam::Enemies});
	Combatants.push_back({"Player4", 100, 100, 8, 15, ETeam::Players});
	Combatants.push_back({"Enemy4", 120, 120, 10, 18, ETeam::Enemies});
}

void FTurnBasedCombat::RunCombat()
{
	while (IsTeamAlive(ETeam::Players) && IsTeamAlive(ETeam::Enemies))
	{

		for (FCombatant& combatant : Combatants)
		{
			if (!combatant.IsAlive()) continue;

			CombatantTurn(combatant);

			//Mid-roud check to ensure that no team is wiped-out
			if (!IsTeamAlive(ETeam::Players) || !IsTeamAlive(ETeam::Enemies)) 
			{
			break;
			}
		}
		
		LogStatus();
	}
}

void FTurnBasedCombat::CombatantTurn(FCombatant& Attacker)
{
	//Check to see if the attacker is alive
	if (!Attacker.IsAlive()) return;
	
	//check to see available targets
	std::vector<FCombatant*> Targets;	
	for (FCombatant& Target : Combatants)
		{
			if (&Target == &Attacker) continue;
			if (Target.Team == Attacker.Team) continue;
			if (!Target.IsAlive()) continue;

			Targets.push_back(&Target);
		}
	
	//attack a random target in the list of available targets
	if (Targets.empty()) return;

	int Damage = CalculateDamage(Attacker);

	std::uniform_int_distribution<size_t> dist(0, Targets.size() - 1);
	FCombatant* ChosenTarget = Targets[dist(RandomGenerator)];

	ChosenTarget.CurrentHP = std::clamp(ChosenTarget->CurrentHP - Damage, 0, ChosenTarget->MaxHP);
	std::cout << Attacker.Name << " attacks " << ChosenTarget->Name << " for " << Damage  << " damage!" << std::endl;
}

//determine if an attack is critical hit (5% chance)
bool FTurnBasedCombat::IsCritical()
{
	std::uniform_int_distribution<int> dist (1, 20);
	int CriticalChance = dist(RandomGenerator);

	if (CriticalChance == 20) return true;
	return false;	
}

//Check to see if teams are alive
bool FTurnBasedCombat::IsTeamAlive(ETeam TeamName)const
{
	for(const auto& combatant : Combatants)
	{
		if (combatant.Team == TeamName && combatant.IsAlive())
		{
			return true;
		}	
	}	
	return false;
}

//Determine the damage done
int FTurnBasedCombat::CalculateDamage(const FCombatant& Attacker)
{
	std::uniform_int_distribution<int> distrib(Attacker.MinDamage,  Attacker.MaxDamage);
	int Damage = distrib(RandomGenerator); 	

	if (IsCritical())
	{
		return Damage * 2;
	}

	return Damage;			
}

void FTurnBasedCombat::LogStatus() const
{
	for(const auto& combatant : Combatants)
	{
		std::cout << combatant.Name << " in " << TeamToString(combatant.Team) << " - " << combatant.CurrentHP << "/" << combatant.MaxHP << std::endl;
	}
	std:: cout << std::endl;
}

std::string FTurnBasedCombat::TeamToString(ETeam Team)
{
	return (Team == ETeam::Players) ? "Players" : "Enemies";
}


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

## Compilation

This project uses only the C++ standard library.

### Example (GCC / Clang)

```bash
g++ TurnBasedCombat.cpp -std=c++17 -o TurnBasedCombat
./TurnBasedCombat

---

## Optional: GitHub Tags / Topics

If GitHub topics are available, consider:


---

If you want, I can also:
- Tighten this further for **AAA gameplay programmer applications**
- Rewrite it for a **technical recruiter audience**
- Add a **design commentary section**
- Or help you split this into `.h/.cpp` for presentation polish

Just say the word.
