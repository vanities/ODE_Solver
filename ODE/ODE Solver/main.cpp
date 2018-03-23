/*Adam Mischke
CSCI/MATH 3180
Lab Assignment #2

Description:
	This program output estimates the derivatives of 4 relatively simple Ordinary Differential Equations (ODEs),
	using Euler’s, Heun’s, and Runge-Kutta’s Taylor expansions, with the support of an analytical solution,
	the program can calculate an absolute error, relative error, and can attempt to quantize Loss of Significant Figures (LOS) 
	in terms of it’s Catastrophic Cancellation (CC).

Instructions:
	First, the user picks a choice of one of the four ODEs (a,b,c,d (lowercase)) 
	Next, the user manually enters the analytical solution.
	The next input is the initial value for x, in the form x(t0).
	After that, the next two options are [a,b]: I decided to have b the first argument and a the 	second.
	Lastly, you can choose the step size (sub-intervals), N.

*/
#include <iostream>		// cout, cin
#include <cmath>		// fabs for fabulous

// prototypes that take in a series of parameters and prints out t and x
double Euler	 (char ODE, double a, double N, double h, double ivaluex, double ansol);
double Heun		 (char ODE, double a, double N, double h, double ivaluex, double ansol);
double RungeKutta(char ODE, double a, double N, double h, double ivaluex, double ansol);

int main() {

	char ODE = 'e';		// Choice of an ODE and analytical solution
	double N;			// Integer N, the number of sub intervals
	double ivaluex;		// Initial value for t, x(a) = x(t0)
	double a;			// Interval @ a, t0
	double b;			// Interval @ b, tN
	double ansol;		// The Ananlytic Solution entered in by the user
	
	// block that has the user pick an ODE
	while (ODE != 'a' && ODE != 'b' && ODE != 'c' && ODE != 'd') {

		std::cout << "Please choose an Ordinary Differential Equation:\n\
		a: x'= x / (1+t)       Analytical Solution: x= t+1\n\
		b: x'= t+x             Analytical Solution: x= -t+2e^t-1\n\
		c: x'= t-x			   Analytical Solution: x= t+2e^(1-t)-1\n\
		d: x'= (t-x) / (t+x)   Analytical Solution: x= sqrt(2t^2+1)-t\n";
		std::cin >> ODE;
	}
	// in addition to the ODE, we also need the analytical solution
	std::cout << "For the ODE, " << ODE << ", what is the Analytical Solution? (be as accurate as you can!) ";
	std::cin >> ansol;

	// set the initial value for the function x
	std::cout << "Next, choose an initial value for x(t0): ";
	std::cin >> ivaluex;

	// next, set the the end interval
	std::cout << "Next, choose the interval starting with b, in [a,b]: ";
	std::cin >> b;

	// then, the beginning interval
	std::cout << "Next, choose the beginning of the interval with a, in [a,b]: ";
	std::cin >> a;
	
	// lastly, the number of subintervals
	std::cout << "Finally, choose the number of subintervals, N: ";
	std::cin >> N;
	std::cout << "\n";

	double h = (b - a) / N;						// calculate the step size, h
	Euler(ODE, a, N, h, ivaluex, ansol);		// Do Euler's approximation
	Heun(ODE, a, N, h, ivaluex, ansol);			// Do Heun's approximation
	RungeKutta(ODE, a, N, h, ivaluex, ansol);   // Do Runge-Kutta's approximation

	return 0;	// exit
}

double Euler(char ODE, double t, double N, double h, double x, double ansol) {
	std::cout << "Euler's:\n------------------\n";
	double dx;		// derivative value

	std::cout << t << "\t" << x << "\n";
	if (ODE == 'a') {
		for (int i = 1; i <= N; i++) {

			dx = x / (1 + t);		// find the value
			x = x + (h * dx);		// use it to approximate x
			t += h;					// increment t by a step
			std::cout << t << "\t" << x << "\n";
		}
	}
	else if (ODE == 'b') {
		for (int i = 1; i <= N; i++) {

			dx = t + x;				// find the value
			x = x + (h * dx);		// use it to approximate x
			t += h;					// increment t by a step
			std::cout << t << "\t" << x << "\n";
		}
	}
	else if (ODE == 'c') {
		for (int i = 1; i <= N; i++) {

			dx = t - x;				// find the value
			x = x + (h * dx);		// use it to approximate x
			t += h;					// increment t by a step
			std::cout << t << "\t" << x << "\n";
		}
	}
	else if (ODE == 'd') {
		for (int i = 1; i <= N; i++) {

			dx = (t - x) / (t + x);	// find the value
			x = x + (h * dx);		// use it to approximate x
			t += h;					// increment t by a step
			std::cout << t << "\t" << x << "\n";
		}
	}

	// Error Calculation:
	double absErr = std::fabs(ansol - x);
	double relErr = std::fabs(((ansol - x) / ansol));

	std::cout << "\n" << "Absolute Error : " << absErr << "\n";	// print the absolute error
	std::cout << "Relative Error : " << relErr << "\n";		    // print the relative error
	std::cout << "Catastrophic Cancellation : " << absErr - relErr << "\n\n"; // finds the Loss of Significance
	return 0; // exit
}

