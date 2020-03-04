#include <stdio.h>

typedef struct prova{
    int *a,*b;
} prova;

int main(){
    prova boh = (prova){NULL,NULL};
    printf("%p %p\n",boh.a,boh.b);
    return 0;
}