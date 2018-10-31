#include "../computorv.h"

vector<Instruction> Instruction::instructions;

Instruction::Instruction() {
    this->valid = false;
    this->matrix = NULL;
    this->function = NULL;
}

Instruction::Instruction(string str) {
    this->matrix = NULL;
    this->function = NULL;
    this->splitString(str, '=', this->commands);
    this->isPrint = false;
    if (this->commands.size() != 2) {
        this->valid = false;
        return ;
    }
    this->valid = this->verifyInstruction();
}

Instruction& Instruction::operator=(Instruction const &rhs) {
    this->value = rhs.getValue();
    this->floatValue = rhs.getfloatValue();
    this->instructionType = rhs.getType();
    this->instruction = rhs.getInstruction();
    this->command = rhs.getCommand();
    return (*this);
}

bool    Instruction::setupFunction(polynomial *equation) {
    tempInstruction = new Instruction();
    Functions *function = new Functions();
    
    function->setVariableName(equation->getFunctionVariable());
    function->setEquation(equation);
    tempInstruction->setFunction(function);
    tempInstruction->setInstruction(FUNCTION);
    return (true);
}

void    Instruction::setFunction(Functions *function) {
    this->function = function;
}

bool    Instruction::setEquation(string rhs_string) {
    polynomial *equation = new polynomial();
    Validate validator;

    if (!validator.isPolynomialValid(rhs_string, equation, *this)) {
        cout << "Is not valid polynomial" << endl;
        return (false);
    }
    // equation->showAll();
    // cout << "see equation before calculating" << endl;
    equation->calculate();
    // equation->showAll();
    // cout << "Counter : " << equation->counter << endl;
    if (equation->getMaxTerms() == 1 && !equation->isFunction()) {
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
    else if (equation->isImaginary() && equation->getMaxTerms() > 0) {
        tempInstruction = new Instruction();
        tempInstruction->setCommand(equation->toEquation());
        tempInstruction->setInstruction(IMAGINERY);
        return (true);
    }
    else if (equation->isFunction() && equation->getMaxTerms() > 0) {
        return (this->setupFunction(equation));
    } 
    return (false);
}

bool    Instruction::setupMatrix(string rhs_string) {
    Matrix *matrix = new Matrix(rhs_string, *this);

    if (matrix->matrixOk()) {
        cout << "matrix valid" << endl;
        tempInstruction = new Instruction();
        tempInstruction->setMatrix(matrix);
        tempInstruction->setInstruction(MATRIX);
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
        return (this->setEquation(rhs_string));
    }
    else if (validator.foundOperator(rhs.at(0)) || validator.foundMixedTerm(rhs.at(0))) {
        return (this->setEquation(rhs_string));
    }
    else if (Matrix::isValidMatrix(rhs_string)) {
        return (setupMatrix(rhs_string));
    }
    cout << "Got here" << endl;
    return (false);
}

bool    Instruction::checkOneFunctionValue(string rhs_string) {
    if (rhs_string.compare("?")) {
        tempInstruction = new Instruction();
        this->isPrint = true;
        return (true);
    }
    return (false);
}

bool    Instruction::checkRightHandSide(vector<string> rhs, bool isFunction, string rhs_str) {
    if (!isFunction) {
        if (rhs.size() == 1) {
            return (this->checkOneValue(rhs, rhs_str));
        }
        return (this->setEquation(rhs_str));
    }
    cout << "Function identified" << endl;
    if (rhs.size() == 1) {
        return (this->checkOneFunctionValue(rhs_str));
    }
    return (this->setEquation(rhs_str));
}

bool    Instruction::prepareForPrint(string str) {
    cout << "Finding instruction" << endl;
    if (findInstruction(str) == NULL) {
        cout << "Instruction not found" << endl;
        return (false);
    }
    cout << "Instruction found" << endl;
    *this = *findInstruction(str);
    this->setMatrix(findInstruction(str)->getMatrix());
    this->setFunction(findInstruction(str)->getFunction());
    this->isPrint = true;
    return (true);
}

bool    Instruction::setVariableData(vector<string> rightInstructions, string str, string rhs) {
    tempInstruction = NULL;
    if (!this->checkRightHandSide(rightInstructions, false, rhs)) {
        return (false);
    }
    if (tempInstruction == NULL) {
        return (false);
    }
    else if (this->isPrint) {
        return (prepareForPrint(str));
    }
    tempInstruction->setInstructionHead(str);
    this->setInstructionData(*tempInstruction);
    return (true);
}

string  Instruction::getVariableName(string str) {
    vector<string>  strSplit;

    this->splitString(str, '(', strSplit);
    if (strSplit.size() != 2) {
        return ("");
    }
    if (strSplit[1][strSplit[1].length() - 1] != ')') {
        return ("");
    }
    return (strSplit[1].substr(0, strSplit[1].length() - 1));
}

string  Instruction::getFunctionName(string str) {
    if (str.find("(") == string::npos) {
        return ("");
    }
    return (str.substr(0, str.find("(") + 1));
}

Functions   *Instruction::getFunction() {
    return (this->function);
}

bool    Instruction::setFunctionData(vector<string> rhs_array, string str, string rhs_string) {
    tempInstruction = NULL;
    string              variableName;

    if (str.compare("?")) {
        
    }
    if (!this->checkRightHandSide(rhs_array, true, rhs_string)) {
        return (false);
    }
    if (!this->getFunctionName(str).compare("")) {
        return (false);
    }
    tempInstruction->setInstructionHead(this->getFunctionName(str));
    if (!this->getVariableName(str).compare("")) {
        return (false);
    }
    variableName = getVariableName(str);
    if (variableName.compare(tempInstruction->getFunction()->getVariableName())) {
        return (false);
    }
    this->setInstructionData(*tempInstruction);
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
        if (!Validate::isValidVariable(str, true) && !Validate::isValidFunction(str)) {
            return (false);
        }
        if (Validate::isValidVariable(str, true)) {
            return (setVariableData(rightInstructions, str, commands.at(1)));
        }
        else if (Validate::isValidFunction(str)) {
            return (setFunctionData(rightInstructions, str, commands.at(1)));
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
    Instruction *savedInstruction = findInstruction(data.getInstruction());
    if (savedInstruction != NULL) {
        *this = *savedInstruction;
    }
    this->value = data.getValue();
    this->floatValue = data.getfloatValue();
    this->instructionType = data.getType();
    this->instruction = data.getInstruction();
    this->command = data.getCommand();
    this->matrix = data.getMatrix();
    this->function = data.getFunction();
    if (savedInstruction != NULL) {
        instructions.erase(instructions.begin() + foundIndex);
    }
    instructions.push_back(*this);
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
    string  compareName;

    if (str.find("(") == string::npos) {
        compareName = str;
    }
    else {
        compareName = this->getFunctionName(str);
    }
    while (++index < len) {
        if (instructions.at(index).compareCommand(compareName)) {
            foundIndex = index;
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

void        Instruction::setMatrix(Matrix *tempMatrix) {
    this->matrix = tempMatrix;
}