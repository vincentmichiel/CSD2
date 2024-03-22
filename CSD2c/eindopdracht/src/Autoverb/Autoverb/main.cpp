//
//  main.cpp
//  Autoverb
//
//  Created by Vincent Van den Broeck on 22/03/2024.
//

#include <iostream>
#include "CustomCallback.h"

int main(int argc, const char * argv[]) {
    // init audio
    CustomCallback callback = CustomCallback {};
    JackModule jackModule = JackModule { callback };
    std::cout << "multittaptest";
    jackModule.init(1, 2);
    
    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
        }
    }
    return 0;
}
