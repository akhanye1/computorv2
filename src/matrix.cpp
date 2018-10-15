#include "../computorv.h"

bool    Matrix::isValidMatrix(string str) {
    if (str[0] != '[') {
        return (false);
    }
    return (Validate::bracketsOk(str));
}