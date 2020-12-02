// Hello World CPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class Password {
	int min, max;
	char character;
	string password;
public: 
	Password(int, int, char, string);
	bool isvalid();
	bool isinposition();
};

Password::Password(int i, int a, char c, string s) {
	min = i;
	max = a;
	character = c;
	password = s;
}

bool Password::isvalid() {
	int occurrences = count(password.begin(), password.end(), character);
	if (occurrences >= min && occurrences <= max)
		return true;
	else
		return false;
}

bool Password::isinposition() {
	int first = min - 1, second = max - 1;
	if (password[first] == character && password[second] != character || 
		password[first] != character && password[second] == character)
		return true;
	else
		return false;
}


bool parseLine(string strminmax, string strchar, string strpass) {
	int min = stoi(strminmax.substr(0, strminmax.find("-")));
	int max = stoi(strminmax.substr(strminmax.find("-") + 1));
	char character = strchar[0];
	Password pass = *new Password(min, max, character, strpass);
	return pass.isinposition();
}

int main(int argc, char** argv)
{
	ifstream inputFile;
	inputFile.open("C:\\Users\\Abacaxi\\Desktop\\Advent Of Code 2020\\Inputs\\input2.txt");
	if (!inputFile) {
		cerr << "Unable to open file input.txt";
		exit(1);
	}

	vector<string> lines;
	string minmax = "", character = "", password = "";
	int counter = 0;

	while (inputFile >> minmax >> character >> password) {
		if (parseLine(minmax, character, password))
			counter++;
	}

	cout << counter << " passwords were valid";

	inputFile.close();
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
