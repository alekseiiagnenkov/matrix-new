#include <stdio.h>
#include <malloc.h>

// Характеристики строки матрицы
typedef struct Line {
    int n; // кол-во элементов в строке матрицы
    int *a; // указатель на первый элемент массива
} Line;

// Матрица
typedef struct Matrix {
    int lines; // кол-во строк матрицы
    Line *arr; // динамический массив строк матрицы
} Matrix;


// Объявление функций
int summNum(int a); //вычисление суммы цифр числа
void erase(Matrix *a); // очистка указателей
int getInt(int *); // функция ввода числа
int input(Matrix *matr); // ввод матрицы
int output(Matrix matr, int a); // вывод матрицы
int getRes(Matrix *matr1, Matrix *matr2);


//Тело программы
int main() {
    Matrix matr1 = {1, NULL}; //матрица #1

    Matrix matr2 = {0, NULL}; //матрицa #2
    if (input(&matr1) == 0) { //ввод матрицы
        printf("%s\n", "End of file occured");
        return 1;
    }
    getRes(&matr1, &matr2);
    output(matr1, 1);
    output(matr2, 2);
    erase(&matr1); //очищение памяти
    erase(&matr2); //очищение памяти
    return 0;
}

//Функция ввода числа
int getInt(int *a) {
    int n;
    do {
        printf("Enter a number:");
        n = scanf("%d", a, sizeof(int));
        if (n == 0) {
            printf("%s\n", "Error, re-enter the number.\n");
            //scanf_s("%*[^\n]");
            scanf("%*c", 0);
        }
    } while (n == 0);
    return n < 0 ? 0 : 1;
}

//Ввод матрицы
int input(Matrix *matr) {
    const char *pr = ""; //будущее сообщение об ошибке
    int m; //кол-во строк матрицы
    int i, j;

    printf("Entering a matrix.");

    //Ввод кол-ва строк
    do {
        printf("%s\n", pr);
        printf("Enter the number of lines ");
        pr = "Error, repeat!";
        if (getInt(&m) == 0)
            return 0; //обнаружен конец файла (память не выделилась)
    } while (m < 1);
    matr->lines = m;

    //Выделяем память под массив структур - строк матрицы(создание динамического массива указателей)
    matr->arr = (Line *) calloc(m, sizeof(Line));

    //Ввод кол-ва элементов для каждой строки
    for (i = 0; i < matr->lines; ++i) {
        pr = "";
        do {
            printf("%s\n", pr);
            printf("Enter the number of characters for line #%d. ", i + 1);
            pr = "Error, repeat!";
            if (getInt(&m) == 0) {
                matr->lines = i; //Кол-во сформированных строк
                erase(matr);
                return 0; //Обнаружен конец файла
            }
        } while (m < 1);

        matr->arr[i].n = m;

        //Выделение памяти под элементы строки
        matr->arr[i].a = (int *) malloc(sizeof(int) * m);

        //Ввод элементов
        printf("Enter items for matrix line #%d. \n", i + 1);
        for (j = 0; j < m; ++j) {
            if (getInt(&matr->arr[i].a[j]) == 0) {
                //Освобождение выделенной памяти
                matr->lines = i + 1; //Выделена память и под текущую, i-ую строку
                erase(matr);
                return 0;
            }
        }
    }
    return 1;
}

int getRes(Matrix *matr1, Matrix *matr2) {
    int curr, last, *res, counter = 0;
    matr2->lines = matr1->lines;
    matr2->arr = (Line *) calloc(matr2->lines, sizeof(Line));

    for (int i = 0; i < matr1->lines; i++) {
        counter=0;
        res = (int *) calloc(matr1->arr[i].n, sizeof(int));
        last = summNum(matr1->arr[i].a[matr1->arr[i].n-1]);
        for (int j = 0; j < matr1->arr[i].n; j++) {
            curr = summNum(matr1->arr[i].a[j]);
            if (curr == last) {
                res[counter] = matr1->arr[i].a[j];
                counter++;
            }
        }
        if(counter>0){
            matr2->arr[i].n=counter;
            matr2->arr[i].a = (int *) calloc(counter, sizeof(int));
            for(int j=0; j<counter; j++){
                matr2->arr[i].a[j]=res[j];
            }
        }
        free(res);
    }
    return 0;
}

int summNum(int num) {
    int res = 0;
    do {
        res += num % 10;
        num /= 10;
    } while (num > 0);
    return res;
}

//Вывод матрицы
int output(Matrix matr, int a) {
    //Вывод матрицы
    int i, j;
    printf("Matrix #%d\n", a);
    for (i = 0; i < matr.lines; ++i) {
        for (j = 0; j < matr.arr[i].n; ++j)
            printf("%d  ", matr.arr[i].a[j]);
        printf("\n");
    }
    return 0;
}

//Освобождение памяти
void erase(Matrix *a) {
    //освобождение памяти матрицы
    for (int i = 0; i < a->lines; ++i)
        free(a->arr[i].a);
    free(a->arr);
    a->lines = 0;
    a->arr = NULL;
}
