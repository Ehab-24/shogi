#pragma once

#include <string>

class Player
{
public:
	friend class Shogi;

	bool inCheck{ false };

	Player(std::string, int);

	std::string getName();

	int getColor();

	void updateTimer();

	void setStartTime();

	void showTimer();

	void setName(std::string);

	~Player() {}

private:
	std::string name{};

	int timeleft{};

	int startTime{};

	int color;

	/*
	
	int time;
	
	int score; etc

	*/
};

