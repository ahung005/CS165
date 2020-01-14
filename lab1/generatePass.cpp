#include <iostream>
#include <array>
using namespace std;


// Recursively call this function to generate all possible combos of passLen from
// The array of characters from charArr
void testPasswordRecursion(char charArr[], string prefix, int passLen, int arrLen) {
	
	// Base case to print
	if (passLen == 0) {
		cout << (prefix) << endl;
		return;
	}

	// Recursively find all possible combos of passLen
	for (int i = 0; i < arrLen; i++) {
		string newPrefix;

		newPrefix = prefix + charArr[i];

		testPasswordRecursion(charArr, newPrefix, passLen - 1, arrLen);
	}
}

void testPassword(char charArr[], int passLen, int arrLen) {
	testPasswordRecursion(charArr, "", passLen, arrLen);
}

int main() {
	char alphabet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	
	/* Test function call.

	testPassword(alphabet, 1, 26);

	 	Expected Result: All contents of array alphabet in order
	 	Passed Test
	 */

	for (int i = 1; i <= 6; i++) {
		testPassword(alphabet, i, 26);
	}
}
