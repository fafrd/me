/*
int main 
{
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip> //color and format
#include <time.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      // Black
#define RED     "\033[31m"      // Red
#define GREEN   "\033[32m"      // Green 
#define YELLOW  "\033[33m"      // Yellow 
#define BLUE    "\033[34m"      // Blue 
#define MAGENTA "\033[35m"      // Magenta 
#define CYAN    "\033[36m"      // Cyan 
#define WHITE   "\033[37m"      // White 
#define BOLDBLACK   "\033[1m\033[30m"      // Bold Black 
#define BOLDRED     "\033[1m\033[31m"      // Bold Red 
#define BOLDGREEN   "\033[1m\033[32m"      // Bold Green 
#define BOLDYELLOW  "\033[1m\033[33m"      // Bold Yellow 
#define BOLDBLUE    "\033[1m\033[34m"      // Bold Blue 
#define BOLDMAGENTA "\033[1m\033[35m"      // Bold Magenta 
#define BOLDCYAN    "\033[1m\033[36m"      // Bold Cyan 
#define BOLDWHITE   "\033[1m\033[37m"      // Bold White 
}
*/

#include "jap.h"

using namespace std;

//MAIN
int main()
{
	//load library
	string library = path + "library.txt";
	//const char* libPointer = charPointer(library);
	readLIB(library);

	while(true)
	{
		string filename = chooseLesson();

		cout << "Do you want to load romanji? (Y/N): ";
		char input = YesNoPrompt();
		int readMode = 0;
		if(input == 'Y' || input == 'y') 
		{
			readMode = 1;
		}
		else 
		{
			readMode = 2;
		}
		

		readFromFile(filename, readMode);
		
		while(chooseMode(filename, readMode)) {}

		cout << BOLDYELLOW << "Do you want to continue? (Y/N): " << RESET;
		input = YesNoPrompt();
		if(input != 'Y' && input != 'y') break;
	}

	return 0;
}

//Edit_Mode
string chooseLesson()
{
	cout << BOLDYELLOW << setw(20) << "" << "Library List:" << RESET << endl;
	cout << YELLOW << "-- below are list of available lessons"<< endl;
	cout << YELLOW << "-- choose a lesson you want to study" << endl;
	cout << YELLOW << "-- enter its name or its indexing number to select" << RESET << endl;
	cout << endl;

	printVector(LIB, 1);
	cout << CYAN << "Which lesson do you want to load?: " << RESET;
	string inputfile;
	stringInputPrompt(inputfile);

	int i = 0;
	//check if they input integer
	while(true)
	{
		if(isInteger(inputfile))
		{
			int inputInt = atoi(inputfile.c_str())-1;
			if(inputInt < LIB.size()) 
			{
				i = inputInt;
				break;
			}
			else i = LIB.size()-1;
		}
		else
		{
			if(inputfile.compare(LIB[i]) == 0) break;
		}
		i++;

		if(i == LIB.size())
		{
			cout << "No such entry! Again: ";
			stringInputPrompt(inputfile);
			i = 0;
		}
	}
	cout << YELLOW << "Load " << RESET << LIB[i] << "." << endl;

	inputfile = path + LIB[i] + ".txt";
	//char* filename = charPointer(inputfile);
	cout << endl;
	return inputfile;
}

