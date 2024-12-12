#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    char *data;
    int top;
    int size;
} Stack;

// Функция для инициализации стека
Stack *create_stack(int size) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->data = (char *)malloc(size * sizeof(char));
    stack->top = -1;
    stack->size = size;
    return stack;
}

// Функция для добавления элемента в стек
void push(Stack *stack, char c) {
    if (stack->top == stack->size - 1) return; // Переполнение
    stack->data[++stack->top] = c;
}

// Функция для удаления элемента из стека
char pop(Stack *stack) {
    if (stack->top == -1) return '\0'; // Пустой стек
    return stack->data[stack->top--];
}

// Функция для проверки верхнего элемента стека
char peek(Stack *stack) {
    if (stack->top == -1) return '\0'; // Пустой стек
    return stack->data[stack->top];
}

// Функция для проверки парности скобок
bool is_matching_pair(char open, char close) {
    return (open == '(' && close == ')') || 
           (open == '{' && close == '}') || 
           (open == '[' && close == ']');
}

// Основная функция для проверки строки
int validate_brackets(const char *str) {
    Stack *stack = create_stack(strlen(str));

    for (int i = 0; str[i] != '\0'; i++) {
        char current = str[i];

        if (current == '(' || current == '{' || current == '[') {
            push(stack, current); // Добавляем открывающую скобку в стек
        } else if (current == ')' || current == '}' || current == ']') {
            char top = peek(stack);
            if (!is_matching_pair(top, current)) {
                free(stack->data);
                free(stack);
                return i + 1; // Ошибка: неправильная закрывающая скобка
            }
            pop(stack); // Удаляем соответствующую открывающую скобку
        }
    }

    int result = stack->top == -1 ? 0 : stack->top + 1; // Если стек пуст, скобки правильные
    free(stack->data);
    free(stack);
    return result;
}

// Пример использования
int main() {
    const char *test1 = "((())){}[{{}}]";
    const char *test2 = "((()){)}";
    const char *test3 = "[[[]]]}";

    printf("Test 1: %s -> %s\n", test1, validate_brackets(test1) == 0 ? "true" : "false");
    printf("Test 2: %s -> %d\n", test2, validate_brackets(test2));
    printf("Test 3: %s -> %d\n", test3, validate_brackets(test3));

    return 0;
}
