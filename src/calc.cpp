#include <string>

int Calculate(std::string input) {
	std::string s1, s2;
	char op;
	bool secn = false;
	for (char c : input) {
		switch (c) {
			case '+': case '-': case '*': case '/':
				op = c;
				secn = true;
				break;
			default:
				if (!secn)
					s1 += c;
				else
					s2 += c;
		}
	}
	int result;
	int n1 = stoi(s1);
	int n2 = stoi(s2);
	switch (op) {
		case '+':
			result = n1 + n2;
			break;
		case '-':
			result = n1 - n2;
			break;
		case '*':
			result = n1 * n2;
			break;
		case '/':
			result = n1 / n2;
	}
	return result;
}
