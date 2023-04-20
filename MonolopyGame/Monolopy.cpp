#include "pch.h"
#include "Monolopy.h"
#include <algorithm>

using namespace ::std;


Monopoly::Monopoly(std::string names[10], int countPlaers)
{
	for (int i = 0; i < countPlaers; i++)
	{
		Players.push_back(make_tuple(names[i], 6000));
	}
	Fields.push_back(make_tuple("Ford", Monopoly::Type::AUTO, 0, false));
	Fields.push_back(make_tuple("MCDonald", Monopoly::Type::FOOD, 0, false));
	Fields.push_back(make_tuple("Lamoda", Monopoly::Type::CLOTHER, 0, false));
	Fields.push_back(make_tuple("Air Baltic", Monopoly::Type::TRAVEL, 0, false));
	Fields.push_back(make_tuple("Nordavia", Monopoly::Type::TRAVEL, 0, false));
	Fields.push_back(make_tuple("Prison", Monopoly::Type::PRISON, 0, false));
	Fields.push_back(make_tuple("MCDonald", Monopoly::Type::FOOD, 0, false));
	Fields.push_back(make_tuple("TESLA", Monopoly::Type::AUTO, 0, false));
}

std::list<std::tuple<std::string, int>>* Monopoly::GetPlayersList()
{
	return &Players;
}

std::list<std::tuple<std::string, Monopoly::Type, int, bool>>* Monopoly::GetFieldsList()
{
	return &Fields;
}

const std::tuple<std::string, int>& Monopoly::GetPlayerInfo(int playerIndex)
{
	return *(std::next(Players.begin(), playerIndex - 1));
}

bool Monopoly::Buy(int const playerIndex, std::tuple<std::string, Type, int, bool> fieldInfo)
{
	auto fieldIterator = FindFieldByName(fieldInfo);
	UpdateFieldOwner(fieldIterator, playerIndex);
	UpdatePlayerBalance(playerIndex, get<1>(GetPlayerInfo(playerIndex)) - GetFieldCost(fieldInfo));

	return true;
}
std::list<std::tuple<std::string, Monopoly::Type, int, bool>>::iterator Monopoly::FindFieldByName(const std::tuple<std::string, Type, int, bool>& fieldInfo)
{
	return std::find_if(Fields.begin(), Fields.end(), [fieldInfo](const auto& field) {
		return get<0>(field) == get<0>(fieldInfo);
		});
}
list<tuple<string, int>>::iterator Monopoly::FindPlayerInfoByName(const std::string& playerName)
{
	return find_if(Players.begin(), Players.end(),
		[&](const auto& playerInfo) { return get<0>(playerInfo) == playerName; });
}
int Monopoly::GetFieldCost(const std::tuple<std::string, Type, int, bool>& fieldInfo) const
{
	switch (get<1>(fieldInfo))
	{
	case Type::AUTO:
		return 500;
	case Type::FOOD:
		return 250;
	case Type::TRAVEL:
		return 700;
	case Type::CLOTHER:
		return 100;
	default:
		return 0;
	}
}
void Monopoly::UpdateFieldOwner(std::list<std::tuple<std::string, Monopoly::Type, int, bool>>::iterator fieldIter, int playerIndex)
{
	*fieldIter = std::make_tuple(get<0>(*fieldIter), get<1>(*fieldIter), playerIndex, true);
}
void Monopoly::UpdatePlayerInfo(int playerIndex,  tuple<string, int>& playerInfo, int cost)
{
	auto playerIter = Players.begin();
	advance(playerIter, playerIndex - 1);
	*playerIter = playerInfo;
    playerInfo = make_tuple(get<0>(playerInfo), get<1>(playerInfo) - cost);
}

void Monopoly::UpdatePlayerBalance(int playerIndex, int balance)
{
	auto playerIter = std::next(Players.begin(), playerIndex - 1);
	*playerIter = std::make_tuple(get<0>(*playerIter), balance);
}

std::tuple<std::string, Monopoly::Type, int, bool>  Monopoly::GetFieldByName(std::string fieldName)
{
	std::list<std::tuple<std::string, Monopoly::Type, int, bool>>::iterator i = find_if(Fields.begin(), Fields.end(), [fieldName](std::tuple<std::string, Monopoly::Type, int, bool> fieldInfo) {
		return get<0>(fieldInfo) == fieldName;
		});
	return *i;
}

bool Monopoly::Renta(const int playerIndex, std::tuple<std::string, Type, int, bool>& fieldInfo)
{
	auto senderInfo = GetPlayerInfo(playerIndex);
	std::tuple<std::string, int> receiverInfo;

	switch (get<1>(fieldInfo))
	{
	case Type::AUTO:
	case Type::TRAVEL:
	case Type::CLOTHER:
		if (!get<2>(fieldInfo))
			return false;
		receiverInfo = GetPlayerInfo(get<2>(fieldInfo));
		receiverInfo = make_tuple(get<0>(receiverInfo), get<1>(receiverInfo) + RENT_COST);
		UpdatePlayerInfo(playerIndex, senderInfo, RENT_COST);
		break;
	case Type::FOOD:
		if (!get<2>(fieldInfo))
			return false;
	case Type::PRISON:
		UpdatePlayerInfo(playerIndex, senderInfo, PRISON_COST);
		break;
	case Type::BANK:
		UpdatePlayerInfo(playerIndex, senderInfo, BANK_COST);
		break;
	default:
		return false;
	}
	auto receiverIter = FindPlayerInfoByName(get<0>(receiverInfo));
	*receiverIter = receiverInfo;
	return true;
}



