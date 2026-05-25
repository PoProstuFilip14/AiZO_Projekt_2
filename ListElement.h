#pragma once

//klasa reprezentująca pojedynczy element listy
class ListElement
{
	private:
		int value; //wartość przechowywana w liście
		ListElement* previousElement; //wskaźnik na poprzedni element
		ListElement* nextElement; //wskaźnik na następny element
	public:

		ListElement(int value, ListElement* previousElement, ListElement* nextElement) {
			this->value = value;
			this->nextElement = nextElement;
			this->previousElement = previousElement;
		}

		void setValue(int value) {
			this->value = value;
		}

		void setPreviousElement(ListElement* previousElement) {
			this->previousElement = previousElement;
		}

		void setNextElement(ListElement* nextElement) {
			this->nextElement = nextElement;
		}

		int getValue() {
			return value;
		}

		ListElement* getPreviousElement() {
			return previousElement;
		}

		ListElement* getNextElement() {
			return nextElement;
		}
};

