#include "categorys.h"
#include "books.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "response.h"
// ---- Core Functions ----

// Add a new category to the category list

void addCategory(categorys_pointer *head, char *name) {
    if (*head == NULL) {
        *head = allocCategory();
        setCategoryInfo(*head, name, NULL, 0);
        return;
    }
    categorys_pointer temp = *head;
    while (temp->nextCategoryNode != NULL) {
        temp = temp->nextCategoryNode;
    }
    temp->nextCategoryNode = allocCategory();
    setCategoryInfo(temp->nextCategoryNode, name, NULL, 0);
}

// Search for a category by name

categorys_pointer searchCategory(categorys_pointer head, char *name) {
    while (head != NULL) {
        if (strcmp(head->Name, name) == 0) return head;
        head = head->nextCategoryNode;
    }
    return NULL;
}

bool addBookToCategoryWithOutSearchFunction(categorys_pointer *head, char *categoryName, char *Title, char *Author,
                                            char *Publisher, int NumberExp) {
    categorys_pointer cat = NULL;
    while (*head != NULL) {
        if (strcmp((*head)->Name, categoryName) == 0)
            cat = *head;
        *head = (*head)->nextCategoryNode;
    }
    books_pointer newBook = allocBook();
    setBookInfo(newBook, Title, Author, Publisher, NumberExp);
    if (cat == NULL) {
        addCategory(head, categoryName);
        setCategoryInfo(*head, categoryName, newBook, 1);
        while (*head != NULL) {
            if (strcmp((*head)->Name, categoryName) == 0)
                cat = *head;
            *head = (*head)->nextCategoryNode;
        }
        cat->BooksNumber++; // its impossible to be NULL because we are already add it !!
        return true;
    } else {
        books_pointer temp = cat->Books;
        if (temp == NULL) {
            cat->Books = newBook;
            cat->BooksNumber++;
            return true;
        } else {
            while (temp->nextBookNode != NULL) {
                if (temp == newBook)
                    return false;
                else
                    temp = temp->nextBookNode;
            }
            temp->nextBookNode = newBook;
            cat->BooksNumber++;
            return true;
        }
    }
}

// Add book to existing category, or create the category if it doesn't exist

// Search for a book by Author
// NOTE: Cannot mark parameters as '' here because 'strcpy' requires non- char*.
// Making them '' would prevent modifying or copying their values into struct fields.

bool addBookToCategory(categorys_pointer *head, char *categoryName, char *Title, char *Author,
                       char *Publisher, int NumberExp) {
    categorys_pointer cat = searchCategory(*head, categoryName);
    books_pointer newBook = allocBook();
    setBookInfo(newBook, Title, Author, Publisher, NumberExp);
    if (cat == NULL) {
        addCategory(head, categoryName);
        setCategoryInfo(*head, categoryName, newBook, 1);
        cat = searchCategory(*head, categoryName);
        cat->BooksNumber++;
        return true;
    } else {
        books_pointer temp = cat->Books;
        if (temp == NULL) {
            cat->Books = newBook;
            cat->BooksNumber++;
            return true;
        } else {
            while (temp->nextBookNode != NULL) {
                if (temp == newBook)
                    return false;
                else
                    temp = temp->nextBookNode;
            }
            temp->nextBookNode = newBook;
            cat->BooksNumber++;
            return true;
        }
    }
}


books_pointer searchBookByAuthor(categorys_pointer head, char *Author) {
    while (head != NULL) {
        books_pointer book = head->Books;
        while (book != NULL) {
            if (strcmp(book->Author, Author) == 0) return book;
            book = book->nextBookNode;
        }
        head = head->nextCategoryNode;
    }
    return NULL;
}

// Search for a book by Title
books_pointer searchBookByTitle(categorys_pointer head, char *Title) {
    while (head != NULL) {
        books_pointer book = head->Books;
        while (book != NULL) {
            if (strcmp(book->Title, Title) == 0) return book;
            book = book->nextBookNode;
        }
        head = head->nextCategoryNode;
    }
    return NULL;
}

