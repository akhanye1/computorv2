#include "../computorv.h"

int polynomial::counter = 0;
bool polynomial::debug = false;

bool    polynomial::addTerm(term *termVal) {
    this->terms.push_back(*termVal);
    polynomial::counter++;
    return (true);
}

void    polynomial::debugOn() {
    debug = true;
}

bool    polynomial::isDebug() {
    return (debug);
}

term        polynomial::getTerm(int index) {
    return (this->terms.at(index));
}

void        polynomial::changeSide(term tempTerm, int index) {
    char    tempOperand;

    if (tempTerm.getOperand() == '+' || tempTerm.getOperand() == '-') {
        tempOperand = (tempTerm.getOperand() == '+') ? '-' : '+';
    }
    else {
        tempOperand = (tempTerm.getOperand() == '*') ? '/' : '*';
    }
    tempTerm.setOperand(tempOperand);
    tempTerm.setSide(0);
    this->terms.at(index).replaceTerm(tempTerm);
}

void        polynomial::moveLeft(term tempTerm, int changeIndex, int removeIndex) {
    this->terms.at(changeIndex).replaceTerm(tempTerm);
    this->terms.erase(this->terms.begin() +  removeIndex);
    polynomial::counter--;
}

void        polynomial::toString(void) {
    term oneTerm;

    for (int x = 0; x < polynomial::counter; x++) {
        oneTerm = this->terms.at(x);
        oneTerm.toString();
    }
}

void        polynomial::showReduced(void) {
    cout << "Reduced from : ";
    for (int x = 0; x < polynomial::counter; x++) {
        if (x > 0 || (x == 0 && this->terms.at(x).getOperand() == '-')) {
            cout << this->terms.at(x).getOperand() << " ";
        }
        if (this->terms.at(x).isConst()) {
            if ((this->terms.at(x).getConstant() == 1 && this->terms.at(x).isVar()) ||
                (this->terms.at(x).getConstant() == 0 && this->terms.at(x).isVar())) {

            }
            else {
                cout << this->terms.at(x).getConstant();
            }
        }
        if (this->terms.at(x).isVar()) {
            cout << this->terms.at(x).getVariable();
        } 
        if (this->terms.at(x).isExp()) {
            cout << "^" << this->terms.at(x).getExponent();
        }
        cout << " ";
    }
    cout << "= 0" << endl;
}

polynomial::polynomial(void) {
    polynomial::counter = 0;
}

void    polynomial::simplifyRight() {
    int     index = -1;

    while (++index < counter && this->terms.at(index).getSide() == 0);
    if (index == counter) {
        return;
    }
    bodmasRule(index);
    showExpression("After reducing right side");
}

float   power(float number, int exponent) {
    float sum;

    sum = number;
    while (--exponent > 0) {
        sum = sum * number;
    }
    return (sum);
}

void    polynomial::solveExponents(int start) {
    int     tempNumber;
    float   number;
    int     exponent;

    while (start < counter) {
        if (this->terms.at(start).getConstant() == 0 && this->terms.at(start).isVar()) {
            this->terms.erase(this->terms.begin() + start);
            counter--;
            return (solveExponents(start));
        }
        if (this->terms.at(start).isExp()) {
            if (this->terms.at(start).isVar() && this->terms.at(start).getExponent() == 0) {
                this->terms.at(start).removeVariable();
                tempNumber = this->terms.at(start).getConstant() * 1;
                this->terms.at(start).setConstant(tempNumber);
            }
            else if (!this->terms.at(start).isVar()) {
                number = this->terms.at(start).getConstant();
                exponent = this->terms.at(start).getExponent();
                tempNumber = power(number, exponent);
                this->terms.at(start).removeVariable();
                this->terms.at(start).setConstant(tempNumber);
            }
        }
        start++;
    }
}

void    polynomial::solveByOrder(int start, char check) {
    if (start >= counter) {
        return ;
    }
    while (start < counter) {
        if (this->terms.at(start).getOperand() == check) {
            if (this->terms.at(start - 1).addTerm(this->terms.at(start))) {
                moveLeft(this->terms.at(start - 1), start - 1, start);
                return (solveByOrder(start, check));
            }
        }
        start++;
    }
}

void    polynomial::bodmasRule(int start) {
    solveExponents(start);
    solveByOrder(start + 1, '/');
    solveByOrder(start + 1, '*');
    solveByOrder(start + 1, '+');
    solveByOrder(start + 1, '-');
    solveExponents(start);
}

