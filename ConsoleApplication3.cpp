//
//  main.cpp
//  testerForDigital
//
//  Created by Ahmed Moamen on 15/03/2023.
//

#include <iostream>
#include <vector>
#include<math.h>
#include <string>
#include <set>
#include<map>
#include<unordered_map>
using namespace std;

class coveredBool {
public:
    std::string value; // The value of the covered string
    std::vector<int> coverIndexes; // The indexes of the minterms that cover this string
    bool isCombined; // Flag indicating whether this string has been combined with another one
    bool isVisited = false;
    coveredBool() {
        value = "";
        isCombined = false;
    }

    coveredBool(std::string val, int coverIndex) {
        value = val;
        coverIndexes.push_back(coverIndex);
        isCombined = false;
    }

    coveredBool(std::string val, std::vector<int> coverIndices) {
        value = val;
        coverIndexes = coverIndices; //shallow copy, dont forget to fix this.
        isCombined = false;
    }

    bool operator==(const coveredBool& other) const {
        return (value == other.value && coverIndexes == other.coverIndexes);
    }

    bool operator<(const coveredBool& other) const {
        return (value < other.value);
    }

    bool is_covered_by(int coverIndex) const {
        return (std::find(coverIndexes.begin(), coverIndexes.end(), coverIndex) != coverIndexes.end());
    }

    void add_cover_index(int coverIndex) {
        coverIndexes.push_back(coverIndex);
    }

    int get_num_cover_indices() const {
        return coverIndexes.size();
    }
};

vector<coveredBool> generate_covered_bools(const vector<string>& minterms) {
    vector<coveredBool> coveredBools;
    for (const string& minterm : minterms) {
        coveredBools.emplace_back(minterm, vector<int>{stoi(minterm)}); //fix up
    }
    return coveredBools;
}




int hammingDistance(string x, string y) {
    int diff = 0;
    for (int i = 0; i < x.length(); i++) {
        if (x[i] != y[i]) {
            diff++;
        }
    }
    return diff;
}
coveredBool combine_minterms(coveredBool x, coveredBool y) {
    coveredBool result;
    int diffCount = 0;
    int xLen = x.value.length();
    int yLen = y.value.length();
    //maybe here add a combined bool that changes x and y so that if it is combinable then, remove it from the primeImplicants list
    if (xLen != yLen) {
        // Strings have different lengths, return empty string
        return result;
    }

    for (int i = 0; i < xLen; i++) {
        if (x.value[i] != y.value[i]) {
            diffCount++;
            if (diffCount > 1) {
                // Strings differ by more than 1 character, return empty string
                return result;
            }
            result.value += "-";
        }
        else {
            result.value += x.value[i];
        }
    }

    // If the two strings differ by only one character, return the combined string
    if (diffCount == 1) {
        result.coverIndexes = x.coverIndexes; //shallow copy???
        result.coverIndexes.insert(result.coverIndexes.end(), y.coverIndexes.begin(), y.coverIndexes.end());
        return result;
    }

    // Strings are identical, return empty string
    return result;
}

string minterm_to_binary(string Minterm)
{
    string binary = "";
    int multiplier = 1;
    for (int j = 0; j < Minterm.size(); j++)
    {
        if (Minterm[j] == '\'')
        {
            multiplier = 0;

        }
        else {
            binary += static_cast<char>(1 * multiplier + 48);
            multiplier = 1;
        }
    }

    return binary;
}
string minterm_to_binary2(string Minterm, int num_vars)
{
    string binary = "";
    int multiplier = 1;
    int var_index = num_vars - 1;

    for (int j = 0; j < Minterm.size(); j++)
    {
        if (Minterm[j] == '\'')
        {
            multiplier = 0;
        }
        else {
            if (var_index >= 0 && Minterm[j] == 'a' + var_index) {
                binary += static_cast<char>(1 * multiplier + 48);
                var_index--;
            }
            else {
                binary += "-";
            }
            multiplier = 1;
        }
    }

    // Add dashes for remaining variables if any
    for (int i = var_index; i >= 0; i--) {
        binary += "-";
    }

    return binary;
}
vector<vector<coveredBool>> groupprimes(vector<vector<coveredBool>>& mintermGroups, int numVars) {

    vector<vector<coveredBool>> primeimplicants(numVars);
    for (int i = 0; i < mintermGroups.size() - 1; i++) {
        for (int j = 0; j < mintermGroups[i].size(); j++) {
            for (int k = 0; k < mintermGroups[i + 1].size(); k++) {
                int diff = hammingDistance(mintermGroups[i][j].value, mintermGroups[i + 1][k].value);
                if (diff == 1) {
                    coveredBool combinedMin = combine_minterms(mintermGroups[i][j], mintermGroups[i + 1][k]);
                    bool duplicate = false;
                    for (auto it = primeimplicants[i].begin(); it != primeimplicants[i].end(); it++) {
                        if (it->value == combinedMin.value && it->coverIndexes == combinedMin.coverIndexes) {
                            duplicate = true;
                            break;  
                        }
                    }
                    if (!duplicate) {
                        combinedMin.isVisited = true;
                        primeimplicants[i].push_back(combinedMin);
                        
                    }
                    mintermGroups[i][j].isCombined = true;
                    mintermGroups[i + 1][k].isCombined = true;
                }
            }
        }
    }

    for (int i = 0; i < mintermGroups.size() ; i++) {
        for (int j = 0; j < mintermGroups[i].size(); j++) {

            if (mintermGroups[i][j].isCombined == false) {
                primeimplicants[i].push_back(mintermGroups[i][j]);


            }


        }

    }
    return primeimplicants;
}

