#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Instruction {
public:
	string op;
	int value;
	bool has_ran;
	bool has_flipped;
	Instruction(string, int);
};

Instruction::Instruction(string string_op, int int_value) {
	op = string_op;
	value = int_value;
	has_flipped = false;
	has_ran = false;
}

void resetInstructions(vector<Instruction>* instructions) {
	vector<Instruction> ins = *instructions;
	for (auto i = ins.begin(); i != ins.end(); ++i) {
		Instruction x = *i;
		x.has_ran = false;
		*i = x;
	}
	*instructions = ins;
}

int run(vector<Instruction> instructions) {
	int accumulator = 0;
	int i = 0;
	bool system_flip = false;
	while (true) {
		if (i >= instructions.size()) {
			cout << "End of file!\n";
			return accumulator;
		}
		Instruction ins = instructions[i];
		if (ins.has_ran) {
			cout << "Reseting due to looping.\n";
			i = 0;
			system_flip = false;
			accumulator = 0;
			resetInstructions(&instructions);
		}
		else {
			if (!system_flip && (ins.op == "nop" || ins.op == "jmp") && !ins.has_flipped) {
				system_flip = true;
				instructions[i].has_flipped = true;
				if (ins.op == "nop") {
					ins.op = "jmp";
				}
				else {
					ins.op = "nop";
				}
			}
			instructions[i].has_ran = true;
			if (ins.op == "nop") {
				// nothing happens here
				i++;
			}
			else if (ins.op == "acc") {
				accumulator += ins.value;
				i++;
			}
			else if (ins.op == "jmp") {
				i += ins.value;
			}
		}
	}
}

int main()
{
	ifstream inputFile;
	inputFile.open("C:\\Users\\Abacaxi\\Desktop\\Advent Of Code 2020\\Inputs\\input8.txt");
	if (!inputFile) {
		cerr << "Unable to open file input.txt";
		exit(1);
	}

	string op, value;
	vector<Instruction> instructions;

	while (inputFile >> op >> value) {
		instructions.push_back(*new Instruction(op, stoi(value)));
	}
	inputFile.close();

	cout << run(instructions);

}