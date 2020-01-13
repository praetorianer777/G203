//
// Created by steve on 19.12.19.
//

#ifndef G203_MOTOR_H
#define G203_MOTOR_H

#include <thread>
#include <mutex>

class Motor {
public:
    /**
     * Constructor for the motor class.
     * @param en1Pin EN1 pin for direction control of the motor.
     * @param en2Pin EN2 pin for direction control of the motor.
     * @param pwmPin Pin used for the PWM signal.
     * @param scale Defines the max usage of the motor (1==full power, 0.5==half power).
     */
    Motor(int en1Pin, int en2Pin, int pwmPin, float scale);

    ~Motor();

    /**
     * Sets the desired target speed of this motor.
     * @param targetSpeed [-1,1] - Full backward to full forward.
     */
    void SetTargetSpeed(float targetSpeed);

    /**
     * Stops the motor.
     */
    void Stop();

private:
    // en1 and en2 are for rotation direction of the motor
    // if both are OFF or ON, then the motor will stop
    // if they have different output (e.g. LOW and HIGH)
    // the motor will rotate in one direction (or the other if inverted)
    int m_en1Pin;
    int m_en2Pin;

    // this pin will output the pwm signal for the motors
    int m_pwmPin;

    // this is the current speed of the motor [-1,1] (-1 == backward, 1== forward)
    float m_currentSpeed = 0;

    // the target speed of the motor [-1,1] (-1 == backward, 1== forward)
    float m_targetSpeed = 0;

    // some motors will have more max speed, you can scale them, for instance to 75% max output
    float m_scale = 1;
    int m_maxPwm = 100;

    // raspi specific: pwm port has pwm signal from 0 to 1024 (1024 = max)
    static int constexpr MAX_PWM = 1024;
    static float constexpr STOP_PWM = 0;

    // this is for floating point calculations
    static float constexpr EPSILON = 0.00001;

    // the step size to increase or decrease the current speed to the target speed
    static float constexpr STEP_PWM = 0.02;

    static float constexpr MIN_PWM = 0.3;

    /**
     * Initializes wiringPi and pins.
     */
    void Init();
};


#endif //G203_MOTOR_H
