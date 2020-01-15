#include <iostream>
#include <array>
#include <string>
#include <hashlib2plus/trunk/src/hashlibpp.h>
using namespace std;

// Recursively call this function to generate all possible combos of passLen from
// The array of characters from charArr
void testPasswordRecursion(char charArr[], string prefix, int passLen, int arrLen) {
	
	// Base case to print
	if (passLen == 0) {
		try {
			// TODO: Replace salt with the actual salt from etc/shadow file
			string alternateSum = md5wrap->getHashFromString(prefix + salt + prefix);
			/* TODO: Compute intermediate0
			hash(prefix + magic(???) + salt + length(prefix) byte of alternateSum + append NULL byte if bit is set and append first byte of prefix is unset)
			*/

			for (int i = 0; i <= 999; i++) {
				string tmp = "";

				if (i % 2 == 0) {
					tmp += intermediate;
				}
				else {
					tmp += prefix;
				};

				if (i % 3 !== 0) {
					tmp += salt;
				}

				if (i % 7 !== 0) {
					tmp += prefix;
				}

				if (i % 2 == 0) {
					tmp += prefix;
				}
				else {
					tmp += intermediate;
				};

				intermediate = md5wrap->getHashFromString(tmp);
			}
		}
		catch(h1Exception &e) {
			cout << "Hashing error" << endl;
		}
		// cout << prefix << endl;
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
	hashwrapper *md5wrap = new md5wrapper();

	/* Test function call.

	testPassword(alphabet, 1, 26);

	 	Expected Result: All contents of array alphabet in order
	 	Passed Test
	 */

	for (int i = 1; i <= 6; i++) {
		testPassword(alphabet, i, 26);
	}
}
