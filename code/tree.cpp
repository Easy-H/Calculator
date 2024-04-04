#include <iostream>

using namespace std;

double Calc(double d1, double d2, char ch);

class INode {
public:
    INode* left;
    INode* right;
    char _oper = '@';
    bool used;
    bool calced;
    virtual double GetValue() = 0;
    void SetNode(INode* l, INode* r) {
        left = l;
        right = r;
        left->used = true;
        right->used = true;
        calced = true;
    }
};

class NodeNode : public INode{
private:
    INode* value;
public:
    NodeNode(INode* input) {
        value = input;
        used = false;
        left = NULL;
        right = NULL;
        _oper = '@';
    }
    ~NodeNode() {
        free(value);
    }
    double GetValue() {
        return value->GetValue();
    }
};

class Node : public INode {
public:
    double _num;
    Node(double num) {
        _num = num;
        used = false;
        left = NULL;
        right = NULL;
        _oper = '@';
    }
    Node(char oper) {
        _oper = oper;
        calced = false;
        used = false;
        left = NULL;
        right = NULL;
    }
    ~Node() {
        if (left)
            free(left);
        if (right)
            free(right);
    }
    double GetValue() override{
        if (_oper == '@') {
            return _num;
        }
        return Calc(left->GetValue(), right->GetValue(), _oper);
    }
    
};

bool isChar(char value);
bool input(double& retval, char& stopChar);

void AddNode(INode* &root, INode* insert);
INode* MakeFormular(char endChar);

int main() {

    INode* formular = MakeFormular('=');
    cout << formular->GetValue() << endl;
    return 0;

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
			continue;
        }
        retval *= 10;
        retval += c - 48;
    }
}

void AddNode(INode* &root, INode* insert) {
    if (root == NULL) {
        root = insert;
        return;
    }
    INode* tmp = root;
    while (tmp->right) {
        tmp = tmp->right;
    }
    tmp->right = insert;
    insert->left = tmp;
}

INode* MakeFormular(char endChar) {
    INode* root = NULL;
    while (true) {
        double d;
        char c;
        bool b = input(d, c);
        if (b) {
            Node* tmp = new Node(d);
            AddNode(root, tmp);
        }
        if (c == endChar)
            break;
        if (c == '(') {
            if (b) {
                Node* tp = new Node('*');
                AddNode(root, tp);
            }
            INode* t = MakeFormular(')');
            NodeNode* tmp = new NodeNode(t);
            AddNode(root, tmp);
            continue;
        }
        Node* t = new Node(c);
        AddNode(root, t);
    }
    int size = 0;
    INode* tmp = root;
    while (tmp) {
        tmp = tmp->right;
        size++;
    }
    INode** arr = new INode*[size];
    tmp = root;
    for (int i = 0; i < size; i++) {
        arr[i] = tmp;
        tmp = tmp->right;
    }
    INode* last = root;
    for (int i = 0; i < size; i++) {
        INode* t = arr[i];
        if (t->calced) {
            continue;
        }
        if (t->_oper == '@' || t->_oper == '+' || t->_oper == '-')
            continue;

        int le, ri;
        for (le = i - 1; le >= 0 && arr[le]->used; le--);
        for (ri = i + 1; ri < size && arr[ri]->used; ri++);
        
        t->SetNode(arr[le], arr[ri]);
        last = t;
        
    }
    for (int i = 1; i < size; i++) {
        INode* t = arr[i];
        if (t->calced || t->used) {
            continue;
        }
        if (t->_oper == '@' || t->_oper == '*' || t->_oper == '/')
            continue;
        int le, ri;
        for (le = i - 1; le >= 0 && arr[le]->used; le--);
        for (ri = i + 1; ri < size && arr[ri]->used; ri++);
        
        t->SetNode(arr[le], arr[ri]);
        last = t;
    }
    return last;
}