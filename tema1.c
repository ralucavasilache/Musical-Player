// Copyright Raluca Vasilache 314 CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./tema1.h"

// Setare valori initiale pentru campurile specifice
// structurii DoublyLinkedList

void init_list(struct DoublyLinkedList *list)
{
    list -> head = NULL;
    list -> current = NULL;
    list -> size = 0;
}

// Functie care returneaza pozitia cursorului

int search_current(struct DoublyLinkedList *list)
{
    struct Node *aux = list->head;
    int pos = 0;

    if (list -> size == 0)
    {
        return -1;
    }
    while (aux != list -> current)
    {
        aux = aux -> next;
        pos++;
    }

    return pos;
}

// Pe baza datelor trimise prin pointerul new_data,
// se creeaza un nou nod care e adaugat pe pozitia n a listei
// Pozitiile din lista sunt indexate incepand cu 0.

void add_nth_node(struct DoublyLinkedList *list, int n, char *n_title,
					char *n_artist, char *n_album, char *n_year)
{
    struct Node *newNode;
    struct Node *curr;
    int i;

    if (n < 0 || list == NULL)
    {
        return;
    }
    else if (list->size == 0)
    {
        newNode = (struct Node*)malloc(sizeof(struct Node));

        snprintf(newNode -> title, sizeof(newNode -> title), "%s", n_title);
        snprintf(newNode -> artist, sizeof(newNode->artist), "%s", n_artist);
        snprintf(newNode -> album, sizeof(newNode->album), "%s", n_album);
        snprintf(newNode -> year, sizeof(newNode->year), "%s", n_year);

        newNode->next = NULL;
        newNode->prev = NULL;
        list -> head = newNode;
        list -> current = newNode;

        list -> size++;
    }
    else if (n == 0)
    {
        newNode = (struct Node*)malloc(sizeof(struct Node));
        curr = list -> head;

        snprintf(newNode -> title, sizeof(newNode -> title), "%s", n_title);
        snprintf(newNode -> artist, sizeof(newNode->artist), "%s", n_artist);
        snprintf(newNode -> album, sizeof(newNode->album), "%s", n_album);
        snprintf(newNode -> year, sizeof(newNode->year), "%s", n_year);

        newNode -> next = list -> head;
        newNode -> prev = NULL;
        list -> head -> prev = newNode;
        list -> head = newNode;

        list -> size++;
    }
    else if (n == list->size)
    {
        newNode = (struct Node*)malloc(sizeof(struct Node));
        curr = list -> head;

        snprintf(newNode -> title, sizeof(newNode -> title), "%s", n_title);
        snprintf(newNode -> artist, sizeof(newNode->artist), "%s", n_artist);
        snprintf(newNode -> album, sizeof(newNode->album), "%s", n_album);
        snprintf(newNode -> year, sizeof(newNode->year), "%s", n_year);

        newNode -> next = NULL;

        while (curr->next != NULL)
        {
            curr = curr->next;
        }

        curr->next = newNode;
        newNode->prev = curr;

        list->size++;
    }
    else
    {
        curr = list->head;
        newNode = (struct Node*)malloc(sizeof(struct Node));

        snprintf(newNode -> title, sizeof(newNode -> title), "%s", n_title);
        snprintf(newNode -> artist, sizeof(newNode->artist), "%s", n_artist);
        snprintf(newNode -> album, sizeof(newNode->album), "%s", n_album);
        snprintf(newNode -> year, sizeof(newNode->year), "%s", n_year);

        for (i = 0; i < n-1; i++)
        {
            curr = curr->next;
        }

        newNode->next = curr->next;
        newNode->prev = curr;
        curr->next->prev = newNode;
        curr->next = newNode;

        list->size++;
    }
}

// Elimina nodul de pe pozitia n din lista
// al carei pointer este trimis ca parametru.
// Pozitiile din lista se indexeaza de la.

