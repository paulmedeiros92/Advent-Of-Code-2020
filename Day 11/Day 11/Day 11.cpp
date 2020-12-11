#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <regex>
#include <algorithm>

using namespace std;

const int PADDING = 100;

int countAdjacentSeats(vector<string> rows, int row, int col, int range, char ch) {
	string adjacent = rows[row].substr(col - range, range) + rows[row].substr(col + range, range);
	for (int i = 0; i < range; ++i) {
		int col_range = i + 1;
		adjacent += rows[row - col_range][col - col_range];
		adjacent += rows[row - col_range][col];
		adjacent += rows[row - col_range][col + col_range];
		adjacent += rows[row + col_range][col - col_range];
		adjacent += rows[row + col_range][col];
		adjacent += rows[row + col_range][col + col_range];
	}

	return count(adjacent.begin(), adjacent.end(), ch);
}

int countFirstAdjacentSeats(vector<string> rows, int row, int col, int range, char ch) {
	vector<bool> raycast = { false, false, false, false, false, false, false, false };
	vector<bool> isSet = { false, false, false, false, false, false, false, false };
	int counter = 0;
	for (int i = 0; i < range; ++i) {
		int col_range = i + 1;
		if (!isSet[0] && (rows[row - col_range][col - col_range] == 'L' || rows[row - col_range][col - col_range] == '#')) {
			raycast[0] = rows[row - col_range][col - col_range] == '#';
			isSet[0] = true;
		}
		if (!isSet[1] && (rows[row - col_range][col] == 'L' || rows[row - col_range][col] == '#')) {
			raycast[1] = rows[row - col_range][col] == '#';
			isSet[1] = true;
		}
		if (!isSet[2] && (rows[row - col_range][col + col_range] == 'L' || rows[row - col_range][col + col_range] == '#')) {
			raycast[2] = rows[row - col_range][col + col_range] == '#';
			isSet[2] = true;
		}
		if (!isSet[3] && (rows[row][col - col_range] == 'L' || rows[row][col - col_range] == '#')) {
			raycast[3] = rows[row][col - col_range] == '#';
			isSet[3] = true;
		}
		if (!isSet[4] && (rows[row][col + col_range] == 'L' || rows[row][col + col_range] == '#')) {
			raycast[4] = rows[row][col + col_range] == '#';
			isSet[4] = true;
		}
		if (!isSet[5] && (rows[row + col_range][col - col_range] == 'L' || rows[row + col_range][col - col_range] == '#')) {
			raycast[5] = rows[row + col_range][col - col_range] == '#';
			isSet[5] = true;
		}
		if (!isSet[6] && (rows[row + col_range][col] == 'L' || rows[row + col_range][col] == '#')) {
			raycast[6] = rows[row + col_range][col] == '#';
			isSet[6] = true;
		}
		if (!isSet[7] && (rows[row + col_range][col + col_range] == 'L' || rows[row + col_range][col + col_range] == '#')) {
			raycast[7] = rows[row + col_range][col + col_range] == '#';
			isSet[7] = true;
		}
	}

	for (auto i = raycast.begin(); i < raycast.end(); ++i) {
		if (*i) {
			++counter;
		}
	}

	return counter;
}

int countSeats(vector<string> rows, char ch) {
	int ticker = 0;
	for (int i = PADDING; i < rows.size() - PADDING; ++i)
		ticker += count(rows[i].begin(), rows[i].end(), ch);
	return ticker;
}

bool areSeatsTheSame(vector<string> old, vector<string> fresh) {
	bool same = true;
	for (int i = PADDING; i < old.size() - PADDING; ++i)
		same = same && old[i] == fresh[i];
	return same;
}

vector<string> fillSeats(vector<string> rows) {
	vector<string> modified_rows = rows;
	for (int i = PADDING; i < rows.size() - PADDING; ++i) {
		string row = rows[i];
		for (int j = PADDING; j < row.size() - PADDING; ++j) {
			if (row[j] == 'L' && countFirstAdjacentSeats(rows, i, j, 97, '#') == 0)
				modified_rows[i][j] = '#';
			if (row[j] == '#' && countFirstAdjacentSeats(rows, i, j, 97, '#') > 4)
				modified_rows[i][j] = 'L';
		}
	}
	return modified_rows;
}

vector<string> padInput(vector<string> lines) {
	for (int i = 0; i < PADDING; ++i)
		lines.push_back(".........................................................................................................................................................................................................................................................................................................");
	return lines;
}

int main(int argc, char** argv)
{
	ifstream inputFile;
	inputFile.open("C:\\Users\\Abacaxi\\Desktop\\Advent Of Code 2020\\Inputs\\input11.txt");
	if (!inputFile) {
		cerr << "Unable to open file input.txt";
		exit(1);
	}

	vector<string> lines;
	string x = "";

	auto start = chrono::high_resolution_clock::now();
	lines = padInput(lines);
	while (inputFile >> x) {
		lines.push_back("...................................................................................................." + x + "....................................................................................................");
	}
	inputFile.close();
	lines = padInput(lines);

	vector<string> new_lines = lines;
	bool looping = true;
	while (looping) {
		new_lines = fillSeats(new_lines);
		looping = !areSeatsTheSame(lines, new_lines);
		lines = new_lines;
		for (auto i = lines.begin(); i != lines.end(); ++i)
			cout << *i << endl;
		cout << endl << endl;
	}

	auto stop = chrono::high_resolution_clock::now();


	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout.precision(20);
	cout << countSeats(lines, '#') << " seats filled!" << endl;
	cout << duration.count() << " miliseconds" << endl;

}
