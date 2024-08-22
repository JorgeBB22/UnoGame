#include<stdio.h>
int main(){
    float metros;
    float decimetros;
    float centimetros;
    float milimetros;
     
     printf("digite metros: ");
     scanf("%f", metros);

     decimetros = metros * 10;
     centimetros = metros * 100;
     milimetros = metros * 1000; 

      printf ("%.2f metros é equivalente a: \n", metros);
      printf ("%.2f decimetros\n",decimetros);
      printf ("%.2f centimetros\n", centimetros);
      printf ("%.2f milimetros\n", milimetros);

      return 0;
      
     
    
    

}