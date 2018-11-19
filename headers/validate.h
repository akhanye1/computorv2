#ifndef VALIDATE_H
#define VALIDATE_H

#include "../computorv.h"

class   Instruction;

class	Validate {
    private:
        string          unknownVar;
        int             unknownCount;
        bool            isImaginary;
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
        void            splitForClosingBracket(string str);
        void            addexpression(polynomial *equation);
        static char     oneVar;
        bool            sameVariables(char *poly);
        bool            checkVariables(polynomial *equation, Instruction instruction);
        bool            varIsOkay(polynomial *equation, Instruction instruction, int index);
        bool            foundUnknown(polynomial *equation, int index);
        bool            replaceFunctionVar(polynomial *equation, Instruction instructions,
                                int index, term *tempTerm, Instruction *tempInstructions);
        int             findNextOperand(int index);
        bool            isNextOperand(string ch);
        int             addTermForOperand(polynomial *equation, int index, int termSide);
        int             addTermForOpenBracket(polynomial *equation, int index, int termSide,
                            string bracketOperand);
        int             addTermForClosingBracket(polynomial *equation, int index, int termSide);
        bool            isValidExpression(int index);
        bool            isExponentCorrect();
        bool            closePreviousTerm(polynomial *equation, string str);
        void            setAllBracketExponents(polynomial *equation, int expValue, int index);

	public:
        Validate(void);
		bool	        isPolynomialValid(string poly, polynomial *equation, Instruction instruction);
        bool            isTermValid(char *term, polynomial *equation, int *termValid);
        static bool     isValidVariable(string str, bool strict);
        static bool     isValidFunction(string str, bool strict = true);
        static bool     isNumeric(string str);
        bool            foundOperator(string str);
        bool            foundMixedTerm(string str);
        static bool     bracketsOk(string str);
        static string   trimString(string str);
};
#endif
