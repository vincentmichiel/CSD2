//
//  UI.hpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 18/12/2023.
//

#ifndef UI_hpp
#define UI_hpp

#include <stdio.h>
#include <iostream>

class UI
{
public:
  int retrieveUserSelection(std::string selectionOptions[], int numOptions);
  float retrieveValueInRange(float min, float max);
private:
  std::string retrieveUserInput(std::string selectionOptions[], int numOptions);
};

#endif /* UI_hpp */
