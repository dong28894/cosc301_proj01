#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

/* your list function definitions */
struct node {
    int value;
    struct node *next; 
};

void list_clear(struct node *list) {
    while (list != NULL) {
        struct node *tmp = list;
        list = list->next;
        free(tmp);
    }
}

void list_print(const struct node *list) {
    int i = 0;
    printf("In list_print\n");
    while (list != NULL) {
        printf("List item %d: %s\n", i++, list->name);
        list = list->next;
    }
}

int list_delete(int value, struct node **head) {
    // your code here
	struct node *temp = *head;
	if (temp->value == value){
		*head = temp->next;
		free(temp);
		return 1;
	}
	temp = temp->next;
	struct node *prev = *head;
	while (temp != NULL){
		if (temp->value == value){
			prev->next = temp->next;
			free(temp);
			return 1;
		}
		prev = temp;
		temp = temp->next;
	}
	return 0;
}

void list_append(int value, struct node **head) {
    // your code here
	struct node *newNode = malloc(sizeof(struct node));
	struct node *temp = *head;
	newNode->value = value;
	newNode->next = NULL;
	if (*head == NULL){
		*head = newNode;
	}else{
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newNode;
	}
}

void list_reverse(struct node **head) {
    // your code here
	struct node *prev = NULL;
	struct node *curr = *head;
	struct node *next = NULL;
	while (curr != NULL){
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

void list_sort(struct node **head) {
    // your code here
	struct node *newHead = NULL;
	struct node *curr = NULL;
	struct node *temp;
	struct node *minPrev = NULL;
	struct node *min;
	while (*head != NULL){
		min = *head;
		temp = *head;
		//Find min
		while ((temp->next) != NULL){
			if ((temp->next)->value < min->value){
				minPrev = temp;
				min = temp->next;
			}
			temp = temp->next;
		}
		//Append min to new list
		if (newHead == NULL){
			newHead = min;
		}else{
			curr->next = min;			
		}
		curr = min;
		//Take min out of original list
		if (minPrev == NULL){
			*head = (*head)->next;
		}else{
			minPrev->next = min->next;
			minPrev = NULL;
		}
	}
	*head = newHead;
}

