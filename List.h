#pragma once
#include "ListElement.h"
#include <limits>

//klasa reprezentująca listę jedno- i dwukierunkową
template <typename T>
class List
{
	private:
		ListElement<T>* firstElement; //wskaźnik na pierwszy element listy
        ListElement<T>* lastElement; //wskaźnik na ostatni element listy
        int size; //rozmiar listy
	public:

		List(ListElement<T>* firstElement, ListElement<T>* lastElement, int size) {
            this->firstElement = firstElement;
            this->lastElement = lastElement;
            this->size = size; 
		}

		void setFirstElement(ListElement<T>* firstElement) {
			this->firstElement = firstElement;
		}

		ListElement<T>* getFirstElement() {
			return firstElement;
		}

		ListElement<T>* getLastElement() {
			return lastElement;
		}

        //dodawanie elementu na koniec listy
        void addElement(T value) {
            if (firstElement == nullptr) {
                firstElement = new ListElement<T>(value, nullptr, nullptr);
                lastElement = firstElement;
            }
            else {
                ListElement<T>* element = firstElement;
                while (element->getNextElement() != nullptr) {
                    element = element->getNextElement();
                }
                element->setNextElement(new ListElement<T>(value, element, nullptr));
                lastElement = element->getNextElement();
            }
            size++;
        }

        //dodawanie elementu na koniec listy w wersji dwukierunkowej
        void addElementDouble(T value){
            if (firstElement == nullptr) {
                firstElement = new ListElement<T>(value, nullptr, nullptr);
                lastElement = firstElement;
            }
            else{
                lastElement = new ListElement<T>(value, lastElement, nullptr);
                lastElement->getPreviousElement()->setNextElement(lastElement);
            }
            size++;
        }

        //funkcja zwracająca wartość wybranego elemntu z listy
        T getElement (int position) {
            if (position >= size || position < 0){
                return std::numeric_limits<T>::max();
            }
            int i = 0;
            ListElement<T>* element = firstElement;
            while (i < position) {
                element = element->getNextElement();
                i++;
            }
            return element->getValue();
        }

        //funkcja zwracająca wartość wybranego elemntu z listy dwukierunkowej
        T getElementDouble(int position){
            if (position >= size || position < 0){
                return std::numeric_limits<T>::max();
            }
            if(position < size / 2){
                int i = 0;
                ListElement<T>* element = firstElement;
                while (i < position) {
                    element = element->getNextElement();
                    i++;
                }
                return element->getValue();
            }
            else{
                int i = size - 1;
                ListElement<T>* element = lastElement;
                while (i > position) {
                    element = element->getPreviousElement();
                    i--;
                }
                return element->getValue();
            }
        }

        //funkcja zmienająca wartość wybranego elemntu z listy
        void setElement (int position, T value) {
            if(position >= 0 && position < size){
                int i = 0;
                ListElement<T>* element = firstElement;
                while (i < position) {
                    element = element->getNextElement();
                    i++;
                }
                element->setValue(value);
            }
        }
        
        //funkcja zmienająca wartość wybranego elemntu z listy dwukierunkowej
        void setElementDouble(int position, T value){
            if(position >= 0 && position < size){
                if(position < size / 2){
                    int i = 0;
                    ListElement<T>* element = firstElement;
                    while (i < position) {
                        element = element->getNextElement();
                        i++;
                    }
                    element->setValue(value);
                }
                else{
                    int i = size - 1;
                    ListElement<T>* element = lastElement;
                    while (i > position) {
                        element = element->getPreviousElement();
                        i--;
                    }
                    element->setValue(value);
                }
            }
        }
        
        ~List() {
            ListElement<T>* element = firstElement;
            while (element != nullptr) {
                ListElement<T>* next = element->getNextElement();
                delete element;
                element = next;
            }
        }
};