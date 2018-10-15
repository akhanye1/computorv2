#include "../computorv.h"

vector<Instruction> Instruction::instructions;

Instruction::Instruction() {
    this->valid = false;
}

Instruction::Instruction(string str) {
    this->splitString(str, '=', this->commands);
    this->isPrint = false;
    if (this->commands.size() != 2) {
        this->valid = false;
        return ;
    }
    this->valid = this->verifyInstruction();
}

Instruction& Instruction::operator=(Instruction const &rhs) {
    this->setInstructionData(rhs);
    return (*this);
}

bool    Instruction::setEquation(string rhs_string) {
    polynomial *equation = new polynomial();
    Validate validator;

    if (!validator.isPolynomialValid(rhs_string, equation, *this)) {
        cout << "Is not valid polynomial" << endl;
        return (false);
    }
    // equation->showAll();
    equation->calculate();
    // equation->showAll();
    // cout << "Counter : " << equation->counter << endl;
    if (equation->counter == 1) {
        tempInstruction = new Instruction();
        tempInstruction->setInstruction(equation->getEquationType());
        if (equation->getEquationType() == VARIABLE || equation->getEquationType() == FUNCTION) {
            tempInstruction->setFloatValue(equation->getTerm(0)->getCorrectValue());
            // cout << "first if statement" << endl;
        }
        else {
            tempInstruction->setCommand(rhs_string);
            // cout << "second if statement" << endl;
        }
        return (true);
    }
    else if (equation->isImaginary() && equation->counter > 0) {
        tempInstruction = new Instruction();
        tempInstruction->setCommand(equation->toEquation());
        tempInstruction->setInstruction(IMAGINERY);
        return (true);
    }
    return (false);
}

bool    Instruction::setupMatrix(string rhs_string) {
    Matrix *matrix = new Matrix(rhs_string, *this);

    if (matrix->matrixOk()) {
        cout << "matrix valid" << endl;
        this->matrix = matrix;
        this->instructionType = MATRIX;
        return (true);
    }
    cout << "matrix failed" << endl;
    return (false);
}

bool    Instruction::checkOneValue(vector<string> rhs, string rhs_string) {
    Validate validator;

    if (!rhs.at(0).compare("i") || !rhs.at(0).compare("I")) {
        tempInstruction = new Instruction();
        tempInstruction->setInstruction(IMAGINERY);
        tempInstruction->setCommand("i");
        return (true);
    }
    else if (Validate::isNumeric(rhs.at(0))) {
        tempInstruction = new Instruction();
        tempInstruction->setInstruction(VARIABLE);
        tempInstruction->setFloatValue(atof(rhs.at(0).c_str()));
        return (true);
    }
    else if (!rhs.at(0).compare("?")) {
        tempInstruction = new Instruction();
        this->isPrint = true;
        return (true);
    }
    else if (Validate::isValidVariable(rhs.at(0), false)) {
        // cout << "Found variable" << endl;
        return (this->setEquation(rhs_string));
    }
    else if (validator.foundOperator(rhs.at(0)) || validator.foundMixedTerm(rhs.at(0))) {
        // cout << "Mixed term found : " << rhs.at(0) << endl;
        return (this->setEquation(rhs_string));
    }
    else if (Matrix::isValidMatrix(rhs_string)) {
        return (setupMatrix(rhs_string));
    }
    cout << "Got here" << endl;
    return (false);
}

bool    Instruction::checkRightHandSide(vector<string> rhs, bool isFunction, string rhs_str) {
    if (!isFunction) {
        if (rhs.size() == 1) {
            return (this->checkOneValue(rhs, rhs_str));
        }
        else {
            return (this->setEquation(rhs_str));
        }
    }
    return (false);
}

bool    Instruction::setVariableData(vector<string> rightInstructions, string str, string rhs) {
    tempInstruction = NULL;
    if (!this->checkRightHandSide(rightInstructions, false, rhs)) {
        return (false);
    }
    if (this->getType() == MATRIX) {
        this->instruction = str;
        this->instructions.push_back(*this);
        return (true);
    }
    if (tempInstruction == NULL) {
        return (false);
    }
    if (this->isPrint) {
        cout << "Finding instruction" << endl;
        if (findInstruction(str) == NULL) {
            cout << "Instruction not found" << endl;
            return (false);
        }
        else {
            cout << "Instruction found" << endl;
            this->setInstructionData(*findInstruction(str));
            this->isPrint = true;
        }
        return (true);
    }
    tempInstruction->setInstructionHead(str);
    if (this->findInstruction(str) == NULL) {
        this->setInstructionData(*tempInstruction);
        instructions.push_back(*this);
        return (true);
    }
    else {
        findInstruction(str)->setInstructionData(*tempInstruction);
        this->setInstructionData(*tempInstruction);
        return (true);
    }
    return (false);
}

bool    Instruction::verifyInstruction() {
    vector<string>  leftInstructions;
    vector<string>  rightInstructions;
    string          str;

    splitString(commands.at(0), ' ', leftInstructions);
    splitString(commands.at(1), ' ', rightInstructions);
    if (leftInstructions.size() == 1) {
        str = leftInstructions.at(0);
        if (!Validate::isValidVariable(str, true) && !Validate::isValidFunction(str)) {
            return (false);
        }
        if (Validate::isValidVariable(str, true)) {
            return (setVariableData(rightInstructions, str, commands.at(1)));
        }
    }
    else if (rightInstructions.size() == 1) {
        if (rightInstructions.at(0).compare("?")) {
            return (false);
        }
    }
    return (true);
}

void    Instruction::setInstructionData(Instruction data) {
    this->value = data.getValue();
    this->floatValue= data.getfloatValue();
    this->instructionType = data.getType();
    this->instruction = data.getInstruction();
    this->command = data.getCommand();
    this->matrix = data.getMatrix();
}

string  Instruction::getCommand() const {
    return (this->command);
}

void	Instruction::splitString(string poly, char deliminator, vector<string> &tempVector) {
	string  temp;
	size_t  pos;

	while ((pos = poly.find(deliminator)) != string::npos) {
        temp = Validate::trimString(poly.substr(0, pos));
		poly = poly.substr(pos + 1);
        if (temp.length() > 0)
		    tempVector.push_back(temp);
	}
	tempVector.push_back(Validate::trimString(poly));
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

Instruction *Instruction::findInstruction(string str) {
    int index = -1;
    int len = (int)instructions.size();

    while (++index < len) {
        if (instructions.at(index).compareCommand(str)) {
            return (&instructions.at(index));
        }
    }
    return (NULL);
}

void        Instruction::showAllInstructions() {
    int index = -1;
    int len = (int)instructions.size();

    while (++index < len) {
        cout << "Instruction : " << instructions.at(index).getInstruction();
        cout << " " << instructions.at(index).getfloatValue() << endl;
    }
}

void        Instruction::setInstructionHead(string head) {
    this->instruction = head;
}

void        Instruction::setCommand(string commandType) {
    this->command = commandType;
}

Matrix      *Instruction::getMatrix() {
    return (this->matrix);
}