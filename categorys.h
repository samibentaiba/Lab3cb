#ifndef CATEGORYS_H_INCLUDED
#define CATEGORYS_H_INCLUDED

#include <stdbool.h>
#include "books.h"  // Include books.h to use books_pointer and related functions

// Structure Definition
typedef struct categoryNode {
    char Name[50];
    int BooksNumber;
    books_pointer Books;
    struct categoryNode *nextCategoryNode;
} categorys;

typedef categorys *categorys_pointer;

// Function Prototypes for Categories
categorys_pointer allocCategory();
void freeCategoryNode(categorys_pointer *Categorys);
void setCategoryTitle(categorys_pointer Categorys, char *Name);
void setCategoryBooksNumber(categorys_pointer Categorys, int BooksNumber);
void setCategoryBooks(categorys_pointer Categorys, books_pointer Books);
void setCategoryNext(categorys_pointer Categorys, categorys_pointer NextCategory);
void setCategoryInfo(categorys_pointer P, char *name, books_pointer Books, int BooksNumber);
bool IsCategoryEmpty(categorys_pointer P);
char *getCategoryName(categorys_pointer P);
categorys_pointer getNextCategory(categorys_pointer P);
books_pointer getCategoryBooks(categorys_pointer P);
int getCategoryBooksNumber(categorys_pointer P);

#endif // CATEGORYS_H_INCLUDED
