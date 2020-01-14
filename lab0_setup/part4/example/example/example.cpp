// A first C++ program
// Standard libraries
#include <iostream>
#include <string>

// Specially named function that's entry point into code
int main()
{
	// allocate an array on the stack
	// this array can't be referenced outside the main function
	int myArray[10];
	// a loop that pre-increments 'i' by one each iteration of the loop
	for (int i = 0; i < 10; ++i) {
		myArray[i] = i;
		//cout is part of standard library, prints text to standard output (typically terminal window)
		std::cout << i << " ";
	}

	// create a string type. part of the standard library namespace, which is why it begins with std::
	std::string s = "hello";

	// diff kind of loop
	for (char c : s) {
		// range-based loops useful if not modifying any value
		std::cout << c;
	}


}