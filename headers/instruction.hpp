#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include "../computorv.h"

using namespace std;

enum    {VARIABLE, MATRIX, FUNCTION, IMAGINERY};

class Instruction {
    private:
        string      value;
        int         instructionType;
    public:
        Instruction();
        string      getValue() const;
        int         getType() const;
        void        setInstruction(int instructionType);
};

#endif