#include <iostream>
#include <string>
#include <vector>

using namespace std;

class FormularUnit {
public:
	virtual bool IsChar() = 0;
	virtual double GetDValue() = 0;
	virtual char GetCValue() = 0;
};

class Num : public FormularUnit {
private:
	double _value;
public:
	Num(double c) {
		_value = c;
	}
	double GetDValue() override {
		return _value;
	}
	char GetCValue() override { return ' '; }
	bool IsChar() override { return false; }


};

class Char : public FormularUnit {
private:
	char _value;
public:
	Char(char c) {
		_value = c;
	}
	double GetDValue() override { return 0; }
	char GetCValue() override { return _value; }
	bool IsChar() override { return true; }
	static bool Compare(Char* C1, Char* C2) {
		char c1 = C1->GetCValue();
		char c2 = C2->GetCValue();

		if (c2 == '(') return false;
		if (c2 == ')' || c2 == '+' || c2 == '-') return true;
		if (c1 == '*' || c1 == '/') return true;

		return false;
	}
};

bool isChar(char value) {
	if (value >= 48 && value <= 57) return false;
	if (value == '.') return false;
	return true;
}

bool input(double& retval, char& stopChar) {
    bool beforeNum = false;
    bool beforeDot = false;
    double dotValue = 0;

    retval = 0;

    while (true) {
        char c = getc(stdin);
        if (c == ' ' || c == '\n')
            continue;
        if (isChar(c)) {
            stopChar = c;
            return beforeNum;
        }
        beforeNum = true;
        if (c == '.') {
            beforeDot = true;
            dotValue = 0.1f;
            continue;
        }
        if (dotValue) {
            retval += dotValue * (c - 48);
            dotValue *= 0.1f;
        }
        retval *= 10;
        retval += c - 48;
    }
}

double Calc(double d2, double d1, char op) {
	if (op == '+')
		return d1 + d2;
	if (op == '-')
		return d1 - d2;
	if (op == '*')
		return d1 * d2;
	if (op == '/')
		return d1 / d2;

}

int main() {

	vector<FormularUnit *> formular;
	vector<Char*> chars;

	while (true) {
		double d;
		char c;
		bool numInput = input(d, c);
		if (numInput) formular.push_back(new Num(d));
		if (c == '=') break;

		Char* t1 = new Char(c);
		if (numInput && c == '(') {
			chars.push_back(new Char('*'));
		}
		while (!chars.empty() && Char::Compare(chars.back(), t1)) {
			Char* t = chars.back();
			chars.pop_back();
			if (t->GetCValue() == '(') break;
			formular.push_back(t);
		}
		if (c == ')') continue;
		chars.push_back(t1);

	}

	while (!chars.empty()) {
		formular.push_back(chars.back());
		chars.pop_back();
	}

	vector<FormularUnit*>::iterator iter = formular.begin();
	vector<FormularUnit*> numbers;

	double retval = 0;

	for (; iter != formular.end(); iter++) {
		if ((*iter)->IsChar()) {
			double d1 = numbers.back()->GetDValue();
			numbers.pop_back();
			double d2 = numbers.back()->GetDValue();
			numbers.pop_back();
			
			numbers.push_back(new Num(Calc(d1, d2, (*iter)->GetCValue())));
			continue;
		}
		numbers.push_back(*iter);
	}

	cout << numbers.back()->GetDValue() << endl;

	return 0;
}