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
        bool error; //zmienna boolowska informująca o tym czy algorytm zadziałał błędnie
	public:
		Result(long long  time = -1, int size = -1, bool error = false);

		void setResult(long long  time, int size, bool error);

		long long  getTime();

		time_t getTimestamp();

		int getSize();

		bool getError();
};