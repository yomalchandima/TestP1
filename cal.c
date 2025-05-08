#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define MAX_HISTORY 100

char history[MAX_HISTORY][100]; // Array to store history
int historycount = 0; // Counter for history entries

void displaymenue() {
    printf("##########################################\n");
    printf("##    SCS 1301 -Scientific Calculator   ##\n");
    printf("##              by                      ##\n");
    printf("##          Yomal chandima              ##\n");
    printf("##########################################\n");
    printf("##########################################\n");
    printf("#   1. Addition        8.   Sine         #\n");
    printf("#   2. Subtraction     9.   Cosine       #\n");
    printf("#   3. Multiplication  10.  Tangent      #\n");
    printf("#   4. Division        11.  Inverse      #\n");
    printf("#   5. Power           12.  Remainder    #\n");
    printf("#   6. LCM             13.  Odd or Even  #\n");
    printf("#   7. GCD             14.  Precentage   #\n");
    printf("#                                        #\n");
    printf("#   15. Exit           16.  History      #\n");
    printf("##########################################\n");
    printf("##########################################\n");
}
void dissubmenue() {
    printf("##########################################\n");
    printf("#   1. Inter Division                    #\n");
    printf("#   2. Normal Division                   #\n");
    printf("##########################################\n");
}
void displayhistory() {if (historycount == 0) {
    printf("No operations performed yet.\n");
    return;
}
printf("========== Operation History ==========\n");
for (int i = 0; i < historycount; i++) {
    printf("%d. %s\n", i + 1, history[i]);
}
}

int addition(int a, int b) {
    return a + b;
}
int sub(int a, int b) {
    return a - b;
}
int multiply(int a, int b) {
    return a * b;
}
int interdivision(int a, int b) {
    if (b != 0) { return a / b;
    } else {
    printf("Error: Division by zero!\n");
    return 0;
    }
}
int power(int a, int b) {
    return pow(a, b);
}
int Lcm(int a, int b) {
    int max = (a > b) ? a : b;
    while (1) {
        if (max % a == 0 && max % b == 0) {
            return max;
        }
        max++;
    }
}
int Gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int reminder(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
        return 0;
    }
    else 
    return a % b;
}
int oddeven(int a) {
    if (a % 2 == 0) {
        printf("%d is even\n", a);
    }else{
        printf("%d is odd\n", a);
    } 
    return 0;
 }
 double normaldivision(double a, double b) {
    if (b != 0) { return a / b;
    } else { 
    printf("Error: Division by zero!\n");
    return 0.0;
    }
 }
 double sine(double a) {
    return sin(a);
 }
