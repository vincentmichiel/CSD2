//
//  main.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 08/02/2024.
//

#include <iostream>
#include "CustomCallback.h"

int main(int argc, const char * argv[]) {
    // init audio
    CustomCallback callback = CustomCallback {};
    JackModule jackModule = JackModule { callback };
    jackModule.init(1, 1);
    
    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
        }
    }
    
    return 0;
}
