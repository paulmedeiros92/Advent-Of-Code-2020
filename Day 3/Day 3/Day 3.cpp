#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class Position {
	int x, y;
public:
	double collisions;
	Position();
	void move(string, int);
};

Position::Position() {
	x = 0;
	y = 0;
	collisions = 0;
}

void Position::move(string line, int slopeX) {
	x = (x + slopeX) % line.length();

	if (line[x] == '#')
		collisions++;
}

int main(int argc, char** argv)
{
	ifstream inputFile;
	inputFile.open("C:\\Users\\Abacaxi\\Desktop\\Advent Of Code 2020\\Inputs\\input3.txt");
	if (!inputFile) {
		cerr << "Unable to open file input.txt";
		exit(1);
	}

	vector<string> lines;
	string x = "";

	while (inputFile >> x) {
		lines.push_back(x);
	}
	inputFile.close();

	Position top1 = *new Position();
	Position top3 = *new Position();
	Position top5 = *new Position();
	Position top7 = *new Position();
	Position top12 = *new Position();

	bool alternate = false;
	for (auto i = lines.begin(); i != lines.end(); ++i) {
		if (i != lines.begin()) {
			string line = *i;
			top1.move(line, 1);
			top3.move(line, 3);
			top5.move(line, 5);
			top7.move(line, 7);
			if (alternate) {
				top12.move(line, 1);
			}
			alternate = !alternate;
		}
	}

	double total = top1.collisions * top3.collisions * top5.collisions * top7.collisions * top12.collisions;

	cout << total;

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
