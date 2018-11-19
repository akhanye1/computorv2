#include "../computorv.h"

// bool	setValue(polynomial *equation, term oneTerm, int index) {
// 	int		i;
// 	term	tempTerm;
// 	int		maxTerms = equation->getMaxTerms();

// 	i = -1;
// 	while (++i < maxTerms) {
// 		tempTerm = *equation->getTerm(i);
// 		if (tempTerm.getSide() > 0) {
// 			equation->changeSide(oneTerm, index);
// 			equation->showExpression("Swap term");
// 			break;
// 		}
// 		if (tempTerm.sameAs(oneTerm)) {
// 			tempTerm.swapTerm(oneTerm);
// 			equation->moveLeft(tempTerm, i, index);
// 			equation->showExpression("Swap term");
// 			break ;
// 		}
// 	}
// 	return (true);
// }

// bool	reducedOk(polynomial *equation) {
// 	int		index;
// 	term	oneTerm;
// 	int		maxRight;
// 	int		maxTerms = equation->getMaxTerms();

// 	index = -1;
// 	equation->simplifyRight();
// 	index = -1;
// 	while (++index < maxTerms) {
// 		oneTerm = *equation->getTerm(index);
// 		if (oneTerm.getSide() > 0) {
// 			setValue(equation, oneTerm, index);
// 			index = -1;
// 		}
// 	}
// 	maxRight = 0;
// 	index = -1;
// 	while (++index < maxTerms) {
// 		if (equation->getTerm(index)->getSide() > 0) {
// 			maxRight++;
// 		}
// 	}
// 	if (maxRight > 0) {
// 		cout << "Max Right is more that 0 >> " << maxRight << endl;
// 		return (false);
// 	}
// 	equation->showReduced();
// 	equation->solveExponents(0);
// 	return (true);
// }

// int		polynomialDegree(polynomial *equation) {
// 	int		len;
// 	term	oneTerm;
// 	int		polDegree;
// 	int		maxTerms = equation->getMaxTerms();

// 	len = -1;
// 	polDegree = 1;
// 	while (++len < maxTerms) {
// 		oneTerm = *equation->getTerm(len);
// 		if (oneTerm.getSide() > 0) {
// 			return (polDegree);
// 		}
// 		if (oneTerm.isExp() &&  oneTerm.getExponent() > polDegree) {
// 			polDegree = oneTerm.getExponent();
// 		}
// 	}
// 	return (polDegree);
// }

void	processInstruction(string str) {
	Instruction *instruction = new Instruction(str);

	if (instruction->isValid()) {
		if (!instruction->isShowAnswer()) {
			return ;
		}
		switch (instruction->getType()) {
			case VARIABLE:
					// cout << "VARIABLE" << endl;
					cout << instruction->getfloatValue() << endl;
				break;
			case IMAGINERY:
					// cout << "IMAGINARY" << endl;
					cout << instruction->getCommand() << endl;
				break;
			case MATRIX:
					// cout << "MATRICES" << endl;
					cout << instruction->getMatrix()->toString() << endl;
				break;
			case FUNCTION:
					// cout << "FUNCTION" << endl;
					cout << instruction->getFunction()->toString() << endl;
				break;
		}
	}
	else {
		cout << "Instruction not valid" << endl;
	}
}

int		main(void) {
	string	input;
	bool	proceed = true;
	
	while (proceed) {
		cout << "> ";
		getline(cin, input);
		if (!input.compare("exit")) {
			proceed = false;
		}
		else if (!input.compare("showAll")) {
			Instruction::showAllInstructions();
		}
		else {
			processInstruction(input);
		}
	}
	return (0);
}
