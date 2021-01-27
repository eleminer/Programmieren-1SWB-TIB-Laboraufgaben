#include <stdio.h>

int main(int argc, char* argv[]) {
    int i1, i2, i3;
    scanf("%d %d %d", &i1, &i2, &i3);
    printf("Ganze Zahlen: %d, %d, %d \n", i1, i2, i3);

    float f;
    scanf("%f", &f);
    printf("Fliesskommazahl mit Formatangabe: %.2f \n", f);

    char s[100];
    scanf("%s", s);
    printf("Zeichenkette: %s \n", s);
    return 0;
}