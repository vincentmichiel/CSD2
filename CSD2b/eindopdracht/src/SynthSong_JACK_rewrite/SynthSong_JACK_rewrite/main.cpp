#include <iostream>
#include <fstream>
#include "CustomCallback.h"
#include "UI.hpp"
#include<thread>
#include "Melody.hpp"
#include "midi_io.h"

int synthSelection;
CustomCallback callback = CustomCallback {};
MIDI_io midi_io;

void playMelody(){
    Melody melody;
    float note;
    float dur;
    
    // turn up synth volume
    callback.synths[synthSelection]->setAmp(1);
    
    while(true){
        note = melody.getNote();
        dur = melody.getDur();
        
        callback.synths[synthSelection]->setNote(note);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(dur)));
    }
}

void readMidi(){
    PmEvent event;
    bool event_read;
    unsigned char cmd,channel,data1;
    int note;
    
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(1)));
        event_read = midi_io.read_event(event);
        // midi available
        if(event_read){
            cmd=Pm_MessageStatus(event.message)&0xf0;
            channel=Pm_MessageStatus(event.message)&0xf;
            data1=Pm_MessageData1(event.message);
            
            // filter for note on and note off messages
            if(cmd == 0x90 || cmd == 0x80) {
                //std::cout << (int) cmd << " " << (int) channel << " " << (int) data1 << std::endl;
                
                if(int(cmd) == 144){
                    // note on
                    note = (int) data1;
                    callback.synths[synthSelection]->setNote(note);
                    callback.synths[synthSelection]->setAmp(1);
                } else if ((int)cmd == 128){
                    // note off
                    callback.synths[synthSelection]->setAmp(0);
                }
            }
        }
      } // while
}

int main() {
    UI * ui = new UI;
    std::thread melodyThread;
    std::thread midiThread;
    // clear plot file
    std::ofstream ofs;
    ofs.open("waveform.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    
    // init jack
    JackModule jackModule = JackModule { callback };
    
    // user input
    // clear console
    std::cout << "\x1B[2J\x1B[H";
    std::string synthTypes[2] = {"analog", "fm"};
    synthSelection = ui->retrieveUserSelection(synthTypes, 2);
    
    int inputType = 0;
    std::string inputTypes[2] = {"melody", "midi"};
    inputType = ui->retrieveUserSelection(inputTypes, 2);
    
    callback.customInit(synthSelection);
    jackModule.init (0, 1);
    
    
    switch (inputType) {
        case 0: {
            // MELODY
            // play melody in seperate thread
            melodyThread = std::thread(playMelody);
        } break;
            
        case 1: {
            // MIDI
            midi_io.create_virtual_input_device("jacksynth");
            int input_device = 0;
            midi_io.list_devices();
            std::cout << "\nGive input device number: ";
            cin >> input_device;
            midi_io.set_input_device(input_device);
            midi_io.set_output_device(0);
            midi_io.initialise();
            midi_io.set_input_filter(0);
            
            // read midi in seperate thread
            midiThread = std::thread(readMidi);
        } break;
            
        default:
            break;
    }
        
    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
        }
    }
    // cleanup
    if (melodyThread.joinable()) {
        melodyThread.join();
    }

    if (midiThread.joinable()) {
        midiThread.join();
    }
    midi_io.finalise();
    delete ui;
    return 0;
}
