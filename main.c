/**
 * Author: Emre Gurkan - 150121823
 * Email: emregurkan@marun.edu.tr
 * Compile: gcc -o main main.c
 */

#include <stdio.h>
#include <stdlib.h>

struct node
{
  int data;
  struct node* prev;
  struct node* next;
};

void ll_pushf(int, struct node**);
int ll_set_numbers(struct node** n1, struct node** n2);
int ll_fprint(struct node**);
int ll_fprintr(struct node**);
void ll_free(struct node**);

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

int ll_set_numbers(struct node** n1, struct node** n2)
{
  int d, n = 0;
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
      n = 1;
      continue;
    }
    
    d = c - '0';
   
    switch (n)
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

int ll_fprint(struct node** list)
{
  FILE* file;
  struct node* i = NULL;

  if ((file = fopen("output.txt", "a")) == NULL)
  {
    return EXIT_FAILURE;
  }
  
  for (i = *list; i != NULL; i = i->next)
  {
    fprintf(file, "%i", i->data);
  }

  fprintf(file, "\n");

  fclose(file);

  return EXIT_SUCCESS;
}

int ll_fprintr(struct node** list)
{
  FILE* file;
  struct node* i = NULL;

  if ((file = fopen("output.txt", "a")) == NULL)
  {
    return EXIT_FAILURE;
  }

  for (i = *list; i->next != NULL; i = i->next);

  for (; i != NULL; i = i->prev)
  {
    fprintf(file, "%i", i->data);
  }

  fprintf(file, "\n");

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

void calculate(struct node** n1, struct node** n2, struct node** res)
{
  char u = '0'; // 8 bit
  int d, c = 0;
  struct node* i = NULL;
  struct node* j = NULL;
  struct node* t = NULL;

  for (i = *n2; i != NULL; i = i->next)
  {
    for (j = *n1; j != NULL; j = j->next)
    {
      d = i->data * j->data + c;

      switch (u)
      {
        case '0':
          c = d / 10;
          d = d % 10;

          ll_pushf(d, res);

          if (i == *n2 && j == *n1)
          {
            t = *res;
          }

          break;

        default:
          (*res)->data += d;
          c = (*res)->data / 10;
          (*res)->data = (*res)->data % 10;

          if (*res != NULL && (*res)->prev != NULL)
          {
            *res = (*res)->prev;
          }
          else
          {
            u = '0';
          }
          
          break;
      }

      if (j->next == NULL && c != 0)
      {
        ll_pushf(c, res);
        c = 0;
      }
    }
    
    if (i->next != NULL)
    {
      u = '1';
      t = t->prev;
      *res = t;
    }
  }

  return;
}
