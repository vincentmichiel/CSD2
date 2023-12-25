#include <iostream>
#include <fstream>
#include "CustomCallback.h"
#include "UI.hpp"
#include<thread>
#include "Melody.hpp"
#include "midi_io.h"

int synthSelection;
CustomCallback callback = CustomCallback {};

void playMelody(){
    Melody melody;
    float note;
    float dur;
    
    while(true){
        note = melody.getNote();
        dur = melody.getDur();
        
        callback.synths[synthSelection]->setFrequency(note);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(dur)));
    }
};

int main() {
    JackModule jackModule = JackModule { callback };
    
    // user input
    UI * ui = new UI;
    std::string synthTypes[2] = {"analog", "fm"};
    synthSelection = ui->retrieveUserSelection(synthTypes, 2);
    
    
    callback.customInit(synthSelection);
    jackModule.init (0, 1);
    
    // clear plot file
    std::ofstream ofs;
    ofs.open("waveform.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    
    // play melody
    std::thread melodyThread(playMelody);
    
    // MIDI test
    MIDI_io midi_io;
    
    

    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
        }
    }
    melodyThread.join();
    delete ui;
    return 0;
}
