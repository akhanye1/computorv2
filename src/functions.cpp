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
