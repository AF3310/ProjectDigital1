//
//  boolCovered.hpp
//  DigitalDesign Project1
//
//  Created by Ahmed Moamen on 18/03/2023.
//

#ifndef boolCovered_hpp
#define boolCovered_hpp

#include <stdio.h>


#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class coveredBool {
public:
    string value; // The value of the covered string
    vector<int> coverIndexes; // The indexes of the minterms that cover this string
    bool isCombined; // Flag indicating whether this string has been combined with another one
    coveredBool();
    coveredBool(string val, int coverIndex);
    coveredBool(string val, vector<int> coverIndices);
    bool operator==(const coveredBool& other) const;
    bool operator<(const coveredBool& other) const;
    bool is_covered_by(int coverIndex) const;
    void add_cover_index(int coverIndex);
    int get_num_cover_indices() const;
};

vector<coveredBool> generate_covered_bools(const vector<string>& minterms);
int hammingDistance(string x, string y);
coveredBool combine_minterms(coveredBool x, coveredBool y);
string minterm_to_binary(string Minterm);
vector<vector<coveredBool>> groupprimes(vector<vector<coveredBool>>& mintermGroups, int numVars);
vector<vector<coveredBool>> group_by_num_ones(const vector<coveredBool>& coveredBools, int size);

#endif /* boolCovered_hpp */