double Heun(char ODE, double t, double N, double h, double x, double ansol) {
	std::cout << "Heun's:\n------------------\n";
	double dx, k;	// derivative and k

	std::cout << t << "\t" << x << "\n";
	if (ODE == 'a') {
		for (int i = 1; i <= N; i++) {

			dx = x / (1 + t);			// find the value
			k = x + (h * dx);			// approximate k
			t += h;						// increment t by a step
			x = x + ((h / 2) * (dx + (k / (1 + t))));	// find the average approximation
			std::cout << t << "\t" << x << "\n";
		}
	}
	else if (ODE == 'b') {
		for (int i = 1; i <= N; i++) {

			dx = t + x;					// find the value
			k = x + (h * dx);			// approximate k
			t += h;						// increment t by a step
			x = x + ((h / 2) * (dx + (t + k)));		// find the average approximation
			std::cout << t << "\t" << x << "\n";;
		}
	}
	else if (ODE == 'c') {
		for (int i = 1; i <= N; i++) {

			dx = t - x;					// find the value
			k = x + (h * dx);			// approximate k
			t += h;						// increment t by a step
			x = x + ((h / 2) * (dx + (t - k)));		// find the average approximation
			std::cout << t << "\t" << x << "\n";;
		}
	}
	else if (ODE == 'd') {
		for (int i = 1; i <= N; i++) {

			dx = (t - x) / (t + x);		// find the value
			k = x + (h * dx);			// approximate k
			t += h;						// increment t by a step
			x = x + ((h / 2) * (dx + ((t - k) / (t + k))));	// find the average approximation
			std::cout << t << "\t" << x << "\n";;
		}
	}

	// Error Calculation:
	double absErr = std::fabs(ansol - x);
	double relErr = std::fabs(((ansol - x) / ansol));

	std::cout << "\n" << "Absolute Error : " << absErr << "\n";	// print the absolute error
	std::cout << "Relative Error : " << relErr << "\n";		    // print the relative error
	std::cout << "Catastrophic Cancellation : " << absErr - relErr << "\n\n"; // finds the Loss of Significance
	return 0; // exit
}

double RungeKutta(char ODE, double t, double N, double h, double x, double ansol) {
	std::cout << "Runge-Kutta's:\n------------------\n";
	double dx, k1, k2, k3, k4;	// derivative, k1 - k4 approximations

	std::cout << t << "\t" << x << "\n";
	if (ODE == 'a') {
		for (int i = 1; i <= N; i++) {
			
			dx = x / (1 + t);							 // find values for dx & k1-k4
			k1 = h * dx;
			dx = (x + (k1 / 2)) / (1 + (t + (h / 2)));
			k2 = h * dx;
			dx = (x + (k2 / 2)) / (1 + (t + (h / 2)));
			k3 = h * dx;
			dx = (x + k3) / (1 + (t + h));
			k4 = h * dx;
			t += h;										 // increment t by a step
			x = x + (k1 + (2 * k2) + (2 * k3) + k4)/6;	 // average the 4 approximations
			std::cout << t << "\t" << x << "\n";;
		}
	}
	else if (ODE == 'b') {
		for (int i = 1; i <= N; i++) {

			dx = t + x;									 // find values for dx & k1-k4
			k1 = h * dx;
			dx = (t + (h / 2) + (x + (k1/2)));
			k2 = h * dx;
			dx = (t + (h / 2) + (x + (k2 / 2)));
			k3 = h * dx;
			dx = ((t + h) + (x + k3));
			k4 = h * dx;
			t += h;										 // increment t by a step
			x = x + (k1 + (2 * k2) + (2 * k3) + k4) / 6; // average the 4 approximations
			std::cout << t << "\t" << x << "\n";;
		}
	}
	else if (ODE == 'c') {
		for (int i = 1; i <= N; i++) {

			dx = t - x;									 // find values for dx & k1-k4
			k1 = h * dx;
			dx = (t + (h / 2) - (x + (k1 / 2)));
			k2 = h * dx;
			dx = (t + (h / 2) - (x + (k2 / 2)));
			k3 = h * dx;
			dx = ((t + h) - (x + k3));
			k4 = h * dx;
			t += h;										 // increment t by a step
			x = x + (k1 + (2 * k2) + (2 * k3) + k4) / 6; // average the 4 approximations
			std::cout << t << "\t" << x << "\n";;
		}
	}
	else if (ODE == 'd') {
		for (int i = 1; i <= N; i++) {

			dx = (t - x) / (t + x);						// find values for dx & k1-k4
			k1 = h * dx;
			dx = (t + (h / 2) - (x + (k1 / 2)))/ (t + (h / 2) + (x + (k1 / 2)));
			k2 = h * dx;
			dx = (t + (h / 2) - (x + (k2 / 2))) / (t + (h / 2) + (x + (k2 / 2)));
			k3 = h * dx;
			dx = ((t + h) - (x + k3))/ ((t + h) + (x + k3)); 
			k4 = h * dx;
			t += h;										 // increment t by a step
			x = x + (k1 + (2 * k2) + (2 * k3) + k4) / 6; // average the 4 approximations
			std::cout << t << "\t" << x << "\n";;
		}
	}
	
	// Error Calculation:
	double absErr = std::fabs(ansol - x);
	double relErr = std::fabs(((ansol - x) / ansol));

	std::cout << "\n" << "Absolute Error : " << absErr << "\n";	// print the absolute error
	std::cout << "Relative Error : " << relErr << "\n";		    // print the relative error
	std::cout << "Catastrophic Cancellation : " << absErr - relErr << "\n\n"; // finds the Loss of Significance
	return 0; // exit
}