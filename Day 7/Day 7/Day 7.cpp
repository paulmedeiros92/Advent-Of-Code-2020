#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class Line {
public:
    string bag_name;
	vector<string> args;
	vector<int> counts;
	Line(string, vector<string>, vector<int>);
};

Line::Line(string str_name, vector<string> arg_vector, vector<int> count_vector) {
    bag_name = str_name;
	args = arg_vector;
	counts = count_vector;
}

int countBags(vector<Line> lines, Line line) {
	int count = 0;
	if (line.args.size() > 0) {
		for (int i = 0; i < line.args.size(); ++i) {
			string arg = line.args[i];
			vector<Line>::iterator found = find_if(lines.begin(), lines.end(), [arg](const Line& obj) {return obj.bag_name == arg;});
			if (found != lines.end()) {
				int bag_count = countBags(lines, *found);
				count += line.counts[i] * bag_count;
				if (bag_count != 1)
					count += line.counts[i];
			}
		}
	}
	else {
		count = 1;
	}

	return count;
}

Line parseLine(string line) {
	const string first_delimeter = " bags contain ";
	string color = line.substr(0, line.find(first_delimeter));
	line.erase(0, line.find(first_delimeter) + first_delimeter.length());
	
	vector<string> args;
	vector<string> clean_args;
	vector<int> counts;
	if (line.find("no other") == string::npos) {
		while (line.find(", ") != string::npos) {
			args.push_back(line.substr(0, line.find(", ")));
			line.erase(0, line.find(", ") + 2);
		}
		args.push_back(line);

		for (auto i = args.begin(); i != args.end(); ++i) {
			string arg = *i;
			counts.push_back(stoi(arg.substr(0, arg.find(' '))));
			arg.erase(0, arg.find(' ') + 1);
			clean_args.push_back(arg.substr(0, arg.find(" bag")));
		}
	}
	return Line(color, clean_args, counts);
}

int main()
{
	ifstream inputFile;
	inputFile.open("C:\\Users\\Abacaxi\\Desktop\\Advent Of Code 2020\\Inputs\\input7.txt");
	if (!inputFile) {
		cerr << "Unable to open file input.txt";
		exit(1);
	}

	string x = "";
	vector<Line> lines;
	while (getline(inputFile, x)) {
		lines.push_back(parseLine(x));
	}
	inputFile.close();

	string name = "shiny gold";
	vector<Line>::iterator found = find_if(lines.begin(), lines.end(), [name](const Line& obj) {return obj.bag_name == name;});
	int count = countBags(lines, *found);
	cout << count;

}
