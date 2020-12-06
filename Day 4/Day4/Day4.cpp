#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;


bool isvalid(vector<string> validations, string passport) {
	for (auto i = validations.begin(); i != validations.end(); i++) {
		string validation = *i;
		smatch m;
		bool didmatch = regex_search(passport, m, regex(validation));
		if (!didmatch)
			return false;
	}
	return true;
}

int main(int argc, char** argv)
{
	ifstream inputFile;
	inputFile.open("C:\\Users\\Abacaxi\\Desktop\\Advent Of Code 2020\\Inputs\\input4.txt");
	if (!inputFile) {
		cerr << "Unable to open file input.txt";
		exit(1);
	}

	vector<string> fields = { "ecl", "pid", "eyr", "hcl", "byr", "iyr", "hgt" };
	vector<string> validations = {"ecl:(amb|blu|brn|gry|grn|hzl|oth)", "pid:\\d{9}\\D", "eyr:(202[0-9]|2030)\\D", "hcl:#([a-f]|[0-9]){6}\\W", "byr:(19[2-9][0-9]|200[0-2])\\D", "iyr:(201[0-9]|2020)\\D", "hgt:(((1[5-8][0-9]|19[0-3])cm)|((59|6[0-9]|7[0-6])in))"};
	string passport;
	string x = "";
	int validcount = 0;

	while (getline(inputFile, x)) {
		
		if (x == "") {
			if (isvalid(validations, passport)) {
				validcount++;
			}
			passport = "";
		}
		passport += x + " ";
	}

	if (isvalid(validations, passport)) {
		validcount++;
	}

	inputFile.close();

	cout << validcount;

}
