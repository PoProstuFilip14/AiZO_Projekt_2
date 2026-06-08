#include "Result.h"
#include <ctime>

Result::Result(long long  time, int size) {
	this->time = time;
    this->timestamp = std::time(NULL);
	this->size = size;
}

void Result::setResult(long long  time, int size) {
	this->time = time;
    this->timestamp = std::time(NULL);
	this->size = size;
}

long long Result::getTime(){
	return time;
}

time_t Result::getTimestamp(){
	return timestamp;
}

int Result::getSize(){
	return size;
}