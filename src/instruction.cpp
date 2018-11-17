#include "../computorv.h"

vector<Instruction> Instruction::instructions;

Instruction::Instruction() {
    this->valid = false;
    this->matrix = NULL;
    this->function = NULL;
    this->viewOnly = false;
}

Instruction::Instruction(string str) {
    this->matrix = NULL;
    this->function = NULL;
    this->splitString(str, '=', this->commands);
    this->isPrint = false;
    this->viewOnly = false;
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

bool    Instruction::setStoreValue(polynomial *equation) {
    // cout << "Equation Type :: " << equation->getEquationType() << " | tempInstruction type :: " << tempInstruction->getType() << endl;
    if (tempInstruction->getType() == VARIABLE) {
        if (equation->getEquationType() != VARIABLE && equation->getEquationType() != MATRIX &&
            equation->getEquationType() != IMAGINERY) {
                cout << "<<>> Exited here" << endl;
            return (false);
        }
    }
    else if (tempInstruction->getType() != equation->getEquationType()) {
        return (false);
    }
    tempInstruction->setInstruction(equation->getEquationType());
    // equation->showAll();
    // cout << "Counter : " << equation->counter << endl;
    if (equation->getMaxTerms() == 1 && equation->getEquationType() == VARIABLE) {
        tempInstruction->setFloatValue(equation->getTerm(0)->getCorrectValue());
        // if (this->viewOnly) {
        //     cout << equation->getTerm(0)->getCorrectValue() << endl;
        // }
        return (true);
    }
    else if (equation->isImaginary() && equation->getMaxTerms() > 0) {
        tempInstruction->setCommand(equation->toEquation());
        tempInstruction->setInstruction(IMAGINERY);
        if (this->viewOnly) {
            cout << equation->toEquation() << endl;
        }
        return (true);
    }
    else if (equation->isFunction() && equation->getMaxTerms() > 0) {
        return (this->setupFunction(equation));
    }
    return (false);
}

bool    Instruction::storePrintedValue(polynomial *equation) {
    tempInstruction = new Instruction();

    // Just for now, debugging purposes, will still need to implement better code
    if (equation->getMaxTerms() > 0 && equation->getTerm(0)->isVar()) {
        return (false);
    }
    tempInstruction->setInstruction(equation->getEquationType());
    switch(equation->getEquationType()) {
        case VARIABLE:
                tempInstruction->setFloatValue(equation->getTerm(0)->getCorrectValue());
            break;
        case IMAGINERY:
                tempInstruction->setCommand(equation->toEquation());
        case FUNCTION:
                tempInstruction->setupFunction(equation);
            break;
        default:
            return (false);
            break;
    }
    this->setInstructionData(*tempInstruction, false);
    return (true);
}

bool    Instruction::setEquation(string rhs_string) {
    polynomial *equation = new polynomial();
    Validate validator;

    if (!validator.isPolynomialValid(rhs_string, equation, *this)) {
        cout << "Is not valid polynomial" << endl;
        return (false);
    }
    if (!equation->calculate()) {
        return (false);
    }
    if (this->viewOnly) {
        cout << "Returned from equation :: " << equation->getEquationType() << endl;
        return (this->storePrintedValue(equation));
    }
    return (this->setStoreValue(equation));
}

bool    Instruction::setupMatrix(string rhs_string) {
    Matrix *matrix = new Matrix(rhs_string, *this);

    if (matrix->matrixOk()) {
        cout << "matrix valid" << endl;
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
        tempInstruction->setInstruction(IMAGINERY);
        tempInstruction->setCommand("i");
        return (true);
    }
    else if (Validate::isNumeric(rhs.at(0))) {
        tempInstruction->setInstruction(VARIABLE);
        tempInstruction->setFloatValue(atof(rhs.at(0).c_str()));
        return (true);
    }
    // else if (!rhs.at(0).compare("?")) {
    //     this->isPrint = true;
    //     return (true);
    // }
    // else if (Validate::isValidVariable(rhs.at(0), false) || validator.foundOperator(rhs.at(0)) ||
    //     validator.foundMixedTerm(rhs.at(0))) {
    //     return (this->setEquation(rhs_string));
    // }
    else if (Matrix::isValidMatrix(rhs_string)) {
        return (setupMatrix(rhs_string));
    }
    // else if (Validate::isValidFunction(rhs.at(0))) {
    //     return (this->setEquation(rhs_string));
    // }
    cout << "Got here" << endl;
    return (this->setEquation(rhs_string));
}

bool    Instruction::checkOneFunctionValue(string rhs_string) {
    // cout << "Should print something :: " << rhs_string << endl;
    // if (!rhs_string.compare("?")) {
    //     cout << "Got int to print" << endl;
    //     this->isPrint = true;
    //     return (true);
    // }
    // cout << "Should print something (2)" << endl;
    return (this->setEquation(rhs_string));
}

bool    Instruction::checkRightHandSide(vector<string> rhs, bool isFunction, string rhs_str) {
    if (!isFunction) {
        if (rhs.size() == 1) {
            return (this->checkOneValue(rhs, rhs_str));
        }
        return (this->setEquation(rhs_str));
    }
    // cout << "Function identified (1)" << endl;
    if (rhs.size() == 1) {
        // cout << "RHS is 1" << endl;
        return (this->checkOneFunctionValue(rhs_str));
    }
    // cout << "Finding more instruction" << endl;
    return (this->setEquation(rhs_str));
}

bool    Instruction::prepareForPrint(string str) {
    // cout << "Finding instruction" << endl;
    if (findInstruction(str) == NULL) {
        // cout << "Instruction not found" << endl;
        return (false);
    }
    // cout << "Instruction found" << endl;
    *this = *findInstruction(str);
    this->setMatrix(findInstruction(str)->getMatrix());
    this->setFunction(findInstruction(str)->getFunction());
    this->isPrint = true;
    return (true);
}

bool    Instruction::setVariableData(vector<string> rightInstructions, string str, string rhs) {
    tempInstruction = new Instruction();
    tempInstruction->setInstruction(VARIABLE);

    if (!this->checkRightHandSide(rightInstructions, false, rhs)) {
        return (false);
    }
    // if (this->isPrint) {
    //     return (prepareForPrint(str));
    // }
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
    tempInstruction = new Instruction();
    tempInstruction->setInstruction(FUNCTION);
    string              variableName;

    if (str.compare("?")) {

    }
    if (Matrix::isValidMatrix(rhs_string)) {
        return (false);
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

// bool    Instruction::showEquationValue(string str) {
//     tempInstruction = new Instruction();

//     tempInstruction->setInstruction(VARIABLE);
//     cout << "String value :: " << str << endl;
//     return (this->setEquation(str));
// }

bool    Instruction::sortRightHand(vector<string> leftInstructions, vector<string> rhs) {
    cout << "Left" << endl;
    if (!Validate::isValidVariable(leftInstructions.at(0), true) &&
        !Validate::isValidFunction(leftInstructions.at(0))) {
        return (false);
    }
    if (Validate::isValidVariable(leftInstructions.at(0), true)) {
        return (setVariableData(rhs, leftInstructions.at(0), commands.at(1)));
    }
    else if (Validate::isValidFunction(leftInstructions.at(0))) {
        return (setFunctionData(rhs, leftInstructions.at(0), commands.at(1)));
    }
    return (true);
}

// bool    Instruction::sortLeftHand(vector<string> rhs) {
//     cout << "Sorting left :: instruction.cpp line 279" << endl;
//     if (!rhs.at(0).compare("?")) {
//         this->viewOnly = true;
//         return (showEquationValue(commands.at(0)));
//     }
//     return (true);
// }

bool    Instruction::isViewOnly(string commandString) {
    int cnt = -1;
    int times = 0;
    int len = (int)commandString.length();

    while (++cnt < len) {
        if ((commandString[cnt] == '?') ||
                (times > 0 && (isalpha(commandString[cnt]) && isdigit(commandString[cnt])))) {
            times++;
        }
    }
    return (times == 1);
}

bool    Instruction::showValue(vector<string> lhs, vector<string> rhs) {
    if (lhs.size() > 0) {

    }
    this->viewOnly = true;
    if (rhs.at(rhs.size() - 1).compare("?")) {
        return (false);
    }
    else if (rhs.size() == 1 && !rhs.at(0).compare("?")) {
        if (lhs.size() == 1) {
            cout << "Left is 1 and right is 1:: instruction.cpp line 312" << endl;
            if (this->prepareForPrint(lhs.at(0)) && this->getType() != FUNCTION) {
                return (true);
            }
        }
        return (this->setEquation(commands.at(0)));
    }
    else if (rhs.size() == 2) {

    }
    else {
        cout << "question mark is not at the right place :: instruction.cpp line 312" << endl;
    }
    return (false);
}

bool    Instruction::verifyInstruction() {
    vector<string>  leftInstructions;
    vector<string>  rightInstructions;

    this->viewOnly = false;
    splitString(commands.at(0), ' ', leftInstructions);
    splitString(commands.at(1), ' ', rightInstructions);
    if (leftInstructions.size() == 1 && !this->isViewOnly(commands.at(1))) {
        return (this->sortRightHand(leftInstructions, rightInstructions));
    }
    // else if (rightInstructions.size() == 1 && !this->isViewOnly(commands.at(1))) {
    //     return (this->sortLeftHand(rightInstructions));
    // }
    else if (isViewOnly(commands.at(1))) {
        cout << "Is view only checking values:: instruction.cpp line 333" << endl;
        return (this->showValue(leftInstructions, rightInstructions));
    }
    else {
        cout << "verifyInstruction not implemented as yet:: instruction.cpp line 307" << endl;
    }
    //Still need to check for two either side.
    return (false);
}

void    Instruction::setInstructionData(Instruction data, bool store) {
    Instruction *savedInstruction;
    if ((savedInstruction = findInstruction(data.getInstruction())) != NULL && store) {
        *this = *savedInstruction;
    }
    this->value = data.getValue();
    this->floatValue = data.getfloatValue();
    this->instructionType = data.getType();
    this->instruction = data.getInstruction();
    this->command = data.getCommand();
    this->matrix = data.getMatrix();
    this->function = data.getFunction();
    if (savedInstruction != NULL && store) {
        instructions.erase(instructions.begin() + foundIndex);
    }
    if (store) {
        instructions.push_back(*this);
    }
}

string  Instruction::getCommand() const {
    return (this->command);
}

void	Instruction::splitString(string poly, char deliminator, vector<string> &tempVector) {
	string  temp;
	size_t  pos;

    while ((pos = poly.find("\t")) != string::npos) {
		poly[pos] = ' ';
	}
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
        cout << "Instruction : " << instructions.at(index).getInstruction() << endl;
        //cout << " " << instructions.at(index).getfloatValue() << endl;
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

bool        Instruction::isViewOnly() const {
    return this->viewOnly;
}