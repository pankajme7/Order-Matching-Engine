#include <bits/stdc++.h>

using namespace std;

typedef class Order {
public:
    string type;
    int coin;
    int price;
    int trader_id; 
    int id;  

    Order operator = (const Order &ord) {
        cout <<"**********Ord cpy *********\n";
        this->type = ord.type;
        this->coin = ord.coin;
        this->price = ord.price;
        this->trader_id = ord.trader_id;
        this->id = ord.id;
    } 

    Order() {
        
    }

}Order;


extern map<int , Order *> order_book;