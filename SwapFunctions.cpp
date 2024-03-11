#include <iostream>
#include <limits>
#include <type_traits>

#define INPUT_ERROR_MESSAGE "Invalid input. Please enter a valid value.\n"
#define CHAR_INPUT_ERROR_MESSAGE "Invalid input. Please enter 'y' or 'n'.\n"
#define IS_Y_OR_N(x) (tolower(x) == 'y' || tolower(x) == 'n')


using namespace std;

/**
 * Prompts the user to input a value of a specified type and handles invalid input.
 *
 * @param message The message displayed to prompt the user for input.
 * @param var Reference to the variable where the input value will be stored.
 */
template <typename T>
void getInput(const string& message, T& var) {
	while (true) {
		cout << message;
		if (!(cin >> var)) {
			cin.clear(); // Clear error flag on failed extraction.
			cerr << INPUT_ERROR_MESSAGE;
		}
		else if constexpr (is_same<T, char>::value) {
			var = tolower(var);
			if (IS_Y_OR_N(var)) return; // Use macro for 'y' or 'n' check.
			cerr << CHAR_INPUT_ERROR_MESSAGE;
		}
		else {
			return; // Exit the function for valid non-char input.
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input.
	}
}


/**
 * Swaps two values of any type.
 *
 * @param a Reference to the first value.
 * @param b Reference to the second value.
 */
void swapValues(void* a, void* b) {

	// Check if either a or b is a null pointer. If so, print an error and exit the function.
	// This check is conceptually incorrect for non-pointer T, as the dereference is invalid.
	if (a == nullptr || b == nullptr) {
		cerr << "Error: Cannot swap using null pointers." << endl;
		return;
	}

	// Create a temporary object to hold the value of a. Use std::move for efficiency,
	// enabling move semantics when possible. If T isn't a class supporting move semantics,
	// this will result in a copy operation.
	void* temp = move(a);

	// Assign the value of b to a, using std::move to enable move semantics.
	a = move(b);

	// Assign the value of temp (originally a) to b, completing the swap.
	b = move(temp);
}

/**
 * Prints the integer value.
 *
 * @param value The integer value to be printed.
 */
void printInt(const int& value) {
	cout << value;
}

/**
 * Displays the values along with a given message.
 *
 * @param message The message to be displayed before the values.
 * @param a First value.
 * @param b Second value.
 * @param printFunc Function to print the values.
 */
template <typename T>
void displayValues(const string& message, const T& a, const T& b, void (*printFunc)(const T&)) {
	cout << message << ": ";
	printFunc(a);
	cout << ", ";
	printFunc(b);
	cout << endl;
}

/**
 * Main function: Executes a loop that swaps two integers input by the user.
 *
 * @return Integer indicating exit status.
 */
int main() {
	int num1, num2;
	char repeat = 'y';

	while (tolower(repeat) == 'y') {
		getInput("Enter the value for num1 (int): ", num1);
		getInput("Enter the value for num2 (int): ", num2);

		displayValues("Before swap (integers)", num1, num2, printInt);
		swapValues(&num1, &num2);
		displayValues("After swap (integers)", num1, num2, printInt);

		getInput("Do you want to repeat the program? (y/n): ", repeat);
	}

	return 0;
}