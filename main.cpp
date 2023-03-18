#include <iostream>
#include <bitset>
#include <cmath>
#include <stack>
#include <string>
#include <vector>
#include <set>

using namespace std;


vector<string> splitString(string inputStr) {
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


vector<int> print(vector<string> function, int size)
{
    int numRows = pow(2, size);
    
    vector<vector<int>> table(numRows, vector<int>(size)); //try BOOL for both if get errors
    
    for (int i = 0; i < numRows; i++) {
        for (int j = size - 1; j >= 0; j--) {
            table[i][j] = (i >> (size - j - 1)) & 1;
        }
    }
    
    vector<bool> F(numRows, false);
    
    vector<string> tableU;
    
    for (int i = 0; i < numRows; i++) {
        string temp = "";
        for (int j = 0; j < size; j++) {
            temp += static_cast<char>(table[i][j] + 48);
        }
        tableU.push_back(temp);
    }
    
    for(int i =0; i< numRows; i++)
    {
        for(int j =0; j<function.size(); j++)
        {
            int counter =0;
            for(int x =0; x<size; x++)
            {
                if(tableU[i][x] == function[j][x] ||function[j][x] == '-')
                {
                    counter++;
                    //cout << tableU[i][x] << "== " << function[j][x] << endl;
                }//else
                   //cout << tableU[i][x] << "!= " << function[j][x] << endl;
            }
            //cout << counter << endl;
            if(counter ==  size){
                F[i] = true;
                break;
            }
        }
    }
    char c;
    for(c = 'a'; c < 'a'+ size; c++)
    {
        cout << c << " ";
    }
    cout << "F"<< endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < size; j++) {
            cout << table[i][j] << " ";
        }
        if(F[i]==true)
        {
            cout<<"1";
        }
        else
        {
            cout<<"0";
        }
        cout << endl;
    }
    
    vector<int> posLines;
    vector<int> sopLines;
    
    //function to put the lines of sop or pos
    for (int i=0;  i < numRows; i++)
    {
            if(F[i]==true)
            {
                sopLines.push_back(i);
            }
            else if(F[i]==false)
            {
                posLines.push_back(i);
            }
    }
    
    
    int i=0;
    vector<string> sopValues(sopLines.size());
    vector<string> posValues(posLines.size());
    
    cout << "\nm:Σ(";
    while (i<sopLines.size())
        {
            cout << sopLines[i] << ",";
            i++;
        }
    i = 0;
    cout << ")\nM:Π(";
    while (i<posLines.size())
        {
            cout << posLines[i] << ",";
            i++;
        }
    cout << ")\n";

    
    return sopLines;
}


