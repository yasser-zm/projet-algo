#include <stdio.h>

int main() {

    printf("Hello calculator!\n");

    char expr[256];

    printf("Tap your full operation:\n");
    scanf("%s", expr);

    int tab[200];    
    int tabIndex = 0; 
    int number = 0;   

    for (int i = 0; expr[i] != '\0'; i++) {

        if (expr[i] >= '0' && expr[i] <= '9') {
            number = number * 10 + (expr[i] - '0');
        }
        else {
            tab[tabIndex++] = number;  // stocke le nombre
            number = 0;               

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

    // Affichage du tableau encodé
    printf("Tableau encodé :\n");
    for (int i = 0; i < tabIndex; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");

   
    int sum = 0;
    for (int i = 0; i < tabIndex; i++) {
        if (tab[i] > 0) sum += tab[i];  // on additionne seulement les nombres
    }
    printf("Somme des nombres = %d\n", sum);

    return 0;
}
