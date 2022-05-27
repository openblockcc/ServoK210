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

#include <Servo.h>

Servo::Servo() {
    _resetFields();
};

Servo::~Servo() {
    detach();
}

bool Servo::attach(int pin, int minPulseWidth, int maxPulseWidth)
{

    _pin = pin;
    _minPulseWidth = minPulseWidth;
    _maxPulseWidth = maxPulseWidth;

    analogWriteResolution(12); // 12-bit resolution
    analogWriteFrequency(50); // 50 Hz
    analogWrite(_pin, 0);

    return true;
}

bool Servo::detach() {
    if (!this->attached()) {
        return false;
    }

    return true;
}

void Servo::write(int degrees) {
    writeMicroseconds(_angleToUs(degrees));
}

void Servo::writeMicroseconds(int pulseUs) {
    if (!attached()) {
        return;
    }
    pulseUs = constrain(pulseUs, _minPulseWidth, _maxPulseWidth);
    _pulseWidthDuty = _usToDuty(pulseUs);
    analogWrite(_pin, _pulseWidthDuty);
}

int Servo::read() {
    return _usToAngle(readMicroseconds());
}

int Servo::readMicroseconds() {
    if (!this->attached()) {
        return 0;
    }
    return _dutyToUs(_pulseWidthDuty);
}

bool Servo::attached() const { return _pin != PIN_NOT_ATTACHED; }

int Servo::attachedPin() const { return _pin; }

void Servo::_resetFields(void) {
    _pin = PIN_NOT_ATTACHED;
    _pulseWidthDuty = 0;
    _minPulseWidth = MIN_PULSE_WIDTH;
    _maxPulseWidth = MAX_PULSE_WIDTH;
}