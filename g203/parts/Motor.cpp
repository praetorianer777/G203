//
// Created by steve on 19.12.19.
//

#include <wiringPi.h>
#include <softPwm.h>
#include <cstdio>
#include <cstdlib>
#include "../Util.h"
#include "Motor.h"

Motor::Motor(int en1Pin, int en2Pin, int pwmPin, float scale)
{
    m_en1Pin = en1Pin;
    m_en2Pin = en2Pin;
    m_pwmPin = pwmPin;
    m_scale = scale;
    Init();
}

void Motor::Init()
{
    if (wiringPiSetup() == -1)
    {
        perror("WiringPI setup error");
        exit(-1);
    }
    pinMode(m_en1Pin, OUTPUT);
    pinMode(m_en2Pin, OUTPUT);
    pinMode(m_pwmPin, PWM_OUTPUT);
    pwmWrite(m_pwmPin, STOP_PWM);
}

Motor::~Motor()
{
    digitalWrite(m_en1Pin, LOW);
    digitalWrite(m_en2Pin, LOW);
    pwmWrite(m_pwmPin, 0);
}

void Motor::SetTargetSpeed(float targetSpeed)
{
    m_targetSpeed = targetSpeed;

    if(!IsEqual(m_targetSpeed * m_scale, m_currentSpeed, EPSILON))
    {
        if(m_targetSpeed < STOP_PWM)
        {
            digitalWrite(m_en1Pin, HIGH);
            digitalWrite(m_en2Pin, LOW);
        }
        else
        {
            digitalWrite(m_en1Pin, LOW);
            digitalWrite(m_en2Pin, HIGH);
        }
        m_currentSpeed = m_targetSpeed;

        // write the current speed (absolute value and unnormalized) as pwm signal
        pwmWrite(m_pwmPin, static_cast<int> (std::abs(m_currentSpeed) * MAX_PWM * m_scale));
    }
}

void Motor::Stop()
{
    pwmWrite(m_pwmPin, STOP_PWM);
    m_targetSpeed = 0;
    m_currentSpeed = m_targetSpeed;
    digitalWrite(m_en1Pin, LOW);
    digitalWrite(m_en2Pin, LOW);
}