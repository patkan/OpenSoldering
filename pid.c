/*
 *    Filename: pid.c
 *     Version: 0.0.4
 * Description: PID controller for the soldering module
 *     License: GPLv3 or later
 *     Depends:
 *
 *      Author: Patrick Kanzler, adaption of code by Brett Beauregard
 *        Date: 2014-12-30
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */


//TODO Variablenformate sind noch vollkommen durcheinander und müssen optimiert werden

  #define SAMPLETIME_US 4080
  #define COMPUTE_EVERY_NTH_CYCLE 1
  volatile uint8_t cycle_count = 0;

  float outMin, outMax;


  /*working variables*/
  double ITerm, lastInput;
  volatile float kp, ki, kd; //diese Variablen werden in loetkolbenmodul.c auch gebraucht --> TODO so anpassen, dass nur noch die Funktionen zur Anpassung genommen werden
  int SampleTime = 1000; //1 sec

  float output = 0;



  float pid_compute(uint16_t input, uint16_t setpoint)
  {



    cycle_count++;
    if(cycle_count == COMPUTE_EVERY_NTH_CYCLE)
    {
      //compute new output value

      /*Compute all the working error variables*/
      double error = setpoint - input;
      ITerm+= (ki * error);
      if(ITerm > outMax) ITerm = outMax;
      else if(ITerm < outMin) ITerm = outMin;
      double dInput = (input - lastInput);

      /*Compute PID Output*/
      output = kp * error + ITerm - kd * dInput;
      if(output > outMax) output = outMax;
      else if(output < outMin) output = outMin;

      /*Remember some variables for next time*/
      lastInput = input;

    } else if (cycle_count >= COMPUTE_EVERY_NTH_CYCLE)
    {
      //skip this cycle, take old value
      cycle_count = 0;
    }

    return output;
  }

  uint8_t pid_SetTunings(double Kp, double Ki, double Kd)
  {
    if (Kp<0 || Ki<0|| Kd<0) return 1;

      double SampleTimeInSec = ((double)SAMPLETIME_US)/1000000;
      kp = Kp;
      ki = Ki * SampleTimeInSec;
      kd = Kd / SampleTimeInSec;

      return 0;
      }

  uint8_t SetOutputLimits(float Min, float Max)
  {
    if(Min > Max) return 1;
    outMin = Min;
    outMax = Max;

    if(output > outMax) output = outMax;
    else if(output < outMin) output = outMin;

    if(ITerm > outMax) ITerm= outMax;
    else if(ITerm < outMin) ITerm= outMin;
    return 0;
  }


          // uint8_t Initialize()
          // {
          //   lastInput = input;
          //   ITerm = Output;
          //   if(ITerm > outMax) ITerm= outMax;
          //   else if(ITerm < outMin) ITerm= outMin;
          // }
