#ifndef VALIDATE_H
#define VALIDATE_H

#include "../computorv.h"

class   Instruction;

class	Validate {
    private:
        void            splitString(string poly);
        void            correctSplit();
        void            splitMixedTerm(string str);
        vector<string>  tempStrings;
        vector<string>  correctStrings;
        bool            checkPolynomialAuthentacity();
        void            splitForAlphaAndDigit(string str);
        void            splitForAlpha(string str);
        void            splitForDigit(string str);
        void            splitForEqualSign(string str);
        void            splitForOperand(string str);
        void            addexpression(polynomial *equation);
        static char     oneVar;
        bool            sameVariables(char *poly);
        bool            foundOperator(string str);
        bool            checkVariables(polynomial *equation, Instruction instruction);

	public:
        Validate(void);
		bool	        isPolynomialValid(string poly, polynomial *equation, Instruction instruction);
        bool            isTermValid(char *term, polynomial *equation, int *termValid);
        static bool     isValidVariable(string str, bool strict);
        static bool     isValidFunction(string str);
        static bool     isNumeric(string str);
};
#endif
