#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int max(int a,int b){
    if((a>0)||(b>0)){
        if(a >= b)
            return a;
        else
            return b;
    }
    else{
        if(a>=b)
            return b;
        else
            return a;
    }
}

int bits(int a){
    int count = 0;
    while(a!=0){
        a = a/2;
        count++;
    }
    return ++count;
}

void display(int* a,int size){
    for(int i=0;i<size;i++){
        printf("%d",a[i]);
    }
    printf("\t");
}

int *convertBinary(int a,int size){
    int *bin;
    bin = (int*)malloc((size)*sizeof(int));
    int count = bits(a);
    int i = size - 1;
    while( a!=0 ){
        bin[i] = a%2;
        a = a/2;
        i--;
    }
    while( i>=0 ){
        bin[i] = 0;
        i--;
    }
    return bin;  
}

int *twosComplement(int a,int size){
    int *bin;
    bin = (int*)malloc((size)*sizeof(int));
    bin = convertBinary(a,size);
    for(int j=0;j<size;j++){
        if( bin[j] == 0 )
        bin[j] = 1;
        else
        bin[j] = 0;  
    }
    for(int k=size-1;k>=0;k--){
        if( bin[k] == 1)
            bin[k] = 0;
        else{
            bin[k] = 1;
            break;
        }
    }
    return bin;
}

void shiftRight(int* a,int* q,int* qc,int size){
    *qc = q[size-1];
    for(int j = size-1;j>0;j--){
        q[j] = q[j-1];
    }
    q[0] = a[size-1];
    for(int j = size-1;j>0;j--){
        a[j] = a[j-1];
    }
    display(a,size);
    display(q,size);
    printf("%d",*qc);
    printf("\tASR\n");
}

void binAddition(int* a,int* b,int* q,int* qc,int size){
    int c = 0;
    for(int j=size-1;j>=0;j--){
       if( a[j] == 1 ){
        if( b[j]==1 && c==1){
            a[j] = 1; c = 1;
        }
        else if( b[j]==0 && c==0){
            a[j] = 1; c = 0;
        }
        else if( b[j]==1 && c==0){
            a[j] = 0; c =1 ;
        }
        else{
            a[j] = 0; c = 1;
        }
       }
       else{
        if( b[j]==1 && c==1){
            a[j] = 0; c = 1;
        }
        else if( b[j]==0 && c==0){
            a[j] = 0; c = 0;
        }
        else if( b[j]==1 && c==0){
            a[j] = 1; c = 0;
        }
        else{
            a[j] = 1; c = 0;
        }
       }
    }
    display(a,size);
    display(q,size);
    printf("%d",*qc);
}

void multiply(int* mul1,int* mul1c,int* acc,int* q,int* qc,int size){
    printf("A\tQ\tQc\tStep\n");
    for(int i=1;i<=size;i++){
        printf("Step %d:\n",i);
        if((q[size-1]==1 && *qc==0)){
            binAddition(acc,mul1c,q,qc,size);
            printf("\tA - M\n");
        }
        else if((q[size-1]==0 && *qc==1)){
            binAddition(acc,mul1,q,qc,size);
            printf("\tA + M\n");
        }
        shiftRight(acc,q,qc,size);
        printf("\n");
    }
    printf("Final answer = ");
    display(acc,size);
    display(q,size);
}

int main(){
    int a, b;
    printf("Enter the two numbers to multiply by Booth's algorithm: \n");
    scanf("%d %d",&a,&b);
    int size = bits(max(a,b));
    int *mul1,*mul1c,*mul2,*acc;
    int q = 0;
    acc = (int*)malloc(size*sizeof(int));
    for(int i =0;i<size;i++){
        acc[i] = 0;
    }
    printf(" M = ");
    if( a>=0 ){
        mul1 = convertBinary(a,size);
        display(mul1,size);
        printf("\nMc = ");
        mul1c = twosComplement(a,size);
        display(mul1c,size);
    }
    else{
        mul1 = twosComplement(a,size);
        display(mul1,size);
        printf("\nMc = ");
        mul1c = convertBinary((-1*a),size);
        display(mul1c,size);
    }
    printf("\nQ = ");
    if( b>=0 ){
        mul2 = convertBinary(b,size);
        display(mul2,size);
    }
    else{
        mul2 = twosComplement(b,size);
        display(mul2,size);
    }
    printf("\nA = ");
    display(acc,size);
    printf("\n");
    multiply(mul1,mul1c,acc,mul2,&q,size);
    printf("\nWhich is equivalent to %d in decimal",a*b);
}
