#include <iostream>
#include <fstream>
#include "CustomCallback.h"


int main() {
    CustomCallback callback = CustomCallback {};
    JackModule jackModule = JackModule { callback };
    jackModule.init (0, 1);
    
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
