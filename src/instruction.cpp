#include "../computorv.h"

vector<Instruction> Instruction::instructions;

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

bool    Instruction::checkRightHandSide(vector<string> rhs, bool isFunction) {
    float   tempFloat;
    if (!isFunction) {
        if (rhs.size() == 1) {
            if (Validate::isNumeric(rhs.at(0))) {
                tempFloat = atof(rhs.at(0).c_str());
                tempInstruction = new Instruction();
                tempInstruction->setInstruction(VARIABLE);
                tempInstruction->setFloatValue(tempFloat);
                return (true);
            }
        }
    }
    return (true);
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
        if (Validate::isValidVariable(str)) {
            tempInstruction = NULL;
            if (!this->checkRightHandSide(rightInstructions, false)) {
                return (false);
            }
            if (tempInstruction == NULL) {
                return (false);
            }
            tempInstruction->setInstructionHead(str);
            if (!this->findInstruction(str)) {
                //*this = this->findInstruction(str);
                // this->setInstructionData(this->findInstruction(str));
            }
            else {
                // this->setInstructionData(tempInstruction);
            }
        }
    }
    else if (rightInstructions.size() == 1) {
        if (rightInstructions.at(0).compare("?")) {
            return (false);
        }
    }
    return (true);
}

void    Instruction::setInstructionData(Instruction *data) {
    this->value = data->getValue();
    this->floatValue= data->getfloatValue();
    this->instructionType = data->getType();
    this->instruction = data->getInstruction();
    this->command = data->getCommand();
}

string  Instruction::getCommand() const {
    return (this->command);
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
    int index = -1;
    int len = (int)command.length();

    while (++index < len && index < (int)this->instruction.length()) {
        if (tolower(this->getInstruction()[index]) != tolower(command[index])) {
            return (false);
        }
    }
    return (index == (int)command.length() && index == (int)this->instruction.length());
}

string      Instruction::getInstruction() const {
    return (this->instruction);
}

float       Instruction::getfloatValue() const {
    return (this->floatValue);
}

 void        Instruction::setFloatValue(float val) {
     this->floatValue = val;
 }

bool Instruction::findInstruction(string str) {
    int index = -1;
    if (str.length() > 0) {

    }
    int len = (int)instructions.size();

    if (++index < len) {
        if (instructions.at(index).compareCommand(str)) {
            // return (&instructions.at(index));
            this->setInstructionData(&instructions.at(index));
            return (true);
        }
    }
    return (false);
}

void        Instruction::setInstructionHead(string head) {
    this->instruction = head;
}