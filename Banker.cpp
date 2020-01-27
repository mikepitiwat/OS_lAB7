#include <stdio.h>
#include <conio.h>

int np,nr; // number process and number resource
int Allocation[10][5],Max[10][5],Need[10][5],Available[10][5];;
int resource[5],state[10],AvailDrives[5],AvailSUM[5];

//int np = 4, nr = 3;
//int resource[5]         = {12,16,13};
//int Allocation[10][5]   = {{8,5,3},{1,3,5},{1,3,0},{0,1,3}};
//int Max[10][5]          = {{10,9,5},{12,7,7},{3,6,9},{8,13,5}};
//int Need[10][5];
//int AvailDrives[5];
//int Available[10][5];
//int AvailSUM[5];
//int state[10];

void calAvailable(){
    for (int i = 0; i < nr; ++i) {
        for (int j = 0; j < np; ++j) {
            AvailDrives[i] += Allocation[j][i];
        }
        AvailDrives[i] = resource[i] - AvailDrives[i];
        AvailSUM[i] = AvailDrives[i];
        Available[0][i] = AvailDrives[i];
    }
}
void calNeed(){
    for (int i = 0; i < np; ++i) {
        for (int j = 0; j < nr; ++j) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}
void func(int i){
    for (int j = 0; j < nr; ++j) {
        Available[i][j] = Allocation[i][j] + AvailSUM[j];
        AvailSUM[j] = Available[i][j];
    }
}
void Banker(){
    int Level = 0;
    for (int round = 1; round <=2; ++round) {
        for (int i = 0; i < np; ++i) {
            if(round == 1 || round == 2 && state[i] == -1) {
                for (int j = 0; j < nr; ++j) {
                    Available[i][j] =-1;
                    if (AvailSUM[j] >= Need[i][j]) {
                        if (j == nr - 1) { // round 3 finish
                            func(i);
                            state[i] = Level+=1;
                        }
                    } else {
                        state[i] = -1;  // NULL
                        Available[i][j] =-1;
                        break;
                    }
                }
            }
        }
    }
}
char* ansState(){
    int countNULL = 0;
    for (int i = 0; i < np; ++i) {
        if(state[i] == -1){
            countNULL +=1;
        }
    }
    if(countNULL == np)
        return "**ALL process don't run to completion=DEADLOCK";
    else if(countNULL > 0 && countNULL < np)
        return "Next state ... Not enough for process needs remaining\nProcess may get deadlock = UNSAFE STATE";
    else
        return "**ALL process run to completion = SAFE STATE";
}

void input(){
    printf("->> Input state\n");
    printf("Enter number of process :");
    scanf("%d", &np);
    printf("Enter number of resource :");
    scanf("%d", &nr);
    printf("------------------------------------------------------\n");
    printf("Enter all unit of resource :\n");
    for (int i = 0; i < nr; ++i) {
        printf(" resource0%d : ", i + 1);
        scanf("%d", &resource[i]);
    }
    printf("\n------------------------------------------------------");
    for (int i = 0; i < np; ++i) {
        printf("\nEnter allocation of process : %d\n", i + 1);
        for (int j = 0; j < nr; ++j) {
            printf("resource0%d : ", i + 1);
            scanf("%d", &Allocation[i][j]);
        }
    }
    printf("------------------------------------------------------\n");
    for (int i = 0; i < np; ++i) {
        printf("\nEnter max of process : %d\n", i + 1);
        for (int j = 0; j < nr; ++j) {
            int temp;
            printf("resource0%d : ", i + 1);
            scanf("%d", &Max[i][j]);
        }
    }
    printf("------------------------------------------------------\n");
}

void inTable(int i, int temp[][5]) {
    for (int j = 0; j < nr; ++j) {
        if(temp[i][j] == -1) {
            printf("        ");
            break;
        }
        else
            printf("%2d ", temp[i][j]);
    }
}
void showTable(){
    printf("\n===========================================================\n");
    printf("Poscess      Alloc      Max      Need       Avail      State\n         ");
    for (int i = 0; i < 4; ++i){
        printf("  ");
        for (int j = 0; j < nr; ++j)
            printf("%c  ", 65 + j);
    }
    printf("\n");
    for (int i = 0; i < np; ++i){
        printf("P%d\t  ",i+1);
        inTable(i,Allocation);printf("  ");
        inTable(i, Max);printf("  ");
        inTable(i, Need);printf("  ");
        inTable(i, Available);printf("    ");
        if(state[i] == -1)
            printf("NULL");
        else
            printf("%d", state[i]);
        printf("\n");
    }
    printf("===========================================================\n");
}
int main(){
    input();
    calAvailable();
    calNeed();
    Banker();
    printf("%d process\n", np);
    printf("%d resource is ", nr);
    for (int i = 0; i < nr; ++i)
        printf("%c(%d instances) ", 65 + i, resource[i]);
    showTable();
    printf("Available drives = ");
    for (int i = 0; i < nr; ++i)
        printf("%d ", AvailDrives[i]);
    printf("\n");
    printf("%s", ansState());




}