// Delete a category by name
void deleteCategory(categorys_pointer *head, char *name) {
    categorys_pointer temp = *head, prev = NULL;

    while (temp != NULL && strcmp(temp->Name, name) != 0) {
        prev = temp;
        temp = temp->nextCategoryNode;
    }

    if (temp == NULL) return; // Not found

    // Delete all books in category
    books_pointer book = temp->Books;
    while (book != NULL) {
        books_pointer next = book->nextBookNode;
        free(book);
        book = next;
    }

    // Remove category from list
    if (prev == NULL) {
        *head = temp->nextCategoryNode;
    } else {
        prev->nextCategoryNode = temp->nextCategoryNode;
    }

    free(temp);
}

// Delete a single book from the book list by Title
void deleteBook(books_pointer *head, char *Title) {
    books_pointer temp = *head, prev = NULL;

    while (temp != NULL && strcmp(temp->Title, Title) != 0) {
        prev = temp;
        temp = temp->nextBookNode;
    }

    if (temp == NULL) return; // Not found

    // Remove book from list
    if (prev == NULL) {
        *head = temp->nextBookNode;
    } else {
        prev->nextBookNode = temp->nextBookNode;
    }

    free(temp);
}


// Delete all categories
void deleteAllCategories(categorys_pointer *head) {
    while (*head != NULL) {
        deleteCategory(head, (*head)->Name);
    }
}

// Delete all books in the list
void deleteAllBooks(books_pointer *head) {
    while (*head != NULL) {
        deleteBook(head, (*head)->Title);
    }
}

// Save Author book in binary file
void saveBooksByAuthorToBinaryFile(categorys_pointer head, char *Author) {
    // Step 1: Count matching books and prepare output filename
    int count = 0;
    char filename[100];
    snprintf(filename, sizeof(filename), "%s_books.bin", Author);

    // Step 2: Open binary file for writing
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Failed to create file %s\n", filename);
        return;
    }

    // Step 3: Traverse all categories and books
    while (head != NULL) {
        books_pointer book = head->Books;
        while (book != NULL) {
            if (strcmp(book->Author, Author) == 0) {
                fwrite(book, sizeof(books), 1, fp);
                count++;
            }
            book = book->nextBookNode;
        }
        head = head->nextCategoryNode;
    }

    fclose(fp);

    // Step 4: Notify result
    if (count > 0) {
        printf("Saved %d book(s) by %s to %s\n", count, Author, filename);
    } else {
        printf("No books found for Author %s. No file created.\n", Author);
        remove(filename); // Clean up empty file
    }
}

void deleteAuthorFile(char *Author) {
    char filename[100];
    snprintf(filename, sizeof(filename), "%s_books.bin", Author);

    if (remove(filename) == 0) {
        printf("File %s deleted successfully.\n", filename);
    } else {
        printf("Failed to delete file %s (file may not exist).\n", filename);
    }
}

void renameAuthorFile(char *oldAuthor, char *newAuthor) {
    char oldFilename[100], newFilename[100];
    snprintf(oldFilename, sizeof(oldFilename), "%s_books.bin", oldAuthor);
    snprintf(newFilename, sizeof(newFilename), "%s_books.bin", newAuthor);

    if (rename(oldFilename, newFilename) == 0) {
        printf("Renamed %s to %s successfully.\n", oldFilename, newFilename);
    } else {
        printf("Failed to rename %s to %s.\n", oldFilename, newFilename);
    }
}

void importBooksFromFile(categorys_pointer *head, char *filename, char *categoryName) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Failed to open file %s\n", filename);
        return;
    }

    books tempBook;
    while (fread(&tempBook, sizeof(books), 1, fp) == 1) {
        addBookToCategory(head, categoryName, tempBook.Title, tempBook.Author, tempBook.Publisher, tempBook.NumberExp);
    }

    fclose(fp);
    printf("Imported books from %s into category '%s'.\n", filename, categoryName);
}

void listBooksInFile(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("File %s not found.\n", filename);
        return;
    }

    books book;
    int count = 0;
    printf("Listing books in %s:\n", filename);
    while (fread(&book, sizeof(books), 1, fp) == 1) {
        printf("  Title: %s | Author: %s | Publisher: %s | Copies: %d\n",
               book.Title, book.Author, book.Publisher, book.NumberExp);
        count++;
    }

    fclose(fp);

    if (count == 0) {
        printf("No books found in file.\n");
    }
}

