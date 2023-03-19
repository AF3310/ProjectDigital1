//
//  main.cpp
//  DigitalDesign Project1
//
//  Created by Ahmed Moamen on 13/03/2023.
//

#include <iostream>
#include "validateSOP.hpp"
#include "epiGenerator.hpp"
#include "truthtable.hpp"
#include "boolCovered.hpp"
#include <bitset>
using namespace std;


vector<string> getPI(vector<int> minterms, int numvars)
{
    vector<coveredBool> cam(minterms.size());
    for (int i = 0; i < minterms.size(); i++) {

        cam[i].value = decimalToBinary(minterms[i], 3);
    }
   
    
    vector<vector<coveredBool>> x = group_by_num_ones(cam, 3);
    vector<vector<coveredBool>> ysy = groupprimes(x, 8);
    vector<vector<coveredBool>> test = groupprimes(ysy, 8);
    vector<vector<coveredBool>> test1 = groupprimes(test, 8);
    vector<string> PI;
    for (int i = 0; i < test1.size(); i++) {
        for (int j = 0; j < test1[i].size(); j++) {
            string temp;
            for(int c =0; c< test1[i][j].value.size(); c++)
            {
                if(test1[i][j].value[c] == '1')
                {
                    char t = 97+c;
                    temp += t;
                }else if (test1[i][j].value[c] == '0')
                {
                    char t = 97 +c;

                    temp += "\'" + t;
                }
            }
            if(!temp.empty())
                PI.push_back(temp);
        }
    }
    for(int i =0; i<PI.size(); i++)
    {
        cout << PI[i] << ",";
    }
    return PI;
}
int main()
    {
    string function1 = "a + b + c";
    string function2 = "'a + 'b + 'c";
    string function3 = "a'b'c'd' + a'b'cd + ab'c'd";
    string function4 = "a'b + ac + bcd";
    string function5 = "'a'b + bcd";
    string function6 = "'ab + ac";
    string function7 = "a'bc +bd + ad";
    string function8 = "abc + bcd + cde + def + efg + fgh";
    string function9 = "abc";
    string function10 = "ac + bd";
    vector<string> functions = {function1, function2, function3, function4, function5, function6, function7, function8, function9, function10};
    vector<int> size = {3,3,4,4,4,3,4,8,3,4};
    vector<string> result;
    vector<string> convertedSop;
    vector<int> minterms;
    set<string> epis;
    vector<string> PI;
    for(int k =0; k<10; k++){
        if(validateSOP(functions[k])){
            int n = size[k];
            cout << "F="<<functions[k] << endl << endl;
            result = splitStringByPlus(functions[k]);
            convertedSop = convert(result, n);
            minterms = print(convertedSop, n);
            //PI
            cout << "bye";
            PI = getPI(minterms, n);
            cout << "hi";
            //EPI
            epis = epifinder(PI, n, minterms);
            result.clear();
            cout << endl;
        }
    }
    cout << endl;
    return 0;
}

