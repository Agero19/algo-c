#include <stdio.h>
#include <stdlib.h>

// Структура для узла списка
typedef struct Cell {
    int data;
    struct Cell *next;
} Cell;

// Структура для управления списком
typedef struct LinkedList {
    Cell *head;
} LinkedList;

LinkedList *create_list() {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

Cell *create_cell(int data) {
    Cell *new_cell = (Cell *)malloc(sizeof(Cell));
    new_cell->data = data;
    new_cell->next = NULL;
    return new_cell;
}

void insert_head(LinkedList *list, int data) {
    Cell *new_cell = create_cell(data);
    new_cell->next = list->head;
    list->head = new_cell;
}

void remove_head(LinkedList *list) {
    if (list->head == NULL) {
        printf("List is empty. Nothing to remove.\n");
        return;
    }
    Cell *temp = list->head;
    list->head = list->head->next;
    free(temp);
}

void print_list(LinkedList *list) {
    Cell *current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void delete_list(LinkedList *list) {
    Cell *current = list->head;
    while (current != NULL) {
        Cell *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

Cell *append_list(Cell *head1, Cell *head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    Cell *current = head1;
    while (current->next != NULL) { // Идем до конца первого списка
        current = current->next;
    }
    current->next = head2; // Присоединяем второй список

    return head1;
}

struct Cell* copy_list(struct Cell* head) {
    if (head == NULL) { 
        return NULL; 
    } else {
        // Allocate memory for a new node
        struct Cell* new_cell = (struct Cell*)malloc(sizeof(struct Cell));
        new_cell->data = head->data;

        // Recursively copy the next node
        new_cell->next = copyList(head->next);

        return new_cell;
    }
}

int main() {
    LinkedList *list = create_list();

    // Вставка элементов
    insert_head(list, 10);
    insert_head(list, 20);
    insert_head(list, 30);

    // Печать списка
    printf("List after insertions: ");
    print_list(list);

    // Удаление элемента
    remove_head(list);
    printf("List after removing head: ");
    print_list(list);

    // Удаление всего списка
    delete_list(list);
    printf("List after deleting all elements: ");
    print_list(list);

    free(list); // Освобождаем память для структуры списка
    return 0;
}
