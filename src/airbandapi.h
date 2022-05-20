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

#include <boost/filesystem.hpp>

#include "rtl_airband.h"
//#include "squelch.h"

using namespace std;
//using namespace boost::filesystem;

class API_CHANNEL
{
  private:

  FledTime TIME;
  FILE_WATCH API_FILE;
  TIMED_IS_READY TIMER_FILE_WRITE;

  bool FIRST_RUN = true;

  // Comm Control
  bool ACK_SEARCH = true;
  bool ACK_FOUND = false;

  // Channel Info
  int frequency = 0;  // needs / 1000000.0
  string label = "";

  // Channel Squelch Info
  float noise_level = 0;
  float signal_level = 0;

  bool signal_outside_filter = false;

  string STATUS = "Not started";

  string API_PATH_NAME = "/home/pi/radio_api";
  string API_CONTROL_FILE_NAME = "/home/pi/radio_api/comm.txt";

  void prep()
  {
    // To prevent runaway file acess, restrict access times to certain 
    //  minumal time intervals.
    TIMER_FILE_WRITE.set(TIME.now(), 1000);

    // Create the directory if it does't exist.
    if( boost::filesystem::exists(API_PATH_NAME) == true)
    {
      STATUS ="Path Found";
    }
    else
    {
      STATUS ="Path Not Found";
      boost::filesystem::create_directories(API_PATH_NAME);
    }

    // Open the file watch passivly on the api control file.
    API_FILE.open(API_CONTROL_FILE_NAME, true);

    // Preperations have been made.
    FIRST_RUN = false;    
  }

  void store_frequency_information(freq_t *fparms)
  {
    frequency = fparms->frequency;
    //label = fparms->label;

    noise_level = level_to_dBFS(fparms->squelch.noise_level());
    signal_level = level_to_dBFS(fparms->squelch.signal_level());
  }

  public:

  void put(freq_t *fparms)
  {
    if (FIRST_RUN == true)
    {
      prep();
    }

    // ACK_SEARCH and ACK_FOUND routine.
    if ((ACK_SEARCH == true) && (ACK_FOUND == false))
    // If looking for comm and didn't find any yet.
    {

      STATUS = "Waiting                     ";

      if (TIMER_FILE_WRITE.is_ready(TIME.now()))
      // Only access if time is ready.
      {

        STATUS = "Checking                     ";

        if (API_FILE.size_changed() == true)
        // Did the file change
        {

          STATUS = "Verifying                     ";

          if (API_FILE.get_first_line() == "rasfled")
          // Does the file cotain the ACK id.
          {

            STATUS = "Acknoleging                     ";

            // File is ACKed. Change the mode.
            ACK_SEARCH = false;
            ACK_FOUND = true;

            store_frequency_information(fparms);

          }
        }
      }
    }

    if(ACK_FOUND == true)
    {
      // Write all necessary information to be sent.
      STATUS = "Sending                     ";

      // Send NACK code.

      // Reset to ACK Search.
      ACK_SEARCH = true;
      ACK_FOUND = false;
    }

    printf(" :%s", STATUS.c_str());

  }
  
};



#endif