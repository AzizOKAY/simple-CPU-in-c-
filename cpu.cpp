/*****    Aziz OKAY *****/

#include <iostream>
using namespace std;

#include "cpu.h"


/**
 * Function that organize all function for cpu
 * @param line that has been read in file
 * @param registerArray to store our five register
 * @param inpStream input stream pointer 
 * @return line number that we find a problem
 */
int organizCpu(char *line, int registerArray[], ifstream &inpStream, int option) {
    int PCounter = 1, resultOfJmp;
    bool PControl = true;
    char MOV[]="MOV", ADD[]="ADD", SUB[]="SUB", JMP[]="JMP", PRN[]="PRN", HLT[]="HLT";
    char mov[]="mov", add[]="add", sub[]="sub", jmp[]="jmp", prn[]="prn", hlt[]="hlt";
    
    while(PControl) {
        int resultOfJmp = 0;
        readFile(PCounter, inpStream, line);
        if(option == 1) {
		    for(int i = 0; isEndOfLine(line[i]); i++)
		    	cout << line[i];
		    cout << " >>> ";
		}    
		 
		if(gtuStrNCmp(line, MOV, 3) != -1 || gtuStrNCmp(line, mov, 3) != -1) {
			movInstruction(line, registerArray);
		}	
		else if(gtuStrNCmp(line, ADD, 3) != -1 || gtuStrNCmp(line, add, 3) != -1) {
			if(addInstruction(line, registerArray) == -1)
				return PCounter;
		}	
		else if(gtuStrNCmp(line, SUB, 3) != -1 || gtuStrNCmp(line, sub, 3) != -1) {
			if(subInstruction(line, registerArray) == -1)
				return PCounter;	
		}	
        else if(gtuStrNCmp(line, JMP, 3) != -1 || gtuStrNCmp(line, jmp, 3) != -1) {
        	resultOfJmp = jmpInstruction(line, registerArray);
            if(resultOfJmp == 0)
                ;
            else if(resultOfJmp != -1)
                PCounter = jmpInstruction(line, registerArray) - 1;
            else {
            	cerr << "There is a problem at JMP" << endl;
            	PControl = false;
            	return PCounter;
            } 
        }       
		else if(gtuStrNCmp(line, PRN, 3) != -1 || gtuStrNCmp(line, prn, 3) != -1) {
			if(prnInstruction(line, registerArray) == -1)
				return PCounter;	
		}	
        else if(gtuStrNCmp(line, HLT, 3) != -1 || gtuStrNCmp(line, hlt, 3) != -1) {
            cout << "The instruction is HLT" << endl;
            PControl = false;
        }
        else {
            cout << "Unknown instruction!!!!" << endl;
            return PCounter;
        }    
        
        if(option == 1)    
        	printAllReg(registerArray);
        	    
        PCounter = PCounter + 1;
        if(inpStream.eof()) {
            cout << "End of File!!!" << endl;
            if(PControl == true)
            	cout << "There is no HLT in your code.Please check your code." << endl;
        }
    }
return 0;    
}

/**
 *  The function that find given srchStr in given str string
 * @param str source string
 * @param srchStr string that searching
 * @param index that searching will began
 * @return return ending index that srchStr -1 otherwise
 */
int gtuStrNCmp(char *str, char *srchStr, int index) {
    int counter = 0, result  = -1;
    for(int i = 0; isEndOfLine(str[i]); i++) {
        if(str[i] == srchStr[0]) {
            counter = i + 1;
            result  = i;
            for(int j = 1; j < index; j++) {
                if(str[counter] == srchStr[j])
                    result  = i;
                else
                    result = -1;
                counter++;    
            }
            if(result != -1)
            	return result;
        }
    }
    return result;
}
/**
 * The function that find which register will be changed
 * @param line line is we read to file
 * @return number of register or constant value
 */
int findRegisterNumber(char *line, int startIndex){

	for(int i = startIndex; isEndOfLine(line[i]); i++) {
		if(line[i] == 'R' || line[i] == 'r') {
			if(line[i+1] == '1')
				return 1;
			if(line[i+1] == '2')
				return 2;	
			if(line[i+1] == '3')
				return 3;
			if(line[i+1] == '4')
				return 4;
			if(line[i+1] == '5')
				return 5;			
		}
	}
	return 0; 
}
/**
 * The function that check between given two index
 * @param line line is we read to file
 * @param startIndex start index for search
 * @param endIndex end index for search 
 * @return true if there is no problem false otherwise
 */