void remove_nth_node(struct DoublyLinkedList *list, int n)
{
	int i;
    if (list == NULL || list->head == NULL)
    {
        return;
    }

    else if (list->size == 0)
    {
        return;
    }

    else if (list->size == 1)
    {
        free(list->head);
        list->head = NULL;
        list->current = NULL;

        list->size--;
    }

    else if (n == 0)
    {
        struct Node* rmNode;
        rmNode = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        list->size--;
        free(rmNode);
        return;
    }

    else if (n == list->size-1)
    {
        struct Node* rmNode = list->head;
        struct Node* currNode = list->head;

        for (i = 0; i < n-1; i++)
        {
            rmNode = rmNode->next;
            currNode = currNode->next;
        }

        rmNode = rmNode->next;
        currNode->next = NULL;
        list->size--;

        free(rmNode);
        return;
    }
    else
    {
        struct Node* rmNode = list->head;;
        struct Node* currNode = list->head;

        if (n >= list->size)
        {
            return;
        }

        for (i = 0; i < n; i++)
        {
            rmNode = rmNode->next;
        }

        for (i = 0; i < n-1; i++)
        {
            currNode = currNode->next;
        }

        currNode->next = rmNode->next;
        rmNode->next->prev = currNode;
        list->size--;

        free(rmNode);
        return;
    }
}

// Procedura elibereaza memoria folosita de toate nodurile din lista,
// iar la sfarsit, elibereaza memoria folosita de structura lista

void free_list(struct DoublyLinkedList **pp_list)
{
	while (pp_list[0]->head)
	{
		struct Node *tmp = pp_list[0]->head;
		pp_list[0]->head = pp_list[0]->head->next;
		free(tmp);
	}
	free(*pp_list);
}

// Functia scrie in fisier datele stocate in nodurile din lista.

void print_data(struct Node *node_to_print, FILE *out)
{
    fprintf(
        out,
        "Title: %s\nArtist: %s\nAlbum: %s\nYear: %s\n",
        node_to_print->title, node_to_print->artist,
        node_to_print->album, node_to_print->year);
}

// Cauta un nod trimis ca parametru in lista inlantuita.
// Resturneaza 0 daca acesta exista, si -1 daca nu exista.

int search_node(struct DoublyLinkedList *list, struct Node *mel)
{
    struct Node *currNode;
    currNode = list->head;
    int pos = -1;

    if (list -> head == NULL)
    {
        return -1;
    }

    if (list->size == 1)
    {
        if (strcmp (list->head->title, mel->title) == 0)
        {
            return 0;
        }

        else
        {
        	return -1;
        }
    }
    while (currNode != NULL)
    {
        pos++;
        if (strcmp (currNode->title, mel->title) == 0)
        {
            return pos;
        }
        currNode = currNode->next;
    }

    return -1;
}

// Deplasarea cursorului cu o pozitie la dreapta.

void move_next(struct DoublyLinkedList *list)
{
    if (list != NULL)
    {
        if (list->current != NULL)
        {
            if (search_current(list) != list->size)
            {
                if (list->current->next != NULL)
                {
                    list->current = list->current->next;
                }
            }
        }
    }
}

// Deplasarea cursorului cu o pozitie la stanga.

void move_prev(struct DoublyLinkedList *list)
{
    if (list != NULL)
    {
        if (search_current(list) != 0)
        {
            if (list->current->prev != NULL)
            {
                list->current = list->current->prev;
            }
        }
    }
}

// Extrage datele din fisierul song trimis ca parametru
// si le memoreaza intr-o structura de tip nod.

void get_data(struct Node *n, FILE *song_file)
{
    fseek(song_file, -4, SEEK_END);
    fgets(n->year, 5, song_file);

    fseek(song_file, -34, SEEK_END);
    fgets(n->album, 31, song_file);

    fseek(song_file, -64, SEEK_END);
    fgets(n->artist, 31, song_file);

    fseek(song_file, -94, SEEK_END);
    fgets(n->title, 31, song_file);
}

