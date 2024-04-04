#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct NumChar {

	int value;	// 0 < 정수, -1: +, -2: -, -3: *, -4: /

	struct NumChar *child[2]; // 0: left, 1: right;

};

void SetNC(struct NumChar *ncs, int nodeNum) {
	char str[100];
	char *tok;

	gets(str);
	tok = strtok(str, " ");

	//첫째로 들어온 값이 노드의 value, value가 숫자면 자식 노드는 없음
	if (isdigit(*tok)) {
		ncs[nodeNum].value = atoi(tok);
		ncs[nodeNum].child[0] = NULL;
		ncs[nodeNum].child[1] = NULL;
		return;
	}
	else {
		if (*tok == '+')
			ncs[nodeNum].value = -1;
		else if (*tok == '-')
			ncs[nodeNum].value = -2;
		else if (*tok == '*')
			ncs[nodeNum].value = -3;
		else
			ncs[nodeNum].value = -4;
	}
	tok = strtok(NULL, " ");
	ncs[nodeNum].child[0] = ncs + atoi(tok) - 1;

	tok = strtok(NULL, " ");
	ncs[nodeNum].child[1] = ncs + atoi(tok) - 1;
}

int CalcNC(struct NumChar *mainNC) {

	//노드의 값이 숫자면 바로 리턴, 아니면 자식을 소환후 계산한 값을 리턴
	if (mainNC->value > 0)
		return mainNC->value;
	else {
		int a, b;
		a = CalcNC(mainNC->child[0]);
		b = CalcNC(mainNC->child[1]);
		if (mainNC->value == -1) {
			return a + b;
		}
		else if (mainNC->value == -2) {
			return a - b;
		}
		else if (mainNC->value == -3)
			return a * b;
		else
			return a / b;
	}
}

int main () {

	freopen("input.txt", "r", stdin);
	struct NumChar ncs[1000];
	int n, k;

	scanf("%d", &n);

	for (int a = 0; a < n; a++) {
		scanf("%d", &k);
		printf("Start %d: ", k);
		for (int j = 0; j < k; j++) {
			int i;
			scanf("%d", &i);
			SetNC(ncs, i - 1);
		}
		printf("#%d %d\n", a + 1, CalcNC(ncs));
	}

	return 0;

}