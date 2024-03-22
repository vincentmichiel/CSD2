#include <iostream>
#include "CustomCallback.h"
#include "osc.hpp"

CustomCallback callback = CustomCallback {};

int mapValue(int input, int minIn, int maxIn, int minOut, int maxOut) {
    // Define input and output ranges
    int input_min = minIn;
    int input_max = maxIn;
    int output_min = minOut;
    int output_max = maxOut;

    // Calculate the scaling factor
    double scale = static_cast<double>(output_max - output_min) / (input_max - input_min);

    // Map the input value to the output range
    int output = static_cast<int>((input - input_min) * scale + output_min);

    return output;
}


// subclass OSC into a local class so we can provide our own callback
class localOSC : public OSC
{
  int realcallback(const char *path,const char *types,lo_arg **argv,int argc)
  {
  std::string msgpath=path; // convert char* to std::string
    if(!msgpath.compare("/x")){
      int x = argv[0]->i;
        x = x/11;
        x = x*x;
        callback.setDepth(x);
    }if(!msgpath.compare("/y")){
      int y = argv[0]->i;
        int f = mapValue(y, -100, 100, 45, 72);
        std::cout << "note: " << f << std::endl;
        callback.setFrequency(f);
    } // if
    if(!msgpath.compare("/s")){
        int s = argv[0]->i;
        callback.setAmp(s);
    }
    return 0;
  } // realcallback()
};


int main() {
    // init jack
    JackModule jackModule = JackModule { callback };
    jackModule.init (0, 1);
    
    // OSC SERVER
    
    localOSC osc;
    std::string serverport="7777";
    std::string user_input;

      osc.init(serverport);
    
      osc.set_callback("/x","i");
      osc.set_callback("/y","i");
      osc.set_callback("/s","i");
      osc.set_callback("/quit","");

      osc.start();

      std::cout << "Listening on port " << serverport << std::endl;
        
    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
        }
    }
    osc.stop();
    return 0;
}
