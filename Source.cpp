#include <iostream>
using namespace std;
double f(double, double y = 0 );
void Trapez(double, double);
void Sipmson(double, double);
void CubSipmson(double, double, double, double);
int main()
{
	double a = 0;
	double b = 2;
	double c = 0;
	double d = 1;
	//Trapez(a, b);
	//Sipmson(a, b);
	CubSipmson(a, b, c, d);
}

double f(double x, double y)
{
	double func = x * x + 2 * y;
	return func;
}

void Trapez(double a, double b)
{
	double eps = 1e-4;
	int n = 0;
	double func1 = 0;
	double func2 = 0;
	do
	{
		n++;
		double h = (b - a) / n;
		double rh = h / 2;
		double sum1 = 0;
		double sum2 = 0;
		double x1 = a;
		double x2 = a;
		for (int i = 1; i <= n; i++)
		{
			sum1 += f(x1);
			x1 += h;
		}
		for (int i = 1; i <= 2 * n; i++)
		{
			sum2 += f(x2);
			x2 += rh;
		}
		func1 = (h / 2) * (f(a) + 2 * sum1 + f(b));
		func2 = (rh / 2) * (f(a) + 2 * sum2 + f(b));
	} while (abs(func2 - func1) > 3 * eps);
	cout << "Trapez: " << func1 << endl;
	cout << "R= " << (4 * (func1 - func2)) / 3 << endl;
	double sum = 0;
	double h = (b - a) / n;
	double x = a;
	for (int i = 0; i < n; i++)
	{
		sum += f(x);
		x += h;
	}
	double d = 5e-14;
	sum = abs(sum);
	cout << "Delta: " << (sum * d * (b - a) * (b - a)) / (2 * h) << endl;
}

void Sipmson(double a, double b)
{
	double eps = 1e-4;
	int n = 10;
	double func1 = 0;
	double func2 = 0;
	do
	{
		n += 2;
		double h =  (b - a) / n;
		double rh = h / 2;
		double sum11 = 0;
		double sum12 = 0;
		double sum21 = 0;
		double sum22 = 0;
		double x11 = a;
		for (int i = 1; i <= n/2; i++)
		{
			sum11 += f(x11);
			x11 += 2 * h;
		}
		double x12 = a + h;
		for (int i = 1; i <= n/2-1; i++)
		{
			sum12 += f(x12);
			x12 += 2 * h;
		}
		double x21 = a;
		for (int i = 1; i <n; i++)
		{
			sum21 += f(x21);
			x21 += 2 * rh;
		}
		double x22 = a + rh;
		for (int i = 1; i < (n-1); i++)
		{
			sum22 += f(x22);
			x22 += 2 * rh;
		}
		func1 = (h / 3) * (f(a) + 4 * sum11 + 2 * sum12 + f(b));
		func2 = (rh / 3) * (f(a) + 4 * sum21 + 2 * sum22 + f(b));
	} while (abs(func2 - func1) > 15 * eps);
	cout << "Simpson: " << func1 << endl;
	cout << "R= " << (16 * (func1 - func2)) / 15 << endl;
}

void CubSipmson(double a, double b, double c, double d)
{
	double eps = 1e-4;
	int n = 10;
	int m = 10;
	double hx = (b - a) / (2*n);
	double hy = (d - c) /(2* m);
	double func = hx*hy/9;
	double sum = 0;
	double x = a;
	double y = c;
	for (int i = 0; i <= m - 1; i++)
	{
		for (int j=0; j<=n-1; j++)
		{
			sum += f(x, y) + 4 * f(x + hx, y) + f(x + 2 * hx, y) + 4 * f(x, y + hy) + 16 * f(x + hx, y + hy) +
			+4 * f(x + 2 * hx, y + hy) + f(x, y + 2 * hy) + 4 * f(x + hx, y + 2 * hy) + f(x + 2 * hx, y + 2 * hy);
			x += 2 * hx;
		}
		x = a;
		y += 2 * hy;
	}
	func = func * sum;
	cout << "CubSimpson: " << func << endl;
}