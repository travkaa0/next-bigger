#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int compare(const void* a, const void* b);
char* itoa(long long num);
long long my_atoi(const char* str);
long long next_bigger_number(long long num);

char* itoa(long long num)
{
    // определение максимальной длины строки для числа long long
    int max_length = snprintf(NULL, 0, "%lld", num);
    
    // выделение памяти под строку
    char* str = (char*)malloc((max_length + 1) * sizeof(char));
    if (str == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    // преобразование числа в строку
    sprintf(str, "%lld", num);
    
    return str;
}

long long my_atoi(const char* str)
{
    long long num;
    sscanf(str, "%lld", &num);
    return num;
}

long long next_bigger_number(long long num)
{
    char* numStr = itoa(num); 
    int len = strlen(numStr);
    
    // выделение динамического массива для хранения цифр
    int* digits = (int*)malloc(len * sizeof(int));
    if (digits == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    // заполнение массива цифрами
    for (int i = 0; i < len; i++)
    {
        digits[i] = numStr[i] - '0';
    }
    
    free(numStr); // освобождение памяти, выделенную под строку
    
    // поиск индекса, с которого начинается убывающая последовательность цифр
    int i;
    for (i = len - 2; i >= 0; i--)
    {
        if (digits[i] < digits[i + 1]) break;
    }

    if (i == -1)
    {
        free(digits); // освобождение памяти, выделенной под массив цифр
        return -1;
    }

    int smallest_idx = i + 1;
    for (int j = i + 1; j < len; j++)
    {
        if (digits[j] > digits[i] && digits[j] < digits[smallest_idx])
        {
            smallest_idx = j;
        }
    }

    // обмен местами цифр
    int tmp = digits[i];
    digits[i] = digits[smallest_idx];
    digits[smallest_idx] = tmp;

    // сортировка цифр после i по возрастанию
    qsort(digits + i + 1, len - i - 1, sizeof(int), compare);

    long long result = 0;
    // сборка нового числа из отсортированных цифр
    for (int k = 0; k < len; k++)
    {
        result = result * 10 + digits[k];
    }

    free(digits); // освобождение памяти, выделенную под массив цифр
    
    return result; 
}

int compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}