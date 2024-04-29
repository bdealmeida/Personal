#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Maps binary 1 to postive voltage 
// and binary 0 to negative voltage.
//
// EXAMPLE
// Input signal : |  1 |  0 |  0 |  1 |  1 |  1 |  0 |
// Output signal: | +1 | -1 | -1 | +1 | +1 | +1 | -1 |
string encodeNRZL(string input) {
    string output = "|";
    
    for(unsigned long i = 0; i < input.length(); i++)
        output += input[i] == '1' ? "+V|" : "-V";

    return output;
}

// Encodes input signal by toggling
// output voltage whenever binary 0
// is read.
//
// EXAMPLE
// Input signal : | 1 | 0 | 0 | 1 | 0 | 1 | 0 |
// Output signal: | 0 | 1 | 0 | 0 | 1 | 1 | 0 |
string encodeNRZI(string input) {
    string output = "|";
    
    char c;
    bool state = 0;
    for(unsigned long i = 0; i < input.length(); i++) {
        c = input[i];
        if(c == '0')
            state = !state;
        output += state ? "+V|" : "-V|";
    }

    return output;
}

// Binary 0 is encoded as 0V.
// Binary 1 is encoded as +V or -V,
// with each input binary 1 
// alternating between a positive or 
// negative output voltage.
//
// EXAMPLE
// Input signal : |  1 | 0 | 0 |  1 |  1 |  1 | 0 |
// Output signal: | -1 | 0 | 0 | +1 | -1 | +1 | 0 |
string encodeBAMI(string input) {
    string output = "|";
    
    char c;
    bool state = 1;
    for(unsigned long i = 0; i < input.length(); i++) {
        c = input[i];
        if(c == '1') {
            state = !state;
            output += state ? "+V|" : "-V|";
        } else if(c == '0') {
            output += "0V|";
        }
    }

    return output;
}

// The clock is divided by 2, such that
// each input data bit has a transition
// in the output signal at half the 
// time of the original clock.
//
// Binary 1's transition is low-to-high.
// Binary 0's transistion is high-to-low.
//
// EXAMPLE
// Input signal : | 1 | 0 | 0 | 1 | 1 | 1 | 0 |
// Output signal: |0 1|1 0|1 0|0 1|0 1|0 1|1 0|
string encodeManchester(string input) {
    string output = "|";
    
    char c;
    for(unsigned long i = 0; i < input.length(); i++) {
        c = input[i];
        if(c == '1')
            output += "-V+V|";
        else if(c == '0')
            output += "+V-V|";
    }

    return output;
}

// The clock is divided by 2, such that
// each input data bit can have a transition
// in the encoded signal at half the 
// time of the original clock. There is 
// always a transition on the output signal
// at each period of the original clock.
//
// Binary 1's is held for the original 
//     clock period
// Binary 0's has a transition at each
//     half-clock period
// 
// EXAMPLE
// Input signal : | 1 | 0 | 0 | 1 | 1 | 1 | 0 |
// Output signal: | 0 |1 0|1 0| 1 | 0 | 1 |0 1|
string encodeDManchester(string input) {
    string output = "|";
    
    char c;
    bool state = 0;
    for(unsigned long i = 0; i < input.length(); i++) {
        c = input[i];
        if(c == '1') {
            output += state ? "+V|" : "-V|";
            state = !state;
        } else if(c == '0')
            output += state ? "+V-V|" : "-V+V|";
    }

    return output;
}

// Prints the list of accepted encoding indexes 
// and their respective encoding scheme
void printEncodings() {
    cout << "Encodings:\n\t0:NRZ-L\n\t1:NRZ-I\n\t2:B-AMI\n\t3:Manchester\n\t4:D-Manchester\n";
}





int main(int argc, char* argv[]) {
    // Validate inputs
    if(argc != 3) {
        cout << "Error: please include filename and encoding as arg (encode <FILENAME> <encoding>)" << endl;
        printEncodings();
        return 1;
    }

    // Open input file
    string inputfile = argv[1];
    ifstream ifs;
    ifs.open(inputfile);
    if(!ifs.good()) {
        cout << "Error: could not open input file." << endl;
        return 1;
    }

    // Read input data stream
    string input;
    ifs >> input;
    ifs.close();

    // Read desired encoding scheme
    short encoding;
    try {
        encoding = stoi(argv[2]);
    } catch(...) {
        cout << "Error: encoding scheme should be a number." << endl;
        printEncodings();
        return 1;
    }

    // Route encoding
    string output;
    string outputFileName = "OUTPUT";
    cout << "Using encoding ";
    switch(encoding) {
        case 0: 
            cout << "NRZ-L" << endl; 
            output = encodeNRZL(input);
            outputFileName += ".NRZL";
            break;
        case 1: 
            cout << "NRZ-I" << endl;
            output = encodeNRZI(input);
            outputFileName += ".NRZI";
            break;
        case 2: 
            cout << "B-AMI" << endl; 
            output = encodeBAMI(input);
            outputFileName += ".BAMI";
            break;
        case 3: 
            cout << "Manchester" << endl; 
            output = encodeManchester(input);
            outputFileName += ".MANCHESTER";
            break;
        case 4: 
            cout << "D-Manchester" << endl; 
            output = encodeDManchester(input);
            outputFileName += ".DMANCHESTER";
            break;
        default:
            cout << "Error: encoding scheme not recognized." << endl;
            printEncodings();
            return 1;
    }

    // Write result to output file
    ofstream ofs;
    ofs.open(outputFileName);
    ofs << output << endl;
    ofs.close();

    // Print result to console
    cout << "INPUT: " << input << endl;
    cout << "OUTPUT: " << output << endl;

    return 0;
}
