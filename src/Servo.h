/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2017 RoboticsBrno (RobotikaBrno)
 * Copyright (c) 2022 OpenBlock.cc
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

#pragma once

#include "Arduino.h"

class Servo {
    // Default min/max pulse widths (in microseconds) and angles (in
    // degrees).  Values chosen for Arduino compatibility.  These values
    // are part of the public API; DO NOT CHANGE THEM.
    static const int MIN_ANGLE = 0;
    static const int MAX_ANGLE = 180;
    
    static const int MIN_PULSE_WIDTH = 544;     // the shortest pulse sent to a servo
    static const int MAX_PULSE_WIDTH = 2400;     // the longest pulse sent to a servo
    static const int MAX_COMPARE = ((1 << 12) - 1); // 4095
    
    static const int TAU_MSEC = 20;
    static const int TAU_USEC = (TAU_MSEC * 1000);

public:

    // Pin number of unattached pins
    static const int PIN_NOT_ATTACHED = -1;
    
    /**
     * @brief Construct a new Servo instance.
     *
     * The new instance will not be attached to any pin.
     */
    Servo();

    /**
     * @brief Destruct a Servo instance.
     *
     * Call _() and detach().
     */
    ~Servo();

     /**
     * @brief Associate this instance with a servomotor whose input is
     *        connected to pin.

     * @param pin Pin connected to the servo pulse wave input. This
     *            pin must be capable of PWM output (all k210 pins).
     *  
     * @param minPulseWidth Minimum pulse width to write to pin, in
     *                      microseconds.  This will be associated
     *                      with a minAngle degree angle.  Defaults to
     *                      MIN_PULSE_WIDTH = 544.
     *
     * @param maxPulseWidth Maximum pulse width to write to pin, in
     *                      microseconds.  This will be associated
     *                      with a maxAngle degree angle. Defaults to
     *                      MAX_PULSE_WIDTH = 2400.
     *
     * @sideeffect May set pinMode(pin, PWM).
     *
     * @return true if successful, false when pin doesn't support PWM.
     */
    bool attach(int pin, int minPulseWidth = MIN_PULSE_WIDTH, 
        int maxPulseWidth = MAX_PULSE_WIDTH);
                
    /**
     * @brief Stop driving the servo pulse train.
     *
     * If not currently attached to a motor, this function has no effect.
     *
     * @return true if this call did anything, false otherwise.
     */
    bool detach();

    /**
     * @brief Set the servomotor target angle.
     *
     * @param angle Target angle, in degrees.  If the target angle is
     *              outside the range specified at attach() time, it
     *              will be clamped to lie in that range.
     *
     * @see Servo::attach()
     */
    void write(int degrees);

    /**
     * @brief Set the pulse width, in microseconds.
     *
     * @param pulseWidth Pulse width to send to the servomotor, in
     *                   microseconds. If outside of the range
     *                   specified at attach() time, it is clamped to
     *                   lie in that range.
     *
     * @see Servo::attach()
     */
    void writeMicroseconds(int pulseUs);

    /**
     * Get the servomotor's target angle, in degrees.  This will
     * lie inside the range specified at attach() time.
     *
     * @see Servo::attach()
     */
    int read();

    /**
     * Get the current pulse width, in microseconds.  This will
     * lie within the range specified at attach() time.
     *
     * @see Servo::attach()
     */
    int readMicroseconds();
    
    /**
     * @brief Check if this instance is attached to a servo.
     * @return true if this instance is attached to a servo, false otherwise.
     * @see Servo::attachedPin()
     */
    bool attached() const;

    /**
     * @brief Get the pin this instance is attached to.
     * @return Pin number if currently attached to a pin, PIN_NOT_ATTACHED
     *         otherwise.
     * @see Servo::attach()
     */
    int attachedPin() const;


private:
    void _resetFields(void);

    int _usToDuty(int us)    { return map(us, 0, TAU_USEC, 0, MAX_COMPARE); }
    int _dutyToUs(int duty)  { return map(duty, 0, MAX_COMPARE, 0, TAU_USEC); }
    int _usToAngle(int us)   { return map(us, _minPulseWidth, _maxPulseWidth, 0, 180); }
    int _angleToUs(int angle){ return map(angle, 0, 180, _minPulseWidth, _maxPulseWidth); }

    int _pin;
    int _pulseWidthDuty;
    int _min, _max;
    int _minPulseWidth, _maxPulseWidth;
};