void writeToFile(string &filename, int readMode)
{
	cout << BOLDYELLOW << setw(20) << "" << "Edit Mode" << RESET << endl;
	cout << YELLOW << "-- edit loaded text file to add or remove entry(ies)" << endl;
	cout << "-- enter END! to stop adding in line" << endl;
	cout << "-- incomplete lines (do not have 3 entries) will not be added" << endl;
	cout << "-- do you want to see text file before edit (Y/N): " << RESET;

	char Cinput = YesNoPrompt();
	if(Cinput == 'Y' || Cinput == 'y')
	{
		cout << filename << endl;
		showFile(filename);
	}

	cout << YELLOW << "-- do you want to edit file (Y/N): " << RESET;
	Cinput = YesNoPrompt();
	//Edit
	if(Cinput == 'Y' || Cinput == 'y') 
	{
		ofstream myfile(filename.c_str(), ofstream::app); //file
		
		int i = 1;
		string input;
		string lineInput = "";

		while(true)
		{
			if(i == 1) cout << "    Japanese-Romanji: ";
			if(i == 2) cout << "             English: ";
			if(i == 3) cout << "Japanese-Non-Romanji: ";

			getline(cin,input);
			if(input == "END!") break; //break
			if(input == "") lineInput += " "; //avoid empty entry

			switch(i)
			{
				case 1:
				case 2:
				{
					lineInput += input;
					lineInput += "=";
					i++; break;
				}
				case 3:
				{
					lineInput += input;
					lineInput += "=\n";
					myfile << lineInput;

					lineInput = "";
					i=1; 
					cout << endl;
					break;
				}
			}
		}
		cout << YELLOW << "-- adding line(s) to file" << RESET << endl;
		myfile.close();
		cout << endl;
		
		cout << YELLOW << "-- do you want to see text file now (Y/N): " << RESET;
		Cinput = YesNoPrompt();
		if(Cinput == 'Y' || Cinput == 'y') 
		{
			showFile(filename);
		}

		//read new file
		cout << YELLOW << "-- do you want to load newly editted file (Y/N): " << RESET;
		Cinput = YesNoPrompt();
		if(Cinput == 'Y' || Cinput == 'y') 
		{
			readFromFile(filename, readMode);
		}
	}
}

void readLIB(string &filename)
{
	ifstream lib(filename.c_str());
	string line;
	string trash;
	while(!lib.eof())
	{
		getline(lib, line, '=');
		getline(lib, trash);
		LIB.push_back(line);
	}
	lib.close();
}

void readFromFile(string &filename, int readMode)
{
	string trash;
	clearVector();
	ifstream myfile(filename.c_str()); //file
	while(!myfile.eof())
	{
		string input1 = ""; //jap romanji
		string input2 = ""; //english
		string input3 = ""; //not romanji

		getline(myfile,input1,'='); //first string

		//create commend // in input file (use at beginning of line and line must end with '='')
		if(input1.substr(0,2) == "//")
		{
			getline(myfile,input1);
			continue;
		}
		//create commend /* in input file (use at beginning of line)
		//closing */ has to be on a following line
		if(input1.substr(0,2) == "/*")
		{
			while(input1.substr(0,2) != "*/" && !myfile.eof())
			{
				getline(myfile,input1);
			}
			continue;
		}

		getline(myfile,input2,'='); //second string
		getline(myfile,input3,'='); //third string
		getline(myfile,trash);

		//avoid blank entry
		if(input1[0] == '\n') continue;
		if(input1 == "" || input2 == "" || input3 == "") continue;

		switch(readMode)
		{
			default:
			case 1:
			{
				JAP.push_back(input1);
				ENG.push_back(input2);
				JAP2.push_back(input3);
				EMP.push_back("");
				break;
			}
			case 2:
			{
				JAP.push_back("");
				ENG.push_back(input2);
				JAP2.push_back(input3);
				EMP.push_back("");
				break;
			}
		}
	}
	myfile.close();
}

bool chooseMode(string &filename, int readMode)
{
	int modeChoice;
	cout << BOLDYELLOW << "Program modes:" << RESET << endl;
	cout << YELLOW << "-- 1 for ENG->JAP, 2 for JAP->ENG"<< endl;
	cout << YELLOW << "-- 3 for ENG->JAP NO ROMANJI" << endl;
	cout << YELLOW << "-- 4 for E->J NO_RANDOM, 5 for E->J N_RAN N_ROMAN" << endl;
	cout << YELLOW << "-- 6 for Study_Mode" << endl;
	cout << YELLOW << "-- 7 for Edit_Mode" << endl;
	cout << YELLOW << "-- 0 to Exit" << RESET << endl;
	cout << CYAN << "Enter mode: " << RESET;
	cin >> modeChoice;
	cout << endl;

	string trash;
	getline(cin,trash,'\n');


	switch(modeChoice)
	{
		case 1:
		{
			mode(JAP, ENG, JAP2);
			break;
		}
		case 2:
		{
			mode(ENG, JAP, JAP2);
			break;
		}
		case 3:
		{
			mode(JAP2, ENG, JAP);
			//mode(JAP2, ENG, EMP);
			break;
		}
		case 4:
		{
			modeNoRandom(JAP, ENG, JAP2);
			break;
		}
		case 5:
		{
			modeNoRandom(JAP2, ENG, JAP);
			//modeNoRandom(JAP2, ENG, EMP);
			break;
		}
		case 6:
		{
			modeStudy();
			break;
		}
		case 7:
		{
			cout << filename << endl;
			writeToFile(filename, readMode);
			break;
		}
		default: //default is Exit
		{
			return false;
		}
	}

	cout << BOLDYELLOW << "Do you want to use different modes? (Y/N): " << RESET;
	char input = YesNoPrompt();
	if(input == 'Y' || input == 'y') return true;
	else return false; //false to end program
}

