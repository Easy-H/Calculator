#include <iostream>

using namespace std;

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

double Calc(double d1, double d2, char op) {
	if (op == '+')
		return d1 + d2;
	if (op == '-')
		return d1 - d2;
	if (op == '*')
		return d1 * d2;
	if (op == '/')
		return d1 / d2;

}

int Calculator(char endChar) {

    double value[3];
    char ch[3];

    bool beforeNum;
    double num;
    while (!input(value[0], ch[0])) {
        if (ch[0] == '(') {
            value[0] = Calculator(')');
            double tmp;
            input(tmp, ch[0]);
            break;
        }
    }
    if (ch[0] == endChar) return value[0];
    input(value[1], ch[1]);

    while (true) {

        if (ch[1] == endChar) {
            value[0] = Calc(value[0], value[1], ch[0]);
            break;

        }
        if (ch[1] == '(') {
            ch[1] = '*';
            value[2] = Calculator(')');
            double tmp;
            input(tmp, ch[2]);
        }
        else {
            if (!input(value[2], ch[2])) {
                if (ch[2] == '(')
                    value[2] = Calculator(')');
                double tmp;
                input(tmp, ch[2]);
            }
        }

        if ((ch[1] == '*' || ch[1] == '/') && (ch[0] == '+' || ch[0] == '-')) {
            value[1] = Calc(value[1], value[2], ch[1]);
            ch[1] = ch[2];
            continue;
        }
        value[0] = Calc(value[0], value[1], ch[0]);
        ch[0] = ch[1];
        value[1] = value[2];
        ch[1] = ch[2];

    }


    return value[0];
}

int main() {

    cout << Calculator('=') << endl;
}