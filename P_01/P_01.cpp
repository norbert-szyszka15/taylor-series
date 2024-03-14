#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)
FILE* fp;

struct SERIES {
	double sum;
	double exact;
	int num_of_terms;
};

struct SERIES power_series(double x, double delta, int terms_max);

double modulus(double num);

int main(int argc, char* argv[]) {
	double a, b, x, dx, delta;
	int terms_max, i;
	struct SERIES series;

	printf("Podaj liczby ograniczajace przedzial [a, b], krok dx, dokladnosc oraz maksymalna ilosc wyrazow do obliczenia:\n");
	if (scanf("%lf %lf %lf %lf %d", &a, &b, &dx, &delta, &terms_max) != 5) {
		printf("Blad wprowadzenia danych.\n");
		system("pause");
		exit(1);
	}

	if (!(fp = fopen("results.txt", "w"))) {
		printf("Blad otwarcia pliku.\n");
		exit(2);
	}
	
	printf("\tx\t|\tf_szereg(x)\t|\tf_scisle(x)\t|\tliczba wyrazow szeregu\t|\t\twarunek stopu\n");
	for (i = 0; i < 2; i++) {
		printf("---------------------------------------------------------------------"); 
	}
	printf("\n");

	fprintf(fp, "\tx\t|\tf_szereg(x)\t|\tf_scisle(x)\t|\tliczba wyrazow szeregu\t|\t\twarunek stopu\n");
	for (i = 0; i < 2; i++) {
		fprintf(fp, "---------------------------------------------------------------------");
	}
	fprintf(fp, "\n");

	for (x = a; x <= b + 0.5 * dx; x += dx) {
		series = power_series(x, delta, terms_max);

		printf("%10.3lf \t|\t%lf\t|\t%lf\t|\t\t%d\t\t|\tOSIAGNIETO ZADANA DOKLADNOSC\n",
			x, series.sum, series.exact, series.num_of_terms);
	}

	fclose(fp);
	exit(0);
	system("pause");
}

double modulus(double num) {
	if (num >= 0) {
		return num;
	} else {
		return - num;
	}
}

struct SERIES power_series(double x, double delta, int terms_max) {
	struct SERIES taylor;
	taylor.sum = 2 * (x - 1) / (x + 1);
	taylor.exact = log(x);
	taylor.num_of_terms = 1;
	double d = 2 * (x - 1) / (x + 1);
	int n = 1;

	do {
		d *= (n * (x - 1) * (x - 1)) / ((n + 2) * (x + 1) * (x + 1));
		taylor.sum += d;
		n += 2;
		taylor.num_of_terms++;
	} while ((modulus(d) >= delta) && taylor.num_of_terms < terms_max);

	return taylor;
}