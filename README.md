# ServoESP32 [![Build Status](https://travis-ci.com/RoboticsBrno/ServoESP32.svg?branch=master)](https://travis-ci.com/RoboticsBrno/ServoESP32)

Generate RC servo signal on a selected pins with k210 device and Arduino framework.

Base on [servo library for esp32](https://github.com/RoboticsBrno/ServoESP32).

## Interface

The interface is similar to Arduino/Servo: https://www.arduino.cc/en/Reference/Servo

But there are still some small differences:

1. The detach function doesn't really work.
2. This function conflicts with the pwm output function. After executing the attch instruction, the timer frequency will be modified to 50hz, which will change the output frequency of other pwm using this timer.
3. Since k210 has a total of 3 timers, each timer has 4 output channels, so it can only support the creation of 12 servos at most.