int main(int argc, char **argv)
{
    struct DoublyLinkedList *list;
    list = malloc(sizeof(struct DoublyLinkedList));

    init_list(list);

    FILE *file_in = fopen(argv[1], "r");
    FILE *file_out = fopen(argv[2], "w");

    char buff[102];
    char *str;
    int i;
    // se citesc datele linie cu linie;
    while (fgets(buff, 100, file_in))
    {
        char *token = strtok_r(buff, " ", &str);

        if (token[strlen(token) - 1] == '\n')
        {
            token[strlen(token) - 1] = '\0';
        }

        // se primeste comanda ADD_FIRST
        if (strcmp(token, "ADD_FIRST") == 0)
        {
        	char pth[100];

        	// se formeaza numele fisierului mp3 si se deschide
            token = strtok_r(NULL, "\n", &str);
            snprintf(pth, sizeof(pth), "%s", "songs/");
            snprintf(pth + strlen(pth), sizeof(pth) - strlen(pth), "%s", token);
            FILE *song = fopen(pth, "rb");

            // se aloca un nou nod in care se introduc
            // datele citite din fisierul song
            struct Node *new = malloc(sizeof(struct Node));
            get_data(new, song);

            // se cauta pozitia cursorului
            // se verifica existenta melodiei in playlist
            int exist = search_node(list, new);
            int pos_cur = search_current(list);

            // daca melodia nu exista, se adauga pe pozitia 0
            if (exist == -1)
            {
               add_nth_node(list, 0,
               				new->title, new->artist,
               				new->album, new->year);
            }
            // daca melodia exista se adauga pe pozitia 0
            // si se sterge de pe pozitia existenta
            else
            {
            	// daca cursorul pointeaza la aceasta
            	// se muta la stanga sau la dreapta, dupa caz
                if (exist == pos_cur)
                {
                    if (pos_cur == list->size -1 && list->size > 1)
                    {
                        move_prev(list);
                    }
                    else if (list->size > 1)
                    {
                        move_next(list);
                    }
                }

               add_nth_node(list, 0,
               				new->title, new->artist,
               				new->album, new->year);
                remove_nth_node(list, exist + 1);
            }

            fclose(song);
            free(new);
        }
        // se primeste comanda ADD_LAST
        else if (strcmp (token, "ADD_LAST") == 0)
        {
        	char pth[100];

        	// se formeaza numele fisierului mp3 si se deschide
            token = strtok_r(NULL, "\n", &str);
            snprintf(pth, sizeof(pth), "%s", "songs/");
            snprintf(pth + strlen(pth), sizeof(pth) - strlen(pth), "%s", token);
            FILE *song = fopen(pth, "rb");

            // se aloca un nou nod in care se introduc datele
            // citite din fisierul song
            struct Node *new = malloc(sizeof(struct Node));
            get_data(new, song);

            // se cauta pozitia cursorului
            // se verifica existenta melodiei in playlist
            int exist = search_node(list, new);
            int pos_cur = search_current(list);

            // daca melodia nu exista, se adauga pe ultima pozitie
            if (exist == -1)
            {
               add_nth_node(list, list->size,
               				new->title, new->artist,
               				new->album, new->year);
            }
            // daca melodia exista se adauga pe ultima pozitie
            // si se sterge de pe pozitia existenta
            else
            {
            	// daca cursorul pointeaza la aceasta
            	// se muta la stanga sau la dreapta, dupa caz
                if (exist == pos_cur)
                {
                    if (pos_cur == list->size -1 && list->size > 1)
                    {
                        move_prev(list);
                    }
                    else if (list->size > 1)
                    {
                        move_next(list);
                    }
                }

               add_nth_node(list, list->size,
               				new->title, new->artist,
               				new->album, new->year);
                remove_nth_node(list, exist);
            }

            fclose(song);
            free(new);
        }
        else if (strcmp (token, "ADD_AFTER") == 0 && list->current != NULL)
        {
        	char pth[100];

            token = strtok_r(NULL, "\n", &str);
            snprintf(pth, sizeof(pth), "%s", "songs/");
            snprintf(pth + strlen(pth), sizeof(pth) - strlen(pth), "%s", token);
            FILE *song = fopen(pth, "rb");

            struct Node *new = malloc(sizeof(struct Node));
            get_data(new, song);

            if (list->size > 0)
            {
                if (strcmp(list->current->title, new->title) != 0)
                {
                    int pos_cur = search_current(list);
                    int exist = search_node(list, new);

                    if (exist == -1 && list->head != NULL)
                    {
		               add_nth_node(list, pos_cur + 1,
		               				new->title, new->artist,
		               				new->album, new->year);
                    }
                    else if (list->head != NULL)
                    {
                        remove_nth_node(list, exist);
                        if (exist > pos_cur)
                        {
			               add_nth_node(list, pos_cur + 1,
			               				new->title, new->artist,
			               				new->album, new->year);
                        }
                        if (exist < pos_cur)
                        {
			               add_nth_node(list, pos_cur,
			               				new->title, new->artist,
			               				new->album, new->year);
                        }
                    }
                }
            }

            free(new);
            fclose(song);
        }
        // se primeste comanda SHOW_FIRST
        else if (strcmp(token, "SHOW_FIRST") == 0)
        {
        	// daca lista nu este goala
        	// se afiseaza primul nod
            if (list->size > 0)
            {
                print_data(list->head, file_out);
            }
            // altfel se afiseaza mesajul de eroare
            else if (list->size == 0)
            {
                fprintf(file_out, "Error: show empty playlist\n");
            }
        }

        else if (strcmp(token, "SHOW_LAST") == 0)
        {
            if (list->size == 0)
            {
                fprintf(file_out, "Error: show empty playlist\n");
            }
            else
            {
                struct Node *aux = list ->head;
                for (i = 0; i < list->size-1; i++)
                {
                  aux = aux->next;
                }
                print_data(aux, file_out);
            }
        }

        else if (strcmp(token, "SHOW_CURR") == 0)
        {
            if (list->size == 0)
            {
                fprintf(file_out, "Error: show empty playlist\n");
            }
            else
            {
                print_data(list->current, file_out);
            }
        }

        else if (strcmp(token, "SHOW_PLAYLIST") == 0)
        {
            fprintf(file_out, "[");
            struct Node *aux = list ->head;

           for (i = 0; i < list->size; i++)
           {
              fprintf(file_out, "%s", aux->title);

              if (i != list->size - 1)
              {
                fprintf(file_out, "; ");
              }
              aux = aux->next;
           }

           fprintf(file_out, "]\n");
        }

        else if (strcmp(token, "MOVE_NEXT") == 0)
        {
            if (list->size == 0)
            {
                fprintf(file_out, "Error: no track playing\n");
            }
            else if (list->size > 0)
            {
                move_next(list);
            }
        }

        else if (strcmp(token, "MOVE_PREV") == 0)
        {
            if (list->size == 0)
            {
                fprintf(file_out, "Error: no track playing\n");
            }
            else if (list->size > 0)
            {
                move_prev(list);
            }
        }

        else if (strcmp(token, "DEL_FIRST") == 0)
        {
            if (list->size == 0)
            {
                fprintf(file_out, "Error: delete from empty playlist\n");
            }
            if (list->current == list->head && list->size > 1)
            {
                move_next(list);
            }
            remove_nth_node(list, 0);
        }

        else if (strcmp(token, "DEL_LAST") == 0)
        {
            if (list->size == 0)
            {
                fprintf(file_out, "Error: delete from empty playlist\n");
            }
            if (search_current(list) == list->size-1)
            {
                move_prev(list);
            }
            remove_nth_node(list, list->size-1);
        }
        // se primeste comanda DEL_CURR
        else if (strcmp(token, "DEL_CURR") == 0)
        {
        	// se cauta pozitia cursorului
            int pos_cur = search_current(list);

            // daca cursorul nu exista se afiseaza mesajul de eroare
            if (pos_cur == -1 || list->current == NULL)
            {
                fprintf(file_out, "Error: no track playing\n");
            }

            // daca cursorul se afla pe ultima melodie
            // se muta o pozitie la stanga
            if (pos_cur == list->size-1)
            {
                if (list->size >1)
                {
                    move_prev(list);
                }
            }
            // in caz contrar, daca lista are mai mult de un element
            // se muta o pozitie la dreapta
            else if (list->size > 1)
            {
                move_next(list);
            }
            // se sterge nodul din lista
            remove_nth_node(list, pos_cur);
        }
        // se primeste comanda DEL_SONG
        else if (strcmp(token, "DEL_SONG") == 0)
        {
        	char pth[100];

        	// se formeaza numele fisierului mp3 si se deschide
            token = strtok_r(NULL, "\n", &str);
            snprintf(pth, sizeof(pth), "%s", "songs/");
            snprintf(pth + strlen(pth), sizeof(pth) - strlen(pth), "%s", token);
            FILE *song = fopen(pth, "rb");

            struct Node *new = malloc(sizeof(struct Node));
            get_data(new, song);

            // se cauta pozitie melodiei in lista
            int pos_del = search_node(list, new);

            // daca melodia nu exista se afiseaza mesajul de eroare
            if (pos_del == -1)
            {
                fprintf(file_out, "Error: no song found to delete\n");
            }

            // altfel se sterge melodia din lista
            else
            {
            	// daca cursorul se afla pe melodie
            	// se muta la stanga sau la dreapta, dupa caz
                if (search_current(list) == pos_del)
                {
                    if (pos_del == list->size - 1)
                    {
                        move_prev(list);
                    }
                    else
                    {
                        move_next(list);
                    }
                }
                remove_nth_node(list, pos_del);
            }

            fclose(song);
            free(new);
        }
    }

    free_list(&list);
    fclose(file_in);
    fclose(file_out);
    return 0;
}
