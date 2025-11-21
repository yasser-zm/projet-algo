#include <stdio.h>

int main() {


    printf("Hello calculator!\n");

char expr[256];

    printf("tap your  full operation  \n");

scanf("%s", expr);

    int tab[200];     // tableau final
    int tabIndex = 0; // position dans le tableau
    int number = 0;   // pour reconstituer les nombres

    for (int i = 0; expr[i] != '\0'; i++) {

        if (expr[i] >= '0' && expr[i] <= '9') {
            number = number * 10 + (expr[i] - '0');
        }
        else {
            tab[tabIndex++] = number;  // on stocke le nombre
            number = 0;                // reset

            // encodage des opérateurs
            if (expr[i] == '+') tab[tabIndex++] = -1;
            else if (expr[i] == '-') tab[tabIndex++] = -2;
            else if (expr[i] == '*') tab[tabIndex++] = -3;
            else if (expr[i] == '/') tab[tabIndex++] = -4;
            else if (expr[i] == '^') tab[tabIndex++] = -5;
        }
    }

    // Ajouter le dernier nombre
    tab[tabIndex++] = number;
  printf("Tableau encodé :\n");
    for (int i = 0; i < tabIndex; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");

    return 0;
}
