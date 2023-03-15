//
//  epiGenerator.cpp
//  DigitalDesign Project1
//
//  Created by Ahmed Moamen on 14/03/2023.
//

#include "epiGenerator.hpp"
using namespace std;

string decimalToBinary(int decimalNum, int numBits) {
    // Convert decimal number to binary string
    bitset<64> binary(decimalNum);
    return binary.to_string().substr(binary.size() - numBits);
}
//helper function to remove
vector<vector<bool>> removeRowsAndKeepColumns(vector<vector<bool>> inputVector, vector<int> rowsToRemove, vector<int> columnsToKeep) {
    // Remove rows
    for (int i = rowsToRemove.size() - 1; i >= 0; i--) {
        inputVector.erase(inputVector.begin() + rowsToRemove[i]);
    }

    // Keep columns
    for (int i = 0; i < inputVector.size(); i++) {
        vector<bool> temp;
        for (int j = 0; j < columnsToKeep.size(); j++) {
            temp.push_back(inputVector[i][columnsToKeep[j]]);
        }
        inputVector[i] = temp;
    }
    return inputVector;
}

template<typename T>
void printSet(const set<T>& s) {
    cout << "{ ";
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << *it;
        if (next(it) != s.end()) {
            cout << ", ";
        }
    }
    cout << " }" << endl;
}

set<string> epifinder(vector<string> pi, int n, vector<int> minterms)
{
    //base case
    set<string> epis;
    if(pi.size() == 1)
        return epis;
    
    //2d vector for checking
    vector<vector<bool>> checkEPI(pi.size(), vector<bool> (minterms.size()));
    
    //minterms in a set to check for remaining
    set<int> remaining(minterms.begin(), minterms.end());
    
    //convert minterms to binary values
    vector<string> mintermsB;
    for(int i =0; i<minterms.size(); i++)
    {
        mintermsB.push_back(decimalToBinary(minterms[i], n));
    }
    
    //converts pi to binary
    vector<string> piS;
    for(int i =0; i <pi.size(); i++)
    {
        string temp;
        temp.resize(n,'-');
        int multiplier = 1;
        for (int j =0; j<pi[i].size(); j++)
        {
            int value = pi[i][j] - 'a';
            temp[value] = static_cast<char>(1*multiplier + 48);
            if(pi[i][j] == '\'')
            {
                multiplier = 0;
            }else{
                multiplier = 1;
            }
            }
        piS.push_back(temp);
        }
    
    //checks if minterms and pis to check which belongs to which
    for(int i =0; i< mintermsB.size(); i++)
    {
        for(int j =0; j<piS.size(); j++)
        {
            int counter =0;
            for(int x =n-1; x>=0; x--)
            {
                if(mintermsB[i][x] == piS[j][x] ||piS[j][x] == '-')
                {
                    counter++;
                }
            }
            if(counter ==  n){
                checkEPI[j][i] = true;
            }
        }
    }

    int epiIndex =-1;
    // set to store in epis index in pi
    set<int> episI;
    
    //fill in episI
    for(int i = 0; i<mintermsB.size(); i++){
        int counter = 0;
        for(int j = 0; j< pi.size(); j++){
            if(checkEPI[j][i] == true){
                counter++;
                epiIndex = j;
            }
        }
        if(counter == 1)
        {
            episI.insert(epiIndex);
        }
        else
            epiIndex = -1;
    }
    
    //remove called minterms
    for(int elm : episI)
    {
        for (int j =0; j< minterms.size(); j++)
        {
            if(checkEPI[elm][j] == true)
                remaining.erase(minterms[j]);
        }
    }
    //fill in epis
    for(int elm :episI){
        epis.insert(pi[elm]);
    }
    
    //paet 5
    vector<int> episIV(episI.begin(),episI.end());// convert from set to vector
    vector<int> rem(remaining.begin(),remaining.end()); // convert from set to vector
    vector<string> episV(epis.begin(),epis.end());//convert from set to vector
    vector<string> equation(epis.begin(), epis.end());// minimized equation
    vector<vector<bool>> findrestPI = removeRowsAndKeepColumns(checkEPI, episIV, rem);//remove epis and called minterms
    
    //remove EPI from rest of PI
        for(int j =0; j< epis.size(); j++)
        {
            pi.erase(pi.begin()+episIV[j]);
        }
    //fill in the rest of the minimized equation
    for(int i =0; i<pi.size()-episIV.size(); i++){
        if(remaining.empty())
            break;
        for(int j = 0; j< rem.size(); j++)
        {
            if(findrestPI[i][j] == true)
            {
                equation.push_back(pi[i]);
                
            }
        }
    }
    
    // printing all information needed
    set<string> Minmized_equation(equation.begin(), equation.end());
    cout << "These are the EPIS: ";
    printSet(epis);
    cout << "These the remaining minterms not coverd: ";
    printSet(remaining);
    cout << "This is the final equation : ";
    int k =0;
    for (auto it = Minmized_equation.begin(); it != Minmized_equation.end(); ++it) {
        cout << *it;
        k++;
        if (k != Minmized_equation.size())
            cout << " + ";
    }
    cout << endl;
    
    return epis;
}