bool check(char *str, int startIndex, int endIndex) {	
	for(int i = startIndex; i < endIndex; i++) {
		if(str[i] != ' ')
			return false;
	}
	return true;
}

/**
 * The function that add given register or constant number to another register
 * @param line line is we read to file
 * @param registerArray array that hold registers 
 * @return 0 if there is no problem -1 otherwise  
 */
int addInstruction(char *line, int registerArray[]) {
	char A[] = "ADD", r[] = "R", comma[] = ",", a[] = "add";
	int index, regNum1, regNum2, regIndex1, commaIndex, regIndex2;
	int constIndex, endOfConstIndex, endIndex;
	
	index = gtuStrNCmp(line, a, 3);
	if(index == -1)
		index = gtuStrNCmp(line, A, 3);
		
	regNum1 = findRegisterNumber(line, index);
	regIndex1 = gtuStrNCmp(line, r, 1);
	commaIndex = gtuStrNCmp(line, comma, 1);
	endIndex = findEndIndex(line);
	if(check(line, 0, index) && check(line, index+3, regIndex1) &&
	   check(line, regIndex1+2, commaIndex)) {
		regNum2 = findRegisterNumber(line, regIndex1+1);
		if(regNum2 <= 5 && regNum2 != 0) {
			regIndex2 = gtuStrNCmp(&line[commaIndex], r, 1)+commaIndex;
			if(check(line, commaIndex+1, regIndex2)  && check(line, regIndex2+2, endIndex))
				registerArray[regNum1-1] += registerArray[regNum2-1];	
		}				
		else if(regNum2 == 0){
			constIndex = findConstantIndex(line, commaIndex);
			endOfConstIndex = findEndOfConstIndex(line, commaIndex); 
			if(check(line, commaIndex+1, constIndex) && check(line, endOfConstIndex, endIndex))
				registerArray[regNum1-1] += gtuAtoi(&line[commaIndex]);
			else {
				cout << "There is a problem between const and reg." << endl;
				return -1;
			}	
		}
		else {
			cerr << "problem between comma/rg1 or comma/rg2" << endl;
			return -1;
		}				
	}
	else {
		cerr << "There is/are a problem(s) before or post of 'MOV' instruction" << endl;
		return -1;
	}
return 0;		
}

/**
 * The function that sub given register or constant number to another register
 * @param line line is we read to file
 * @param registerArray array that hold registers 
 * @param index that point after instruction
 * @return 0 if there is no problem -1 otherwise  
 */
int subInstruction(char *line, int registerArray[]) {
	char S[] = "SUB", r[] = "R", comma[] = ",", s[] = "sub";
	int index, regNum1, regNum2, regIndex1, commaIndex, regIndex2;
	int constIndex, endOfConstIndex, endIndex;
	
	index = gtuStrNCmp(line, S, 3);
	if(index == -1)
		index = gtuStrNCmp(line, s, 3);
		
	regNum1 = findRegisterNumber(line, index);
	regIndex1 = gtuStrNCmp(line, r, 1);
	commaIndex = gtuStrNCmp(line, comma, 1);
	endIndex = findEndIndex(line);
	if(check(line, 0, index) && check(line, index+3, regIndex1) &&
	   check(line, regIndex1+2, commaIndex)) {
		regNum2 = findRegisterNumber(line, regIndex1+1);
		if(regNum2 <= 5 && regNum2 != 0) {
			regIndex2 = gtuStrNCmp(&line[commaIndex], r, 1)+commaIndex;
			if(check(line, commaIndex+1, regIndex2)  && check(line, regIndex2+2, endIndex))
				registerArray[regNum1-1] -= registerArray[regNum2-1];	
		}				
		else if(regNum2 == 0){
			constIndex = findConstantIndex(line, commaIndex);
			endOfConstIndex = findEndOfConstIndex(line, commaIndex); 
			if(check(line, commaIndex+1, constIndex) && check(line, endOfConstIndex, endIndex))
				registerArray[regNum1-1] -= gtuAtoi(&line[commaIndex]);
			else {
				cout << "There is a problem between const and reg." << endl;
				return -1;
			}	
		}
		else {
			cerr << "problem between comma/rg1 or comma/rg2" << endl;
			return -1;	
		}			
	}
	else {
		cerr << "There is/are a problem(s) before or post of 'MOV' instruction" << endl;
		return -1;
	}	
return 0;	
}