void    polynomial::showAll() {
    int index = -1;

    cout << "START START START" << endl;
    while (++index < counter) {
        this->getTerm(index).toString();
    }
    cout << "END END END" << endl;
}

void    polynomial::moveRight(int index) {
    char    operand;

    operand = this->terms.at(index).getOperand() == '+' ? '-' : '+';
    this->terms.at(index).setOperand(operand);
    this->terms.at(index).setSide(1);
}

term    *getEmptyTerm() {
    term *temp = new term("0", '+', 0);
    return (temp);    
}

void    polynomial::solveExpression() {
    term    *varTerm;
    term    *rightTerm;
    float   tempVal;

    rightTerm = varTerm = NULL;
    if (this->counter == 1) {
        this->addTerm(getEmptyTerm());
    }
    if (this->terms.at(0).isVar()) {
        moveRight(1);
        varTerm = &this->terms.at(0);
        rightTerm = &this->terms.at(1);
    }
    else if (this->terms.at(1).isVar()) {
        moveRight(0);
        varTerm = &this->terms.at(1);
        rightTerm = &this->terms.at(0);
    }
    else {
        if (this->terms.at(0).getConstant() == this->terms.at(1).getConstant()) {
            cout << "All the real numbers are solutions" << endl;
            return ;
        }
        else if (this->terms.at(1).getConstant() == 0) {
            cout << "Cannot solve expression" << endl;
            return ;
        }
        else {
            cout << "Error solving expression" << endl;
            return ;
        }
    }
    showExpression("move to right side");    
    tempVal = rightTerm->getCorrectValue() / varTerm->getCorrectValue();
    varTerm->setConstant(varTerm->getCorrectValue()/ varTerm->getCorrectValue());
    varTerm->setOperand('+');
    rightTerm->setConstant(tempVal);
    if (rightTerm->getConstant() >= 0) {
        rightTerm->setOperand('+');
    }
    else {
        rightTerm->setOperand('-');
    }
    showExpression("Divide both sides");    
    cout << "The solution is:" << endl;
    cout << tempVal << endl;
}

void    printTerm(term printTerm) {
    cout << printTerm.getOperand() << " ";
    if (printTerm.getOperand() == '-' && printTerm.getConstant() < 0) {
        cout << (-1 * printTerm.getConstant());
    }
    else {
        cout << printTerm.getConstant();
    }
    if (printTerm.isVar()) {
        cout << printTerm.getVariable();
    }
    if (printTerm.isExp()) {
        cout << "^" << printTerm.getExponent();
    }
    cout << " ";
}

void    polynomial::showExpression(string explainLine) {
    int     index = -1;
    int     foundRight = false;

    if (!debug) {
        return ;
    }
    while (++index < counter) {
        if (this->terms.at(index).getSide() == 0) {
            printTerm(this->terms.at(index));
        }
        else {
            foundRight = true;
        }
    }
    if (!foundRight) {
        cout << " = 0";
        if (debug) {
            cout << "\t" << explainLine << endl;
        }
        else {
            cout << endl;
        }
        return ;
    }
    cout << " = ";
    index = -1;
    while (++index < counter) {
        if (this->terms.at(index).getSide() == 1) {
            printTerm(this->terms.at(index));
        }
    }
    if (debug) {
        cout << "\t" << explainLine << endl;
    }
    else {
        cout << endl;
    }
}

void    polynomial::addRemaining(int index) {
    int i;

    i = index;
    while (++i < counter) {
        if (this->terms.at(index).sameAs(this->terms.at(i))) {
            this->terms.at(index).addTerm(this->terms.at(i));
            moveLeft(this->terms.at(index), index, i);
            return (addRemaining(index));
        }
    }
    if (index < counter) {
        return (addRemaining(index + 1));
    }
}

float   polynomial::getA() {
    int index = -1;
    while (++index < counter) {
        if (this->terms.at(index).isExp() && this->terms.at(index).getExponent() == 2) {
            return (this->terms.at(index).getCorrectValue());
        }
    }
    return (0);
}

float   polynomial::getB() {
    int index = -1;
    while (++index < counter) {
        if (this->terms.at(index).isExp() && this->terms.at(index).isVar() && this->terms.at(index).getExponent() == 1) {
            return (this->terms.at(index).getCorrectValue());
        }
    }
    return (0);
}

float   polynomial::getC() {
    int index = -1;
    while (++index < counter) {
        if (!this->terms.at(index).isVar()) {
            return (this->terms.at(index).getCorrectValue());
        }
    }
    return (0);
}

