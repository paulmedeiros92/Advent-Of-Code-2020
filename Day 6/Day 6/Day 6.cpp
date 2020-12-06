#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;


double countquestions(vector<vector<string>> groups) {
	double sum = 0;
	for (auto i = groups.begin(); i != groups.end(); i++) {
		vector<string> group = *i;
		string list = "abcdefghijklmnopqrstuvwxyz";
		for (auto j = group.begin(); j != group.end(); j++) {
			string answer = *j;
			for (int k = 0; k < answer.length(); k++) {
				int position = list.find(answer[k]);
				if (position != string::npos) {
					list.erase(position, 1);
				}
			}
		}
		sum += 26 - list.length();
	}
	return sum;
}

string allyes(vector<string> answers, int i) {
	if (i == answers.size() - 1) {
		return answers[i];
	}
	string intersection = allyes(answers, i + 1);
	string string_intersection;
	sort(intersection.begin(), intersection.end());
	sort(answers[i].begin(), answers[i].end());

	set_intersection(intersection.begin(), intersection.end(), answers[i].begin(), answers[i].end(), back_inserter(string_intersection));
	return string_intersection;
}

int main(int argc, char** argv)
{
	ifstream inputFile;
	inputFile.open("C:\\Users\\Abacaxi\\Desktop\\Advent Of Code 2020\\Inputs\\input6.txt");
	if (!inputFile) {
		cerr << "Unable to open file input.txt";
		exit(1);
	}

	vector<vector<string>> groups;
	vector<string> group;
	string x = "";

	while (getline(inputFile, x)) {
		if (x == "") {
			groups.push_back(group);
			group.clear();
		}
		else {
			group.push_back(x);
		}
	}
	groups.push_back(group);

	inputFile.close();
	
	int sum = 0;
	for (auto i = groups.begin(); i != groups.end(); i++) {
		vector<string> group = *i;
		sum += allyes(group, 0).length();
	}

	cout << sum;


}