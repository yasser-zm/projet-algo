#include <stdio.h>
#include <ctype.h>



// stackklkkkkkkkkkkkkkk ya wlidi 
typedef struct {
    int data[256];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    s->data[++s->top] = value;
}

int pop(Stack *s) {
    return s->data[s->top--];
}

int peek(Stack *s) {
    return s->data[s->top];
}


// prioritiessssssssssssssssssssss 
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// infix to postfix things 
void infixToPostfix(const char expr[], char output[][20], int *outSize) {

    Stack ops;
    init(&ops);
    *outSize = 0;

    char token[20];
    int t = 0;

    for (int i = 0; expr[i] != '\0'; i++) {

        if (isdigit(expr[i])) {
            token[t++] = expr[i];
        }
        else {
            if (t > 0) {
                token[t] = '\0';
                strcpy(output[(*outSize)++], token);
                t = 0;
            }

            while (!isEmpty(&ops) &&
                   precedence(peek(&ops)) >= precedence(expr[i])) {
                char op[2] = { pop(&ops), '\0' };
                strcpy(output[(*outSize)++], op);
            }

            push(&ops, expr[i]);
        }
    }

    if (t > 0) {
        token[t] = '\0';
        strcpy(output[(*outSize)++], token);
    }

    while (!isEmpty(&ops)) {
        char op[2] = { pop(&ops), '\0' };
        strcpy(output[(*outSize)++], op);
    }
}



// evaluation de l'expression postfixée



int evalPostfix(char output[][20], int size) {

    Stack values;
    init(&values);

    for (int i = 0; i < size; i++) {

        if (isdigit(output[i][0])) {
            push(&values, atoi(output[i]));
        }
        else {
            int b = pop(&values);
            int a = pop(&values);

            switch(output[i][0]) {
                case '+': push(&values, a + b); break;
                case '-': push(&values, a - b); break;
                case '*': push(&values, a * b); break;
                case '/': push(&values, a / b); break;
                case '^': push(&values, pow(a, b)); break;
            }
        }
    }

    return pop(&values);
}












// Vérifie si un caractère est un opérateur
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Vérifie que l'expression est correcte
int isValidExpression(const char *expr) {

    int i = 0;

    if (expr[0] == '\0') return 0;

    if (isOperator(expr[0])) return 0;

    for (i = 0; expr[i] != '\0'; i++) {

        if (!isdigit(expr[i]) && !isOperator(expr[i])) {
            return 0;
        }

        if (isOperator(expr[i]) && isOperator(expr[i+1])) {
            return 0;
        }
    }

    if (isOperator(expr[i-1])) return 0;

    return 1;
}


//   Fonction d'encodage

int encodeExpression(const char *expr, int tab[]) {

    int tabIndex = 0;
    int number = 0;

    for (int i = 0; expr[i] != '\0'; i++) {

        if (expr[i] >= '0' && expr[i] <= '9') {
            number = number * 10 + (expr[i] - '0');
        }
        else {
            tab[tabIndex++] = number;
            number = 0;

            if (expr[i] == '+') tab[tabIndex++] = -1;
            else if (expr[i] == '-') tab[tabIndex++] = -2;
            else if (expr[i] == '*') tab[tabIndex++] = -3;
            else if (expr[i] == '/') tab[tabIndex++] = -4;
            else if (expr[i] == '^') tab[tabIndex++] = -5;
        }
    }

    tab[tabIndex++] = number;

    return tabIndex;
}

//              MAIN

int main() {

    printf("Hello calculator!\n");

    char expr[256];

    printf("Tape ton expression: ");
    scanf("%s", expr);

    // Vérification syntaxique
    if (!isValidExpression(expr)) {
        printf("Expression invalide KHOYAAAAAAAAAAAAA !\n");
        return 1;
    }

    printf("Expression valide : %s\n", expr);

    // Conversion en postfix avec stack
    char postfix[256][20];
    int size = 0;

    infixToPostfix(expr, postfix, &size);

    printf("\nPostfix : ");
    for (int i = 0; i < size; i++) {
        printf("%s ", postfix[i]);
    }
    printf("\n");

    // Évaluation postfix avec stack
    int result = evalPostfix(postfix, size);

    printf("\nRésultat = %d\n", result);

    return 0;
}

  