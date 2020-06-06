#include <stdio.h>
#include <stdlib.h>
#define FIVE 5
#define TEN 10

int main(void){

    int choice;
    printf("1- Display a random grade array\n");
    printf("2- Display Avg grade of each student\n");
    printf("3- Display letter grade of each\n");
    printf("4- Display min and max\n");
    printf("5- Display avg of all\n");
    printf("6- reset\n");
    printf("7- exit\n");

    int grades[TEN][FIVE];
    double avg [TEN];
    while(choice!=7){
    scanf("%d",&choice);

    if (choice==1|| choice ==6){
        for(int i=0;i<TEN;i++){
            for(int j=0;j<FIVE;j++){
                grades[i][j]=rand() % 100;
         }
        }
        printf("             C1        C2        C3        C4        C5\n\n");
        for(int i=1;i<TEN+1;i++){
        printf("Std%2d",i);
            for(int j=0;j<FIVE;j++){
                printf("%10d",grades[i-1][j]);
        }
        printf("\n");

        }


    }
    else if (choice==2 ){
        
        for(int i=0;i<TEN;i++){
            for(int j=0;j<FIVE;j++){
                avg[i] = avg[i] + grades[i][j];
             }
             avg[i]= avg[i]/FIVE;
            printf("%10.1f",avg[i]);

        }
        printf("\n");

    }
    else if (choice==3){

        for(int i=0;i<TEN;i++){

    if(avg[i]>=80){
        printf("        F       ");
    }
    else if(avg[i]>=50 && avg[i]<60)
    {
        printf("F       ");
    }
    else if(avg[i]>=60 && avg[i]<70)
    {
        printf("F       ");
    }
    else if(avg[i]>=70 && avg[i]<80)
    {
        printf("F       ");
    }
    else if(avg[i]>=80 && avg[i]<90)
    {
        printf("F       ");
    }
    else
    {
        printf("F       ");
    }
        }
        printf("\n");        
    }    
    else if (choice==4){
        int min = 10000;
        int max = -10000;


        for(int i=0;i<TEN;i++){
            for(int j=0;j<FIVE;j++){
             if(grades[i][j]>max){
                 max = grades[i][j];
             }
            if(grades[i][j]<min){
                 min = grades[i][j];
             }
            }
        }
        printf("%d    %d",min,max);
            }
    else if (choice==5){
        double globalAvg=0;
        for(int i=0;i<TEN;i++){
            for(int j=0;j<FIVE;j++){
             globalAvg= grades[i][j]+globalAvg;
            }
        }
        globalAvg = globalAvg/50;
        printf("%10.1f",globalAvg);             

        printf("\n");
    } 
    }
    return 0;

}