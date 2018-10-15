#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../computorv.h"

using namespace std;

class Matrix {
    private:
        size_t                      rows;
        Instruction                 instruction;
        vector<vector<float> >      values;
        size_t                      cols;
        bool                        colSet;
        string                      rhs_string;
        bool                        isValidMatrixTerm(string str);
        void                        setCol(string str);
        bool                        setValues(string str);

    public:
        Matrix(string rhs_str, Instruction instruction);
        bool                        matrixOk();
        static bool                 isValidMatrix(string str);
        string                      toString();
        float                       getValue(int row, int col);
};

#endif