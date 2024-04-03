#include <iostream>

using namespace std;

class Node {
private:
    double _num;
    char _oper;
    Node* left;
    Node* right;
public:
    Node(double num) {
        _num = num;
        _oper = '@';
    }
    Node(char oper) {
        _oper = oper;
    }
    ~Node() {
        if (left)
            free(left);
        if (right)
            free(right);
    }
    double GetValue() {
        if (_oper == '@')
            return _num;
        return left->GetValue() + right->GetValue();
    }
    
};

Node* MakeFormular() {

    return new Node(double(3));
}

int main() {

    Node* formular = MakeFormular();

    cout << formular->GetValue() << endl;
    return 0;

}