//TEST MODE 1, 2
void mode(vector<string> &compareString, vector<string> &showString, vector<string> &showString2)
{
	cout << BOLDYELLOW << setw(20) << "" << "Test Mode" << RESET << endl;
	cout << YELLOW << "-- enter appropriate translation to word(s) or phrase(s) showed below" << endl;
	cout << "-- enter HELP! for dictionary; 1hint!, 2hint!, or 3hint! for up-to-first-3-chars hint" << endl;
	cout << "-- enter END! to stop the test" << endl;
	cout << "-- enter amount of questions: " << RESET;
	//read in amount right here
	int amount;
	cin >> amount;
	string trash;
	getline(cin,trash,'\n');
	cout << endl;

	int j =0;
	int repeatproof = -1;
	int i = 0;
	vector<int> wrongindex; //save indexes of wrong answer

	srand(time(NULL));

	while(j < amount)
	{
		i = rand() % (compareString.size());

		if(repeatproof == i) continue; //to stop immediate repeating (decrease performance, shiettt)
		else
		{
			repeatproof = i;
			string input;
			cout << BOLDWHITE << j+1 << "/" << amount << RESET << endl; // 1/amount first entry
			cout << YELLOW << showString[i] << RESET << endl;
			getline(cin,input,'\n');

			//skip
			if(input == "")
			{
				wrongindex.push_back(i); //saving wrong index
				j++;
				continue;
			}

			//end
			if(input == "END!")
			{
				break;
			}
			//calling HELPER. syntax: HELPER!
			if(input == "HELP!")
			{
				cout << endl;
				helper();
				cout << CYAN << "Again: " << RESET << endl;
				cout << showString[i] <<endl;
				getline(cin,input,'\n');
			}

			//calling hint, hint shows up to 3 chars. syntax: 1hint!, 2hint!, or 3hint!
			if(input.substr(1,5) == "hint!")
			{
				int request = atoi(input.substr(0,1).c_str());
				if(hint(compareString[i], request, input))
				{
					cout << CYAN << "Try: " << RESET << endl;
					getline(cin,input,'\n');
				}
				else continue;
			}

			if(input != compareString[i])
			{
				cout << BOLDRED << "Incorrect!" << RESET << " Should be: " << compareString[i] << " " << showString2[i] << endl;
				wrongindex.push_back(i); //saving wrong index
				cout << endl;
			}
			else
			{
				cout << BOLDGREEN << "Correct! " << RESET << showString2[i] << endl;
				cout << endl;
			}
			j++;
		}
	}

	//test wrong items again, cant use HELP! or ~hint!
	if(wrongindex.size() != 0) 
	{
		cout << BOLDYELLOW << "-- " << BOLDRED << wrongindex.size() << "/" << j << BOLDYELLOW << " wrong(s)!" << RESET << endl;
		cout << endl;
		mistakeMode(compareString, showString, showString2, wrongindex);
	}
	else
	{
		cout << BOLDYELLOW << "-- " << BOLDGREEN << "0/" << j << BOLDYELLOW << " wrong!" << RESET << endl;
		cout << endl;
	}
}

