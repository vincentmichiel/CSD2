//
//  UI.hpp
//  effects1
//
//  Created by Vincent Van den Broeck on 19/02/2024.
//

#ifndef UI_hpp
#define UI_hpp

#include <stdio.h>
#include <string>

class UI {
public:
    static bool getYesNo(std::string input);
    static float getFloat(std::string input, float min, float max);
};

#endif /* UI_hpp */
