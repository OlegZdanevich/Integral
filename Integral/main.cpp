
#include <iostream>

using namespace std;

void IsDataValid(double&, double&, double&, int&);
typedef double(*Formula) (double, double, int);
double Simpson(double, double, int);
double DualConversion(double, double, double, int, Formula);
double LeftTriangle(double, double, int );

int main()
{
	double eps, DownValue, UpValue;
	eps = DownValue = UpValue = 0;
	int n = 0;
	IsDataValid(eps, DownValue, UpValue, n);
	system("cls");
	Formula formula = Simpson;
	cout << "Integral from Simpson : "<< DualConversion(eps, DownValue, UpValue, n, formula) << endl;
	formula = LeftTriangle;
	cout << "Integral left Triangle : "<<DualConversion(eps, DownValue, UpValue, n, formula) << endl;
	char k;
	cout << "If you want to continue, type y or Y" << endl;
	cin >> k;
	if (k == 'y' || k == 'Y') main();
	return 0;
}

void IsDataValid(double& eps, double& DownValue, double& UpValue, int& n)
{
	try 
	{
		cout << "Enter 0 < eps < 1 : " << endl;
		cin >> eps;
		cout << "Enter down value" << endl;
		cin >> DownValue;
		cout << "Enter up value" << endl;
		cin >> UpValue;
		cout << "Enter n > 0 : " << endl;
		cin >> n;
		if (n <= 0) throw 1;
		if (eps <= 0 && eps >= 1) throw 2;
		if (DownValue >= UpValue) throw 3;
	}
	catch (int i)
	{
		cout << "Error " << i << " . Values will be default" << endl;
		system("pause");
		eps = 0.01;
		DownValue = 1;
		UpValue = 2;
		n = 2;
	}
}
double LeftTriangle(double LowerLimit, double UpperLimit, int k)
{
	double step = (UpperLimit - LowerLimit) / k;
	double t = LowerLimit;
	double integral = 0;
	while (t < UpperLimit)
	{
		integral += log(t);
		t += step;
	}
	integral *= step;
	return integral;
}
double Simpson(double a, double b, int n)
{
	double h;
	h = (b - a) / n;

	double I, I2 = 0, I4 = 0;
	I4 = log(a + h);
	for (int k = 2; k < n; k += 2)
	{
		I4 += log(a + (k + 1)*h);
		I2 += log(a + k*h);
	}
	I = log(a) + log(b) + 4 * I4 + 2 * I2;
	I *= h / 3;

	return I;

}
double DualConversion(double eps, double DownValue, double UpValue, int n, Formula formula)
{
	double PreviosIntegral = 0, NextIntegral = 1;
	while (fabs(PreviosIntegral - NextIntegral) > eps)
	{
		PreviosIntegral = formula(DownValue, UpValue, n);
		NextIntegral = formula(DownValue, UpValue, 2 * n);
		n = 2 * n;
	}
	double integral = formula(DownValue, UpValue, n);
	return integral;
}