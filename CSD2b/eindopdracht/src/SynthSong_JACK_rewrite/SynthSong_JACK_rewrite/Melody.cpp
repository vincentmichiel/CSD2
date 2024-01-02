//
//  Melody.cpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 18/12/2023.
//

#include "Melody.hpp"
#include <iostream>

Melody::Melody()
{
    noteIndex = 0;
    durIndex = 0;
}

Melody::~Melody()
{}

float Melody::getNote()
{
  // wrap index back to the beginning
  if(noteIndex >= NUM_NOTES) {
    noteIndex = 0;
      
  }
  // index++ --> use value, then increment
  return melody[noteIndex++];
}

float Melody::getDur()
{
  // wrap index back to the beginning
  if(durIndex >= NUM_DURS) {
    durIndex = 0;
  }
  // index++ --> use value, then increment
  return durations[durIndex++];
}
