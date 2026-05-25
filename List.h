#pragma once
#include "ListElement.h"
#include <limits>

//klasa reprezentująca listę jedno- i dwukierunkową
class List
{
	private:
		ListElement* firstElement; //wskaźnik na pierwszy element listy
        ListElement* lastElement; //wskaźnik na ostatni element listy
        int size; //rozmiar listy
	public:

		List(ListElement* firstElement, ListElement* lastElement, int size) {
            this->firstElement = firstElement;
            this->lastElement = lastElement;
            this->size = size; 
		}

		void setFirstElement(ListElement* firstElement) {
			this->firstElement = firstElement;
		}

		ListElement* getFirstElement() {
			return firstElement;
		}

		ListElement* getLastElement() {
			return lastElement;
		}

        //dodawanie elementu na koniec listy
        void addElement(int value) {
            if (firstElement == nullptr) {
                firstElement = new ListElement(value, nullptr, nullptr);
                lastElement = firstElement;
            }
            else {
                ListElement* element = firstElement;
                while (element->getNextElement() != nullptr) {
                    element = element->getNextElement();
                }
                element->setNextElement(new ListElement(value, element, nullptr));
                lastElement = element->getNextElement();
            }
            size++;
        }

        //dodawanie elementu na koniec listy w wersji dwukierunkowej
        void addElementDouble(int value){
            if (firstElement == nullptr) {
                firstElement = new ListElement(value, nullptr, nullptr);
                lastElement = firstElement;
            }
            else{
                lastElement = new ListElement(value, lastElement, nullptr);
                lastElement->getPreviousElement()->setNextElement(lastElement);
            }
            size++;
        }

        //funkcja zwracająca wartość wybranego elemntu z listy
        int getElement (int position) {
            if (position >= size || position < 0){
                return std::numeric_limits<int>::max();
            }
            int i = 0;
            ListElement* element = firstElement;
            while (i < position) {
                element = element->getNextElement();
                i++;
            }
            return element->getValue();
        }

        //funkcja zwracająca wartość wybranego elemntu z listy dwukierunkowej
        int getElementDouble(int position){
            if (position >= size || position < 0){
                return std::numeric_limits<int>::max();
            }
            if(position < size / 2){
                int i = 0;
                ListElement* element = firstElement;
                while (i < position) {
                    element = element->getNextElement();
                    i++;
                }
                return element->getValue();
            }
            else{
                int i = size - 1;
                ListElement* element = lastElement;
                while (i > position) {
                    element = element->getPreviousElement();
                    i--;
                }
                return element->getValue();
            }
        }

        //funkcja zmienająca wartość wybranego elemntu z listy
        void setElement (int position, int value) {
            if(position >= 0 && position < size){
                int i = 0;
                ListElement* element = firstElement;
                while (i < position) {
                    element = element->getNextElement();
                    i++;
                }
                element->setValue(value);
            }
        }
        
        //funkcja zmienająca wartość wybranego elemntu z listy dwukierunkowej
        void setElementDouble(int position, int value){
            if(position >= 0 && position < size){
                if(position < size / 2){
                    int i = 0;
                    ListElement* element = firstElement;
                    while (i < position) {
                        element = element->getNextElement();
                        i++;
                    }
                    element->setValue(value);
                }
                else{
                    int i = size - 1;
                    ListElement* element = lastElement;
                    while (i > position) {
                        element = element->getPreviousElement();
                        i--;
                    }
                    element->setValue(value);
                }
            }
        }
        
        ~List() {
            ListElement* element = firstElement;
            while (element != nullptr) {
                ListElement* next = element->getNextElement();
                delete element;
                element = next;
            }
        }
};

