#include "../computorv.h"

Functions::Functions() {
    cout << "Called functions function" << endl;
}

void    Functions::setVariableName(string name) {
    this->variableName = name;
}

void    Functions::setEquation(polynomial *equation) {
    this->equation = equation;
}

string  Functions::getVariableName() const {
    return this->variableName;
}

string  Functions::toString() {
    return (this->equation->toEquation());
}

float   Functions::getFunctionValue(float tempValue) {
    int maxTerms;
    polynomial  *tempEquation;

    tempEquation = this->equation->makeCopy();

    maxTerms = tempEquation->getMaxTerms();
    cout << "Function >> " << maxTerms << endl;
    if (tempEquation == NULL) {
        cout << "Equation is null" << endl;
    }
    else {
        cout << "Equation is not null" << endl;
    }
    tempEquation->showAll();
    cout << "counter of equation :: " << tempEquation->getMaxTerms() << endl;
    for (int i = 0; i < maxTerms; i++) {
        cout << "Index :: " << i << endl;
        if (tempEquation->getTerm(i)->isVar()) {
            tempEquation->getTerm(i)->replaceVariable(tempValue);
        }
    }
    cout << "FUNCTION POLYNOMIAL" << endl;
    tempEquation->showAll();
    cout << "calculate the value" << endl;
    tempEquation->calculate();
    if (tempEquation->getMaxTerms() == 1) {
        cout << "Is only one" << endl;
        return (tempEquation->getTerm(0)->getCorrectValue());
    }
    else {
        cout << "More than one term" << endl;
    }
    return (1);
}
