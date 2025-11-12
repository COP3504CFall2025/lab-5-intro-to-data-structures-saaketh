#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    // LinkedList<int> test;
    // test.addTail(40);
    // test.printForward();
    // test.Clear();
    // test.RemoveHead();
    // test.RemoveHead();
    // test.clear();
    // std::cout << test.getCount() << std::endl;
    // test.RemoveTail();
    // test.RemoveTail();
    // std::cout << test.getTail() << std::endl;
    // test.printForward();
    // std::cout << test.getCount() << std::endl;

    // ABQ<int> stuff;
    // stuff.enqueue(1);
    // stuff.enqueue(2);
    // stuff.enqueue(3);
    // stuff.enqueue(4);
    // stuff.enqueue(5);
    // stuff.printForward();

    // LLS<int> stuff;
    // stuff.push(5);
    // stuff.push(7);
    // stuff.push(9);
    // stuff.printForward();

    ABDQ<int> stuff;
    stuff.pushFront(5);
    // std::cout << stuff.getSize() << std::endl;
    stuff.pushFront(7);
    stuff.pushFront(8);
    stuff.pushFront(9);
    stuff.pushFront(10);
    stuff.pushFront(8);
    stuff.pushFront(9);
    stuff.pushFront(10);
    std::cout << stuff.popFront() << std::endl;
    std::cout << stuff.popFront() << std::endl;
    std::cout << stuff.popFront() << std::endl;
    std::cout << stuff.popFront() << std::endl;
    std::cout << stuff.popFront() << std::endl;
    std::cout << stuff.popFront() << std::endl;
    std::cout << stuff.popFront() << std::endl;
    std::cout << stuff.popFront() << std::endl;
    std::cout << stuff.popFront() << std::endl;
    std::cout << stuff.getSize() << std::endl;
    stuff.printOriginal();
    // std::cout << stuff.popFront() << std::endl;
    // std::cout << stuff.popFront() << std::endl;
    // std::cout << stuff.popFront() << std::endl;
    // std::cout << stuff.popFront() << std::endl;
    // std::cout << stuff.popFront() << std::endl;
    // std::cout << stuff.popFront() << std::endl;
    // std::cout << stuff.getSize() << std::endl;
    // std::cout << stuff.front() << std::endl;
    // std::cout << stuff.back() << std::endl;
    // stuff.printOriginal();
    // stuff.dequeue();
    stuff.printForward();

    // std::cout << stuff.getMaxCapacity() << std::endl;
    // stuff.pop();
    // std::cout << stuff.getMaxCapacity() << std::endl;
    // stuff.pop();
    // std::cout << stuff.getMaxCapacity() << std::endl;
    //  stuff.push();
    // std::cout << stuff.getMaxCapacity() << std::endl;
    //  stuff.push();
    // std::cout << stuff.getMaxCapacity() << std::endl;
    //  stuff.pop();
    // std::cout << stuff.getMaxCapacity() << std::endl;
    //  stuff.pop();
    // std::cout << stuff.getMaxCapacity() << std::endl;
    //  stuff.push(10);
    // std::cout << stuff.getMaxCapacity() << std::endl;
    //  stuff.push(10);
    // std::cout << stuff.getMaxCapacity() << std::endl;
    
    // std::cout << stuff.getSize() << std::endl;
    // stuff.peek();
    // std::cout << stuff.getMaxCapacity() << std::endl;
    // stuff.printForward();
    return 0;
}


#endif