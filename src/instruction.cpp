#include "../computorv.h"

Instruction::Instruction() {
    this->valid = false;
}

Instruction::Instruction(string str) {
    this->splitString(str, '=', this->commands);
    if (this->commands.size() != 2) {
        this->valid = false;
        return ;
    }
    this->valid = this->verifyInstruction();
}

bool    Instruction::verifyInstruction() {
    vector<string>  leftInstructions;
    vector<string>  rightInstructions;
    string          str;

    splitString(commands.at(0), ' ', leftInstructions);
    splitString(commands.at(1), ' ', rightInstructions);
    if (leftInstructions.size() == 1) {
        str = leftInstructions.at(0);
        if (!Validate::isValidVariable(str) && !Validate::isValidFunction(str)) {
            return (false);
        }
    }
    else if (rightInstructions.size() == 1) {
        if (rightInstructions.at(0).compare("?")) {
            return (false);
        }
    }
    return (true);
}

string  trimString(string str) {
    string  temp = str;
    int     startPos = -1;
    int     endPos = str.length();

    while (str[++startPos] && str[startPos] == ' ');
    while (--endPos > 0 && str[endPos] == ' ');
    temp = temp.substr(startPos, (endPos - startPos) + 1);
    return (temp);
}

void	Instruction::splitString(string poly, char deliminator, vector<string> &tempVector) {
	string  temp;
	size_t  pos;

	while ((pos = poly.find(deliminator)) != string::npos) {
        temp = trimString(poly.substr(0, pos));
		poly = poly.substr(pos + 1);
        if (temp.length() > 0)
		    tempVector.push_back(temp);
	}
	tempVector.push_back(trimString(poly));
}

string      Instruction::getValue() const {
    return (this->value);
}

int         Instruction::getType() const {
    return (this->instructionType);
}

void        Instruction::setInstruction(int instructionType) {
    this->instructionType = instructionType;
}

bool        Instruction::isValid() const {
    return (this->valid);
}

bool        Instruction::compareCommand(string command) const {
    if (!this->command.compare(command)) {
        return (true);
    }
    return (false);
}

string      Instruction::getInstruction() const {
    return (this->instruction);
}