/**
 * The function that move given register or constant number to register
 * @param line is we read to file
 * @param registerArray array that hold registers 
 * @return 0 if there is no problem -1 otherwise  
 */
int movInstruction(char *line, int registerArray[]) {
	char M[] = "MOV", r[] = "R", comma[] = ",", m[] = "mov";
	int index, regNum1, regNum2, regIndex1, commaIndex, regIndex2;
	int constIndex, endOfConstIndex, endIndex;
	
	index = gtuStrNCmp(line, m, 3);
	if(index == -1)
		index = gtuStrNCmp(line, M, 3);
		
	if(check(line, 0, index)) {
		regNum1 = findRegisterNumber(line, index);
		regIndex1 = gtuStrNCmp(line, r, 1);
		commaIndex = gtuStrNCmp(line, comma, 1);
		
		if(check(line, index+3, regIndex1) && check(line, regIndex1+2, commaIndex)) {
			regNum2 = findRegisterNumber(line, regIndex1+1);
			
			if(regNum2 <= 5 && regNum2 != 0) {
				regIndex2 = gtuStrNCmp(&line[commaIndex], r, 1)+commaIndex;
				endIndex = findEndIndex(line);
				
				if(check(line, commaIndex+1, regIndex2)  && check(line, regIndex2+2, endIndex))
					registerArray[regNum2-1] = registerArray[regNum1-1];
			}		
			else if(regNum2 == 0){
				constIndex = findConstantIndex(line, commaIndex);
				endOfConstIndex = findEndOfConstIndex(line, commaIndex); 
				endIndex = findEndIndex(line);
				
				if(check(line, commaIndex+1, constIndex) && 
				check(line, endOfConstIndex, endIndex)) {
					registerArray[regNum1-1] = gtuAtoi(&line[commaIndex]);
				}
				else {
					cout << "There is a problem between const and reg." << endl;
					return -1;
				}	
			}
			else {
				cerr << "problem between comma/rg1 or comma/rg2" << endl;
				return -1;
			}			
		}	
		else {
			cerr <<	"problem between reg and ins" << endl;
			return -1; 
		}	
	}
	else {
		cerr << "There is/are a problem(s) before or post of 'MOV' instruction" << endl;
		return -1; 
	}	
return 0; 
}

/**
 * The function that print given register or constant number to screen
 * @param line that will be printed on screen
 * @param registerArray array that hold registers 
 * @return 0 if there is no problem -1 otherwise 
 */
int prnInstruction(char *line, int registerArray[]){
	char P[] = "PRN", r[] = "R", p[] = "prn";
	int regNum1, index, constIndex, endOfConstIndex, endIndex, regIndex;
	
	index = gtuStrNCmp(line, p, 3);
	if(index == -1)
		index = gtuStrNCmp(line, P, 3);
		
	if(check(line, 0, index)) {
		regNum1 = findRegisterNumber(line, index);
		regIndex = gtuStrNCmp(&line[index+3], r, 1) + index+3;
		endIndex = findEndIndex(line);;
		if(regNum1 <= 5 && regNum1 != 0 && check(line, index+3, regIndex)
			&& check(line, regIndex+2, endIndex)) 
			cout << registerArray[regNum1-1] << endl;
		else {
			constIndex = findConstantIndex(line, index);
			endOfConstIndex = findEndOfConstIndex(line, index); 
			if(check(line, index+3, constIndex) && check(line, endOfConstIndex, endIndex)) {
				cout << gtuAtoi(&line[index]) << endl;	
			}	
    		else {
				cerr <<"There is a problem with your code!!" << endl;
				return -1;
			}	
		}	
    }    
    else {
		cerr << "There is/are a problem(s) before or post of 'PRN' instruction"<< endl;
		return -1;
	}	
return 0;		  
}
/**
 * The function update program counter if is necessery
 * @param line that will be processed
 * @return new program counter if is necessery 0 otherwise
 */
