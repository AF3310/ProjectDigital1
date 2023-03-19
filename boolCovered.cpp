#include <iostream>
#include <vector>
#include<math.h>
#include <string>
#include <set>
#include<map>
using namespace std;

class coveredBool {
public:
    std::string value; // The value of the covered string
    std::vector<int> coverIndexes; // The indexes of the minterms that cover this string
    bool isCombined; // Flag indicating whether this string has been combined with another one
    bool visited;
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
    string binary="";
        int multiplier = 1;
        for (int j =0; j<Minterm.size(); j++)
        {
            if(Minterm[j] == '\'')
            {
                multiplier = 0;

            }else{
                binary += static_cast<char>(1*multiplier+48);
                multiplier = 1;
            }
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

                        primeimplicants[i].push_back(combinedMin);
                        //primeimplicants[i].visited = true;
                        
                    }
                    mintermGroups[i][j].isCombined = true;
                    mintermGroups[i][j].visited = true;

                    mintermGroups[i + 1][k].isCombined = true;
                }
            }
        }
    }

    for (int i = 0; i < mintermGroups.size() - 1; i++) {
        for (int j = 0; j < mintermGroups[i].size(); j++) {
          
                if (mintermGroups[i][j].isCombined == false &&mintermGroups[i][j].visited ==false) {
                    primeimplicants[i].push_back(mintermGroups[i][j]);


                }
            

        }

    }

    return primeimplicants;
}


vector<vector<coveredBool>> group_by_num_ones(const vector<coveredBool>& coveredBools, int size) {

    vector<vector<coveredBool>> groups(size+1);

    vector<int> numOfOnes;

    for (int i = 0; i < coveredBools.size(); i++)

    {
        int temp = 0;
            for(int c =0; c<coveredBools[i].value.size(); c++)
            {
                temp += coveredBools[i].value[c]-'0';
            }
        numOfOnes.push_back(temp);
    }

    for (int i = 0; i < size+1; i++)

    {
        vector<coveredBool> temp;

        for (int j = 0; j < numOfOnes.size(); j++)
        {
            if (numOfOnes[j] == i)
                temp.push_back(coveredBools[j]);
        }
        groups[i] = temp;
    }

    return groups;

}
