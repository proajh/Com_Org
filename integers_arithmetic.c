#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����
char* add(const char* num1, const char* num2) 
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxlen = (len1 > len2) ? len1 : len2;
    int carry = 0;

    //  (1�� '\0', 1�� �ڸ� �ø��� ���� ����)
    char* result = (char*)calloc((maxlen + 2), sizeof(char));

    if (result == NULL) 
    {
       
        return NULL;
    }

    result[maxlen + 1] = '\0'; // ��� ���ڿ� ���� '\0' �߰�

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

//  ����
char* subtract(const char* num1, const char* num2) 
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    //  (1�� '\0')
    int resultLen = (len1 > len2 ? len1 : len2) + 1;
    char* result = (char*)calloc(resultLen, sizeof(char));

    if (result == NULL) 
    {
        
        return NULL;
    }

    // ����
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


// ����
char* multiply(const char* num1, const char* num2) 
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int* result = (int*)calloc(len1 + len2, sizeof(int));

    // �� ���ڸ� �����Ͽ� ��� �迭�� ����
    for (int i = len1 - 1; i >= 0; i--) 
    {
        for (int j = len2 - 1; j >= 0; j--) 
        {
            int product = (num1[i] - '0') * (num2[j] - '0');
            int sum = product + result[i + j + 1];
            result[i + j + 1] = sum % 10; // ���� �ڸ��� ���� ����
            result[i + j] += sum / 10;    // ���� �ڸ��� �ø� �� ����
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

// ������
char* divide(const char* dividend, const char* divisor, char** remainder) 
{
    int len_dividend = strlen(dividend);
    int len_divisor = strlen(divisor);

    if (len_divisor == 1 && divisor[0] == '0') 
    {
        // 0 ���� ó��
        return NULL;
    }

    // �� �迭�� ũ��� ���� ������ ���̿� ����
    char* quotient = (char*)calloc(len_dividend + 1, sizeof(char));
    char* result_remainder = (char*)calloc(len_dividend + 1, sizeof(char));

    if (quotient == NULL || result_remainder == NULL) 
    {
        // �޸� �Ҵ� ����
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

    // �򿡼� �տ� ���ʿ��� '0' ����
    char* cleanedQuotient = quotient;
    while (*cleanedQuotient == '0' && *(cleanedQuotient + 1) != '\0')
    {
        cleanedQuotient++;
    }

    return cleanedQuotient;
}




int main() 
{
    char num1[1000]; // ù ��° ���ڸ� ������ �迭
    char num2[1000]; // �� ��° ���ڸ� ������ �迭
    char operator;
    char* remainder = NULL; // �������� ������ �迭

    printf(" ����, ���� �Է��ϼ���: \n");
    scanf("%s %c %s", num1, &operator, num2 );
    
    char* sum = add(num1, num2);
    char* diff = subtract(num1, num2);
    char* mul = multiply(num1, num2);
    char* quotient = divide(num1, num2, NULL);
    
    switch (operator)
    {
    case '+':
        printf("���� ���: %s\n", sum);

        break;

    case '-':
        printf("���� ���: %s\n", diff);

        break;

    case '*':
        printf("���� ���: %s\n", mul);

        break;

    case '/':
        printf("������ ��: %s\n", quotient);
        if (remainder != NULL)
        {
            printf("������: %s\n", remainder);
            free(remainder);
        }
            break;
    default:
        printf("invalid operator \n");

        
    }

    return 0;

}
