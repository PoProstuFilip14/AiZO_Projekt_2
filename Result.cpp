#include "Result.h"
#include <ctime>

Result::Result(long long  time, int size, bool error) {
	this->time = time;
    this->timestamp = std::time(NULL);
	this->size = size;
	this->error = error;
}

void Result::setResult(long long  time, int size, bool error) {
	this->time = time;
    this->timestamp = std::time(NULL);
	this->size = size;
	this->error = error;
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

bool Result::getError(){
	return error;
}