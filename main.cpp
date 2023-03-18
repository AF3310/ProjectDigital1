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


int main()
    {
    string function1 = "a + b + c";
    string function2 = "'a + 'b + 'c";
    string function3 = "a'b'c'd' + a'b'cd + ab'c'd";
    string function4 = "a'b + ac + bcd";
    string function5 = "'a'b + a'bc + a'bcd";
    string function6 = "'ab + ac";
    string function7 = "'a'c + 'abd + bcd + acd";
    string function8 = "abc + bcd + cde + def + efg + fgh";
    string function9 = "abc";
    string function10 = "ac + bd";
    vector<string> functions = {function1, function2, function3, function4, function5, function6, function7, function8, function9, function10};
    vector<int> size = {3,3,4,4,4,3,4,8,3,4};
    set<char> numberOfVariables;
    vector<string> result;
    vector<string> convertedSop;
    vector<int> minterms;
    vector<string> PI;
    set<string> epis;
    for(int k =0; k<10; k++){
        if(validateSOP(functions[k])){
            int n = size[k];
            cout << "F="<<functions[k] << endl << endl;
            result = splitStringByPlus(functions[k]);
            for(int i=0; i<result.size(); i++)
            {
                for(int j=0; j<result[i].size(); i++)
                {
                    if(result[i][j]!='\'')
                    {
                        char z = result[i][j];
                        numberOfVariables.insert(z);
                    }
                }
            }
            convertedSop = convert(result, n);
            minterms = print(convertedSop, n);
            vector<coveredBool> cam(result.size());
            for (int i = 0; i < result.size(); i++) {

                cam[i].value = minterm_to_binary(result[i]);
            }
           
            
            vector<vector<coveredBool>> x = group_by_num_ones(cam, n);
            vector<vector<coveredBool>> ysy = groupprimes(x, 8);
            vector<string> PI;
            for (int i = 0; i < ysy.size(); i++) {
                for (int j = 0; j < ysy[i].size(); j++) {
                    string temp;
                    for(int c =0; c< ysy[i][j].value.size(); c++)
                    {
                        if(ysy[i][j].value[c] == '1')
                        {
                            char t = 97+c;
                            temp += t;
                        }else if (ysy[i][j].value[c] == '0')
                        {
                            char t = 97 +c;
                            temp += "\'" + t;
                        }
                    }
                    if(!temp.empty())
                        PI.push_back(temp);
                }
            }
            cout << "PI: ";
            for(int i =0; i<PI.size(); i++)
            {
                cout << PI[i] << ",";
            }
            cout << endl;
            epis = epifinder(PI, n, minterms);
            numberOfVariables.clear();
            result.clear();
            cout << endl;
        }
    }
    cout << endl;
    return 0;
}


