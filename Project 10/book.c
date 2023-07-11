#include "book.h"
#include "readline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct book *head = NULL;
struct book *add_to_end(struct book *list)
{
  struct book *new_node = malloc(sizeof(struct book));
  if(new_node == NULL)
  {
    printf("Error: malloc failed to allocate memory\n");
    free(new_node); //new_node is NULL so is there anything to free
    exit(EXIT_FAILURE);
  }
  //Ask the user to enter a book’s title, author’s first name, author’s last name
  printf("Enter title: ");
  read_line(new_node->title, TITLE_LEN);
  printf("Enter author first name: ");
  read_line(new_node->first, NAME_LEN);
  printf("Enter author last name: ");
  read_line(new_node->last, NAME_LEN);
  printf("Enter classroom: ");
  read_line(new_node->classroom, ROOM_LEN);
  //If the list is empty, the function should return the pointer to the newly created linked list. Otherwise, add the book to the end of the linked list and return the pointer to the linked list.
  if(head == NULL)
  {
    printf("Enter book's price: ");
    scanf("%lf", &new_node->price);
    head = new_node;
    return head;
  }
  //Check whether the book has already existed by title, author’s name, and classroom. If the book has the same title, author’s name, and classroom with an existing book in the list, the function should print a message about book already exists and exit the function. 
  struct book *cur, *prev;
  for(cur = head, prev = NULL; cur != NULL && (strcmp(new_node->last, cur->last) > 0); prev = cur, cur = cur->next)
  {
    //printf("%-50s%-15s%-20s%-12s%-5.2lf\n", cur->title, cur->first, cur->last, cur->classroom, cur->price);
  }
  for(cur = cur; cur != NULL && (strcmp(new_node->last, cur->last) == 0) && (strcmp(new_node->first, cur->first) > 0); prev = cur, cur = cur->next)
  {
    //printf("%-50s%-15s%-20s%-12s%-5.2lf\n", cur->title, cur->first, cur->last, cur->classroom, cur->price);
  }
  
  if(cur != NULL && strcmp(new_node->title, cur->title) == 0 && strcmp(new_node->first, cur->first) == 0 && strcmp(new_node->last, cur->last) == 0 && strcmp(new_node->classroom, cur->classroom) == 0)
    {
        printf("Book already exists\n");
        free(new_node);
        return list;
    }
  printf("Enter book's price: ");
  scanf("%lf", &new_node->price);
  new_node->next = cur;
  if(prev == NULL)
  {
    head = new_node;
  }
  else
  {
    prev->next = new_node;
  }
  return list;
    
//  //If the book does not exist, ask the user to enter price, allocate memory for it, store the data, and add it to the end of the linked list. 
//  
//  list->next = new_node;
//  list = list->next;
//  return list;
}
void search(struct book *list)
{
  struct book *p = head;
  char input[TITLE_LEN + 1];
  int i = 0;
  //Ask the user to enter the book’s title.
  printf("Enter title: ");
  read_line(input, TITLE_LEN);
  
  while(p != NULL)
  {
    if(strcmp(p->title, input) == 0)
    {
      //Find all books with the title. Display title, author name, classroom, and price.
      printf("%s\t%s\t%s\t%s\t%.2lf\n", p->title, p->first, p->last, p->classroom, p->price);
      i++; //Not needed, counts how mant books match, still used to check if book is found or not
    }
    p = p->next;
  }
  //If the book is not found, print a message.
  if(i == 0)
  {
    printf("Book not found. To add a new book, enter operation code: a\n");
  }
  return;
}
void print_list(struct book *list)
{
  struct book *p = head;
  printf("Title                                           First Name      Last Name       Classroom  	Price\n"); //from try_requests
  while(p != NULL)
  {
    //print the title, author, price, and classroom of all books in the list.
    printf("%-50s%-15s%-20s%-12s%-5.2lf\n", p->title, p->first, p->last, p->classroom, p->price);
    p = p->next;
  }
}
void clear_list(struct book *list)
{
  //when the user exists the program, all the memory allocated for the linked list should be deallocated.
  struct book *p;
  while(head != NULL)
  {
    p = head;
    head = head->next;
    if(p != NULL)
    {
      free(p);
    }
  }
  return;
}