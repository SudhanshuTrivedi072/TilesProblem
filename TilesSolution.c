#include <stdio.h>
#include <stdlib.h>
#define SIZE 8//should be power of 2 and greater than 1
int symbol = 100;
int count = 0;

struct cordinate {
    int i;
    int j;
};

struct node {
    int value;
    int symbol;
};

struct cordinate join(struct cordinate cone, struct cordinate ctwo, struct cordinate cthree, int size, struct node(*array)[SIZE]) {
    struct cordinate index;
    int sum = 0;
    //    printf("%d,%d...%d,%d...%d,%d...and...", cone.i, cone.j, ctwo.i, ctwo.j, cthree.i, cthree.j);
    array[cone.i][cone.j].symbol = symbol;
    array[ctwo.i][ctwo.j].symbol = symbol;
    array[cthree.i][cthree.j].symbol = symbol;
    symbol++;
    sum = array[cone.i][cone.j].value + array[ctwo.i][ctwo.j].value + array[cthree.i][cthree.j].value;
    //    printf("sum %d....and ctwo.i = %d,%d", sum, ctwo.i, ctwo.j);

    if (ctwo.i == cone.i && ctwo.j + 1 == cone.j && ctwo.i + 1 == cthree.i && ctwo.j == cthree.j) {
        index.i = ctwo.i + 1;
        index.j = ctwo.j + 1;
    } else if (ctwo.i == cone.i && ctwo.j - 1 == cone.j && ctwo.i + 1 == cthree.i && ctwo.j == cthree.j) {
        index.i = ctwo.i + 1;
        index.j = ctwo.j - 1;
    } else if (ctwo.i - 1 == cone.i && ctwo.j == cone.j && ctwo.i == cthree.i && ctwo.j + 1 == cthree.j) {
        index.i = ctwo.i - 1;
        index.j = ctwo.j + 1;
    } else if (ctwo.i - 1 == cone.i && ctwo.j == cone.j && ctwo.i == cthree.i && ctwo.j - 1 == cthree.j) {
        index.i = ctwo.i - 1;
        index.j = ctwo.j - 1;
    }

    //    printf("index %d %d\n\n", index.i, index.j);
    return index;
}

struct cordinate solve(int size, int portion, int i, int j, struct node(*array)[SIZE]) {
    struct cordinate xreturn;
    //    printf("func(%d,%d) aur (i,j)=(%d,%d)  \n", size, portion, i, j);
    count++;
    if (size == 2) {
        struct cordinate cone, ctwo, cthree;
        if (portion == 1) {
            cone.i = i;
            cone.j = j + 1;
            ctwo.i = i;
            ctwo.j = j;
            cthree.i = i + 1;
            cthree.j = j;
            xreturn = join(cone, ctwo, cthree, 2, array);

        } else if (portion == 2) {
            cone.i = i;
            cone.j = j;
            ctwo.i = i;
            ctwo.j = j + 1;
            cthree.i = i + 1;
            cthree.j = j + 1;
            xreturn = join(cone, ctwo, cthree, 2, array);

        } else if (portion == 3) {
            cone.i = i;
            cone.j = j;
            ctwo.i = i + 1;
            ctwo.j = j;
            cthree.i = i + 1;
            cthree.j = j + 1;
            xreturn = join(cone, ctwo, cthree, 2, array);

        } else if (portion == 4) {
            cone.i = i;
            cone.j = j + 1;
            ctwo.i = i + 1;
            ctwo.j = j + 1;
            cthree.i = i + 1;
            cthree.j = j;
            xreturn = join(cone, ctwo, cthree, 2, array);
        }
    } else {
        size = size / 2;
        struct cordinate cone;
        struct cordinate ctwo;
        struct cordinate cthree;
        if (portion == 1) {
            cone = solve(size, 2, i, j + size, array);
            ctwo = solve(size, 1, i, j, array);
            cthree = solve(size, 3, i + size, j, array);
            xreturn = join(cone, ctwo, cthree, size, array);
            xreturn = solve(size, array[xreturn.i][xreturn.j].value, xreturn.i, xreturn.j, array);
        } else if (portion == 2) {
            cone = solve(size, 1, i, j, array);
            ctwo = solve(size, 2, i, j + size, array);
            cthree = solve(size, 4, i + size, j + size, array);
            xreturn = join(cone, ctwo, cthree, size, array);
            xreturn = solve(size, array[xreturn.i][xreturn.j].value, xreturn.i, xreturn.j - size + 1, array);
        } else if (portion == 3) {
            cone = solve(size, 1, i, j, array);
            ctwo = solve(size, 3, i + size, j, array);
            cthree = solve(size, 4, i + size, j + size, array);
            xreturn = join(cone, ctwo, cthree, size, array);
            xreturn = solve(size, array[xreturn.i][xreturn.j].value, xreturn.i - size + 1, xreturn.j, array);
        } else if (portion == 4) {
            cone = solve(size, 2, i, j + size, array);
            ctwo = solve(size, 4, i + size, j + size, array);
            cthree = solve(size, 3, i + size, j, array);
            xreturn = join(cone, ctwo, cthree, size, array);
            xreturn = solve(size, array[xreturn.i][xreturn.j].value, xreturn.i - size + 1, xreturn.j - size + 1, array);
        }
        return xreturn;
    }
}

void initialize(int size, struct node(*array)[size]) {

    for (int i = 0; i <= size - 1; i++) {
        for (int j = 0; j <= size - 1; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    array[i][j].value = 1;
                } else {
                    array[i][j].value = 2;
                }
            } else {
                if (j % 2 == 0) {
                    array[i][j].value = 3;
                } else {
                    array[i][j].value = 4;
                }
            }
        }
    }

}

int main(int argc, char** argv) {

    struct node array[SIZE][SIZE];
    initialize(SIZE, array);
    solve(SIZE, 1, 0, 0, array);
    for (int i = 0; i <= SIZE - 1; i++) {
        for (int j = 0; j <= SIZE - 1; j++) {
            printf(" %d |", array[i][j].symbol);
        }
        printf("\n");
    }
    printf("\n%d", count);
    return (EXIT_SUCCESS);
}

