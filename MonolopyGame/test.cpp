#include "pch.h"
#include "Monolopy.h"

using namespace ::std;

TEST(LAB2, GetPlayersListReturnCorrectList) {
    string players[]{ "Peter","Ekaterina","Alexander" };

    Monopoly monopoly(players, 3);

    list<tuple<string, int>>* x = monopoly.GetPlayersList();
    int i = 0;
    for (auto c : *x) {
        ASSERT_STREQ(get<0>(c).c_str(), players[i++].c_str());
        ASSERT_EQ(get<1>(c), 6000);
    }
    ASSERT_TRUE(i);
}
TEST(LAB2, GetFieldsListReturnCorrectList) {
    tuple<string, Monopoly::Type, int, bool> expectedCompanies[]{
        make_tuple("Ford",Monopoly::AUTO ,0,false),
        make_tuple("MCDonald",Monopoly::FOOD,0,false),
        make_tuple("Lamoda",Monopoly::CLOTHER,0,false),
        make_tuple("Air Baltic",Monopoly::TRAVEL,0,false),
        make_tuple("Nordavia",Monopoly::TRAVEL,0,false),
        make_tuple("Prison",Monopoly::PRISON,0,false),
        make_tuple("MCDonald",Monopoly::FOOD,0,false),
        make_tuple("TESLA",Monopoly::AUTO,0,false)
    };
    string players[]{ "Peter","Ekaterina","Alexander" };

    Monopoly monopoly(players, 3);
    auto actualCompanies = monopoly.GetFieldsList();
    int i = 0;
    for (auto x : *actualCompanies)
    {
        ASSERT_EQ(x, expectedCompanies[i++]);
    }
    ASSERT_TRUE(i);
}

TEST(LAB2, PlayerBuyNoOwnedCompanies)
{
    string players[]{ "Peter","Ekaterina","Alexander" };

    Monopoly monopoly(players, 3);
    auto x = monopoly.GetFieldByName("Ford");
    monopoly.Buy(1, x);

    auto player = monopoly.GetPlayerInfo(1);
    ASSERT_EQ(get<1>(player), 5500);
    x = monopoly.GetFieldByName("Ford");
    ASSERT_TRUE(get<2>(x) != 0);

    x = monopoly.GetFieldByName("Ford");
    ASSERT_FALSE(monopoly.Buy(2, x));
}

TEST(LAB2, RentaShouldBeCorrectTransferMoney)
{
    string players[]{ "Peter","Ekaterina","Alexander" };
    Monopoly monopoly(players, 3);
    auto x = monopoly.GetFieldByName("Ford");
    monopoly.Buy(1, x);

    x = monopoly.GetFieldByName("Ford");
    monopoly.Renta(2, x);
    auto player1 = monopoly.GetPlayerInfo(1);
    ASSERT_EQ(get<1>(player1), 5750);

    auto player2 = monopoly.GetPlayerInfo(2);
    ASSERT_EQ(get<1>(player2), 5750);
}


bool operator== (std::tuple<std::string, Monopoly::Type, int, bool>& a, std::tuple<std::string, Monopoly::Type, int, bool>& b)
{
    return get<0>(a) == get<0>(b) && get<1>(a) == get<1>(b) && get<2>(a) == get<2>(b) && get<3>(a) == get<3>(b);
}