float   squareRoot(float goal) {
    float minus, ans, sub;
    int   counter;

    if (goal < 0) {
        goal = -1 * goal;
    }
	ans = minus = (goal / 2);
	sub = 1;
    counter = 1;
    while (ans > 0) {
        ans = minus * minus;
        if (ans == goal) {
            return (minus);
        }
        else if (ans < goal) {
            counter = 11;
            minus += sub;
            sub /= 10;
            if (sub < 0.000000000000001)
                return (minus);
        }
        else if (counter < 0 && sub < 1) {
            return (minus);
        }
        counter--;
        minus -= sub;
		}
	return (1);
}

void    showPositiveNegativeDiscriminant(float a, float b, float discriminant, string name) {
    float sol1, sol2, sqroot;
    
    cout << "Discriminant is strickly " << name << " , the two " << name << " are" << endl;
    sqroot = squareRoot(discriminant);
    sol1 = ((-1 * b) + sqroot) / (2 * a);
    sol2 = ((-1 * b) - sqroot) / (2 * a);
    cout << sol1 << endl;
    cout << sol2 << endl;
}

void    showZeroDiscriminant(float a, float b, float discriminant) {
    float sol1;
    
    cout << "Discriminant is strickly zero, the solutions is" << endl;
    sol1 = ((-1 * b) + discriminant) / (2 * a);
    cout << sol1 << endl;
}

void    polynomial::solveSquareRoot() {
    term    *varTerm, *rightTerm;
    float   tempVal;

    varTerm = rightTerm = NULL;
    if (counter == 1) {
        this->addTerm(getEmptyTerm());
    }
    if (this->terms.at(0).isVar()) {
        moveRight(1);
        varTerm = &this->terms.at(0);
        rightTerm = &this->terms.at(1);
    }
    else {
        moveRight(0);
        varTerm = &this->terms.at(1);
        rightTerm = &this->terms.at(0);
    }
    showExpression("move constant to right hand side");    
    tempVal = rightTerm->getCorrectValue() / varTerm->getCorrectValue();
    varTerm->setConstant(varTerm->getCorrectValue()/ varTerm->getCorrectValue());
    varTerm->setOperand('+');
    rightTerm->setConstant(tempVal);
    if (rightTerm->getConstant() >= 0) {
        rightTerm->setOperand('+');
    }
    else {
        rightTerm->setOperand('-');
    }
    showExpression("Divide both sides");
    cout << "The solution is:" << endl;
    cout << "+-" << squareRoot(tempVal) << endl;
    return ;
}

void    polynomial::solveQuadradic() {
    float a, b, c, discriminant;

    a = b = c = 0;
    a = getA();
    b = getB();
    c = getC();
    if (debug) {
        cout << "A : " << a << " | B : " << b << " | c : " << c << endl;
    }
    if (b == 0 && a > 0) {
        return (solveSquareRoot());
    }
    discriminant = power(b, 2) - (4 * a * c);
    if (debug) {
        cout << "Discriminant value is : " << discriminant << endl;
    }
    if (discriminant > 0) {
        showPositiveNegativeDiscriminant(a, b, discriminant,"positive");
    }
    else if (discriminant < 0) {
        showPositiveNegativeDiscriminant(a, b, discriminant,"negative");
    }
    else if (discriminant == 0) {
        showZeroDiscriminant(a, b, discriminant);
    }
}

void    polynomial::multiplyVariables() {
    int     index = 0;

    while (++index < counter) {
        if (this->terms.at(index).getSide() == 0 && this->terms.at(index).isVar()) {
            if (this->terms.at(index).getOperand() == '*' ||
            this->terms.at(index).getOperand() == '/') {
                if (this->terms.at(index - 1).addTerm(this->terms.at(index))) {
                    moveLeft(this->terms.at(index - 1), index - 1, index);
                    return (multiplyVariables());
                }
            }
        }
    }
    index = 0;
    while (++index < counter) {
        if (this->terms.at(index).getSide() == 1 && this->terms.at(index).isVar() &&
        this->terms.at(index - 1).getSide() == 1) {
            if (this->terms.at(index).getOperand() == '*' ||
            this->terms.at(index).getOperand() == '/') {
                if (this->terms.at(index - 1).addTerm(this->terms.at(index))) {
                    moveLeft(this->terms.at(index - 1), index - 1, index);
                    return (multiplyVariables());
                }
            }
        }
    }
    showExpression("Multipliying variables with constants");
}
