#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 덧셈
char* add(const char* num1, const char* num2) 
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxlen = (len1 > len2) ? len1 : len2;
    int carry = 0;

    //  (1은 '\0', 1은 자리 올림을 위한 공간)
    char* result = (char*)calloc((maxlen + 2), sizeof(char));

    if (result == NULL) 
    {
       
        return NULL;
    }

    result[maxlen + 1] = '\0'; // 결과 문자열 끝에 '\0' 추가

    for (int i = 0; i < maxlen; i++)
    {
        int digit1 = (i < len1) ? (num1[len1 - 1 - i] - '0') : 0;
        int digit2 = (i < len2) ? (num2[len2 - 1 - i] - '0') : 0;
        int sum = digit1 + digit2 + carry;

        carry = sum / 10;
        result[maxlen - i] = (sum % 10) + '0';
    }

    result[0] = carry + '0'; 

 
    char* cleanedResult = result;
    while (*cleanedResult == '0' && *(cleanedResult + 1) != '\0') 
    {
        cleanedResult++;
    }
    
    
    return cleanedResult;
}

//  뺄셈
char* subtract(const char* num1, const char* num2) 
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    //  (1은 '\0')
    int resultLen = (len1 > len2 ? len1 : len2) + 1;
    char* result = (char*)calloc(resultLen, sizeof(char));

    if (result == NULL) 
    {
        
        return NULL;
    }

    // 빼기
    int borrow = 0;
    for (int i = 0; i < resultLen - 1; i++)
    {
        int digit1 = (i < len1) ? (num1[len1 - 1 - i] - '0') : 0;
        int digit2 = (i < len2) ? (num2[len2 - 1 - i] - '0') : 0;
        int diff = digit1 - digit2 - borrow;

        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else 
        {
            borrow = 0;
        }

        result[resultLen - 2 - i] = diff + '0';
    }

    char* cleanedResult = result;
    while (*cleanedResult == '0' && *(cleanedResult + 1) != '\0')
    {
        cleanedResult++;
    }

    return cleanedResult;
}


// 곱셈
char* multiply(const char* num1, const char* num2) 
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int* result = (int*)calloc(len1 + len2, sizeof(int));

    // 두 숫자를 곱셈하여 결과 배열에 저장
    for (int i = len1 - 1; i >= 0; i--) 
    {
        for (int j = len2 - 1; j >= 0; j--) 
        {
            int product = (num1[i] - '0') * (num2[j] - '0');
            int sum = product + result[i + j + 1];
            result[i + j + 1] = sum % 10; // 현재 자리에 값을 저장
            result[i + j] += sum / 10;    // 다음 자리에 올림 값 저장
        }
    }

    char* resultStr = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    int i = 0;
    while (i < len1 + len2 && result[i] == 0)
    {
        i++;
    }

    if (i == len1 + len2)
    {
        strcpy(resultStr, "0");
    }
    else {
        int j = 0;
        while (i < len1 + len2)
        {
            resultStr[j++] = result[i] + '0';
            i++;
        }
        resultStr[j] = '\0';
    }

    free(result);
    return resultStr;
}

// 나눗셈
char* divide(const char* dividend, const char* divisor, char** remainder) 
{
    int len_dividend = strlen(dividend);
    int len_divisor = strlen(divisor);

    if (len_divisor == 1 && divisor[0] == '0') 
    {
        // 0 예외 처리
        return NULL;
    }

    // 몫 배열의 크기는 나눌 수식의 길이와 동일
    char* quotient = (char*)calloc(len_dividend + 1, sizeof(char));
    char* result_remainder = (char*)calloc(len_dividend + 1, sizeof(char));

    if (quotient == NULL || result_remainder == NULL) 
    {
        // 메모리 할당 실패
        free(quotient);
        free(result_remainder);
        return NULL;
    }

    int remainder_index = 0;
    int carry = 0;

    for (int i = 0; i < len_dividend; i++)
    {
        int current_digit = dividend[i] - '0';
        int numerator = carry * 10 + current_digit;

        if (numerator < divisor[0] - '0')
        {
            carry = numerator;
            if (i > 0)
            {
                result_remainder[remainder_index++] = '0';
            }
        }
        else
        {
            quotient[i] = (numerator / (divisor[0] - '0')) + '0';
            carry = numerator % (divisor[0] - '0');
        }
    }

    if (remainder != NULL)
    {
        *remainder = result_remainder;
    }
    else
    {
        free(result_remainder);
    }

    // 몫에서 앞에 불필요한 '0' 제거
    char* cleanedQuotient = quotient;
    while (*cleanedQuotient == '0' && *(cleanedQuotient + 1) != '\0')
    {
        cleanedQuotient++;
    }

    return cleanedQuotient;
}




int main() 
{
    char num1[1000]; // 첫 번째 숫자를 저장할 배열
    char num2[1000]; // 두 번째 숫자를 저장할 배열
    char operator;
    char* remainder = NULL; // 나머지를 저장할 배열

    printf(" 숫자, 연산 입력하세요: \n");
    scanf("%s %c %s", num1, &operator, num2 );
    
    char* sum = add(num1, num2);
    char* diff = subtract(num1, num2);
    char* mul = multiply(num1, num2);
    char* quotient = divide(num1, num2, NULL);
    
    switch (operator)
    {
    case '+':
        printf("덧셈 결과: %s\n", sum);

        break;

    case '-':
        printf("뺄셈 결과: %s\n", diff);

        break;

    case '*':
        printf("곱셈 결과: %s\n", mul);

        break;

    case '/':
        printf("나눗셈 몫: %s\n", quotient);
        if (remainder != NULL)
        {
            printf("나머지: %s\n", remainder);
            free(remainder);
        }
            break;
    default:
        printf("invalid operator \n");

        
    }

    return 0;

}
