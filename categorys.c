#include "books.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "categorys.h"
// ---- Utility Functions ----

// Category Functions
categorys_pointer allocCategory() {
    return (categorys_pointer) malloc(sizeof(categorys));
}

void freeCategoryNode(categorys_pointer *Categorys) {
    free(*Categorys);
    *Categorys = NULL;
}

void setCategoryTitle(categorys_pointer Categorys, char *Name) {
    strcpy(Categorys->Name, Name);
}

void setCategoryBooksNumber(categorys_pointer Categorys, int BooksNumber) {
    Categorys->BooksNumber = BooksNumber;
}

void setCategoryBooks(categorys_pointer Categorys, books_pointer Books) {
    Categorys->Books = Books;
}

void setCategoryNext(categorys_pointer Categorys, categorys_pointer NextCategory) {
    Categorys->nextCategoryNode = NextCategory;
}

void setCategoryInfo(categorys_pointer P, char *name, books_pointer Books, int BooksNumber) {
    strcpy(P->Name, name);
    P->Books = Books;
    P->BooksNumber = BooksNumber;
    P->nextCategoryNode = NULL;
}

bool IsCategoryEmpty(categorys_pointer P) {
    return P == NULL;
}

char *getCategoryName(categorys_pointer P) {
    return P->Name;
}

categorys_pointer getNextCategory(categorys_pointer P) {
    return P->nextCategoryNode;
}

books_pointer getCategoryBooks(categorys_pointer P) {
    return P->Books;
}

int getCategoryBooksNumber(categorys_pointer P) {
    return P->BooksNumber;
}
