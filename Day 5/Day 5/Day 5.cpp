#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class Range {
public:
	int min, max, length;
	Range(int, int);
};

Range::Range(int i, int j) {
	min = i;
	max = j;
	length = max - min;
}

int binarySplit(Range range, string path, int i, char highChar) {
	char indicator = path[i];
	bool ishigh = indicator == highChar;
	if (range.max - range.min == 1) {
		return ishigh ? range.max : range.min;
	}
	int halfsize = range.length / 2;
	if (ishigh)
		return binarySplit(*new Range(range.max - halfsize, range.max), path, ++i, highChar);
	return binarySplit(*new Range(range.min, range.min + halfsize), path, ++i, highChar);
}

int main(int argc, char** argv)
{
	ifstream inputFile;
	inputFile.open("C:\\Users\\Abacaxi\\Desktop\\Advent Of Code 2020\\Inputs\\input5.txt");
	if (!inputFile) {
		cerr << "Unable to open file input.txt";
		exit(1);
	}

	string x = "";
	int max = 0;
	vector<int> roster[1000];

	while (inputFile >> x) {
		string rowstr = x.substr(0, 7);
		string columnstr = x.substr(7, 3);

		int row = binarySplit(*new Range(0, 127), rowstr, 0, 'B');
		int column = binarySplit(*new Range(0, 7), columnstr, 0, 'R');
		int id = row * 8 + column;
		roster[row * 8].push_back(column);
	}

	for (int i = 0; i < 1000; i++) {
		if (roster[i].size() > 0 && roster[i].size() < 8) {
			cout << "Row " << i << ": ";
			for (auto j = roster[i].begin(); j != roster[i].end(); ++j)
				cout << *j << ", ";
			cout << "\n";
		}
	}

	inputFile.close();

}
