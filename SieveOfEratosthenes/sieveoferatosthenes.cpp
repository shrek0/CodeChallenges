#include "sieveoferatosthenes.h"
#include "qstring.h"

SieveOfEratosthenes::SieveOfEratosthenes(int endNumber) {
	this->endNumber = endNumber;

	numbersArrayLength = endNumber;

	pNumbersArray = new QVector<int>(numbersArrayLength, 0);
	pResultsArray = new QVector<int>(0);

	(*pNumbersArray)[0] = 1; // set 1
	(*pNumbersArray)[1] = 1;

	doIt();
}

SieveOfEratosthenes::~SieveOfEratosthenes() {
	delete pNumbersArray;
	delete pResultsArray;
}

void SieveOfEratosthenes::markerNumbersInSkips(int skip) {
	(*pNumbersArray)[skip] = skip;

	for(int i = skip*skip; i < pNumbersArray->size(); i+=skip) {
		(*pNumbersArray)[i] = skip;
	}
}

int SieveOfEratosthenes::getSmallestPrimeNumber() {
	return pNumbersArray->indexOf(0);
}

void SieveOfEratosthenes::findNotMarkedNumbers() {
	for(int i = 0; i < pNumbersArray->size(); ++i) {
		if(pNumbersArray->at(i) == 0)
			pResultsArray->append(i); // We are starting from 0.
	}
}


void SieveOfEratosthenes::doIt() {
	int smallestPrimeNumber = 2;

	for(int i = 0; smallestPrimeNumber != -1 &&
		smallestPrimeNumber*smallestPrimeNumber < numbersArrayLength; ++i) {
		pResultsArray->append(smallestPrimeNumber);

		markerNumbersInSkips(smallestPrimeNumber);

		smallestPrimeNumber = getSmallestPrimeNumber();
	}

	findNotMarkedNumbers();
}

QVector<int> &SieveOfEratosthenes::getResults()
{
	return *pResultsArray;
}
