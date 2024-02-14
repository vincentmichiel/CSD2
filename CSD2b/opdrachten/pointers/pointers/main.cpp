#include <iostream>
#include "block.hpp"

/*
 Assignment: complete this program by putting your code in all the locations
 that say -- your code here --
 
 Make sure that the program compiles and builds and check the output
 after every change.
 
 Tip: before you look at the output, always think ahead what you expect to
 see and then check if your assumption was correct.
 */


int numPow(int &x){
    x = x * x;
    std::cout << "value of myNum passed as reference (inside function): " << x << std::endl;
    return x;
};

int numPow(int *x){
    *x = *x * *x;
    std::cout << "value of myNum passed as pointer (inside function): " << *x << std::endl;
    return *x;
};

int numPowValue(int x){
    x = x * x;
    std::cout << "value of myNum passed as value (inside function): " << x << std::endl;
    return x;
};



int main()
{
    const int blockAmount = 50;
    Block* blocks[blockAmount];

    // set sizes
    for (int i = 0; i < blockAmount; i++) {
        blocks[i] = new Block();
        // random size between 1 and 100
        blocks[i]->setSize(std::rand() % 100 + 1);
    }

    // get sizes
    for (int i = 0; i < blockAmount; i++) {
        std::cout << "Size of block " << i << ": " << blocks[i]->getSize() << std::endl;
    }

    // deallocate memory
    for (int i = 0; i < blockAmount; i++) {
        delete blocks[i];
    }
    
} // main()




void functionsUsingPointers(){
    int myNum = 3;
    // pass myNum to function as value
    // function creates a copy
    numPowValue(myNum);
    std::cout << "value of myNum after function: " << myNum << std::endl;
    
    myNum = 3;
    // pass myNum to function as reference
    // function operatates directly on the variable
    numPow(myNum);
    std::cout << "value of myNum after function: " << myNum << std::endl;
    
    myNum = 3;
    // pass myNum to function as pointer
    // function operates on variable through memory adress
    numPow(&myNum);
    std::cout << "value of myNum after function: " << myNum << std::endl;
}

void basicPointerInteraction(){
    char letter = 97; // find this in the ASCII table (type 'man ascii')
    char *letterpointer;
    
    std::cout << "Contents of the variable letter: ";
    std::cout << letter << std::endl;
    
    letterpointer = &letter;
    std::cout << "Contents of letterpointer: ";
    std::cout << letterpointer << std::endl;
    
    std::cout << "Contents of what letterpointer points to: ";
    std::cout << *letterpointer << std::endl;
    
    *letterpointer = 'b';
    std::cout << "The variabele letter has gotten a new value through letterpointer." << std::endl;
    std::cout << "Contents of what letterpointer points to: ";
    std::cout << *letterpointer << std::endl;
    
    std::cout << "Contents of the variable letter: ";
    std::cout << letter << std::endl;
    
    
    /*
     * Create the necessary pointer(s) and use them
     */
    
    unsigned short year = 2019;
    std::cout << "Contents of the variabele year: ";
    std::cout << year << std::endl;
    
    // create a pointer to year
    unsigned short *yearPtr = &year;
    
    std::cout << "Contents of yearpointer: ";
    std::cout << yearPtr << std::endl;
    
    std::cout << "Contents of what yearpointer points to: ";
    std::cout << *yearPtr << std::endl;
    // give year a new value via yearpointer
    *yearPtr = 2023;
    
    std::cout << "Contents of the variabele year: ";
    std::cout << year << std::endl;
    
    
    // create another pointer to year, named anotheryearpointer
    unsigned short *anotheryearpointer = &year;
    
    std::cout << "Contents of anotheryearpointer: ";
    std::cout << anotheryearpointer << std::endl;
    
    std::cout << "Contents of what anotheryearpointer points to: ";
    std::cout << *anotheryearpointer << std::endl;
    
    // give year a new value via anotheryearpointer
    *anotheryearpointer = 2001;
    
    std::cout << "Contents of year: ";
    std::cout << year << std::endl;
    
    std::cout << "Contents of what anotheryearpointer points to: ";
    std::cout << *anotheryearpointer << std::endl;
    
    anotheryearpointer++;
    
    std::cout << "Contents of anotheryearpointer after ++: ";
    std::cout << *anotheryearpointer << std::endl;
}

