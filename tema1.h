// Copyright Raluca Vasilache 314 CA
#ifndef TEMA1_H__
#define TEMA1_H__

struct Node
{
	char title[31];
	char artist[31];
	char album[31];
	char year[5];
    struct Node *next, *prev;
};

struct DoublyLinkedList
{
	struct Node *head;
	struct Node *current;
	int size;
};

void init_list(struct DoublyLinkedList *list);

int search_current(struct DoublyLinkedList *list);

void add_nth_node(struct DoublyLinkedList *list, int n, char *n_title,
					char *n_artist, char *n_album, char *n_year);

void remove_nth_node(struct DoublyLinkedList *list, int n);

void free_list(struct DoublyLinkedList **pp_list);

void print_string_DoublyLinkedList(struct DoublyLinkedList *list,
									FILE *file_out);

int get_size(struct DoublyLinkedList *list);

void print_data(struct Node *node_to_print, FILE *out);

int search_node(struct DoublyLinkedList *list, struct Node *mel);

void move_next(struct DoublyLinkedList *list);

void move_prev(struct DoublyLinkedList *list);

void get_data(struct Node *n, FILE *song_file);

#endif  // TEMA1_H_
