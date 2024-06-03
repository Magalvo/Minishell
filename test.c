#include "../../include/minishell.h"
// Swap function to swap two environment nodes
void swap(t_env **head, t_env *node1, t_env *node2) {
    if (node1 == node2) return;

    t_env *prev1 = NULL;
    t_env *prev2 = NULL;
    t_env *temp = *head;

    // Find previous nodes
    while (temp && temp->next && temp->next != node1 && temp->next != node2) {
        if (temp->next == node1) prev1 = temp;
        if (temp->next == node2) prev2 = temp;
        temp = temp->next;
    }

    // Swap previous pointers
    if (prev1) prev1->next = node2;
    else *head = node2;

    if (prev2) prev2->next = node1;
    else *head = node1;

    // Swap next pointers
    temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;
}

// Bubble sort algorithm to sort environment nodes by key
void bubbleSort(t_env **head) {
    int swapped;
    t_env *ptr1;
    t_env *lptr = NULL;

    if (*head == NULL) return;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->key, ptr1->next->key) > 0) {
                swap(head, ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Print the environment nodes
void printEnv(t_env *head) {
    while (head != NULL) {
        printf("Key: %s, Value: %s\n", head->key, head->value);
        head = head->next;
    }
}

// Function to add a new node to the environment list
void addNode(t_env **head, char *key, char *value) {
    t_env *newNode = (t_env *)malloc(sizeof(t_env));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = *head;
    *head = newNode;
}

// Function to free the memory allocated for the environment list
void freeEnvList(t_node *head) {
    while (head != NULL) {
        t_node *temp = head;
        head = head->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
}