int jmpInstruction(char *line, int registerArray[]) {
	char J[] = "JMP", r[] = "R", comma[] = ",", j[] = "jmp";
	int index, result = -1, regNum1, regIndex1, commaIndex;
	int constIndex, endOfConstIndex, endIndex;
	
	index = gtuStrNCmp(line, j, 3);
	if(index == -1)
		index = gtuStrNCmp(line, J, 3);
	regNum1 = findRegisterNumber(line, index);
	if(check(line, 0, index)) {
		endIndex = findEndIndex(line);
		if(regNum1 <= 5 && regNum1 != 0){
			regIndex1 = gtuStrNCmp(line, r, 1);
			commaIndex = gtuStrNCmp(line, comma, 1);
			constIndex = findConstantIndex(line, commaIndex);
			endOfConstIndex = findEndOfConstIndex(line, commaIndex);
			if(check(line, index+3, regIndex1) && check(line, regIndex1+2, commaIndex) &&
			   check(line, commaIndex+1, constIndex) && check(line, endOfConstIndex, endIndex)) {
				if(registerArray[regNum1-1] == 0)
					result = gtuAtoi(&line[commaIndex]);
				else
					result = 0;	
			}
			else {
				cerr << "There is a problem in your code (at JMP line)" << endl;
				result = -1;
			}
		}
		else if(regNum1 == 0){
			constIndex = findConstantIndex(line, 0);
			endOfConstIndex = findEndOfConstIndex(line, 3);
			
			if(check(line, index+3, constIndex) &&
			   check(line, endOfConstIndex, endIndex))
				result = gtuAtoi(&line[constIndex-1]);
		}
		else {
			cerr << "There is no Regsiter and constant number('JMP')" << endl;
			result = -1;
		}
	}
	else {
		cerr << "There is a problem before JPM instruction!!" << endl;
		result = -1;
	}	
	return result;
}


/**
 *  The function that read a line at given number
 * @param numOfReadLine number of line that will be read
 * @param inpStream input file stream that pointed the file
 * @param line char array that line will be saved
 */
void readFile(int numOfReadLine, ifstream &inpStream, char *line) {
    int counter = 1;
	
	while(counter <= numOfReadLine && inpStream.eof() != true) {
		inpStream.getline(line, 256);
		counter = counter + 1;
	}
	inpStream.seekg (0, inpStream.beg);
}


/**
 * The function that convert string to integer 
 * @param str string that will be converted the integer
 * @return is integer value of string
 */
int gtuAtoi(char *str){
	int result = 0, index;
	index = findConstantIndex(str, 0);
	for(int i = index; isNumber(str[i]) ; i++){
		result = result * 10 + str[i] - '0';
    }
	return result;
} 

/**
 * The function that print all register to screen 
 * @param registerArray array that hold registers 
 */
void printAllReg(int registerArray[]) {
	for(int i = 0; i < 5; i++) {
		cout << "R" << i+1 << " = " << registerArray[i];
		if(i < 4)
			cout << " , ";
	}
	cout << endl;
}
/**
 * The function that find index of last charecter
 * @param str source for searching
 * @return is index of end charecter of line
 */
int findEndIndex(char *str) {
	int index = 0;
	while(isEndOfLine(str[index])) {
		++index;
	}
	return index;
}

/**
 * The function that check given charecter is number or not
 * @param str source for searching
 * @return is true if it is number false otherwise
 */
bool isNumber(char isNum) {
	return (isNum >= 48 && isNum <= 57);
}
/**
 * The function that check given charecter is en of line or ';'
 * @param str source for searching
 * @return true if it is end of line false otherwise
 */
bool isEndOfLine(char isEnd) {
	return (isEnd != '\0' && isEnd != '\n' && isEnd != ';');
}
/**
 * The function that find index of constant number of last
 * @param str source for searching
 * @param index index that searching will start
 * @return true if it is end of constant number false otherwise
 */
int findEndOfConstIndex(char *str, int index) {
	int i = findConstantIndex(str, index);

	for( ; isEndOfLine(str[i]); i++) {
		if(!isNumber(str[i]))
			return i;	
	}
	return -1;
}
/**
 * The function that find index of constant number
 * @param str source for searching
 * @param index index that searching will start
 * @return true if it is end of constant number false otherwise
 */
int findConstantIndex(char *str, int index) {
	for(int i = index; isEndOfLine(str[i]); i++) {
		if(isNumber(str[i]))
			return i;	
	}
	return -1;
}
