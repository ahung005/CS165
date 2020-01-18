#include <iostream>
#include <sstream>
#include <array>
#include <string>
#include <bitset>
#include "hashlib2plus/trunk/src/hashlibpp.h"
using namespace std;

// Recursively call this function to generate all possible combos of passLen from
// The array of characters from charArr

//const string salt = "4fTgjp6q";
const string crypt = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string salt = "hfT7jp2q";

// Convert direct output to human readable format
string checkBytes(string input) {
	std::ostringstream os;

	for (int i = 0; i < 16; i++)
	{
		os.width(2);
		os.fill('0');
		os << std::hex << static_cast<unsigned int>((unsigned char)(input[i]));
	}
	return os.str();
}

void reverseStr(string& str) {
    int n = str.length(); 
    // Swap character starting from two 
    // corners 
    for (int i = 0; i < n / 2; i++) 
        swap(str[i], str[n - i - 1]); 
}

void testPasswordRecursion(char charArr[], string prefix, int passLen, int arrLen) {
	// Base case to print
    string intermediate1000;
    hashwrapper *md5wrap = new md5wrapper();
	//if (passLen == 1) {
        prefix = "zhgnnd";
		try {
			string alternateSum = checkBytes(md5wrap->getHashFromString(prefix + salt + prefix));
			string bytesAlt = "";
			string appendBytes = "";

            cout << alternateSum << endl;

            for (int i = 0; i < prefix.length(); i++) {
                bytesAlt = bytesAlt + alternateSum[i];
            };
            cout << "bytes: " <<  bytesAlt << endl;

            /*
			for (int i = 0; i < (alternateSum.length()/passLen); ++i) {
				bytesAlt = bytesAlt + alternateSum;
			}
            cout << "0" << endl;
			for (int i = 0; i < (alternateSum.length()%passLen); ++i) {
				bytesAlt = bytesAlt + alternateSum[i];
			}
            */
			/*
                for (;passLen != 0; passLen >> 1) {
				    if (passLen & 1) {
                     cout << "2" << endl;
					    appendBytes = appendBytes + '0';
				    }
				    else {
                     cout << "3" << endl;
					    appendBytes = appendBytes + prefix[0];
				    }
			    }
            */
            

            cout << "Prefix length: " << prefix.length() << endl;
            if(prefix.length() == 6) {
                appendBytes += prefix[0];
                appendBytes += '\0';
                appendBytes += '\0';
            }
            else if(prefix.length() == 5) {
                appendBytes += '\0';
                appendBytes += prefix[0];
                appendBytes += '\0';
            }
            else if(prefix.length() == 4) {
                appendBytes += prefix[0]; 
                appendBytes += prefix[0];
                appendBytes += '\0';
            }
            else if(prefix.length() == 3) {
                appendBytes += '\0';
                appendBytes += '\0';
            }
            else if(prefix.length() == 2) {
                appendBytes +=  prefix[0];
                appendBytes += '\0';
            }
            else {
                appendBytes += '\0';
            }

            cout << "appendbYtes: " << appendBytes << endl;
            

			string intermediate = checkBytes(md5wrap->getHashFromString(prefix + "$1$" + salt + bytesAlt + appendBytes));
            cout << intermediate << endl;

			for (int i = 0; i <= 999; i++) {
				string tmp = "";

				if (i % 2 == 0) {
					tmp += intermediate;
				}
				else {
					tmp += prefix;
				};

				if (i % 3 != 0) {
					tmp += salt;
				}

				if (i % 7 != 0) {
					tmp += prefix;
				}

				if (i % 2 == 0) {
					tmp += prefix;
				}
				else {
					tmp += intermediate;
				};

				intermediate = checkBytes(md5wrap->getHashFromString(tmp));
			}
            intermediate1000 = intermediate;
            cout << intermediate1000 << endl;
		}
		catch(hlException &e) {
			cout << "Hashing error" << endl;
		}

		// TODO: Get the final hash
        string finalSum = "";
        finalSum += intermediate1000.at(11);
        finalSum += intermediate1000.at(4);
        finalSum += intermediate1000.at(10);
        finalSum += intermediate1000.at(5);
        finalSum += intermediate1000.at(3);
        finalSum += intermediate1000.at(9);
        finalSum += intermediate1000.at(15);
        finalSum += intermediate1000.at(2);
        finalSum += intermediate1000.at(8);
        finalSum += intermediate1000.at(14);
        finalSum += intermediate1000.at(1);
        finalSum += intermediate1000.at(7);
        finalSum += intermediate1000.at(13);
        finalSum += intermediate1000.at(0);
        finalSum += intermediate1000.at(6);
        finalSum += intermediate1000.at(12);
        //11 4 10 5 3 9 15 2 8 14 1 7 13 0 6 12
        
        string b128 = "";
        for (int i = 0; i < finalSum.size(); i += 2) {
            b128 += std::bitset<8>(finalSum[i]).to_string();
            b128 += std::bitset<8>(finalSum[i + 1]).to_string();
        }

        string final = "";
        string converted = "";
        converted += b128.substr(0,2);
        int val = std::stoull(converted, 0, 2);
        final += crypt.at(val);
        for(int i = 0; i < 21; i++) {
            string converted2 = b128.substr(2 + i * 6, 6);
            int val2 = std::stoull(converted2, 0 , 2);
            final+= crypt.at(val2);
        }
        reverseStr(final); 
        string finalHash = "$1$" + salt + "$" + final;

		//if (finalHash == "$1$4fTgjp6q$pgy8b7CmJFffcOr9Q.HOA1") {
        if (finalHash == "$1$hfT7jp2q$wPwz7GC6xLt9eQZ9eJkaq.") {
			cout << prefix  + " success " <<endl;
			return;
		}

		cout << prefix + " fail " << endl;
		return;

}

void testPassword(char charArr[], int passLen, int arrLen) {
    cout << "testPass" << endl;
	testPasswordRecursion(charArr, "", passLen, arrLen);
}


int main() {
	char alphabet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	
    //char alphabet[] = {'a', 'b', 'l', 'i', 'v', 'd', 'o', 'i'};

	for (int i = 1; i <2; i++) {
		testPassword(alphabet, i, 26);
	}
}
