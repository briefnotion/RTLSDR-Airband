// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: api.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************
// *
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.01A
// *  TEST CODE:                 QACODE: A565              CENSORCODE: EQK6}Lc`:Eg>
// *
// ***************************************************************************************

#ifndef API_H
#define API_H

// Standard Header Files
#include <fstream>
#include <iostream>
#include <string.h>

#include <boost/filesystem.hpp>

// vvvv --- Change these things to customize the API --- vvvv
#include "api_rtlairband.h"
// ^^^^ --- Change these things to customize the API --- ^^^^

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

  string STATUS = "Not started";

// vvvv --- Change these things to customize the API --- vvvv

  string API_PATH_NAME = "/home/pi/radio_api";
  string API_CONTROL_FILE_NAME = "/home/pi/radio_api/control.txt";
  string API_DATA_FILE_NAME = "/home/pi/radio_api/data.txt";

  API_SQUELCH API_INFORMATION;

  // ACK and KNACK codes. 
  string ACK_CODE = "rasfled";      // Code showing data is available.
  string NACK_CODE = "rtl_airband"; // Code showing data is sent.

// ^^^^ --- Change these things to customize the API --- ^^^^

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

  public:

  // vvvv --- Change these things to customize the API --- vvvv
  void gather(freq_t *fparms)
  {
    API_INFORMATION.gather_information(fparms);
  }
  // ^^^^ --- Change these things to customize the API --- ^^^^

  void send_and_receive()
  {
    if (FIRST_RUN == true)
    {
      prep();
    }

    // Look for information from the other program.
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

          if (API_FILE.get_first_line() == ACK_CODE)
          // Look for the ACK code in the API_CONTROL_FILE_NAME
          {

            STATUS = "Acknowledging                     ";

            // File is ACKed. Change the mode.
            ACK_SEARCH = false;
            ACK_FOUND = true;
          }
        }
      }
    }

    // Information is ready to be sent to the other program.
    //  Gather the information and send it out.
    //  This routine is purposely before the get information 
    //  routine because I want a cycle to go through in 
    //  case things change that need to be communicated. 
    if((ACK_SEARCH == false) && (ACK_FOUND == false))
    {
      // Write all necessary information to be sent.
      STATUS = "Sending                     ";

      string new_send_string = "";

      // Make the string to be sent from gathered info.
      new_send_string = API_INFORMATION.make_send_string();

      // Send the info.
      // Write the send string to the API_DATA_FILE_NAME

      // Send NAK.
      // Write the NAK code to the API_CONTROL_FILE_NAME

      // Set to information processed, send and wait again.
      ACK_SEARCH = true;
      ACK_FOUND = false;
    }

    // Information from the other progam is found and 
    //  needs to be processed.
    if((ACK_SEARCH == false) && (ACK_FOUND == true))
    {
      string new_receive_string = "";

      // Read the data from the API_DATA_FILE_NAME
      //new_receive_string = Get Stuff From Comm File;

      // Begin proccessing recieve file.
      API_INFORMATION.process_receive_string(new_receive_string);

      // Set to ACK recieved and need to process.
      ACK_SEARCH = false;
      ACK_FOUND = false;
    }

    printf(" :%s", STATUS.c_str());

  }
  
};



#endif