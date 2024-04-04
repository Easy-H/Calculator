# Calculator

## 개요
- 다양한 방법으로 계산기를 구현하는 것을 목표로 한다.
- 모든 코드는 다음의 기능을 가지는 계산기를 구현한다.
    - 사칙연산의 순서에 맞게 계산된다.
    - 허용되는 기호는 다음과 같다. 이 외의 기호가 들어온 경우에는 작동이 보장되지 않아도 된다.
        - +: 덧셈
        - -: 뺄셈
        - *: 곱셈
        - /: 나눗셈
        - (): 괄호
    - 괄호를 처리할 수 있다.
    - 숫자 다음 기호 없이 괄호가 온다면 괄호의 내용과 이전의 숫자와는 곱셈을 한다.
        - ex) 2 (5 - 2) = 2 * 3 = 6
- 따라서 모든 계산기는 다음의 식에 올바른 결과를 출력해야 한다.
    - 10 + 2 * (4 - 2) = 14
    - 10 + 2 (4 - 2) = 14

## 개발 환경
- [Visual Studio Code](https://code.visualstudio.com/)
- [g++ 컴파일러](https://www.mingw-w64.org/)

## 구현 코드
- [x] [스택을 이용한 계산기](/code/stack.cpp)
- [x] [재귀를 이용한 계산기](/code/recursive.cpp)
- [x] [트리를 이용한 계산기](/code/tree.cpp)