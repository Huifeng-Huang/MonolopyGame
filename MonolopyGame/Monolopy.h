#pragma once

#include <list>
#include <tuple>
#include <string>

#define RENT_COST 250
#define PRISON_COST 1000
#define BANK_COST 700

class Monopoly
{
public:
	enum class Type
	{
		AUTO,
		FOOD,
		TRAVEL,
		CLOTHER,
		PRISON,
		BANK
	};
	Monopoly(std::string names[10], int);
	std::list<std::tuple<std::string, int>>* GetPlayersList();
	std::list<std::tuple<std::string, Type, int, bool>>* GetFieldsList();
	std::list<std::tuple<std::string, Type, int, bool>> Fields;
	bool Buy(int const, std::tuple<std::string, Type, int, bool>);
	bool Renta(int const, std::tuple<std::string, Type, int, bool>&);
private:
	const std::tuple<std::string, int>& GetPlayerInfo(int);
	std::tuple<std::string, Type, int, bool> GetFieldByName(std::string);
	list<tuple<string, int>>::iterator FindPlayerInfoByName(const std::string&);
	std::list<std::tuple<std::string, Type, int, bool>>::iterator FindFieldByName(const std::tuple < std::string, Type, int, bool>& fieldInfo);
	int GetFieldCost(const std::tuple<std::string, Type, int, bool>& fieldInfo) const;
	void UpdatePlayerBalance(int, int);
	void UpdateFieldOwner(std::list<std::tuple<std::string, Type, int, bool>>::iterator fieldIter, int playerIndex);
	void UpdatePlayerInfo(int, tuple<string, int>&, int);
	std::list<std::tuple<std::string, int>> Players;
}; 
