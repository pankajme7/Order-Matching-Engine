It matches order based on price-priority. We have "Buy" and "Sell" order from different traders. We store that data in AVL trees
and as required we execute order based on best available offer.

How to compile this code.
1. "cd src" . Change directory to src.
2. compile program using following command " g++ -std=c++11 main.cpp order.cpp trader.cpp tree.cpp".
3. To test with sample input run executable with command "./a.out < ../test.txt"

Brief description about my code.
- It creates two AVL trees "for_buying" and "for_selling" which contain order for buying and selling respectively.
- When executing order "buy_order" it searches value from other tree and finds a best match. Similarly for other type of order.
- And after completing order it deletes order from tree.
