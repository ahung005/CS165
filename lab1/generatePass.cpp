#include <iostream>
#include <sstream>
#include <array>
#include <string>
#include <bitset>
#include <vector>
#include "hashlib2plus/trunk/src/hashlibpp.h"
using namespace std;


const string salt = "4fTgjp6q";
const string crypt = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//const string salt = "hfT7jp2q";

//convert hex string to bytes
std::vector<char> HexToBytes(const std::string& hex) {
  std::vector<char> bytes;

  for (unsigned int i = 0; i < hex.length(); i += 2) {
    std::string byteString = hex.substr(i, 2);
    char byte = (char) strtol(byteString.c_str(), NULL, 16);
    bytes.push_back(byte);
  }

  return bytes;
}

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

int passCrack(string pass) {
    string intermediate1000;
    std::vector<char> inter1000;
    hashwrapper *md5wrap = new md5wrapper();

    string prefix = pass;
    //prefix = "zhgnnd";
	try {
		string alternateSum = checkBytes(md5wrap->getHashFromString(prefix + salt + prefix));
		string bytesAlt = "";
		string appendBytes = "";
  
        //cout << alternateSum << endl;
        //cout << alternateSum.length() << endl;
        std::vector<char> altSum = HexToBytes(alternateSum);
        /*
        for (int i = 0; i < altSum.size(); i++) {
            cout << altSum.at(i) << " ";
        }
        */
        //cout << endl;
        //cout << altSum.size() << endl;

        for (int i = 0; i < prefix.length(); i++) {
            //bytesAlt = bytesAlt + alternateSum[i];
            bytesAlt = bytesAlt + altSum[i];
        }
        //cout << "bytes: " <<  bytesAlt << endl;

        //cout << "Prefix length: " << prefix.length() << endl;
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

        //cout << "appendbYtes: " << appendBytes << endl;
            
		string intermediate = checkBytes(md5wrap->getHashFromString(prefix + "$1$" + salt + bytesAlt + appendBytes));
        std::vector<char> inter = HexToBytes(intermediate);
        /*
        if(intermediate == "ed7a5307588e49ed3a2777d926d62f96") {
            cout << intermediate  + " pass" << endl;
        } 
        else {
            cout << intermediate + " fail" << endl;
        }
        */

		for (int i = 0; i <= 999; i++) {
			string tmp = "";

			if (i % 2 == 0) {
				//tmp += intermediate;
                for(int j = 0; j < inter.size(); j++) {
                    tmp += inter.at(j);
                }
			}
			else {
				tmp += prefix;
			}

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
					//tmp += intermediate;
                for(int j = 0; j < inter.size(); j++) {
                    tmp += inter.at(j);
                }
			}

			intermediate = checkBytes(md5wrap->getHashFromString(tmp));
            inter = HexToBytes(intermediate);
		}
        intermediate1000 = intermediate;
        inter1000 = HexToBytes(intermediate1000);
        /*
        if(intermediate1000 == "ff202f2e9b6ac6e495570536fc89fd2a") {
            cout << intermediate1000 + " pass" << endl;
        }
        else {
            cout << intermediate1000 + " fail" << endl;
        }
        */
	}
	catch(hlException &e) {
		cout << "Hashing error" << endl;
	}

		// TODO: Get the final hash
    string finalSum = "";
    finalSum += inter1000.at(11);
    finalSum += inter1000.at(4);
    finalSum += inter1000.at(10);
    finalSum += inter1000.at(5);
    finalSum += inter1000.at(3);
    finalSum += inter1000.at(9);
    finalSum += inter1000.at(15);
    finalSum += inter1000.at(2);
    finalSum += inter1000.at(8);
    finalSum += inter1000.at(14);
    finalSum += inter1000.at(1);
    finalSum += inter1000.at(7);
    finalSum += inter1000.at(13);
    finalSum += inter1000.at(0);
    finalSum += inter1000.at(6);
    finalSum += inter1000.at(12);
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
    /*    
    if(final == "wPwz7GC6xLt9eQZ9eJkaq.") {
        cout << final + " pass" << endl;
    }
    else {
        cout << final + " fail" << endl;
    }
    */

    string finalHash = "$1$" + salt + "$" + final;
            cout << finalHash << endl;
    //if (finalHash == "$1$hfT7jp2q$wPwz7GC6xLt9eQZ9eJkaq.") {
    if (finalHash == "$1$4fTgjp6q$pgy8b7CmJFffcOr9Q.HOA1") {
		cout << prefix  + " success " <<endl;
		return 1;
	}

	cout << prefix + " fail " << endl;
	return 0;
}

void testPasswordRecursion(char charArr[], string prefix, int passLen, int arrLen) {
    // Base case to print
    if (passLen == 0) {
        cout << prefix << endl;
        if(passCrack(prefix)) {
            cout<< "all test passed" << endl;
            exit(0);
        }
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

    for (int i = 1; i <= 6; i++) {
        testPassword(alphabet, i, 26);
    }
}
