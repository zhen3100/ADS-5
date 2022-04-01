// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"


int priority(char ch) {
    if (ch == '(') {
        return 1;
    }
    if (ch == '+' || ch == '-') {
        return 2;
    }
    if (ch == '*' || ch == '/') {
        return 3;
    }
    return -1;
}
std::string infx2pstfx(std::string inf) {
  TStack <char, 100> stack1;
    std::string post;
    for (int i = 0; i < inf.size(); i++) {
        int pr = priority(inf[i]);
        if ((priority(inf[i]) == -1) && (inf[i] != ')')) {
            if (!post.empty() && priority(inf[i - 1]) != -1) {
                post.push_back(' ');
            }
            post.push_back(inf[i]);

        } else if ((priority(inf[i]) > priority(stack1.get()))
                   || (stack1.isEmpty()) || (inf[i] == '(')) {
            stack1.push(inf[i]);
        } else {
            if (inf[i] == ')') {
                while (stack1.get() != '(') {
                    post.push_back(' ');
                    post.push_back(stack1.get());
                    stack1.pop();
                }
                stack1.pop();
            } else {
                while (priority(stack1.get()) >= priority(inf[i])) {
                    post.push_back(' ');
                    post.push_back(stack1.get());
                    stack1.pop();
                }
                stack1.push(inf[i]);
            }
        }
    }
    while (!stack1.isEmpty()) {
        post.push_back(' ');
        if (stack1.get() != '(') {
            post.push_back(stack1.get());
        }
        stack1.pop();
    }
    return post;
}
int convert(char num) {
    int k = 0;
    if (num >= '0' && num <= '9') {
        for (char i = '0'; i <= '9'; i++, k++) {
            if (num == i)
                return k;
        }
    }
    return -1;
}
int eval(std::string pref) {
  TStack<int, 100> stack2;
    int op = 0;
    for (int i = 0; i < pref.size(); i++) {
        if (convert(pref[i]) > -1) {
            op = op * 10 + convert(pref[i]);;
        } else {
            if (op != 0) {
                stack2.push(op);
                op = 0;
            }
            switch (pref[i]) {
            case '+':
            {
                int op1 = stack2.get();
                stack2.pop();
                int op2 = stack2.get();
                stack2.pop();
                stack2.push(op1 + op2);
                break;
            }
            case '-':
            {
                int op1 = stack2.get();
                stack2.pop();
                int op2 = stack2.get();
                stack2.pop();
                stack2.push(op2 - op1);
                break;
            }
            case '*':
            {
                int op1 = stack2.get();
                stack2.pop();
                int op2 = stack2.get();
                stack2.pop();
                stack2.push(op1 * op2);
                break;
            }
            case '/':
            {
                int op1 = stack2.get();
                stack2.pop();
                int op2 = stack2.get();
                stack2.pop();
                stack2.push(op2 / op1);
                break;
            }
            }
        }
    }
    return stack2.get();
}
