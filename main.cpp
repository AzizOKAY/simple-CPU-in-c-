/*****    Aziz OKAY *****/
/*****    101044064 *****/

#include <iostream>
#include "cpu.h"

using namespace std;


int main(int argc,char *argv[]){

	int regArray[5], result;
    ifstream inputStream;
    char line[256];

    //inputStream.open("printTenToZero.txt");
    //inputStream.open("squareOfNum.txt");
    //inputStream.open("multipleTwoNum.txt");
    //inputStream.open("addSquareNumToOne.txt");
    if(argc != 3) {
    	cout << "Missing argument please try true format (yourProg filename option)" << endl;
    }
    else {
    	inputStream.open(argv[1]);
    	
    	if(inputStream.is_open()){
    		result = organizCpu(line, regArray, inputStream, gtuAtoi(argv[2]));
        	if(result != 0) {
        		cerr << "There is a problem at " << result << ". line!!!" << endl;
        		return 0;
        	}	
    	}    
    	else{
        	cerr << "Error opening file!!!" << endl;
    		return 0;
    	}	
    }	    
return 0;
}
