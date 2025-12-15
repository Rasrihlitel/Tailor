#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

typedef double(*pFunc)(double);
typedef double(*pMyFunc)(double, int);

//Приветствие
void hello() {
	printf("0. Выход\n");
	printf("1. Ввод данных\n");
	printf("2. Разложение экспоненты\n");
	printf("3. Разложение синуса\n");
	printf("4. Разложение косинуса\n");
	printf("5. Разложение логарифма\n");
	printf("Ваш выбор: ");
}

//Введение данных
void touch(int* n, int* m, double*a, double*b){
	double buff;
	printf("Введите количество точек: ");
	scanf_s("%d", n);
	if ((*n) < 0) {
		touch(n, m ,a, b);
	}
	printf("Введите количество слагаемых: ");
	scanf_s("%d", m);
	printf("Задайте левый конец отрезка: ");
	scanf_s("%lf", a);
	printf("Задайте правый конец отрезка: ");
	scanf_s("%lf", b);
	if (a > b) {
		buff = (*a);
		(*a) = (*b); 
		(*b) = buff;
	}
}

//Создание массива
double* arr(double* m, int s) {
	if (m != NULL) {
		free(m);
	}
	m = (double*)malloc(s * sizeof(double));
	return m;
}
//Заполнение массивов
void input(double a, double b, int n, int m, pFunc f, pMyFunc my_f,  double* x, double* f_x, double* my_f_x) {
	double l = (b - a) / (n - 1);
	for (int i = 0; i < n; i++) {
		x[i] = a + (l * i);
		f_x[i] = f(x[i]);
		my_f_x[i] = my_f(x[i], m);
	}
}

//Вывод таблицы
void print_tab(double* x, double* f_x, double* my_f_x, int s) {
	double max = 0;
	printf(" Значение X | Функция Си | Моя функция\n");
	for (int i = 0; i < s; i++) {
		printf("%.8lf | %.8lf | %.8lf\n", x[i], f_x[i], my_f_x[i]);
		if (max < fabs(f_x[i] - my_f_x[i])) {
			max = fabs(f_x[i] - my_f_x[i]);
		}
	}
	printf("MAX = %lf\n", max);
}

//Экспонента
double my_exp(double x, int n) {
	double summa = 1, sl = 1; 
	int count = 0;

	while (x > 1.0 || x < -1.0) {
		x = x / 2.0;
		count++;
	}
	for (int i = 1; i <= n; i++) {
		sl = (sl * x) / i;
		summa += sl;
	}
	for (int i = 0; i < count; i++) {
		summa = summa * summa;
	}
	return summa;
}

//Синус
double my_sinus(double x, int n) {
	while (x > 2*M_PI) x -= 2*M_PI;
	while (x < 0) x += 2*M_PI;    
	double result = x;
	double term = x;
	for (int i = 1; i <= n; i++) {
		term *= (-x*x) / ((2 * i) * (2 * i + 1));
		result += term;
	}

	return result;
}
//Косинус
double my_cosinus(double x, int n) {
	while (x > 2 * M_PI) x -= 2 * M_PI;
	while (x < 0) x += 2 * M_PI;

	double summa = 1.0;    
	double sl = 1.0;

	for (int i = 1; i <= n; i++) {
		sl *= (-x * x) / ((2 * i - 1) * 2 * i);
		summa += sl;
	}

	return summa;
}

//Логарифм
double my_log(double x, int n) {
	if (x <= 0) {
		if (x == 0) {
			return -INFINITY;
		}
		return NAN;
	}
	int m = 0;
	double f = x;
	while (f >= 1) {
		f /= 2;
		m++;
	}
	while (f < 0.5) {
		f *= 2;
		m--;
	}
	double z = f - 1, sum = 0, ch = z, sign = 1;
	for (int i = 1; i <= n; n++) {
		sum += (sign*ch) / i;
		ch *= z;
		sign = -sign;
		if (fabs(ch / n) < 1e-12) {
			break;
		}
	}
	return m*0.69314718056 + sum;
}

int main() {
	setlocale(LC_ALL, "RUS");
	double (*f)(double, int), l, * x = nullptr, * f_x = nullptr, * my_f_x = nullptr, a, b;
	int n, turn, code, m;
	do {
		hello();
		turn = scanf_s("%d", &code);
		switch (code) {
		case 0: break;
		case 1: touch(&n, &m, &a, &b);
			x = arr(x, n);
			f_x = arr(f_x, n);
			my_f_x = arr(my_f_x, n);
			break;
		case 2: input(a, b, n, m, exp, my_exp, x, f_x, my_f_x);
			print_tab(x, f_x, my_f_x, n);
			break;
		case 3:input(a, b, n, m, sin, my_sinus, x, f_x, my_f_x);
			print_tab(x, f_x, my_f_x, n);
			break;
		case 4: input(a, b, n, m, cos, my_cosinus, x, f_x, my_f_x);
			print_tab(x, f_x, my_f_x, n);
			break;
		case 5: input(a, b, n, m, log, my_log, x, f_x, my_f_x);
			print_tab(x, f_x, my_f_x, n);
			break;
		default: if (turn == 0) {
			printf("Ошибка, можно вводить только числа\n");
			while (getchar() != '\n');
			break;
		}
			   if (code > 5 || code < 0) {
				   printf("Можно вводить числа только от 1 до 5\n");
				   break;
			   }
		}
	} while (code != 0);

	if (x != NULL) {
		free(x);
	}
	if (f_x != NULL) {
		free(f_x);
	}
	if (my_f_x != NULL) {
		free(my_f_x);
	}
	return 0;
}