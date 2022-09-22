/*
    stack.h
    Grace Nguyen
    09/17/22
*/

#ifndef STACK_H_EXISTS
#define STACK_H_EXISTS

#include <stdlib.h>
#include <list>


template <typename T>
class Stack {
    public:
        std::list<T> stack;
        int size = 0;


        // accessor methods
        int getSize() {
            return(size);
        } // end getter

        T peek() {
            // returns top element of the stack
            return(stack.front());
        } //end peek


        // stack manipulation methods
        void push(T data) {
            // push data onto stack, increment size
            stack.push_front(data);
            size++;
        } // end push

        void pop() {
            // remove top element ONLY IF stack size is greater than 1
            if(size > 0) {
                stack.pop_front();
                size--;             
            } // end if
        } // end pop

    
        // misc. methods
        bool isEmpty() {
            // returns true if the stack is empty
            if(size == 0){
                return(true);
            }else{
                return(false);
            } // end if
        } // end isEmpty
}; // end stack template

#endif
