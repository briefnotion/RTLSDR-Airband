// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: airbandapi.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef AIRBANDAPI_H
#define AIRBANDAPI_H

// Standard Header Files
#include <fstream>
#include <iostream>
#include <string.h>

#include "rtl_airband.h"
//#include "squelch.h"

using namespace std;

class API_CHANNEL
{
  private:

  // Channel Info
  int frequency = 0;  // needs / 1000000.0
  string label = "";

  // Channel Squelch Info
  float noise_level = 0;
  float signal_level = 0;

  bool signal_outside_filter = false;


  public:

  void test(freq_t *fparms)
  {
    printf(" ** NOISE %f **", level_to_dBFS(fparms->squelch.noise_level()));
  }

  void put(freq_t *fparms)
  {
    frequency = fparms->frequency;
    //label = fparms->label;

    noise_level = level_to_dBFS(fparms->squelch.noise_level());
    signal_level = level_to_dBFS(fparms->squelch.signal_level());

    printf ("Put sucessful.");
  }
};



#endif