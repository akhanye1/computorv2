#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <vector>
#include "term.h"
#include <unistd.h>
#include <sstream>

using namespace std;

enum    {VARIABLE, MATRIX, FUNCTION, IMAGINERY};

class polynomial {
    private:
        vector<term>    terms;
        void            solveByOrder(int start, char check);
        void            moveRight(int index);
        float           getA();
        float           getB();
        float           getC();
        void            solveSquareRoot();
        static bool     debug;
        int             equaitonType;

    public:
        polynomial(void);
        bool            addTerm(term *Term);
        void            toString(void);
        term            *getTerm(int index);
        void            moveLeft(term tempTerm, int changeIndex, int removeIndex);
        void            changeSide(term tempTerm, int index);
        static int      counter;
        void            showReduced();
        void            simplifyRight();
        void            showAll();
        void            bodmasRule(int start);
        void            solveExponents(int start);
        void            solveExpression();
        void            showExpression(string explainLine);
        void            addRemaining(int index);
        void            solveQuadradic();
        void            multiplyVariables();
        void            debugOn();
        bool            isDebug();
        void            calculate();
        int             getEquationType() const;
        bool            isImaginary();
        string          toEquation();
};
#endif
