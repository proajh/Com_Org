#include <stdio.h> 

int main(void)
{
    int num1, num2;
    int result, result1 =0;  //정수의 범위는 -2,147,483,648~ 2,147,483,647
    char operator;

    while(1)
    {
        printf("Enter an operation for two integers:\n");
        printf("Operators are '+' '-' '*' '/'\n");
        scanf("%d%c%d",&num1, &operator, &num2);
        if((operator == '/') && (num2 ==0) )
        {
            printf("ERROR");
        }
        else
        {
            break;
        }
           
    }
    
    switch (operator)
    {
        case '+':
            result = num1 + num2;
            printf("%d", result);
            break;

        case '-':
            result = num1 - num2;
            printf("%d", result);
            break;

        case '*':
            result = num1 * num2;
            printf("%d", result);
            break;

        case '/':
            result = num1 / num2;
            result1 = num1 % num2;
            printf("몫: %d 나머지: %d", result, result1);
            break;

    }
   
    return 0;


}