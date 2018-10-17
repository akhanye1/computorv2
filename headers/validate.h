#ifndef VALIDATE_H
#define VALIDATE_H

#include "../computorv.h"

class   Instruction;

class	Validate {
    private:
        void            splitString(string poly);
        void            correctSplit();
        int             lastIndexOfAlpha(string str);
        int             lastIndexOfFloat(string str);
        void            splitMixedTerm(string str);
        vector<string>  tempStrings;
        vector<string>  correctStrings;
        bool            checkPolynomialAuthentacity();
        void            splitForAlphaAndDigit(string str);
        void            splitForAlpha(string str);
        void            splitForDigit(string str);
        void            splitForEqualSign(string str);
        void            splitForOneChar(string str);
        void            addexpression(polynomial *equation);
        static char     oneVar;
        bool            sameVariables(char *poly);
        bool            checkVariables(polynomial *equation, Instruction instruction);

	public:
        Validate(void);
		bool	        isPolynomialValid(string poly, polynomial *equation, Instruction instruction);
        bool            isTermValid(char *term, polynomial *equation, int *termValid);
        static bool     isValidVariable(string str, bool strict);
        static bool     isValidFunction(string str);
        static bool     isNumeric(string str);
        bool            foundOperator(string str);
        bool            foundMixedTerm(string str);
        static bool     bracketsOk(string str);
        static string   trimString(string str);
};
#endif
