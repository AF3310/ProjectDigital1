//
//  main.cpp
//  Part 2
//
//  Created by Youssof Alwardany on 15/03/2023.
//

#include <iostream>
#include <bitset>
#include <cmath>
#include <stack>
#include <string>
#include <vector>
#include <set>

using namespace std;


vector<string> splitStringByPlus(string inputStr) {
    vector<string> result;
    size_t pos = 0;
    string delimiter = "+";

    while ((pos = inputStr.find(delimiter)) != string::npos) {
        string token = inputStr.substr(0, pos);
        result.push_back(token);
        inputStr.erase(0, pos + delimiter.length());
    }
    result.push_back(inputStr);
    return result;
}


vector<string> convert(vector<string> expression, int n)
{
    vector<string> converted_sop;
    
    for(int i =0; i <expression.size(); i++)
    {
        string temp;
        temp.resize(n,'-');
        int multiplier = 1;
        for (int j =0; j<expression[i].size(); j++)
        {
             int value = expression[i][j] - 'a';
            temp[value] = static_cast<char>(1*multiplier + 48);
            if(expression[i][j] == '\'')
                multiplier = 0;
            else
                multiplier = 1;
        }
        converted_sop.push_back(temp);
    }
    
    return converted_sop;
}


void print(vector<string> function, int size)
{
    int numRows = pow(2, size);
    
    int counter=0;
    
    vector<vector<string>> table(numRows, vector<string>(size)); //try BOOL for both if get errors
    
    for (int i = 0; i < numRows; i++) {
            int entry = i;
            for (int j = 0; j < size; j++) {
                table[i][j] = entry % 2;
                
                entry /= 2;
            }
        }
    
    int j=0;
    vector<bool> x(size, numRows);
    
    for (int i = 0; i < numRows; i++)
    {
            while(j<size)
            {
                for(int k=0; k<function[i].size(); k++)
                {
                if(function[k]!="-")
                    {
                        if(function[k]==table[i][j] && x[i]!=false)
                        {
                            x[i]=true;
                        }
                        else
                        {
                            x[i]=false;
                        }
                        j++;
                    }
                }
            }
            
        }
    
    
    for (int i = 0; i < numRows; i++)
    {
            for (int j = 0; j < size; j++) {
                cout << table[i][j] << " ";
            }
            if(x[i]==true)
            {
                cout<<"1";
            }
            else
            {
                cout<<"0";
            }
            cout << endl;
        }
    
}

    

int main()
    {
    
    string function;
    vector<string> result = splitStringByPlus(function);
    
    set<char> numberOfVariables;
    
    for(int i=0; i<result.size(); i++)
    {
        for(int j=0; j<result[i].size(); i++)
        {
            if(result[i][j]!='!')
            {
                char z = result[i][j];
                numberOfVariables.insert(z);
            }
        }
    }
    
    int size = numberOfVariables.size();
    
    print(convert(result, size), size);
    
    return 0;
}
