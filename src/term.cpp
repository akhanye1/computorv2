#include "../computorv.h"

int term::priorityLevel = 0;
int term::maxPriority = 0;

term::term(int termSide) {
    this->isConstant = false;
    this->isVariable = false;
    this->isExponent = false;
    this->termSide = termSide;
}

term::term(void) {
    this->isConstant = false;
    this->isVariable = false;
    this->isExponent = false;
    this->termSide = 0;
}

term::term(term const & rhs) {
    *this = rhs;
}

term    & term::operator=(term const & rhs) {
    this->constant = rhs.getConstant();
    this->variable = rhs.getVariable();
    this->exponent = rhs.getExponent();
    this->isConstant = rhs.isConst();
    this->isVariable = rhs.isVar();
    this->isExponent = rhs.isExp();
    this->order = rhs.getOrder();
    this->operand = rhs.getOperand();
    this->termSide = rhs.getSide();
    return (*this);
}

char    term::getOrder() const { return (this->order); }

bool    alphaFound(string str) {
    int index = -1;

    while (++index < (int)str.length()) {
        if (isalpha(str[index]) || str[index] == '^') {
            return (true);
        }
    }
    return (false);
}

int     returnAlphaIndex(string str) {
    int index = -1;

    while (++index < (int)str.length()) {
        if (isalpha(str[index]) || str[index] == '^') {
            return (index);
        }
    }
    return (0);
}

bool    numberFound(string str) {
    int index = -1;

    while (++index < (int)str.length()) {
        if (isdigit(str[index]) || str[index] == '^') {
            return (true);
        }
    }
    return (false);
}

void    term::fillTerm(string str) {
    string tempString;

    if (isdigit(str[0])) {
        if (str.find("^") != string::npos) {
            tempString = str.substr(0, str.find("^"));
            this->constant = atof(tempString.c_str());
            this->isConstant = true;
            return (fillTerm(str.substr(str.find("^"))));
        }
        this->constant = atof(str.c_str());
        this->isConstant = true;
    }
    else if (isalpha(str[0])) {
        if (str.find("^") != string::npos) {
            this->isVariable = true;
            this->variable = str.substr(0, str.find("^"));
            return (fillTerm(str.substr(str.find("^"))));
        }
        this->variable = str;
        this->isVariable = true;
    }
    else if (str[0] == '^') {
        if (str[1]) {
            tempString = str.substr(1);
            this->exponent = atoi(tempString.c_str());
            this->isExponent = true;
        }
    }
    if (this->isVariable && !this->isConstant) {
        this->isConstant = true;
        this->constant = 1;
    }
}

term::term(string str, char operand, int termSide) {
    this->isConstant = false;
    this->isVariable = false;
    this->isExponent = false;
    this->termSide = termSide;
    this->operand = operand;
    this->order = priorityLevel;
    this->afterBracket = false;
    fillTerm(str);
}

void    term::replaceTerm(term tempTerm) {
    this->constant = tempTerm.getConstant();
    this->variable = tempTerm.getVariable();
    this->exponent = tempTerm.getExponent();
    this->operand = tempTerm.getOperand();
    this->termSide = tempTerm.getSide();
    this->isConstant = tempTerm.isConst();
    this->isVariable = tempTerm.isVar();
    this->isExponent = tempTerm.isExp();
}

void    term::matchTerm(term rhs) {
    if (rhs.isVar()) {
        this->isVariable = true;
        this->variable = rhs.getVariable();
    }
    if (rhs.isExp()) {
        this->isExponent = true;
        this->exponent = rhs.getExponent();
    }
}

bool    term::setConstant(float constant) {    
    this->constant = constant;
    this->isConstant = true;
    return (true);
}

float   getRealValue(term tempTerm) {
    return (tempTerm.getOperand() == '-') ? (-1 * tempTerm.getConstant()) : tempTerm.getConstant();
}

float   getRightValueConstant(term rightValue) {
    return (-1 * rightValue.getCorrectValue());
}

void    term::addConstant(term rightConstant, term leftConstant) {
    if (rightConstant.getOperand() == '+' || rightConstant.getOperand() == '-') {
        this->constant = (-1 * getRealValue(rightConstant)) + getRealValue(leftConstant);
        this->operand = (this->constant > 0) ? '+' : '-';
        this->constant = (this->constant > 0) ? this->constant : (-1 * this->constant);
    }
}

void    term::addVariable(term rightVariable, term leftVariable) {
    if (!rightVariable.isConst()) {
        rightVariable.setConstant(0);
    }
    if (!leftVariable.isConst()) {
        leftVariable.setConstant(0);
    }
    this->addConstant(rightVariable, leftVariable);
}

