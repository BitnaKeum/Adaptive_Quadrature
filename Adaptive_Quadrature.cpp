#include <stdio.h>
#include <math.h>

double f(double);
double S(double, double);
double Adaptive_Quadrature(double, double, double);

double result = 0;

int main()
{
	double a = 0.0, b = 5.0;
	double TOL = 0.00001;	// 10^(-5)

	Adaptive_Quadrature(a, b, TOL);
	printf("Result : %.8f\n", result);
}

double f(double x)  // f(x) = 4xcos(2x)-(x-2)^2
{
	return 4*x*cos(2*x) - (x-2)*(x-2);	
}

double S(double a, double b) {
	double h = (b - a) / 2;
	return (h / 3) * (f(a) + 4 * f(a + h) + f(b));
}

double Adaptive_Quadrature(double a, double b, double TOL)
{
	double m = (a+b)/2;	// 구간의 중간 값
	double err = fabs(S(a, b) - S(a, m) - S(m, b));	// 오차
	if (err > 15 * TOL) {
		// 조건을 만족하여 재귀함수를 빠져나오면서 반환한 값을 result에 더함
		result += Adaptive_Quadrature(a, m, (double)TOL / 2);
		result += Adaptive_Quadrature(m, b, (double)TOL / 2);
		return 0;
	}
	else {	// 오차 <= 15*TOL
		return S(a, m) + S(m, b);	// 재귀함수 빠져나옴
	}
}
