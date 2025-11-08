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
    LinkedList<int> test;
    test.addTail(40);
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

    ABS<int> stuff;
    stuff.push(10);
    std::cout << stuff.getMaxCapacity() << std::endl;
    stuff.pop();
    stuff.push(10);
    stuff.push(10);
    stuff.push(10);
    stuff.push(10);
    stuff.pop();
    stuff.pop();
    stuff.pop();
    // stuff.peek();
    std::cout << stuff.getMaxCapacity() << std::endl;
    stuff.printForward();
    return 0;
}


#endif