#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

static const string readPath = "../../";
static const string writePath = "../";
static const string libPath = readPath + "library.txt";

int main()
{
	vector<string> lib;
	ifstream LIB(libPath.c_str());
	while(!LIB.eof())
	{
		string input = "";
		string trash = "";
		getline(LIB, input, '=');
		getline(LIB, trash);
		lib.push_back(input);
	}
	LIB.close();

	int i = 0;
	while(i < lib.size())
	{
		string readfilename = lib[i];

		string writefilename = readfilename + ".js";
		readfilename = readPath + readfilename + ".txt";

		writefilename = writePath + writefilename;

		ifstream readFile(readfilename.c_str());

		ofstream writeFile(writefilename.c_str());
		writeFile << "var dictionary = \n";
		writeFile << "[\n";

		while(!readFile.eof())
		{
			string trash = "";
			string input1 = ""; //jap romanji
			string input2 = ""; //english
			string input3 = ""; //not romanji

			getline(readFile,input1,'='); //first string

			//create commend // in input file (use at beginning of line and line must end with '='')
			if(input1.substr(0,2) == "//")
			{
				getline(readFile,input1);
				continue;
			}
			//create commend /* in input file (use at beginning of line)
			//closing */ has to be on a following line
			if(input1.substr(0,2) == "/*")
			{
				while(input1.substr(0,2) != "*/" && !readFile.eof())
				{
					getline(readFile,input1);
				}
				continue;
			}

			getline(readFile,input2,'='); //second string
			getline(readFile,input3,'='); //third string
			getline(readFile,trash);

			//avoid blank entry
			if(input1[0] == '\n') continue;
			if(input1 == "" || input2 == "" || input3 == "") continue;

			writeFile << "\t{\n";
			writeFile << "\t\tromanji: \"" << input1 << "\",\n";
			writeFile << "\t\teng: \"" << input2 << "\",\n";
			writeFile << "\t\tjap: \"" << input3 << "\",\n";
			writeFile << "\t},\n";
		}
		readFile.close();

		writeFile << "];\n";
		writeFile.close();
		i++;
	}
	cout << "Done!" << endl;
	return 0;
}