//TEST MODE 4,5
void modeNoRandom(vector<string> &compareString, vector<string> &showString, vector<string> &showString2)
{
	cout << BOLDYELLOW << setw(20) << "" << "NO_RANDOM TEST Mode" << RESET << endl;
	cout << YELLOW << "-- enter appropriate translation to word(s) or phrase(s) showed below" << endl;
	cout << "-- words and phrases will appear in the same order they appear in the text file" << endl;
	cout << "-- enter HELP! for dictionary; 1hint!, 2hint!, or 3hint! for up-to-first-3-chars hint" << endl;
	cout << "-- enter END! to stop the test" << RESET << endl;
	cout << endl;

	vector<int> wrongindex; //save indexes of wrong answer
	int i =0;
	while(i < compareString.size())
	{
		string input;
		cout << BOLDWHITE << i+1 << "/" << JAP.size() << RESET << endl; // 1/amount first entry
		cout << YELLOW << showString[i] << RESET << endl;
		getline(cin,input,'\n');

		//skip function
		if(input == "")
		{
			wrongindex.push_back(i); //saving wrong index
			i++;
			continue;
		}

		//end
		if(input == "END!")
		{
			break;
		}

		//help()
		if(input == "HELP!")
		{
			cout << endl;
			helper();
			cout << CYAN << "Again: " << RESET << endl;
			cout << showString[i] <<endl;
			getline(cin,input,'\n');
		}

		//calling hint, hint shows up to 3 chars. syntax: 1hint!, 2hint!, or 3hint!
		if(input.substr(1,5) == "hint!")
		{
			int request = atoi(input.substr(0,1).c_str());
			if(hint(compareString[i], request, input))
			{
				cout << CYAN << "Try: " << RESET << endl;
				getline(cin,input,'\n');
			}
			else continue;
		}

		if(input.compare(compareString[i]) != 0)
		{
			cout << BOLDRED << "Incorrect!" << RESET << " Should be: " << compareString[i] << " " << showString2[i] << endl;
			wrongindex.push_back(i); //saving wrong index
			cout << endl;
		}
		else
		{
			cout << BOLDGREEN << "Correct! " << RESET << showString2[i] << endl;
			cout << endl;
		}
		i++;
	}

	//test wrong items again, cant use HELP! or ~hint!
	if(wrongindex.size() != 0) 
	{
		cout << BOLDYELLOW << "-- " << BOLDRED << wrongindex.size() << "/" << i << BOLDYELLOW << " wrong(s)!" << RESET << endl;
		cout << endl;
		mistakeMode(compareString, showString, showString2, wrongindex);
	}
	else
	{
		cout << BOLDYELLOW << "-- " << BOLDGREEN << "0/" << i << BOLDYELLOW << " wrong!" << RESET << endl;
		cout << endl;
	}
}

//show wrong answered questions again (use in TEST MODES)
void mistakeMode(vector<string> &compareString, vector<string> &showString, vector<string> &showString2, vector<int> &wrongindex)
{
	cout << BOLDYELLOW << setw(20) << "" << "MISTAKE_LEARNING Mode" << RESET << endl;
	cout << YELLOW << "-- wrong answered questions will be showed again" << endl;
	cout << "-- do you want to use this mode (Y/N): " << RESET;
	char answer = YesNoPrompt();

	if(answer == 'Y' || answer == 'y')
	{
		while(wrongindex.size() > 0)
		{
			string input;
			cout << YELLOW << showString[wrongindex[0]] << RESET << endl;
			getline(cin,input,'\n');

			if(input != compareString[wrongindex[0]])
			{
				cout << BOLDRED << "Incorrect!" << RESET << " Should be: " << compareString[wrongindex[0]] << " " << showString2[0] << endl;
				cout << endl;
			}
			else
			{
				cout << BOLDGREEN << "Correct! " << RESET << showString2[wrongindex[0]] << endl;
				cout << endl;
			}
			wrongindex.erase(wrongindex.begin());
		}
	}
}

//HELPER! (use in TEST MODES)
void helper()
{
	cout << YELLOW << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
	cout << BOLDYELLOW << "THIS IS DICTIONARY!" << RESET << endl;
	cout << endl;
	int i = 0;
	while(i < JAP.size())
	{
		cout << GREEN << "page: " << i+1 << "/" << JAP.size() << RESET << endl; // 1/size() first entry
		cout << setw(6) << "" << ENG[i] << endl;
		cout << setw(6) << "" << JAP[i] << endl;
		cout << setw(6) << "" << JAP2[i] << endl;
		cout << endl;
		i++;
	}
	cout << BOLDYELLOW << "END OF DICTIONARY!" << endl;
	cout << YELLOW << setfill('-') << setw(80) << "-" << setfill(' ') << RESET << endl;
	cout << endl;
}

//show ~hint! (use in TEST MODES)
bool hint(string &compareString, int request, string &input)
{
	if(request > 3)
	{
		cout << RED << "It's better to use HELP!" << RESET << endl;
		cout << endl;
		return false;
	}
	else
	{
		cout << compareString.substr(0,request) << endl;
		return true;
	}
}

