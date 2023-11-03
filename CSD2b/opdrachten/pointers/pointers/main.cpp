#include <iostream>

/*
 Assignment: complete this program by putting your code in all the locations
 that say -- your code here --
 
 Make sure that the program compiles and builds and check the output
 after every change.
 
 Tip: before you look at the output, always think ahead what you expect to
 see and then check if your assumption was correct.
 */

int main()
{
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
    
    
} // main()

