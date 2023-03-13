//
//  booleanFunction.cpp
//  DigitalDesign Project1
//
//  Created by Ahmed Moamen on 13/03/2023.
//

#include "validateSOP.hpp"
#include <iostream>
#include <string>
#include <regex>

using namespace std;

// Function to validate a Boolean expression given as a SoP
bool validateSOP(string sop) {
    //removing whitepace in order to check sop variables.
    regex whitespace("\\s");
    sop = regex_replace(sop, whitespace,"");
    // Define a regular expression to match a valid SoP expression
    
    string varName = "[A-Za-z]"; // variable name (only letters allowed)
    
    string varNameOptQuotes = "('?)" + varName; // variable name with optional quotes
    
    string term = "(" + varNameOptQuotes + ")+"; // a term is one or more variable names separated by multiplication
    
    string groupOfTerms = "(" + term + ")+(\\+(" + term + ")+)*"; // a group of terms separated by addition
    
    regex sopRegex("^" + groupOfTerms + "$"); // regular expression for the entire SoP expression
    
    //Use regex_match to check if the input string matches the regular expression
    
    return regex_match(sop, sopRegex);
}
    
