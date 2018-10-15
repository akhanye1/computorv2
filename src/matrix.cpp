#include "../computorv.h"

Matrix::Matrix(string rhs_str, Instruction instruction) {
    this->rhs_string = rhs_str;
    this->instruction = instruction;
    this->colSet = false;
}

bool    Matrix::isValidMatrix(string str) {
    if (str[0] != '[') {
        return (false);
    }
    return (Validate::bracketsOk(str));
}

void    Matrix::setCol(string str) {
    vector<string> temp_array;

    Instruction::splitString(str, ',', temp_array);
    this->cols = temp_array.size();
}

bool    Matrix::setValues(string str) {
    vector<string>  temp_array;
    vector<float>   tempValues;

    // cout << "Starting function" << endl;
    Instruction::splitString(str, ',', temp_array);
    if (this->cols != temp_array.size()) {
        return (false);
    }
    // cout << "Cols temp :: <<" << temp_array.size() << ">> | size <<" << temp_array.size() << ">>" << endl;
    for (size_t i = 0; i < this->cols; i++) {
        // cout << "Trimming string" << endl;
        temp_array[i] = Validate::trimString(temp_array.at(i));
        // cout << "Trimmed String <<" << temp_array[i] << ">>" << endl;
        if (Validate::isNumeric(temp_array.at(i))) {
            //tempValues[i] = atof(temp_array.at(i).c_str());
            tempValues.push_back(atof(temp_array.at(i).c_str()));
            // cout << "Adding value" << tempValues[i] << endl;
        }
        else {
            if (!Validate::isValidVariable(temp_array.at(i), true)) {
                return (false);
            }
            Instruction *tempInstruction = this->instruction.findInstruction(temp_array.at(i));
            if (tempInstruction == NULL) {
                return (false);
            }
            if (tempInstruction->getType() != VARIABLE) {
                return (false);
            }
            tempValues.push_back(tempInstruction->getfloatValue());
        }
    }
    if (tempValues.size() == 0) {
        return (false);
    }
    // cout << "Added vector" << endl;
    this->values.push_back(tempValues);
    return (true);
}

bool    Matrix::isValidMatrixTerm(string str) {
    string tempString = Validate::trimString(str);

    if (tempString[0] != '[' && tempString[tempString.length() - 1] != ']') {
        return (false);
    }
    tempString = tempString.substr(1, tempString.length() - 2);
    if (tempString.find("[") != string::npos || tempString.find("]") != string::npos) {
        return (false);
    }
    if (!this->colSet) {
        this->setCol(tempString);
        this->colSet = true;
    }
    return (this->setValues(tempString));
}

bool    Matrix::matrixOk() {
    vector<string>  str_split;
    string          tempString;

    tempString = rhs_string.substr(1, rhs_string.length() - 2);
    // cout << "Temp String :: " << tempString << endl;
    Instruction::splitString(tempString, ';', str_split);
    this->rows = str_split.size();
    for (size_t i = 0 ; i < this->rows; i++) {
        if (!this->isValidMatrixTerm(str_split.at(i))) {
            return (false);
        }
        // cout << "Line :: " << str_split.at(i) << endl;
    }
    return (true);
}

string  Matrix::toString() {
    stringstream stream;

    stream << "[";
    // cout << "Starting to string funciton" << endl;
    // cout << "Rows from vector <<" << this->values.size() << ">> compared to <<" << this->rows << ">>" << endl;
    for (size_t i = 0; i < this->rows; i++) {
        if (i != 0) {
            stream << ";";
        }
        stream << "[";
        for (size_t x = 0; x < this->cols; x++) {
            if (x != 0) {
                stream << ",";
            }
            stream << this->values[i][x];
        }
        stream << "]";
    }
    stream << "]";
    // cout << "Ending to string funciton" << endl;
    return (stream.str());
}

float   Matrix::getValue(int row, int col) {
    return (this->values.at(row).at(col));
}