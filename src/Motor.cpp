#include "Motor.hpp"

Motor::Motor(int STBY, int PWMA, int AIN1, int AIN2, int BIN1, int BIN2) 
	: STBY_(STBY), PWMA_(PWMA), AIN1_(AIN1), AIN2_(AIN2), BIN1_(BIN1), BIN2_(BIN2)
{
    pinMode(STBY_, OUTPUT);
    pinMode(PWMA_, OUTPUT);
    pinMode(AIN1_, OUTPUT);
    pinMode(AIN2_, OUTPUT);
    pinMode(BIN1_, OUTPUT);
    pinMode(BIN2_, OUTPUT);

    digitalWrite(AIN1_, LOW);
    digitalWrite(AIN2_, HIGH);
    digitalWrite(BIN1_, LOW);
    digitalWrite(BIN2_, HIGH);
    analogWrite(PWMA_, 1023);
    digitalWrite(STBY_, LOW);
}

void Motor::startWatering_A(int time_w)
{
    digitalWrite(STBY_, HIGH);
    
    digitalWrite(AIN1_, HIGH);
    digitalWrite(AIN2_, LOW);
    digitalWrite(BIN2_, HIGH);
    
    delay(time_w*1000);
}

void Motor::startWatering_B(int time_w)
{
    digitalWrite(STBY_, HIGH);
    
    digitalWrite(AIN1_, HIGH);
    digitalWrite(AIN2_, HIGH);
    digitalWrite(BIN2_, LOW);
    
    delay(time_w*1000);
}

void Motor::stopWatering()
{
    digitalWrite(STBY_, LOW);
    
}
