#include<bits/stdc++.h>
#include "../include/trader.h"

using namespace std;

map<int , Trader *> trader_list;

Trader* Trader:: createTrader(string name, int coin_balance , int inr_balance) {
    static int traderId = -1;
    traderId++;

    Trader *t = new Trader;
    t->coin_balance = coin_balance;
    t->inr_balance = inr_balance;
    t->id = traderId;
    t->trader_name = name;
    trader_list.insert(make_pair(traderId , t));
    return t;
} 