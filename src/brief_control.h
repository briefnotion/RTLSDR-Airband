// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: brief_control.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef BRIEF_CONTROL_H
#define BRIEF_CONTROL_H

// Standard Header Files
//#include <string.h>
#include <deque>

using namespace std;
//using namespace boost::filesystem;

class CONTROL_FREQUENCY
{
  public:

  int control = 0;
  int frequency = 0;
};

class CONTROL
{

  private:

  // Hold 
  CONTROL_FREQUENCY CONTROL_HOLD_FREQUENCY;

  // Skips
  deque<CONTROL_FREQUENCY> CONTROL_FREQUENCYS;

  public:

  int get_control(int Frequency)
  {
    unsigned int pos = 0;
    bool found = false;

    int ret_control = 0;
      // 0 - No Control
      // 1 - Skip
      // 2 - Hold

    if (CONTROL_HOLD_FREQUENCY.control == 2)
    {
      ret_control = CONTROL_HOLD_FREQUENCY.control;
    }
    else
    {
      while (found == false && pos < CONTROL_FREQUENCYS.size())
      {
        if (CONTROL_FREQUENCYS[pos].frequency == Frequency)
        {
          found = true;
        }
        else
        {
          pos++;
        }
      }

      if (found == false)
      {
        CONTROL_FREQUENCY tmp_frequency_control;
        tmp_frequency_control.frequency = Frequency;

        CONTROL_FREQUENCYS.push_back(tmp_frequency_control);
        ret_control = tmp_frequency_control.control;
      }
      else
      {
        ret_control = CONTROL_FREQUENCYS[pos].control;
      }
    }

    return ret_control;

  }

  void clear(int Frequency)
  {
    unsigned int pos = 0;
    bool found = false;

    if (CONTROL_HOLD_FREQUENCY.control == 2)
    {
      CONTROL_HOLD_FREQUENCY.control = 0;
    }
    else
    {
      while (found == false && pos < CONTROL_FREQUENCYS.size())
      {
        if (CONTROL_FREQUENCYS[pos].frequency == Frequency)
        {
          found = true;
          CONTROL_FREQUENCYS[pos].control = 0;
        }
        else
        {
          pos++;
        }
      }
    }
  }

  void set_skip(int Frequency)
  {
    unsigned int pos = 0;
    bool found = false;

    while (found == false && pos < CONTROL_FREQUENCYS.size())
    {
      if (CONTROL_FREQUENCYS[pos].frequency == Frequency)
      {
        found = true;
        CONTROL_FREQUENCYS[pos].control = 1;
      }
      else
      {
        pos++;
      }
    }
  }

  void set_hold(int Frequency)
  {
    CONTROL_HOLD_FREQUENCY.frequency = Frequency;
    CONTROL_HOLD_FREQUENCY.control = 2;
  }

  int get_hold_frequency()
  {
    return CONTROL_HOLD_FREQUENCY.frequency;
  }
};



#endif