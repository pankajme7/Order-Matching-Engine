#include<bits/stdc++.h>

using namespace std;

typedef class Trader {
public:
    int coin_balance;
    int inr_balance;
    int id;

    string trader_name;
    static Trader *createTrader(string name ,int coin_balance , int inr_balance);


} Trader;

extern map<int , Trader *> trader_list;
