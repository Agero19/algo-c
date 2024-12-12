#include <stdio.h>
#include <stdlib.h>

// Структура для узла списка
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Структура для списка с контроллером
typedef struct LinkedList {
    Node *head; // Указатель на первый элемент
    Node *tail; // Указатель на последний элемент
} LinkedList;

LinkedList *create_list() {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_head(LinkedList *list, int data) {
    Node *new_node = create_node(data);
    if (list->head == NULL) { // Если список пуст
        list->head = list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head = new_node;
    }
}

void insert_tail(LinkedList *list, int data) {
    Node *new_node = create_node(data);
    if (list->tail == NULL) { // Если список пуст
        list->head = list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

void remove_head(LinkedList *list) {
    if (list->head == NULL) {
        printf("List is empty. Nothing to remove.\n");
        return;
    }
    Node *temp = list->head;
    list->head = list->head->next;

    if (list->head == NULL) { // Если список стал пустым
        list->tail = NULL;
    }

    free(temp);
}

void print_list(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void delete_list(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = list->tail = NULL;
}

LinkedList *copy_list_with_controller(LinkedList *list) {
    LinkedList *new_list = create_list(); // Создаем новый пустой список
    Node *current = list->head;

    while (current != NULL) {
        insert_tail(new_list, current->data); // Используем функцию вставки
        current = current->next;
    }

    return new_list;
}

void append_list_with_controller(LinkedList *list1, LinkedList *list2) {
    if (list2->head == NULL) return; // Если второй список пуст, ничего не делаем

    if (list1->tail == NULL) { // Если первый список пуст, просто переназначаем
        list1->head = list2->head;
        list1->tail = list2->tail;
    } else {
        list1->tail->next = list2->head; // Присоединяем второй список к хвосту первого
        list1->tail = list2->tail;      // Обновляем хвост первого списка
    }

    // Очистка второго списка
    list2->head = NULL;
    list2->tail = NULL;
}


int main() {
    LinkedList *list = create_list();

    // Добавление элементов
    insert_head(list, 10);
    insert_tail(list, 20);
    insert_head(list, 30);
    insert_tail(list, 40);

    // Печать списка
    printf("List after insertions: ");
    print_list(list);

    // Удаление элемента из начала
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