std::vector<std::vector<coveredBool>> group_by_ones_new(const std::vector<coveredBool>& cb_vec) {
    std::vector<std::vector<coveredBool>> result;
    std::unordered_map<int, std::vector<coveredBool>> temp_map;
    int max_ones = -1;

    // Iterate through the input vector and group the coveredBool objects
    // based on how many ones are in their value field
    for (const auto& cb : cb_vec) {
        int num_ones = std::count(cb.value.begin(), cb.value.end(), '1');
        if (num_ones > max_ones) {
            max_ones = num_ones;
        }
        temp_map[num_ones].push_back(cb);
    }

    // Convert the map into a vector of vectors and return it
    for (int i = 1; i <= max_ones; i++) {
        result.push_back(temp_map[i]);
    }
    return result;
}

vector<vector<coveredBool>> group_new(const vector<coveredBool>& coveredBools, int size) {
    int x = coveredBools.size();
    vector<int> sizesarr(x);
    //cout << " size is " << x;
    int count = 0;
    //cout << "SUZE: " << sizesarr.size();
    for (int i = 0; i < x; i++) {
        count = 0;
        for (int k = 0; k < coveredBools[i].value.size(); k++) { //not all same size but thas ok
            if (coveredBools[i].value[k] == '1') {
                count++;
            }
        }
        //cout << count << " count is " << endl;
        sizesarr[i]=(count); //look at again
    }
    for (int i = 0; i < sizesarr.size(); i++)
        cout << sizesarr[i] << endl;
    int xxx = sizesarr.size();
    vector<vector<coveredBool>> y;
    y.resize(xxx);
    for (int i = 0; i < xxx; i++) {
        for (int k = 0; k < coveredBools.size(); k++) {
            if (sizesarr[k] == i) {
                y[i].push_back(coveredBools[k]);
            }
        }
    }
    for (int s = 0; s < sizesarr.size(); s++) {
        cout<<sizesarr[s]<< " ";
    }
    return y;

}



std::string convert_variable_string(int num_vars, std::string variable_string) {
    std::string result(num_vars, '-');
    for (char c : variable_string) {
        if (c >= 'A' && c <= 'Z') {
            c += 'a' - 'A';  // convert to lowercase
        }
        if (c >= 'a' && c < 'a' + num_vars) {
            result[c - 'a'] = '1';
        }
        else if (c == '\'') {
            continue;
        }
        else {
            return "";  // invalid character
        }
    }
    return result;
}
string mintermtobinary(string x) { //ex of abd
    string final = "";
    int multiplier=1;
    unordered_map<int, char> y;
    y['a'] = 0;
    y['b'] = 1;
    y['c'] = 2; y['d'] = 3; y['e'] = 4; y['f'] = 5; y['g'] = 6; y['h'] = 7; y['i'] = 8; y['j'] = 9;
    for (int i = 0; i < x.size(); i++) {
        cout << y[x[i]] << " is current ";
        if (y[x[i]] != i) {
            final += "-";
        }
        else {
            if (x[i] == '\'')
            {
                multiplier = 0;

            }
            else {
                final += static_cast<char>(1 * multiplier + 48);
                multiplier = 1;
            }
        }
    }return final;
}
int main() {
    coveredBool xx, yy, zz, xx1, yy1, zz1, zzz, xxx, yyy;
    //make function to implement transforming the abc notation to 1s and 0s
    //string function1 = "a + b + c";
    vector<string> sops = { "a'bcdef","acdb'ef","'abcdef"};

    int numvarsf = 6;
    vector<coveredBool> cam(sops.size());
    for (int i = 0; i < sops.size(); i++) {

        cam[i].value = minterm_to_binary(sops[i]);
        //cout << cam[i].value << endl;
    }


    vector<vector<coveredBool>> x = group_by_ones_new(cam); //group 3 not being read 
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[i].size(); j++)
        {
            //cout << x[i][j].value<<" is in group "<<i<<endl;
        }
        cout << endl;
    }

 //dont forget to update 
    vector<vector<coveredBool>> temp;
    vector<vector<coveredBool>> temp2;
    temp = groupprimes(x, 8);
    for (int i = 0; i < numvarsf-1; i++) {
        temp2 = groupprimes(temp, 8);
        temp = temp2;
    }

    for (int i = 0; i < temp2.size(); i++) {
        cout << "Component " << i << ": ";
        for (int j = 0; j < temp2[i].size(); j++) {
            cout << temp2[i][j].value << " ";
        }
        cout << endl;
    }
    return 0;
}
