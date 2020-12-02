// Hello World CPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int* whichNumbers(int* numbers) {
	int max = 200;
	for (int i = 0; i < max; i++) {
		for (int j = 1; j < max; j++) {
			for (int k = 2; k < max; k++) {
				if (numbers[i] + numbers[j] + numbers[k] == 2020) {
					int* answers = new int[3];
					answers[0] = numbers[i];
					answers[1] = numbers[j];
					answers[2] = numbers[k];
					return answers;
				}
			}
		}
	}
	return { 0 };
}

int main(int argc, char** argv)
{
	ifstream inputFile;
	inputFile.open("C:\\Users\\Abacaxi\\Desktop\\input.txt");
	if (!inputFile) {
		cerr << "Unable to open file input.txt";
		exit(1);
	}

	int* numbers = new int[200];
	int i = 0;
	string x = "";

	while (inputFile >> x) {
		numbers[i] = stoi(x);
		i++;
	}

	int* answers = whichNumbers(numbers);
	if (sizeof(answers) > 1) {
		cout << answers[0] * answers[1] * answers[2];
	}
	else {
		cout << "Error in whichNumbers...";
	}


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
