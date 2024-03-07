// SwapFunctions.cpp : Defines the entry point for the application.
//

#include "SwapFunctions.h"
#include <cstring>
#include <iostream>
#include <limits>
#include <type_traits>

using namespace std;


/**
 * Prompts the user to input a value of a specified type and handles invalid
 * input.
 *
 * @param message The message displayed to prompt the user for input.
 * @param var Reference to the variable where the input value will be stored.
 */
template <typename T> 
void getInput(const char* message, T& var) {
    while (true) {
        cout << message;
        if ((cin >> var)) {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Invalid input. Please enter a valid value.\n";
    }
}

/**
 * Swaps the contents of two memory locations of a given size.
 *
 * @param num1Ptr Pointer to the first memory location.
 * @param num2Ptr Pointer to the second memory location.
 * @param size Size of the memory to be swapped.
 */
void swap(void* num1Ptr, void* num2Ptr, size_t size) {
    unsigned char* buffer = static_cast<unsigned char*>(malloc(size));
    if (buffer == nullptr) {
        std::cerr << "Memory allocation failed.\n";
        exit(EXIT_FAILURE);
    }
    memcpy(buffer, num1Ptr, size);
    memcpy(num1Ptr, num2Ptr, size);
    memcpy(num2Ptr, buffer, size);
    free(buffer);
}

/**
 * Prints the integer value pointed to by a const void pointer.
 *
 * @param value Pointer to the integer value to be printed.
 */
void printInt(const void* value) { cout << *(const int*)value; }

/**
 * Displays the values pointed to by two const void pointers, along with a given
 * message, using a provided printing function.
 *
 * @param message The message to be displayed before the values.
 * @param num1Ptr Pointer to the first value.
 * @param num2Ptr Pointer to the second value.
 * @param printFunc Pointer to a function used to print the values.
 */
void displayValues(const char* message, const void* num1Ptr,
    const void* num2Ptr, void (*printFunc)(const void*)) {
    cout << message << ": ";
    printFunc(num1Ptr);
    cout << ", ";
    printFunc(num2Ptr);
    cout << endl;
}

/**
 * The main function of the program that repeatedly prompts the user to input
 * two integers, displays them, swaps them, and then asks if the user wants to
 * repeat the process.
 *
 * @return Integer (0 for successful execution).
 */
int main() {
    char repeat = 'y';
    while (tolower(repeat) == 'y') {
        int num1, num2;
        getInput("Enter the value for num1 (int): ", num1);
        getInput("Enter the value for num2 (int): ", num2);
        displayValues("Before swap (integers)", &num1, &num2, printInt);
        swap(&num1, &num2, sizeof(num1));
        displayValues("After swap (integers)", &num1, &num2, printInt);
        cout << "Do you want to repeat the program? (y/n): ";
        cin >> repeat;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return 0;
}
