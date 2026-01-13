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