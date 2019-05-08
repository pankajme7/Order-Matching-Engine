It matches order based on price-priority. We have "Buy" and "Sell" order from different traders. We store that data in AVL trees
and as required we execute order based on best available offer.

It is a c++11 project. It contains three classes.
1. Trader - implements trader class which places order. Every trader has a unique ID "traderID".
2. Order - It is description of order which contains all information about. Every order has unique ID "orderId". 
3. Tree - It has implementation of AVL trees. It has key as "( Price , orderId)". Every entry is unique.

How to compile this code.
1. "cd src" . Change directory to src.
2. compile program using following command " g++ -std=c++11 main.cpp order.cpp trader.cpp tree.cpp".
3. To test with sample input run executable with command "./a.out < ../test.txt"

Brief description about my code.
- It creates two AVL trees "for_buying" and "for_selling" which contain order for buying and selling respectively.
- When executing order "BUY" order.
    - It searches value from  "for_selling" tree.
    - It tries to find lowest value from other trader and fulfill the order.
Similarly it works for other case.


