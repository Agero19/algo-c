#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Stack {
    char* data;
    int top;
    int capacity;
} Stack;

// Функции для работы со стеком
Stack* create_stack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (char*)malloc(capacity * sizeof(char));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

bool is_empty(Stack* stack) {
    return stack->top == -1;
}

bool is_full(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

void push(Stack* stack, char value) {
    if (is_full(stack)) return;
    stack->data[++stack->top] = value;
}

char pop(Stack* stack) {
    if (is_empty(stack)) return '\0';
    return stack->data[stack->top--];
}

void free_stack(Stack* stack) {
    free(stack->data);
    free(stack);
}

// Проверка палиндрома
bool is_palindrome(const char* str) {
    int len = strlen(str);
    Stack* stack = create_stack(len);

    // Добавляем половину строки в стек
    for (int i = 0; i < len / 2; i++) {
        push(stack, str[i]);
    }

    // Индекс начала второй половины
    int start = (len % 2 == 0) ? len / 2 : len / 2 + 1;

    // Сравниваем вторую половину с содержимым стека
    for (int i = start; i < len; i++) {
        if (pop(stack) != str[i]) {
            free_stack(stack);
            return false;
        }
    }

    free_stack(stack);
    return true;
}

// Проверка правильности скобок
int check_brackets(const char* str) {
    Stack* stack = create_stack(100); // Предполагаем максимальную длину строки 100

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        
        if (c == '(' || c == '{' || c == '[') {
            push(stack, c);
        } else if (c == ')' || c == '}' || c == ']') {
            char top = pop(stack);
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                free_stack(stack);
                return i; // Возвращаем индекс ошибки
            }
        }
    }

    // Если после проверки стек не пуст, есть несоответствие
    bool result = is_empty(stack);
    free_stack(stack);

    return result ? -1 : -2; // -1 если всё правильно, -2 если стек не пуст
}

int main() {
    const char* test1 = "radar";
    printf("Is \"%s\" a palindrome? %s\n", test1, is_palindrome(test1) ? "Yes" : "No");

    const char* test2 = "{[()]}";
    int result = check_brackets(test2);

    if (result == -1) {
        printf("The brackets in \"%s\" are balanced.\n", test2);
    } else if (result == -2) {
        printf("Unbalanced brackets: unmatched opening bracket.\n");
    } else {
        printf("Unbalanced brackets at position %d.\n", result);
    }
    return 0;
}
