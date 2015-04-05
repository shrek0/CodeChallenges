#ifndef SIEVEOFERATOSTHENES_H
#define SIEVEOFERATOSTHENES_H

#include <QVector>

class SieveOfEratosthenes
{
public:
	SieveOfEratosthenes(int endNumber);
	~SieveOfEratosthenes();

	QVector<int> &getResults();

private:
	void doIt();

	void markerNumbersInSkips(int skip);
	int getSmallestPrimeNumber();

	void findNotMarkedNumbers();

	QVector<int> *pNumbersArray;
	int numbersArrayLength;

	QVector<int> *pResultsArray;

	int endNumber;
};

#endif // SIEVEOFERATOSTHENES_H
