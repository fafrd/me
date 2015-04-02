#ifndef JAP_H
#define JAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip> //color and format
#include <time.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using namespace std;

static vector<string> LIB;
static vector<string> JAP;
static vector<string> ENG;
static vector<string> JAP2;
static vector<string> EMP;

static const string path = "./Library/";

//file handlers
void readLIB(string &filename);

void readFromFile(string &filename, int readMode);

void writeToFile(string &filename, int readMode);

//modes
string chooseLesson();

bool chooseMode(string &filename, int readMode);

bool hint(string &compareString, int request, string &input);

void helper();

void mode(vector<string> &compareString, vector<string> &showString, vector<string> &showString2);

void modeNoRandom(vector<string> &compareString, vector<string> &showString, vector<string> &showString2);

void modeStudy();

void mistakeMode(vector<string> &compareString, vector<string> &showString, vector<string> &showString2, vector<int> &wrongindex);

//tools
void showFile(string &filename);

char* charPointer(string &inputfile);

char YesNoPrompt();

void stringInputPrompt(string &input);

void clearVector();

inline bool isInteger(const std::string & s);

void printVector(vector<string> &Vector, int start_base);

#endif