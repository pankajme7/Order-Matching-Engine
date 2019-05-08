#include<bits/stdc++.h>

#include "../include/tree.h"
using namespace std;

Node *for_selling = NULL;
Node *for_buying = NULL;
Trader *Alice , *Bob;


int addOrder(Order *o) {
    static int orderId = 0;
    orderId ++;
    order_book.insert(make_pair(orderId , o));    
    o->id = orderId;

    if(o->type == "Sell") for_selling = insert(for_selling , make_pair(o->price , o->id) , o);
    if(o->type == "Buy") for_buying = insert(for_buying , make_pair(o->price , o->id) , o);

    return orderId;
}


int cancelAll() {
    for_buying = deleteTree(for_buying);
    for_selling = deleteTree(for_selling);    
    if(for_buying or for_selling) 
        return -1;
    return 0;
}


int cancelOrder(int orderId) {
    auto itr = order_book.find(orderId);
    Order *o = itr->second;

    if(o->type == "Sell") for_selling = deleteNode(for_selling , make_pair(o->price , o->id));
    if(o->type == "Buy") for_buying = deleteNode(for_buying , make_pair(o->price , o->id)); 
    return 0;
}



int getLowestSell() {
    if(for_selling == NULL ) {
        cout << "No orders available for selling";
        return -1;
    }
    Node *lowestSell = getLowest(for_selling);
    return lowestSell->data->price;
}


int getHighestBuy() {
    if(for_buying == NULL) {
        cout << "No orders available for buying";
        return -1;
    }
    Node *highestBuy = getHighest(for_buying);
    return highestBuy->data->price;
}


int executeOrder(int orderId) {
    auto itr = order_book.find(orderId);

    if(itr == order_book.end()) {
        cout << "No such entry in order book.\n";
        return -1;
    }

    Order *o = itr->second;
    if(o->type == "Sell" ) {
        //cout << "**Sell order \n";
        if(for_buying == NULL) {
            //cout << "No orders available for buying\n";
            return -1;       
        }

        if( trader_list.find(o->trader_id)== trader_list.end())  {
            //cout << "Cannot find specified trader\n";
            return -1;
        }
        Trader *trader_selling = trader_list.find(o->trader_id)->second;

        int coin_remaining = min(o->coin , trader_selling->coin_balance);
        int amnt_earned = 0;
        int total_coin_sold = 0;

        Node *node = getHighestFromOtherTrader(for_buying , trader_selling->id);
        Order *current_offer = NULL;
        while(1) {           

            if(node == NULL) break;
            if(node->data == NULL) break;
            if(trader_selling->coin_balance <= 0) break;
            
            current_offer = node->data;
            if(trader_list.find(current_offer->trader_id) == trader_list.end()) break;
            Trader *current_trader = trader_list.find(current_offer->trader_id)->second;

            if(current_trader->inr_balance <= 0) break;
            
            

            //cout <<"Order : " << orderId << " " << node->data->id << endl; 

            int coin_sold = min(coin_remaining , current_offer->coin);
            coin_sold = min(coin_remaining , current_trader->coin_balance);
            coin_remaining -= coin_sold;

            current_trader->coin_balance += coin_sold;
            current_trader->inr_balance -= coin_sold * current_offer->price;
            
            
            total_coin_sold += coin_sold;
            amnt_earned += coin_sold * current_offer->price;            

            if(coin_sold < current_offer->coin)    current_offer->coin -= coin_sold;
            else  cancelOrder(current_offer->id);

            node = getHighestFromOtherTrader(for_buying , trader_selling->id);

        }

        if(total_coin_sold < o->coin) o->coin -= total_coin_sold;
        else cancelOrder(o->id);

        trader_selling->coin_balance -= total_coin_sold;
        trader_selling->inr_balance += amnt_earned;


    }

    if(o->type == "Buy") {
        //cout << "**Buy order \n";
        
        if(for_selling == NULL) {
            //cout << "No order available for selling\n";
            return -1;
        }

        if( trader_list.find(o->trader_id)== trader_list.end())  {
            //cout << "Cannot find specified trader\n";
            return -1;
        }

        Trader *trader_buying = trader_list.find(o->trader_id)->second;
        int coin_needed = o->coin;
        int coin_bought = 0;
        int amnt_remaining = trader_buying->inr_balance;
        
        Node *node = getLowestFromOtherTrader(for_selling , trader_buying->id);
        Order *current_offer = NULL;           
        int cnt = 0;
        if(node)
        //cout << orderId << " " << node->data->id<<endl;
        while(1) 
        {   


            if(node == NULL) break;
            if(node->data == NULL) break;
            
            current_offer = node->data;
            if(trader_list.find(current_offer->trader_id) == trader_list.end()) break;
            Trader *current_trader = trader_list.find(current_offer->trader_id)->second;

            if(current_trader->coin_balance <= 0) break;
            if(amnt_remaining < current_offer->price) break;
            if(coin_bought >= coin_needed) break;

            
            int coin_taken = min(coin_needed , current_offer->coin);
            coin_taken = min(coin_taken , int(amnt_remaining/current_offer->price));
            coin_taken = min(coin_taken , current_trader->coin_balance); 
            
            amnt_remaining -= coin_taken * current_offer->price;  
            coin_bought += coin_taken;

            current_trader->coin_balance -= coin_taken;
            current_trader->inr_balance += coin_taken * current_offer->price;                             
            
            if(coin_taken < current_offer->coin) current_offer->coin -= coin_taken;
            else cancelOrder(current_offer->id);



            node = getLowestFromOtherTrader(for_selling , trader_buying->id);
            
        }

        if(coin_bought < o->coin ) o->coin -= coin_bought;
        else cancelOrder(o->id);
        
        trader_buying->coin_balance += coin_bought;
        trader_buying->inr_balance = amnt_remaining;


    }
}

void printBalance(Trader *trad) {
    cout << trad->trader_name << " " << trad->coin_balance << " " << trad->inr_balance << "\n";
}


void printAll () {
        cout << "For selling\n";
        preOrder(for_selling); cout << endl;
        inOrder(for_selling); cout << endl;
        cout << "For buying\n";
        preOrder(for_buying); cout << endl;
        inOrder(for_buying); cout << endl;
        printBalance(Alice);
        printBalance(Bob);
        cout << endl;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    Alice = Trader::createTrader("Alice" ,1000 , 100000);
    Bob = Trader::createTrader("Bob" , 2000 , 200000);

    

    int n , temp; 
    cin >> n;
    for(int i = 0; i <n; i++) {
        string trad;
        string type;
        int price;
        int coin;

        Order *ord = new Order();

        cin >> trad >> type >> price >> coin;

        ord->type = type;
        ord->coin = coin;
        ord->price = price;
        if(trad == "Alice") ord->trader_id = Alice->id;
        if(trad == "Bob") ord->trader_id = Bob->id; 
        
        
        temp = addOrder(ord);
        executeOrder(temp);
     
        
    }

    printBalance(Alice);
    printBalance(Bob);

    return 0;

}