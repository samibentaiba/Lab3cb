#ifndef BOOKS_H_INCLUDED
#define BOOKS_H_INCLUDED

#include <stdbool.h>
#include <string.h>

// Structure Definition
typedef struct bookNode {
    char Title[50];
    char Author[50];
    char Publisher[50];
    int NumberExp;
    struct bookNode *nextBookNode;
} books;

typedef books *books_pointer;

// Function Prototypes for Books
books_pointer allocBook();
void freeBookNode(books_pointer *Books);
void setBookTitle(books_pointer Books, char *Title);
void setBookAuthor(books_pointer Books, char *Author);
void setBookPublisher(books_pointer Books, char *Publisher);
void setBookNumber(books_pointer Books, int Number);
void setBookNext(books_pointer Books, books_pointer NextBook);
void setBookInfo(books_pointer Books, char *Title, char *Author, char *Publisher, int NumberExp);
bool IsBookEmpty(books_pointer P);
char *getBookTitle(books_pointer P);
char *getBookAuthor(books_pointer P);
char *getBookPublisher(books_pointer P);
int getBookNumber(books_pointer P);
books_pointer getNextBook(books_pointer P);

#endif // BOOKS_H_INCLUDED
