/**
 * Author: Emre Gurkan - 150121823
 * Email: emregurkan@marun.edu.tr
 * Compile: gcc -o main main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
  int data;
  struct node* prev;
  struct node* next;
};

void ll_pushf(int, struct node**);
struct node* ll_rget_node(int, struct node**);
int ll_set_numbers(struct node** n1, struct node** n2);
void ll_free(struct node**);
int ll_fprint(struct node**);
int ll_fprintr(struct node**);

void calculate(struct node**, struct node**, struct node**);

int main(void)
{
  struct node* n1 = NULL;
  struct node* n2 = NULL;
  struct node* res = NULL;

  if (ll_set_numbers(&n1, &n2) == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  calculate(&n1, &n2, &res);

  ll_fprintr(&n1);
  ll_fprintr(&n2);
  ll_fprint(&res);

  ll_free(&n1);
  ll_free(&n2);
  ll_free(&res);

  return EXIT_SUCCESS;
}

void ll_pushf(int data, struct node** list)
{
  struct node* n = (struct node*) malloc(sizeof(struct node));

  n->data = data;
  n->prev = NULL;
  n->next = *list;

  if (*list != NULL)
  {
    (*list)->prev = n;
  }

  *list = n;

  return;
}

struct node* ll_rget_node(int index, struct node** list)
{
  int i;

  struct node* n = NULL;

  for (n = *list; n->next != NULL; n = n->next);
  for (i = 0; i < index; i++)
  {
    n = n->prev;
  }

  return n;
}

int ll_set_numbers(struct node** n1, struct node** n2)
{
  int d, s = 0;
  char c;
  FILE* file;

  if ((file = fopen("input.txt", "r")) == NULL)
  {
    return EXIT_FAILURE;
  }

  while ((c = fgetc(file)) != EOF)
  {
    if (c == '\n')
    {
      s = 1;
      continue;
    }
    
    d = c - '0';
   
    switch (s)
    {
      case 0:
        ll_pushf(d, n1);
        break;
      default:
        ll_pushf(d, n2);
        break;
    }
  }
  
  fclose(file);

  return EXIT_SUCCESS;
}

void ll_free(struct node** list)
{
  struct node* n = NULL;
  struct node* l = *list;

  while (l != NULL)
  {
    n = l->next;
    free(l);
    l = n;
  }

  *list = NULL;

  return;
}

int ll_fprint(struct node** list)
{
  char c;
  FILE* file;
  struct node* i= NULL;

  if ((file = fopen("output.txt", "a")) == NULL)
  {
    return EXIT_FAILURE;
  }
  
  fputc('\n', file);

  for (i = *list; i != NULL; i = i->next)
  {
    c = i->data + '0';
    fputc(c, file);
  }

  fclose(file);

  return EXIT_SUCCESS;
}

int ll_fprintr(struct node** list)
{
  char c;
  FILE* file;
  struct node* i= NULL;

  if ((file = fopen("output.txt", "a")) == NULL)
  {
    return EXIT_FAILURE;
  }
  
  fputc('\n', file);

  for (i = *list; i->next != NULL; i = i->next);

  for (; i != NULL; i = i->prev)
  {
    c = i->data + '0';
    fputc(c, file);
  }

  fclose(file);

  return EXIT_SUCCESS;
}

void calculate(struct node** n1, struct node** n2, struct node** res)
{
  int d, c = 0, b = 0, u = 0;

  struct node* i = NULL;
  struct node* j = NULL;
  struct node* l = NULL;

  for (i = *n2; i != NULL; i = i->next)
  {
    for (j = *n1; j != NULL; j = j->next)
    {
      d = i->data * j->data;

      if (u == 0)
      {
        ll_pushf(d, &l);
      }
      else
      {
        l->data += d;

        if (l != NULL && l->prev != NULL)
        {
          l = l->prev;
        }
        else
        {
          u = 0;
        }
      }
    }
    
    if (i->next != NULL)
    {
      u = 1;
      l = ll_rget_node(++b, &l);
    }
  }

  *res = l;

  while (l->next != NULL)
  {
    l = l->next;
  }

  while (l != (*res)->prev)
  {
    d = l->data + c;
    c = d / 10;
    d = d % 10;
    l->data = d;
    l = l->prev;
  }

  if (c != 0)
  {
    ll_pushf(c, res);
  }

  return;
}
