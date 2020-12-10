#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

vector<double> pushAndShift(double x, vector<double> lines, double max_length) {
	if (lines.size() >= max_length) {
		lines.erase(lines.begin());
		lines.push_back(x);
	}
	else {
		lines.push_back(x);
	}
	return lines;
}

bool checkRule(vector<double> lines, double curr) {
	for (auto i = lines.begin(); i != lines.end(); i++) {
		double prev = *i;
		vector<double> tmp = lines;
		tmp.erase(find(tmp.begin(), tmp.end(), prev));
		if (find(tmp.begin(), tmp.end(), curr - prev) != tmp.end()) {
			return true;
		}
	}
	return false;
}

double sumLine(vector<double>* lines) {
	double line_sum = 0;
	for (auto i = lines->begin(); i < lines->end(); i++) {
		line_sum += *i;
	}
	return line_sum;
}

bool checkSum(double x, vector<double>* lines, double max_value) {
	double line_sum = sumLine(lines);
	while (line_sum + x > max_value) {
		lines->erase(lines->begin());
		line_sum = sumLine(lines);
	}
	if (line_sum + x < max_value){
		lines->push_back(x);
		return false;
	}
	if (line_sum + x == max_value) {
		lines->push_back(x);
		return true;
	}
}

vector<double> findMinMax(vector<double> lines) {
	double min = lines[0], max = lines[0];
	for (auto i = lines.begin(); i != lines.end(); ++i) {
		double curr = *i;
		if (curr < min)
			min = curr;
		if (curr > max)
			max = curr;
	}
	return { min, max };
}

int main(int argc, char** argv)
{
	ifstream inputFile;
	inputFile.open("C:\\Users\\Abacaxi\\Desktop\\Advent Of Code 2020\\Inputs\\input9.txt");
	if (!inputFile) {
		cerr << "Unable to open file input.txt";
		exit(1);
	}

	vector<double> lines;
	string x = "";
	double max_length = 25;
	double funky_numby = NULL;

	auto start = chrono::high_resolution_clock::now();
	while (inputFile >> x) {
		double number = stod(x);
		if (checkSum(number, &lines, 1639024365)) {
			break;
		}
	}
	auto stop = chrono::high_resolution_clock::now();
	inputFile.close();

	vector<double> minMax = findMinMax(lines);

	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout.precision(20);
	cout << minMax[0] + minMax[1] << endl;
	cout << duration.count() << endl;

}
