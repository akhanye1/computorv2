#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include "../computorv.h"

using namespace std;

class Matrix;
class Instruction {
    private:
        vector<string>              commands;
        Instruction                 *tempInstruction;
        string                      value;
        float                       floatValue;
        bool                        isPrint;
        Matrix                      *matrix;
        int                         instructionType;
        bool                        valid;
        string                      command;
        string                      instruction;        
        bool                        verifyInstruction();
        bool                        checkRightHandSide(vector<string> rhs, bool isFunction, string rhs_string);
        bool                        setVariableData(vector<string> instructions, string instr, string rhs);
        bool                        checkOneValue(vector<string> rhs, string rhs_string);
        bool                        setEquation(string rhs_string);
        bool                        setupMatrix(string rhs_string);


    public:
        Instruction();
        Instruction(string str);
        static vector<Instruction>  instructions;
        string                      getValue() const;
        Instruction&                operator=(Instruction const &rhs);
        int                         getType() const;
        void                        setInstruction(int instructionType);
        bool                        isValid() const;
        bool                        compareCommand(string command) const;
        void                        setCommand(string command);
        string                      getInstruction() const;
        Instruction                 *findInstruction(string str);
        float                       getfloatValue() const;
        void                        setFloatValue(float value);
        void                        setInstructionHead(string head);
        void                        setInstructionData(Instruction data);
        string                      getCommand() const;
        bool                        printValue() const;
        void                        showAllInstructions();
        static void                 splitString(string str, char deliminator, vector<string> &tempVector);
        Matrix                      *getMatrix();
};

#endif