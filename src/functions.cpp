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

    maxTerms = equation->getMaxTerms();
    cout << "Function >> " << maxTerms << endl;
    if (this->equation == NULL) {
        cout << "Equation is null" << endl;
    }
    else {
        cout << "Equation is not null" << endl;
    }
    equation->showAll();
    cout << "counter of equation :: " << equation->getMaxTerms() << endl;
    for (int i = 0; i < maxTerms; i++) {
        cout << "Index :: " << i << endl;
        if (this->equation->getTerm(i)->isVar()) {
            this->equation->getTerm(i)->replaceVariable(tempValue);
        }
    }
    cout << "FUNCTION POLYNOMIAL" << endl;
    equation->showAll();
    cout << "calculate the value" << endl;
    equation->calculate();
    if (equation->getMaxTerms() == 1) {
        cout << "Is only one" << endl;
        return (equation->getTerm(0)->getCorrectValue());
    }
    else {
        cout << "More than one term" << endl;
    }
    return (1);
}
