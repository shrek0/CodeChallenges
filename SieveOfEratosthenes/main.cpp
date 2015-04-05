#include <QString>

#include "sieveoferatosthenes.h"

int main(int argc, char *argv[])
{
	SieveOfEratosthenes *sieveOfEratosthenes;
	QVector<int> results;
	QString string;

	sieveOfEratosthenes = new SieveOfEratosthenes(100000);

	results = sieveOfEratosthenes->getResults();

	for(int i = 0; i < results.size(); ++i) {
		string += QString::number(results[i]);
		string += " ";
	}

	qDebug(string.toAscii());

	delete sieveOfEratosthenes;

	return 0;
}
