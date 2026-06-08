#pragma once
#include <ctime>
#include <chrono>

//klasa reprezentująca wynik pojedynczego pomiaru
class Result
{
	protected:
		long long time; //zmierzony czas
        time_t timestamp; //data wykonania pomiaru
		int size; //rozmiar danych, dla którego wykonano pomiar
	public:
		Result(long long  time = -1, int size = -1);

		void setResult(long long  time, int size);

		long long  getTime();

		time_t getTimestamp();

		int getSize();
};