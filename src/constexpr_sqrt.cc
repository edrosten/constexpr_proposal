#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

constexpr double dummy(double d)
{
	return d;
}


constexpr double csqrt(double d)
{
	bool is_constexpr  = noexcept(dummy(d));
	
	if(d < 0)
		return is_constexpr?throw domain_error("sqrt(less than zero) is not a constant expression"):numeric_limits<double>::quiet_NaN();
	else if(d != d)
		return is_constexpr?throw domain_error("sqrt(NaN) is not a constant expression"):d;
	else if(d > numeric_limits<double>::max())
		return is_constexpr?throw domain_error("sqrt(Inf) is not a constant expression"):d;

	double x = d;

	for(int i=0; i < 1000; i++)
	{
		//Bad because x^2 goes out of range
		// x -= (x*x-d)/(2*x);
		x -= (x -d/x)*0.5;
	}
	
	//Fix for very large values.
	if(x*x > numeric_limits<double>::max())
		return x*(1-numeric_limits<double>::epsilon()/2);

	return x;
}


void test(double x)
{
	cerr << (csqrt(x) - sqrt(x)) / sqrt(x) << endl;
}

int main()
{

	test(M_PI);
	test(42);
	test(9);
	test(1e200);
	test(1e-200);
	test(numeric_limits<double>::max());
	test(numeric_limits<double>::max()*0.9999);
	test(numeric_limits<double>::min());
	test(0.99999999999999);

	cout << csqrt(-1) << endl;
	
	
	//constexpr int a =  csqrt(-1);
}
