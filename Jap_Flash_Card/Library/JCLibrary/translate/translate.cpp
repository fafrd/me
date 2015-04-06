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
	ofstream writeFile("../library.js");
	writeFile.close();

	int i = 0;
	while(i < lib.size())
	{
		string readfilename = lib[i];
		string filename = readfilename;

		string writefilename = "library.js";
		writefilename = writePath + writefilename;

		readfilename = readPath + readfilename + ".txt";

		ifstream readFile(readfilename.c_str());

		ofstream writeFile(writefilename.c_str(), std::ios_base::app);
		writeFile << "var " << filename << " = \n";
		writeFile << "[\n";
		writeFile << "\t" << "\"" << filename << "\",\n";

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

	//write the library array
	ofstream AnotherwriteFile("../library.js", std::ios_base::app);
	AnotherwriteFile << "var library =\n";
	AnotherwriteFile << "[\n";
	i = 0;
	while(i < lib.size())
	{
		AnotherwriteFile << "\t" << lib[i] << ",\n";
		i++;
	}
	AnotherwriteFile << "];";
	AnotherwriteFile.close();

	cout << "Done!" << endl;
	return 0;
}

