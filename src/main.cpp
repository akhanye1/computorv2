#include "../computorv.h"

bool	setValue(polynomial *equation, term oneTerm, int index) {
	int		i;
	term	tempTerm;

	i = -1;
	while (++i < equation->counter) {
		tempTerm = equation->getTerm(i);
		if (tempTerm.getSide() > 0) {
			equation->changeSide(oneTerm, index);
			equation->showExpression("Swap term");
			break;
		}
		if (tempTerm.sameAs(oneTerm)) {
			tempTerm.swapTerm(oneTerm);
			equation->moveLeft(tempTerm, i, index);
			equation->showExpression("Swap term");
			break ;
		}
	}
	return (true);
}

bool	reducedOk(polynomial *equation) {
	int		index;
	term	oneTerm;
	int		maxRight;

	index = -1;
	equation->simplifyRight();
	index = -1;
	while (++index < equation->counter) {
		oneTerm = equation->getTerm(index);
		if (oneTerm.getSide() > 0) {
			setValue(equation, oneTerm, index);
			index = -1;
		}
	}
	maxRight = 0;
	index = -1;
	while (++index < equation->counter) {
		if (equation->getTerm(index).getSide() > 0) {
			maxRight++;
		}
	}
	if (maxRight > 0) {
		cout << "Max Right is more that 0 >> " << maxRight << endl;
		return (false);
	}
	equation->showReduced();
	equation->solveExponents(0);
	return (true);
}

int		polynomialDegree(polynomial *equation) {
	int		len;
	term	oneTerm;
	int		polDegree;

	len = -1;
	polDegree = 1;
	while (++len < equation->counter) {
		oneTerm = equation->getTerm(len);
		if (oneTerm.getSide() > 0) {
			return (polDegree);
		}
		if (oneTerm.isExp() &&  oneTerm.getExponent() > polDegree) {
			polDegree = oneTerm.getExponent();
		}
	}
	return (polDegree);
}

void	processInstruction(string str) {
	Instruction *instruction = new Instruction(str);

	if (instruction->isValid()) {
		cout << "OK" << endl;
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
		else {
			processInstruction(input);
		}
	}
	return (0);
}
