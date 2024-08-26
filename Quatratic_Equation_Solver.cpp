// Quatratic_Equation_Solver.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
	This program prompts the user to enter a quadratic equation, extracts the coefficients from the equation using regular expressions, and then calculates and displays the roots (whether they are real or complex) using the quadratic formula.
*/

#include <iostream>
#include <cmath>
#include <string>
#include <regex>
#include <complex>

typedef std::string str;

class QuadraticEquation {

private: 
	str equation; //equation declaration
	double a = 0, b = 0, c = 0; //declaration and initialization of the coefficients

public:
	void promptEquation() {

		//prompt the user to enter the equation in a specific format
		std::cout << "Please enter the quatratic equation in this format ( ax^2 + bx + c = 0 )";
		std::getline(std::cin, equation); //store the equation in a variable

		//remove spaces from the equation string for easier parsing
		equation.erase(
			remove(equation.begin(),
				   equation.end(),
				   ' '),
			equation.end()
		);
	}
	void CoefficientExtratctor() {
		// Use regex to extract the coefficients a, b, and c
		std::regex regexPattern(R"(([-+]?\d*\.?\d*)x\^2([-+]?\d*\.?\d*)x([-+]?\d*\.?\d*)=0)");
		std::smatch matches;

		// If the equation matches the pattern, extract the coefficients
		if (std::regex_search(equation, matches, regexPattern)) {

			// Extract and convert the a coefficient
			std::string aStr = matches[1];
			if (aStr.empty() || aStr == "+") a = 1;       // If no coefficient or just a '+', a = 1
			else if (aStr == "-") a = -1;                 // If just a '-', a = -1
			else a = std::stod(aStr);                     // Convert string to double

			// Extract and convert the b coefficient
			std::string bStr = matches[2];
			if (bStr.empty() || bStr == "+") b = 1;       // If no coefficient or just a '+', b = 1
			else if (bStr == "-") b = -1;                 // If just a '-', b = -1
			else b = std::stod(bStr);                     // Convert string to double

			// Extract and convert the c coefficient
			std::string cStr = matches[3];
			if (cStr.empty()) c = 0;                      // If no coefficient, c = 0
			else c = std::stod(cStr);                     // Convert string to double
		}
		else {
			// If the equation does not match the expected format, display an error
			std::cout << "Invalid quadratic equation format." << std::endl;
		}
	}

	// Prints roots of quadratic equation ax*2 + bx + x
	void quadraticFormula() {
		//before solving for x, check that is not 0 otherwise it isnt a valid quadratic equation
		if (a == 0) {
			std::cout << "Invalid quadratic equation format." << std::endl;
		}

		//step 1 find the discriminent
		double D = (b * b) - (4 * (a * c));

		//step 2 square the discriminent 
		double squaredD = std::sqrt(std::abs(D));

		//step 3 Check the nature of the roots using the discriminant
		if (D > 0) {
			// Two real and distinct roots
			double x1 = (-b + squaredD) / (2 * a);
			double x2 = (-b - squaredD) / (2 * a);
			std::cout << "The roots are real and different: " << x1 << " and " << x2 << std::endl;
		}
		else if (D == 0) {
			// One real root (both roots are the same)
			double x = -b / (2 * a);
			std::cout << "The roots are real and identical: " << x << std::endl;
		}
		else {
			// Two complex roots
			std::complex<double> x1((-b / (2 * a)), (squaredD / (2 * a)));
			std::complex<double> x2((-b / (2 * a)), -(squaredD / (2 * a)));
			std::cout << "The roots are complex: " << x1 << " and " << x2 << std::endl;
		}
	}

	void Solve() {
	//call all the methods to complete the algorithm
		promptEquation();

		CoefeitientExtratctor();

		quadraticFormula();
	}

};

int main()
{
	QuadraticEquation equation;
	equation.Solve();

	std::cin.get();
	return 0;
}