//STUDY MODE
void modeStudy()
{
	cout << BOLDYELLOW << setw(20) << "" << "Study Mode" << RESET << endl;
	cout << YELLOW << "-- enter 'n' to view next entry, 'p' to view previous entry"<< endl;
	cout << "-- enter page number to directly view its entry" << endl;
	cout << "-- enter 'all' to view all entry" << endl;
	cout << "-- enter 'end' to close Study mode" << RESET << endl;
	cout << endl;

	string input = "";
	int i = 0; //entry
	while(input != "end")
	{
		cout << GREEN << "page: " << i+1 << "/" << JAP.size() << RESET << endl; // 1/size() first entry
		cout << setw(6) << "" << ENG[i] << endl;
		//cout << setw(6) << "" << EMP[i] << endl;
		cout << setw(6) << "" << JAP[i] << endl;
		cout << setw(6) << "" << JAP2[i] << endl;
		cout << endl;

		while(true)
		{
			getline(cin,input,'\n');
			cout << endl;
			if(isInteger(input))
			{
				i = atoi(input.c_str())-1;
				if(i >= JAP.size() || i < 0)
				{
					cout << RED << "Out of bound!" << RESET << endl;
					cout << GREEN << "Try again: " << RESET << endl;
					continue;
				}
				break;
			}

			if(input == "n") //next
			{
				if(i < JAP.size()-1) {i++; break;}
				else
				{
					cout << RED << "This is last page! There is not a next page!" << RESET << endl;

					cout << YELLOW << "-- enter 'n' to view next entry, 'p' to view previous entry"<< endl;
					cout << "-- enter page number to directly view its entry" << endl;
					cout << "-- enter 'all' to view all entry" << endl;
					cout << "-- enter 'end' to close Study mode" << RESET << endl;

					cout << GREEN << "Try again: " << RESET << endl;
					continue;
				}
			}
			if(input == "p") //previous
			{
				if(i > 0) {i--; break;}
				else
				{
					cout << RED << "This is first page! There is not a previous page!" << RESET << endl;

					cout << YELLOW << "-- enter 'n' to view next entry, 'p' to view previous entry"<< endl;
					cout << "-- enter page number to directly view its entry" << endl;
					cout << "-- enter 'all' to view all entry" << endl;
					cout << "-- enter 'end' to close Study mode" << RESET << endl;

					cout << GREEN << "Try again: " << RESET << endl;
					continue;
				}
			}
			if(input == "all") //show all, cal helper()
			{
				helper();

				cout << YELLOW << "-- enter 'n' to view next entry, 'p' to view previous entry"<< endl;
				cout << "-- enter page number to directly view its entry" << endl;
				cout << "-- enter 'all' to view all entry" << endl;
				cout << "-- enter 'end' to close Study mode" << RESET << endl;

				continue;
			}
			if(input == "end") break; //end

			if(input != "n" || input != "p" || input != "end" || input != "all") //invalid inputs
			{
				cout << RED << "Wrong input!" << RESET << endl;

				cout << YELLOW << "-- enter 'n' to view next entry, 'p' to view previous entry"<< endl;
				cout << "-- enter page number to directly view its entry" << endl;
				cout << "-- enter 'all' to view all entry" << endl;
				cout << "-- enter 'end' to close Study mode" << RESET << endl;

				cout << GREEN << "Try again: " << RESET << endl;
				continue;
			}
		}
	}
}

//Tools
inline bool isInteger(const std::string & s) //check if string is an int number or not
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}

void clearVector()
{
	JAP.clear();
	ENG.clear();
	JAP2.clear();
	EMP.clear();
}

char YesNoPrompt()
{
	char input;
	cin >> input;
	string trash;
	getline(cin,trash,'\n');
	cout << endl;
	return input;
}

char* charPointer(string &inputfile)
{
	return &(inputfile[0]);
}

void printVector(vector<string> &Vector, int start_base)
{
	int i = 0;
	while(i < Vector.size())
	{
		cout << i + start_base << "	" << Vector[i] << endl;
		i++;
	}
	cout << endl;
}

void stringInputPrompt(string &input)
{
	getline(cin,input,'\n');
}

void showFile(string &filename)
{
	cout << filename << endl;
	int i = 1;
	ifstream myfile(filename.c_str()); //file
	while(!myfile.eof())
	{
		string line;
		getline(myfile,line);
		cout << i << "	" << line << endl;
		i++;
	}
	myfile.close();
	cout << endl;
}