#ifndef RESPONSE_H_INCLUDED
#define RESPONSE_H_INCLUDED


#include <stdbool.h>
#include <string.h>
#include "categorys.h"  // Includes categorys_pointer and categorys-related functions
#include "books.h"  // Includes books_pointer and books-related functions
// Core Functions Prototypes

// Add a new category to the category list
void addCategory(categorys_pointer *head, char *name);

// Search for a category by name
categorys_pointer searchCategory(categorys_pointer head, char *name);

// Add book to existing category, or create the category if it doesn't exist
bool addBookToCategory(categorys_pointer *head, char *categoryName, char *Title, char *Author,
                       char *Publisher, int NumberExp);

// Add book to category without search function
bool addBookToCategoryWithOutSearchFunction(categorys_pointer *head, char *categoryName, char *Title, char *Author,
                                            char *Publisher, int NumberExp);

// Search for a book by Author
books_pointer searchBookByAuthor(categorys_pointer head, char *Author);

// Search for a book by Title
books_pointer searchBookByTitle(categorys_pointer head, char *Title);

// Delete a category by name
void deleteCategory(categorys_pointer *head, char *name);

// Delete a single book from the book list by Title
void deleteBook(books_pointer *head, char *Title);

// Delete all categories
void deleteAllCategories(categorys_pointer *head);

// Delete all books in the list
void deleteAllBooks(books_pointer *head);

// Save Author's books to a binary file
void saveBooksByAuthorToBinaryFile(categorys_pointer head, char *Author);

// Delete Author's binary file
void deleteAuthorFile(char *Author);

// Rename Author's binary file
void renameAuthorFile(char *oldAuthor, char *newAuthor);

// Import books from a binary file into a category
void importBooksFromFile(categorys_pointer *head, char *filename, char *categoryName);

// List all books in a binary file
void listBooksInFile(char *filename);

#endif // RESPONSE_H_INCLUDED
