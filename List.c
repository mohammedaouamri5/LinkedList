#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

// Define a generic linked list type
#define ___INIT_LIST___(LinkedListType, NodeType) \
    typedef struct LinkedListType##Node { \
        NodeType data; \
        struct LinkedListType##Node* next; \
    } LinkedListType##Node; \
    \
    typedef struct { \
        LinkedListType##Node* head; \
        size_t size; \
    } LinkedListType; \
    \
    /* Create a new linked list */ \
    LinkedListType* create_##LinkedListType() { \
        LinkedListType* list = (LinkedListType*)malloc(sizeof(LinkedListType)); \
        if (list == NULL) { \
            return NULL; \
        } \
        list->head = NULL; \
        list->size = 0; \
        return list; \
    } \
    \
    /* Add an element to the end of the linked list */ \
    int push_back_##LinkedListType(LinkedListType* list, NodeType element) { \
        LinkedListType##Node* newNode = (LinkedListType##Node*)malloc(sizeof(LinkedListType##Node)); \
        if (newNode == NULL) { \
            return 0; \
        } \
        newNode->data = element; \
        newNode->next = NULL; \
        if (list->head == NULL) { \
            list->head = newNode; \
        } else { \
            LinkedListType##Node* current = list->head; \
            while (current->next != NULL) { \
                current = current->next; \
            } \
            current->next = newNode; \
        } \
        list->size++; \
        return 1; \
    } \
    \
    /* Add an element to the front of the linked list */ \
    int push_front_##LinkedListType(LinkedListType* list, NodeType element) { \
        LinkedListType##Node* newNode = (LinkedListType##Node*)malloc(sizeof(LinkedListType##Node)); \
        if (newNode == NULL) { \
            return 0; \
        } \
        newNode->data = element; \
        newNode->next = list->head; \
        list->head = newNode; \
        list->size++; \
        return 1; \
    } \
    \
    /* Get the current size of the linked list */ \
    size_t size_##LinkedListType(const LinkedListType* list) { \
        return list->size; \
    } \
    \
    /* Destroy the linked list and free memory */ \
    void destroy_##LinkedListType(LinkedListType* list) { \
        LinkedListType##Node* current = list->head; \
        while (current != NULL) { \
            LinkedListType##Node* next = current->next; \
            free(current); \
            current = next; \
        } \
        free(list); \
    } \
    \
    /* Define a lambda function type */ \
    typedef bool (*LambdaFunction_##LinkedListType)(LinkedListType##Node*, va_list); \
    \
    /* Function to search for a node based on a lambda function */ \
    int Full_Position_Serch_##LinkedListType(LinkedListType* list, LinkedListType##Node** Befor, \
                                             LinkedListType##Node** Me, int* Me_index, LambdaFunction_##LinkedListType lamda, ...) { \
        if (list == NULL) { \
            *Befor = NULL; \
            *Me = NULL; \
            *Me_index = -1; \
            return -1; \
        } \
        \
        va_list args; \
        va_start(args, lamda); \
        \
        *Befor = NULL; \
        *Me = list->head; \
        *Me_index = 0; \
        int index = 0; \
        \
        while (*Me) { \
            if (lamda(*Me, args)) { \
                va_end(args); \
                return index; \
            } \
            \
            (*Befor) = (*Me); \
            (*Me) = (*Me)->next; \
            (*Me_index)++; \
            index++; \
        } \
        \
        va_end(args); \
        return -1; \
    }

// Define a function for printing integers
void Printint(int node, const char* fmt, ...) {
    printf(fmt, node);
}

void Printfloat(float node, const char* fmt, ...) {
    printf(fmt, node);
}

void Printdouble(double node, const char* fmt, ...) {
    printf(fmt, node);
}

void Printchar(char node, const char* fmt, ...) {
    printf(fmt, node);
}

// Define a macro for printing a linked list
#define PrintList(LinkedListType, ElementType, List, fmt, ...) \
    for (LinkedListType##Node* node = (List)->head; node != NULL; node = node->next) { \
        Print##ElementType(node->data, fmt, ##__VA_ARGS__); \
    }
 
