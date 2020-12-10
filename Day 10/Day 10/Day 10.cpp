#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;

vector<double> findCandidates(vector<double> lines, double in) {
	vector<double> candidates;
	for (auto i = lines.begin(); i != lines.end(); i++) {
		double candidate = *i;
		if (candidate - in == 1 || candidate - in == 3) {
			candidates.push_back(candidate);
		}
	}
	return candidates;
}

vector<double> sortByDeviation(vector<double> lines, vector<double> sorted, vector<double>* finished, double line_size) {
	vector<double> candidates = findCandidates(lines, sorted.back());
	for (auto i = candidates.begin(); i != candidates.end(); ++i) {
		double candidate = *i;
		vector<double> lines_minus_candidate = lines;
		lines_minus_candidate.erase(find(lines_minus_candidate.begin(), lines_minus_candidate.end(), candidate));
		vector<double> candidate_specific_sorted = sorted;
		candidate_specific_sorted.push_back(candidate);
		vector<double> tmp = sortByDeviation(lines_minus_candidate, candidate_specific_sorted, finished, line_size);
		if (tmp.size() == line_size)
			*finished = tmp;
	}
	return sorted;
}

double countDeviations(vector<double> lines) {
	double one_count = 0;
	double seven = 0;
	double four = 0;
	double two = 0;
	vector<double> spaces;
	for (auto i = lines.begin(); i != lines.end(); ++i) {
		if ((i + 1) != lines.end()) {
			spaces.push_back(*(i + 1) - *i);
		}
	}
	for (auto i = spaces.begin(); i != spaces.end(); ++i) {
		if (*i == 1) {
			++one_count;
		}
		else {
			if (one_count == 4)
				++seven;
			if (one_count == 3)
				++four;
			if (one_count == 2)
				++two;
			one_count = 0;
		}
	}
	if (one_count == 4)
		++seven;
	if (one_count == 3)
		++four;
	if (one_count == 2)
		++two;
	one_count = 0;
	return pow(2, two) * pow(4, four) * pow(7, seven);
}
 
int main(int argc, char** argv)
{
	ifstream inputFile;
	inputFile.open("C:\\Users\\Abacaxi\\Desktop\\Advent Of Code 2020\\Inputs\\input10.txt");
	if (!inputFile) {
		cerr << "Unable to open file input.txt";
		exit(1);
	}

	vector<double> lines;
	string x = "";
	double deviation = 3;

	auto start = chrono::high_resolution_clock::now();
	while (inputFile >> x) {
		lines.push_back(stod(x));
	}
	vector<double> finished;
	sortByDeviation(lines, { 0 }, &finished, lines.size() + 1.00);
	double number = countDeviations(finished);
	auto stop = chrono::high_resolution_clock::now();
	inputFile.close();


	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout.precision(20);
	cout << number << " count" << endl;
	cout << duration.count() << " miliseconds" << endl;

}
