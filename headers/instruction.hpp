#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include "../computorv.h"

using namespace std;

enum    {VARIABLE, MATRIX, FUNCTION, IMAGINERY};

class Instruction {
    private:
        vector<string>      commands;
        static vector<Instruction> instructions;
        Instruction         tempInstruction;
        string              value;
        float               floatValue;
        int                 instructionType;
        bool                valid;
        string              command;
        string              instruction;
        void                splitString(string str, char deliminator, vector<string> &tempVector);
        bool                verifyInstruction();
        bool                checkRightHandSide(vector<string> rhs, bool isFunction);


    public:
        Instruction();
        Instruction(string str);
        string              getValue() const;
        int                 getType() const;
        void                setInstruction(int instructionType);
        bool                isValid() const;
        bool                compareCommand(string command) const;
        void                setCommand(string command);
        string              getInstruction() const;
        Instruction         findInstruction(string str);
        float               getfloatValue() const;
};

#endif