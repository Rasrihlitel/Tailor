#include <stdio.h>
#include <locale.h>
#include <math.h>
const float pi = 3.14;
const float two_pi = pi * 2;
double e_x(double x, int n) {
	double summa = 1, sl = 1;
	for (int i = 1; i <= n; i++) {
		sl = (sl * x) / i;
		summa += sl;
	}
	return summa;
}

double sinus(double x, int n) {
	double rec = fmod(x, two_pi);
	if (rec > two_pi) {
		rec -= two_pi;
	}
	else if (rec < -two_pi) {
		rec += two_pi;
	}
	x = floor(rec);
	double summa = x, sl = x;
	for (int i = 0; i <= (n / 2); i++) {
		sl = (sl * x * x * (-1)) / ((2 * i) * (2 * i + 1));
		summa += sl;
	}
	return summa;
}

int main() {
	setlocale(LC_ALL, "RUS");
	int n;
	double x, summa;
	printf("Введите значение X в синусе: ");
	scanf_s("%lf", &x);
	printf("Введите количество членов разложения синуса в ряде Тейлора: ");
	scanf_s("%d", &n);
	summa = sinus(x, n);
	printf("Значение синуса: %lf\n", summa);

	printf("Введите значение X в экспоненте: ");
	scanf_s("%lf", &x);
	printf("Введите количество членов разложения экспоненты в ряде Тейлора: ");
	scanf_s("%d", &n);
	summa = e_x(x, n);
	printf("Значение экспоненты: %lf\n", summa);
	return 0;
}