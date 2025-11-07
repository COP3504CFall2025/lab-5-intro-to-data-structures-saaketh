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
    test.AddHead(10);
    test.AddTail(12);
    test.AddHead(10);
    test.AddTail(12);
    test.AddHead(10);
    test.AddTail(12);
    test.RemoveTail();
    test.RemoveHead();
    test.RemoveHead();
    test.printForward();
    LinkedList<int> test2(std::move(test));
    test2.PrintReverse();
    return 0;
}


#endif