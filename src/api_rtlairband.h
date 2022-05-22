// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: api_rtlairband.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef API_RTLAIRBAND_H
#define API_RTLAIRBAND_H

// Standard Header Files
#include <string.h>

#include "rtl_airband.h"
#include "squelch.h"

using namespace std;
//using namespace boost::filesystem;

class API_SQUELCH
{
  private:

  // Information to Send
  // Channel Info
  int FREQUENCY = 0;  // needs / 1000000.0
  string label = "";

  // Channel Squelch Info
  float NOISE_LEVEL = 0;
  float SIGNAL_LEVEL = 0;

  bool SIGNAL_OUTSIDE_FILTER = false;

  // Information to Receive
  bool EVERYTHING_IS_OK = false;

  public:

  // Store Frequency information that may or may not be sent.
  void gather_information(freq_t *fparms)
  {
    FREQUENCY = fparms->frequency;
    //label = fparms->label;

    NOISE_LEVEL = level_to_dBFS(fparms->squelch.noise_level());
    SIGNAL_LEVEL = level_to_dBFS(fparms->squelch.signal_level());
  }

  // Gather information to be sent and put everthing into a string 
  //  to be sent.
  string make_send_string()
  {
    string send_string = "";

    send_string = "Everything is 'OK'";

    return send_string;
  }

  // Parse store the information in the message received, to be processed.
  void process_receive_string(string Received)
  {
    Received = Received;
  }

};


#endif