//
//  UI.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 19/02/2024.
//

#include "UI.hpp"
#include <iostream>

bool UI::getYesNo(std::string input){
    std::string userInput;
    
    // console ui
    std::cout << input << std::endl << "type 'yes' or 'no'" << std::endl;
    
    while (true){
        // retrieve user input
        std::cin >> userInput;
        
        // validate user input
        if (userInput == "yes"){
            return true;
        } else if (userInput == "no"){
            return false;
        } else {
            std::cout << "Non valid input. Try again..." << std::endl;
        }
    }
}

float UI::getFloat(std::string input, float min, float max){
    std::string userInput;
    float userFloat;
    
    // console ui
    std::cout << input << std::endl << "enter a value between " << min << " and " << max << std::endl;
    
    while(true){
        // retrieve user input
        std::cin >> userInput;
        
        // convert to float
        try{
            userFloat = std::stof(userInput);
        } catch(...) {
            std::cout << "Non valid input. Please enter number" << std::endl;
            continue;
        }
        
        if(userFloat >= min && userFloat <= max){
            return userFloat;
        } else {
            std::cout << "Non valid input. Please enter a value between " << min << " and " << max << std::endl;
            continue;
        }
    }
}
