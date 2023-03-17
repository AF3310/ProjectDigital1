#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <math.h>

using namespace std;
std::vector<std::string> get_implicants(const std::string& sop) {
    vector<std::string> implicants;
    int num_vars = sop.find_first_of(' ');
    //try 2
    int i = 0;
    while (i < sop.size()) {
        //cout<<i<<endl;
        if (sop[i] == '+' or sop[i] == ' ') {
            i++;
            continue;
        }
        else if (sop[i] == '!') {
            int lenofbit = 1;
            if (i != 0) {
                if (sop[i - 1] == ' ') {
                    int count = 1; 
                    int j = i;
                    while (sop[j] != ' ' && j<sop.size()) {

                        if (sop[j] == '!') {
                            count++;
                        }
                        j++;
                    }
                    std::string implicant = sop.substr(i, num_vars + count);
                    i += num_vars;
                    implicants.push_back(implicant);

                }
            }

        }
        else {
            std::string implicant = sop.substr(i, num_vars);
            i += num_vars;
            implicants.push_back(implicant);
        }
        i++;
    }
    return implicants; //returns it like 90% correct
}
// Function to find the binary representation of a decimal number
string decimalToBinary(int decimal, int numBits) {
    string binary = "";
    while (decimal > 0) {
        binary = to_string(decimal % 2) + binary;
        decimal /= 2;
    } //converts decimal to binary
    while (binary.length() < numBits) {
        binary = "0" + binary;
    }
    return binary;
}

// Function to find the hamming distance between two binary strings
int hammingDistance(string str1, string str2) {
    int dist = 0;
    for (int i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) {
            dist++;
        }
    }
    return dist;
}
bool isCovered(int minterm, string implicant) {
    string binary = decimalToBinary(minterm, implicant.length());
    for (int i = 0; i < binary.length(); i++) {
        if (implicant[i] != '-' && implicant[i] != binary[i]) { //here we basically check if 
            return false;
        }
    }
    return true;
}


vector<string> findPrimeImplicants(vector<int> minterms, int numBits) { //technically numBits should be same as numVars
    vector<string> implicants;
    for (int minterm : minterms) {
        implicants.push_back(decimalToBinary(minterm, numBits));
    }

    vector<string> primeImplicants;
    while (!implicants.empty()) {
        string maxImplicant;
        int maxCount = 0;

        // Find the implicant that covers the most minterms
        for (string implicant : implicants) {
            int count = 0;
            for (int minterm : minterms) {
                if (isCovered(minterm, implicant)) {
                    count++;
                }
            }
            if (count > maxCount) {
                maxImplicant = implicant;
                maxCount = count;
            }
        }

        // Add the implicant to the list of prime implicants
        primeImplicants.push_back(maxImplicant); //

        // Remove all minterms covered by the implicant from the minterms vector
        for (auto it = minterms.begin(); it != minterms.end();) {
            if (isCovered(*it, maxImplicant)) {
                it = minterms.erase(it);
            }
            else {
                ++it;
            }
        }

        // Remove the implicant from the implicants vector
        implicants.erase(remove(implicants.begin(), implicants.end(), maxImplicant), implicants.end());
    }

    return primeImplicants;
}
// Function to generate a vector of all possible combinations of 1s and 0s
vector<string> generateCombinations(int numBits) {
    vector<string> combinations;
    for (int i = 0; i < pow(2, numBits); i++) {
        combinations.push_back(decimalToBinary(i, numBits));
    }
    return combinations;
}

// Function to generate a vector of minterms given a list of implicants

vector<int> generateMinterms(vector<string> implicants) {
    vector<int> minterms;
    for (string imp : implicants) {
        int minterm = 0;
        for (int i = 0; i < imp.length(); i++) {
            if (imp[i] == '!') {
                minterm += pow(2, imp.length() - i - 1);
            }
        }
        minterms.push_back(minterm);
    }
    return minterms;
}

int main() {
    //cout << "hifsi";
    vector<string> x = get_implicants("ABC + !ABD + !A!BC");

    vector<int> minterms = generateMinterms(x);
    //cout << "hifsi";
    vector<string> yy = findPrimeImplicants(minterms, 3);
    for (int i = 0; i < yy.size() - 1; i++) {

        cout << yy[i] << " ";

    }
    return 0;

}
