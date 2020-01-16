#include <iostream>
#include <array>
#include <string>
//#include <bitset>
#include <hashlib2plus/trunk/src/hashlibpp.h>
using namespace std;

// Recursively call this function to generate all possible combos of passLen from
// The array of characters from charArr
void testPasswordRecursion(char charArr[], string prefix, int passLen, int arrLen) {
	// Base case to print
	if (passLen == 0) {
		try {
			string alternateSum = md5wrap->getHashFromString(prefix + salt + prefix);
			/* TODO: Compute intermediate0
			
			*/
			string bytesAlt = "";
			string appendBytes = "";
			//string binary = bitset<4>(passLen).to_string();

			for (int i = 0; i < (alternateSum.length()/passLen); ++i) {
				bytesAlt = bytesAlt + alternateSum;
			}

			for (int i = 0; i < (alternateSum.length()%passLen); ++i) {
				bytesAlt = bytesAlt + alternateSum[i];
			}

			for (;passLen != 0; passLen >> 1) {
				if (passLen & 1) {
					appendBytes = appendBytes + 0;
				}
				else {
					appendBytes = appendBytes + prefix[0];
				}
			}

			string intermediate = md5wrap->getHashFromString(prefix + "1" + salt + bytesAlt + appendBytes);

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

		// TODO: Get the final hash

		if (finalHash == '$1$4fTgjp6q$pgy8b7CmJFffcOr9Q.HOA1') {
			cout << prefix << endl;
			break;
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
	const string salt = "4fTgjp6q";

	for (int i = 1; i <= 6; i++) {
		testPassword(alphabet, i, 26);
	}
}
