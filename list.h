#ifndef __LIST_H__
#define __LIST_H__

/* your list data structure declarations */
struct node {
    int value;
    struct node *next; 
};

/* your function declarations associated with the list */
void list_clear(struct node *);
void list_print(const struct node *);
int list_delete(int , struct node **);
void list_append(int , struct node **);
void list_reverse(struct node **);
void list_sort(struct node **);

#endif // __LIST_H__
