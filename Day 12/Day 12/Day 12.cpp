#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <regex>
#include <algorithm>

using namespace std;

const int PADDING = 1000;
const int ORIGIN_X = 0;
const int ORIGIN_Y = 0;
const int WAYPOINT_X = 10;
const int WAYPOINT_Y = -1;

class Instruction {
public:
	char command;
	int value;
	Instruction(string);
};

Instruction::Instruction(string input) {
	command = input[0];
	value = stoi(input.substr(1));
}

class Field {
private:
	int x, y, direction, wx, wy;
	char boatChar;
	string directions = "NESW";
	string boatChars = "^>v<";
	void setDirection(Instruction, char, int);
	int convertAxisToDirection(char, int);
	
public:
	Field();
	void rotateAxis(Instruction);
	void moveDirectionally(Instruction);
	void moveForward(Instruction);
	int manhattanDistance();
};

Field::Field() {
	direction = 1;
	boatChar = '>';
	x = ORIGIN_X;
	y = ORIGIN_Y;
	wx = WAYPOINT_X;
	wy = WAYPOINT_Y;
}

int Field::convertAxisToDirection(char axis, int value) {
	if (axis == 'x') {
		return value > 0 ? 1 : 3;
	}
	else {
		return value > 0 ? 2 : 0;
	}
}

void Field::setDirection(Instruction ins, char ch, int value) {
	vector<int> directional_charges = { -1, 1, 1, -1 };
	vector<bool> isX = { false, true, false, true };
	int axis_direction = convertAxisToDirection(ch, value);
	int turns = ((ins.value / 90) % 4) * (ins.command == 'R' ? 1 : -1);
	axis_direction += turns;
	if (axis_direction < 0)
		axis_direction += 4;
	if (axis_direction > 3)
		axis_direction -= 4;

	if (isX[axis_direction]) {
		wx = directional_charges[axis_direction] * abs(value);
	}
	else {
		wy = directional_charges[axis_direction] * abs(value);
	}
}

void Field::rotateAxis(Instruction instruction) {
	int x_value = wx, y_value = wy;
	setDirection(instruction, 'x', x_value);
	setDirection(instruction, 'y', y_value);
}

void Field::moveDirectionally(Instruction instruction) {
	if (instruction.command == 'N') {
		wy -= instruction.value;
	}
	if (instruction.command == 'E') {
		wx += instruction.value;
	}
	if (instruction.command == 'S') {
		wy += instruction.value;
	}
	if (instruction.command == 'W') {
		wx -= instruction.value;
	}
}

void Field::moveForward(Instruction instruction) {
	int offset_x = wx * instruction.value;
	int offset_y = wy * instruction.value;
	x += offset_x;
	y += offset_y;
}

int Field::manhattanDistance() {
	int originX = ORIGIN_X, originY = ORIGIN_Y;
	return abs(originX - x) + abs(originY - y);
}

int runInstructions(vector<Instruction> commands, Field ocean) {
	for (auto i = commands.begin(); i != commands.end(); ++i) {
		if (i->command == 'F')
			ocean.moveForward(*i);
		if (i->command == 'N' || i->command == 'E' || i->command == 'S' || i->command == 'W')
			ocean.moveDirectionally(*i);
		if (i->command == 'L' || i->command == 'R')
			ocean.rotateAxis(*i);
	}
	return ocean.manhattanDistance();
}

int main(int argc, char** argv)
{
	ifstream inputFile;
	inputFile.open("C:\\Users\\Abacaxi\\Desktop\\Advent Of Code 2020\\Inputs\\input12.txt");
	if (!inputFile) {
		cerr << "Unable to open file input.txt";
		exit(1);
	}

	vector<Instruction> commands;
	Field ocean = *new Field();
	string x = "";

	auto start = chrono::high_resolution_clock::now();
	while (inputFile >> x) {
		commands.push_back(*new Instruction(x));
	}
	inputFile.close();

	cout << runInstructions(commands, ocean) << " is the Manhattan Distance." << endl;

	auto stop = chrono::high_resolution_clock::now();


	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout.precision(20);
	cout << duration.count() << " miliseconds" << endl;

}
