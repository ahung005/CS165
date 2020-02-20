#include <iostream>
#include <sstream>
#include <array>
#include <string>
#include <bitset>
#include <vector>
#include <chrono>
#include <ctime>
#include "hashlib2plus/trunk/src/hashlibpp.h"
using namespace std;


const string salt = "4fTgjp6q";
const string crypt = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
double passCount = 0;
const auto start = chrono::system_clock::now();

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
    try {
        string alternateSum = checkBytes(md5wrap->getHashFromString(prefix + salt + prefix));
        string bytesAlt = "";
        string appendBytes = "";
  
        std::vector<char> altSum = HexToBytes(alternateSum);

        for (int i = 0; i < prefix.length(); i++) {
            //bytesAlt = bytesAlt + alternateSum[i];
            bytesAlt = bytesAlt + altSum[i];
        }

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

        string intermediate = checkBytes(md5wrap->getHashFromString(prefix + "$1$" + salt + bytesAlt + appendBytes));
        std::vector<char> inter = HexToBytes(intermediate);

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
    }
    catch(hlException &e) {
        cout << "Hashing error" << endl;
    }

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

    if (finalHash == "$1$4fTgjp6q$pgy8b7CmJFffcOr9Q.HOA1") {
        cout << finalHash << endl;
        cout << prefix  + " success " <<endl;
        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end-start;
        auto throughput = passCount/elapsed_seconds.count();
        cout << "Throughput: " << throughput << "passwords per second" << endl;
        return 1;
    }
    passCount += 1;
    return 0;
}

void testPasswordRecursion(char charArr[], string prefix, int passLen, int arrLen) {
    // Base case to print
    if (passLen == 0) {
        if(passCrack(prefix)) {
            cout << prefix << endl;
            cout<< "all test passed" << endl;
            exit(0);
        }
        return;
    }

    // Recursively find all possible combos of passLen
    for (int i = 1; i <= arrLen; i++) {
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