bool    term::setVariable(char variable) {
    this->variable = variable;
    this->isVariable = true;
    return (true);
}

bool    term::setExponent(int exponent) {
    this->exponent = exponent;
    this->isExponent = true;
    return (true);
}

void    term::addExponent(int rightExponent, int leftExponent) {
    this->exponent = rightExponent - leftExponent;
}

void    term::setSide(int side) {
    this->termSide = side;
}

bool    term::setOperand(char operand) {
    this->operand = operand;
    return (true);
}

bool    term::isVar() const { return (this->isVariable); }
bool    term::isConst() const { return (this->isConstant); }
bool    term::isExp() const { return (this->isExponent); }

void    term::toString() {
    cout << "Signage " << this->operand << " ";
    if (this->isConst()) {
        cout << "Term has const with value " << this->constant << " ";
    }
    if (this->isVar()) {
        cout << "Term has variable with variable " << this->variable << " ";
    }
    if (this->isExp()) { 
        cout << "Term has exponent " << this->exponent << " ";
    }
    if (this->termSide == 0) {
        cout << "Left hand side";
    } else {
        cout << "Right hand side";
    }
    cout << " Side : (" << this->termSide << ") ";
    cout << " | Priority : " << this->order << endl;
}

float   term::getConstant() const { return (this->constant); }
string  term::getVariable() const { return (this->variable); }
char    term::getOperand() const { return (this->operand); }
int     term::getSide() const { return (this->termSide); }
int     term::getExponent() const { return (this->exponent); }

bool    term::sameAs(term compareTerm) {
    if (this->isVar() == compareTerm.isVar() &&
        this->isExp() == compareTerm.isExp()) {
        if (this->isExponent) {
            if (this->exponent != compareTerm.getExponent()) {
                return (false);
            }
        }
        if (compareTerm.getOperand() == '+' || compareTerm.getOperand() == '-' ) {
            return (this->operand == '+' || this->operand == '-');
        }
        else {
            return (this->operand == '*' || this->operand == '/');
        }
    }
    return (false);
}

bool    term::addTerm(term addTerm) {
    float temp1, temp2, tempSum;

    temp1 = this->constant;
    temp2 = addTerm.getCorrectValue();
    if (addTerm.getOperand() == '+' || addTerm.getOperand() == '-') {
        if (this->sameAs(addTerm)) {
            tempSum = temp1 + temp2;
            this->setConstant(tempSum);
            return (true);
        }
    }
    else {
        if (this->isVariable && addTerm.isVar()) {
            if (this->exponent != addTerm.getExponent()) {
                return (false);
            }
        }
        tempSum = (addTerm.getOperand() == '*') ? temp1 * temp2 : temp1 / temp2;
        this->setConstant(tempSum);
        matchTerm(addTerm);
        return (true);
    }
    return (false);
}

void    term::removeVariable() {
    this->isVariable = false;
    this->isExponent = false;
}

void    term::swapTerm(term addTerm) {
    float   temp1, temp2, tempSum;
    char    constant;

    temp1 = getCorrectValue();
    temp2 = getRightValueConstant(addTerm);
    tempSum = 0;
    if (addTerm.getOperand() == '+' || addTerm.getOperand() == '-') {
        if (this->sameAs(addTerm)) {
            tempSum = temp1 + temp2;
            if (tempSum < 0) {
                this->setOperand('-');
                tempSum = -1 * tempSum;
                this->setConstant(tempSum);
            }
            else {
                this->setOperand('+');
                this->setConstant(tempSum);
            }
            return ;
        }
    }
    else {
        constant = (addTerm.getConstant() == '*') ? '/' : '*';
        tempSum = (constant == '*') ? temp1 * temp2 : temp1 / temp2;
        this->setConstant(tempSum);
        return ;
    }
}

float   term::getCorrectValue() const {
    return (getRealValue(*this));
}

void    term::replaceVariable(float value) {
    this->isVariable = false;
    this->isConstant = true;
    this->constant = value;
}

void    term::updatePriority(char bracketType) {
    if (bracketType == '(') {
        priorityLevel++;
        maxPriority++;
        return ;
    }
    priorityLevel--;
}

void    term::setAfterBracket() {
    this->afterBracket = true;
}

void    term::setOperatorBracket(char bracketOperator) {
    this->bracketOperator = bracketOperator;
}

bool    term::isAfterBracket() {
    return (this->afterBracket);
}

char    term::getBracketOperator() {
    return (this->bracketOperator);
}