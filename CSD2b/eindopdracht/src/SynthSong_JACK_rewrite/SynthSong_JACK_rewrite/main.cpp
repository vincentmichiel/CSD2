#include <iostream>
#include <fstream>
#include "CustomCallback.h"
#include "UI.hpp"


int main() {
    CustomCallback callback = CustomCallback {};
    JackModule jackModule = JackModule { callback };
    jackModule.init (0, 1);
    
    UI ui;
    std::string waveFormOptions[4] = {"sine", "saw", "square", "triangle"};
    
    int waveFormSelection = ui.retrieveUserSelection(waveFormOptions, 4);
    
    std::cout << waveFormSelection << std::endl;
    
    // clear plot file
    std::ofstream ofs;
    ofs.open("waveform.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
        }
    }
    return 0;
}
