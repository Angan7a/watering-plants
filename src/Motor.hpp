#pragma once

#include <Ticker.h>

class Motor {
	int STBY_ = 12; //standby
	//Motor A
	int PWMA_ = 5; //Speed control
	int AIN1_ = 14; //Direction
	int AIN2_ = 4; //Direction
	int BIN1_ = 14; //Direction 1
	int BIN2_ = 1; //Direction 0
	int time_wait = 0;
	Ticker d;
	static void wait()
	{
		static int time_elaps = 0;
		time_elaps++;
	}
public:
	Motor(int STBY = 12, int PWMA = 5, int AIN1 = 14, int AIN2 = 4, int BIN1 = 14, int BIN2 = 1);

	void startWatering_A(int time_w);
	void startWatering_B(int time_w);
	void stopWatering();
};