double cosine(double a) {
    return cos(a);
 }
 double tangent(double a) {
    return tan(a);
 }
 double inverse(double a) {
    if (a != 0) return 1 / a;
    else 
    printf("Error: Division by zero!\n");
    return 0;
 }
 double percentage(double a, double b) {
    return (a * b) / 100;
 }
  int main() {
    int choice;
    int a, b;
    double da, db;
    int result;
    double dresult;

    while(1) {
        displaymenue();
        printf("Enter your choice (1-16): ");
        scanf("%d", &choice);

        if(choice == 15) {
            printf("Exiting calculator...\n");
            break;
        }
        if (choice ==16) {
            displayhistory();
            continue;
        }
       /* if (choice == 4) {
            dissubmenue();
            continue;
        }*/

  
switch (choice) {
        case 1:
            printf("Enter two Integers: ");
            scanf("%d %d", &a, &b);
            result = addition(a, b);
            printf("Result: %d\n", result);
            snprintf(history[historycount], 100, "Addition: %d + %d = %d", a, b, result);
            historycount++;
            break;
        case 2:
            printf("Enter two numbers: ");
            scanf("%d %d", &a, &b);
            result = sub(a, b);
            printf("Result: %d\n", result);
            snprintf(history[historycount], 100, "Subtraction: %d - %d = %d", a, b, result);
            historycount++;
            break;
        case 3:
            printf("Enter two numbers: ");
            scanf("%d %d", &a, &b);
            result = multiply(a, b);
            printf("Result: %d\n", result);
            snprintf(history[historycount], 100, "Multiplication: %d * %d = %d", a, b, result);
            historycount++;
            break;
        case 4:
            dissubmenue();
            int subchoice;
            printf("Enter your choice (1-2): ");
            scanf("%d", &subchoice);

        if (subchoice ==1) {
            printf("Enter two Integers: ");
            scanf("%d %d", &a, &b);
            result = interdivision(a, b);
            printf("Result: %d\n", result);
            snprintf(history[historycount], 100, "Integerr Division: %d / %d = %d", a, b, result);
            historycount++;
        } else if (subchoice ==2) {
            printf("Enter two numbers: ");
            scanf("%lf %lf", &da, &db);
            dresult = normaldivision(da, db);
            printf("Result: %lf\n", dresult);
            snprintf(history[historycount], 100, "Normal Division: %.2lf / %.2lf = %.2lf", da, db, dresult);
            historycount++;
        } else {
            printf("Your Choice is Invalid.Try again.\n");
        }
            break;
        case 5:
            printf("Enter base and exponent: ");
            scanf("%d %d", &a, &b);
            result = power(a, b);
            printf("Result: %d\n", result);
            snprintf(history[historycount], 100, "Power: %d ^ %d = %d", a, b, result);
            historycount++;
            break;
        case 6:
            printf("Enter two numbers: ");
            scanf("%d %d", &a, &b);
            result = Lcm(a, b);
            printf("Result: %d\n", result);
            snprintf(history[historycount], 100, "LCM: %d and %d = %d", a, b, result);
            historycount++;
            break;
        case 7:
            printf("Enter two numbers: ");
            scanf("%d %d", &a, &b);
            result = Gcd(a, b);
            printf("Result : %d\n", result);
            snprintf(history[historycount], 100, "GCD: %d and %d = %d", a, b, result);
            historycount++;
            break;
        case 8:
            printf("Enter angle in radians: ");
            scanf("%lf", &da);
            dresult = sine(da);
            printf("Result: %lf\n", dresult);
            snprintf(history[historycount], 100, "Sine: sin(%lf) = %lf", da, dresult);
            historycount++;
            break;
        case 9:     
            printf("Enter angle in radians: ");
            scanf("%lf", &da);
            dresult = cosine(da);
            printf("Result: %lf\n", dresult);
            snprintf(history[historycount], 100, "Cosine: cos(%lf) = %lf", da, dresult);
            historycount++;
            break;
        case 10:
            printf("Enter angle in radians: ");
            scanf("%lf", &da);
            dresult = tangent(da);
            printf("Result: %lf\n", dresult);
            snprintf(history[historycount], 100, "Tangent: tan(%lf) = %lf", da, dresult);
            historycount++;
            break;
        case 11:
            printf("Enter a number: ");
            scanf("%lf", &da);
            dresult = inverse(da);
            printf("Result: %lf\n", dresult);
            snprintf(history[historycount], 100, "Inverse: 1/%lf = %lf", da, dresult);
            historycount++;
            break;
        case 12:
            printf("Enter two numbers: ");
            scanf("%d %d", &a, &b);
            result = reminder(a, b);
            printf("Result: %d\n", result);
            snprintf(history[historycount], 100, "Remainder: %d %% %d = %d", a, b, result);
            historycount++;
            break;
        case 13:
            printf("Enter a number: ");
            scanf("%d", &a);
            oddeven(a);
            snprintf(history[historycount], 100, "Odd or Even: %d", a);
            historycount++;
            break;
        case 14:
            printf("Enter two numbers: ");
            scanf("%lf %lf", &da, &db);
            dresult = percentage(da, db);
            printf("Result: %lf\n", dresult);
            snprintf(history[historycount], 100, "Percentage: %lf %% of %lf = %lf", da, db, dresult);
            historycount++;
            break;
        case 16:
            displayhistory();
            break;
            default:
            printf("Your Choice is Invalid.Try again.\n");
        }    
    }
    return 0;
}