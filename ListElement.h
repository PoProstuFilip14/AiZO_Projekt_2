#pragma once

//klasa reprezentująca pojedynczy element listy
template <typename T>
class ListElement
{
	private:
		T value; //wartość przechowywana w liście
		ListElement<T>* previousElement; //wskaźnik na poprzedni element
		ListElement<T>* nextElement; //wskaźnik na następny element
	public:

		ListElement(T value, ListElement<T>* previousElement, ListElement<T>* nextElement) {
			this->value = value;
			this->nextElement = nextElement;
			this->previousElement = previousElement;
		}

		void setValue(T value) {
			this->value = value;
		}

		void setPreviousElement(ListElement<T>* previousElement) {
			this->previousElement = previousElement;
		}

		void setNextElement(ListElement<T>* nextElement) {
			this->nextElement = nextElement;
		}

		int getValue() {
			return value;
		}

		ListElement<T>* getPreviousElement() {
			return previousElement;
		}

		ListElement<T>* getNextElement() {
			return nextElement;
		}
};