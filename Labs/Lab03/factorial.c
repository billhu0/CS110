#include <stdio.h>

int factorial(int a){
    int result = 1;
    while (a != 1){
        result = result * a;
        a--;
    }
    return result;
}

int main(){
    printf("%d", factorial(5));
}