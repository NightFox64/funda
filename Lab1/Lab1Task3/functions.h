#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

enum ret_type_t{
    SUCCESS,    //Успех
    ERROR_NAN,   //Не является числом
    ERROR_FULL,  //Переполнение
    ERROR_ARGS,  //Количество аргументов неверное
    ERROR_DEL_NULL  //ДЕЛЕНИЕ НА НОЛЬ
};
typedef int (*callback)(double, double, double, double);

//Перевод из строкового представления в double-овое
double chToD(char* x){
    double xD = 0;
    double m = 10;
    double mBuf = m;
    int flag = 1, flagMin = 0;
    

    for (int i = 0; i < (int)strlen(x); ++i){
        if (x[i] == '.'){
            flag = 0;
            m = 10.0;
            mBuf = m;
            continue;
        }
        if (x[i] == '-'){
            flagMin = 1;
            continue;
        }
        if (flag){
            xD = xD * m + (x[i] - '0');
        }
        else{
            xD = xD + ((double)(x[i] - '0')) / m;
            m *= 10.0;
            if (mBuf > m){
                return ERROR_FULL;
            }
            mBuf = m;
        }
    }
    if (flagMin){
        xD *= -1;
    }
    return xD;
}

//Проверка флага
int findFlag(char* qarg, const char** flags, int size){
    for (int i = 0; i < size; ++i)
    {
        if (!(strcmp(qarg, flags[i])))
        {
            return i;
        }
        
    }
   return -1; 
}

//Просто решает уравнение :D
int solveUravn(const double eps, const double a, const double b, const double c){

    double diskr = b * b - 4.0 * a * c;

    if ((a < eps) && (a > -eps)) {
        if ((b < eps) && (b > -eps)) {
            if ((c < eps) && (c > -eps)) {
                printf("With coeffs a=%f, b=%f, c=%f the answer is x=any\n", a, b, c);
                return SUCCESS;
            }
            printf("With coeffs a=%f, b=%f, c=%f, answers are none", a, b, c);
            return SUCCESS;
        }
        printf("With coeffs a=%f, b=%f, c=%f the answer is x=%f\n", a, b, c, -c/b);
        return SUCCESS;
    }

    if ((diskr <= eps) && (diskr >= 0)){
        double res = -b / (2.0 * a);
        printf("With coeffs a=%f, b=%f, c=%f, the ansswer is x=%f\n", a, b, c, res);
    }
    if (diskr > eps){
        double res1 = (-b - sqrt(diskr)) / (2.0 * a);
        double res2 = (-b + sqrt(diskr)) / (2.0 * a);
        printf("With coeffs a=%f, b=%f, c=%f, answers are x1=%f, x2=%f\n", a, b, c, res1, res2);
    }
    if (diskr < 0){
        printf("With coeffs a=%f, b=%f, c=%f, answers are x1, x2 = (%f +- i*%f)/%f\n", a, b, c, -b, sqrt(-diskr), 2.0 * a);
    }

    return SUCCESS;
}

//Решает квадратное уравнение со всеми перестановками аргументов
int funcForQ(const double eps, const double a, const double b, const double c){
    int x[] = {a, b, c};
    double combinations[6][3];
    double combination[3];
    int count = 0;
    for (int k = 0; k < 3; k++)
    {
        for (int i = 1; i <= 2; i++)
        {
            for (int j = k, n = 0; j < 3, n < 3; j = (j + i) % 3, n++)
            {
                combination[n] = x[j % 3]; 
            }
            int flag = 0;
            for (int i = 0; i < count; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if((eps > fabs(combination[j] - combinations[i][j]))){
                        flag++;
                    }
                }
                if(flag == 3){
                    flag = -1;
                    break;
                }
                else{
                    flag = 0;
                }
            }
            if(!flag){
                solveUravn(eps, combination[0], combination[1], combination[2]);
                for (int i = 0; i < 3; i++)
                {
                    combinations[count][i] = combination[i];
                }
                count++;
            }
            else{
                break;
            }
            
            
        }
        
    }
    
    return SUCCESS;

}

//Проверяет кратность первого числа на второе
int funcForM(double a, double b, double c, double d){
    if (b == 0){
        return ERROR_DEL_NULL;
    }
    double delRes = a / b;
    double remain = delRes - (int)delRes;
    if (remain == 0){
        printf("The number %f is a multiple of number %f", a, b);
    }
    else{
        printf("The number %f is NOT a multiple of number %f", a, b);
    }

    return SUCCESS;
}

//Проверяет числа на вершины треугольника прямоугольного
int funcForT(double eps, double a, double b, double c){

    if ((a <= 0) || (b <= 0) || (c <= 0)){
        printf("Triangle with zero side or lower don't exist");
        return SUCCESS;
    }

    double tr1 = a * a + b * b - c * c;
    double tr2 = a * a + c * c - b * b;
    double tr3 = c * c + b * b - a * a;

    if (((tr1 <= eps) && (tr1 >= 0)) || ((tr2 <= eps) && (tr2 >= 0)) || ((tr3 <= eps) && (tr3 >= 0))){
        printf("That's a right-angled triangle");
    }
    else{
        printf("That's NOT a right-angled triangle");
    }

    return SUCCESS;
}

//Проверяет является ли строковое представление вещественным числом
int checkNumber(char* x){
    int flagDot = 0, flagMin = 0;
    for (int i = 0; i < (int)strlen(x); i++){
        if ((x[i] < '0' || x[i] > '9') && (x[i] != '.') && (x[i] != '-')){
            return ERROR_NAN;
        }
        if (x[i] == '.'){
            flagDot++;
            if (flagDot > 1){
                return ERROR_NAN;
            }
        }
        if (x[i] == '-'){
            flagMin++;
            if (flagMin > 1){
                return ERROR_NAN;
            }
        }
    }
    return SUCCESS;
}