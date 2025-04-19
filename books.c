#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "books.h"
// ---- Utility Functions ----

books_pointer allocBook() {
    return (books_pointer) malloc(sizeof(books));
}
void freeBookNode(books_pointer *Books){
    free(*Books);
    *Books = NULL;
}

void setBookTitle(books_pointer Books, char *Title) {
    strcpy(Books->Title, Title);
}

void setBookAuthor(books_pointer Books, char *Author) {
    strcpy(Books->Author, Author);
}

void setBookPublisher(books_pointer Books, char *Publisher) {
    strcpy(Books->Publisher, Publisher);
}

void setBookNumber(books_pointer Books, int Number) {
    Books->NumberExp = Number;
}

void setBookNext(books_pointer Books, books_pointer NextBook) {
    Books->nextBookNode = NextBook;
}

void setBookInfo(books_pointer Books, char *Title, char *Author, char *Publisher, int NumberExp) {
    setBookTitle(Books, Title);
    setBookAuthor(Books, Author);
    setBookPublisher(Books, Publisher);
    setBookNumber(Books, NumberExp);
    setBookNext(Books, NULL);
}

bool IsBookEmpty(books_pointer P) {
    return P == NULL;
}

char *getBookTitle(books_pointer P) {
    return P->Title;
}

char *getBookAuthor(books_pointer P) {
    return P->Author;
}

char *getBookPublisher(books_pointer P) {
    return P->Publisher;
}

int getBookNumber(books_pointer P) {
    return P->NumberExp;
}

books_pointer getNextBook(books_pointer P) {
    return P->nextBookNode;
}
