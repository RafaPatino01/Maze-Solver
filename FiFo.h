#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class T>
class CFiFo {
protected:
	T* aData;
	int aMax;
	int aMaxO;
	int aCur;
	int aErr;
	int aExt;

public:
	CFiFo(int pMax, int pExt);
	~CFiFo(void);

	void push(T pVal);
	T pop(void);
	T front(void);
	bool isEmpty(void);
	bool isFull(void);

	int getErr(void);

	void descr(void);

private:
	bool resize(bool pGrow);
}; // CFiFo

template <class T>
CFiFo<T>::CFiFo(int pMax, int pExt)
{
	aData = NULL;
	aMax = pMax;
	aMaxO = aMax;
	aCur = 0;
	aErr = 0;
	aExt = pExt;
	if (aMax > 0) {
		aData = new T[aMax];
		if (!aData)
			aErr = -1; // Arreglo sin memoria
	}
} // Constructor

template <class T>
CFiFo<T>::~CFiFo(void)
{
	if (aData != NULL)
		delete[] aData;
	aMax = 0;
	aMaxO = 0;
	aCur = 0;
	aErr = 0;
	aExt = 0;
} // Destructor

template <class T>
void CFiFo<T>::push(T pVal)
{
	aErr = 0;

	if (aData) {
		if (!isFull()) {
			aData[aCur++] = pVal;
			//aCur = 10
			//aCur++ -> asigna 10, y luego vale 11
			//++aCur -> incrementa a 11 y luego asigna
		}
		else {
			if (resize(true)) {
				push(pVal);
			}
			else {
				aErr = -4; // No se pudo aumentar el tamaño de la pila
			}
			//aErr = -2; // Inserción sobre pila llena
		}
	}
	else {
		aErr = -1; // Arreglo sin memoria
	}
} // push

template <class T>
T CFiFo<T>::pop(void)
{
	T lVal;

	aErr = 0;

	if (aData) {
		if (!isEmpty()) {
			lVal = aData[0];

			for (int lIdx = 0; lIdx < aCur - 1; lIdx++) {
				aData[lIdx] = aData[lIdx + 1];
			}

			--aCur;

			if (aMax - aCur >= aExt) {
				if (aMax - aExt >= aMaxO) {
					resize(false);
				}
			}

		}
		else {
			aErr = -3; // Sacar dato de pila vacía
		}
	}
	else {
		aErr = -1; // Arreglo sin memoria
	}

	return lVal;
} // pop

template <class T>
T CFiFo<T>::front(void)
{
	T lVal;

	aErr = 0;

	if (aData) {
		if (!isEmpty()) {
			lVal = aData[0];
		}
		else {
			aErr = -3; // Sacar dato de pila vacía
		}
	}
	else {
		aErr = -1; // Arreglo sin memoria
	}

	return lVal;
} // Front


template <class T>
bool CFiFo<T>::isEmpty(void)
{
	return (aCur == 0);
} // isEmpty

template <class T>
bool CFiFo<T>::isFull(void)
{
	return (aCur == aMax);
} // isFull

template <class T>
int CFiFo<T>::getErr(void)
{
	return aErr;
} // getErr

template <class T>
void CFiFo<T>::descr(void)
{
	std::cout << aMax << '|' << (isEmpty() ? 'T' : 'F') << '|' << (isFull() ? 'T' : 'F') << '|';
	std::cout << aErr << '|';

	for (int lIdx = 0; lIdx < aCur; lIdx++) {
		std::cout << aData[lIdx] << ';';
	}

	std::cout << std::endl;
} // descr

template <class T>
bool CFiFo<T>::resize(bool pGrow)
{
	bool lRes = false;

	int lMax = 0;
	if (pGrow) {
		lMax = aMax + aExt;
	}
	else {
		lMax = aMax - aExt;
	}
	T* lData = new T[lMax];
	if (lData) {
		for (int lIdx = 0; lIdx < aCur; lIdx++) {
			lData[lIdx] = aData[lIdx];
		}
		delete[] aData;
		aData = lData;
		aMax = lMax;
		lRes = true;
	}

	return lRes;
} // resize

