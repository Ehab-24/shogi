#include "Player.h"

#include "Utility.h"

#include <time.h>

using namespace std;

Player::Player(string name, int color) :name(name), color(color) { this->timeleft = 600, this->startTime = 0; }

string Player::getName() { return this->name; }

void Player::setStartTime() { this->startTime = time(0); }

void Player::updateTimer() { this->timeleft -= (time(0) - startTime); }

int Player::getColor() { return this->color; }

void Player::showTimer()
{
	int min = this->timeleft / 60;
	int sec = this->timeleft % 60;

	bgiout << min << ":" << sec;

	setcolor(TEXT_COLOR);

	this->color == BLACK ? outstreamxy(1460, 30) : outstreamxy(40, 30);
}

void Player::setName(std::string n) { this->name = n; }