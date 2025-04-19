#include "categorys.h"
#include "response.h"
#include "books.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tests.h"
// ---- Test Functions ----

void testAddCategoryAndSearch() {
    printf("\n--- testAddCategoryAndSearch ---\n");
    categorys_pointer list = NULL;
    addCategory(&list, "History");

    categorys_pointer found = searchCategory(list, "History");
    if (found) {
        printf("Category added and found: %s\n", found->Name);
    }
}

void testAddBookToCategory() {
    printf("\n--- testAddBookToCategory ---\n");
    categorys_pointer list = NULL;

    addBookToCategory(&list, "Science", "Physics 101", "Dr. Smith", "SciPub", 3);
    addBookToCategory(&list, "Science", "Chemistry Basics", "Dr. Brown", "SciPub", 2);

    categorys_pointer cat = searchCategory(list, "Science");
    if (cat) {
        printf("Category: %s has %d books.\n", cat->Name, cat->BooksNumber);
    }

    deleteAllCategories(&list);
}

void testSearchBookByAuthor() {
    printf("\n--- testSearchBookByAuthor ---\n");
    categorys_pointer list = NULL;

    addBookToCategory(&list, "Tech", "C Programming", "Dennis Ritchie", "TechBooks", 5);

    books_pointer found = searchBookByAuthor(list, "Dennis Ritchie");
    if (found) {
        printf("Found book by Dennis Ritchie: %s\n", found->Title);
    }

    deleteAllCategories(&list);
}

void testSearchBookByTitle() {
    printf("\n--- testSearchBookByTitle ---\n");
    categorys_pointer list = NULL;

    addBookToCategory(&list, "Tech", "Clean Code", "Robert C. Martin", "Prentice Hall", 4);

    books_pointer found = searchBookByTitle(list, "Clean Code");
    if (found) {
        printf("Found book Titled 'Clean Code': Author: %s\n", found->Author);
    }

    deleteAllCategories(&list);
}

void testDeleteCategory() {
    printf("\n--- testDeleteCategory ---\n");
    categorys_pointer list = NULL;

    addBookToCategory(&list, "Health", "Yoga Basics", "Yogi Bear", "WellnessPub", 1);
    deleteCategory(&list, "Health");

    categorys_pointer cat = searchCategory(list, "Health");
    if (!cat) {
        printf("Category 'Health' successfully deleted.\n");
    }
}

void testDeleteAllCategories() {
    printf("\n--- testDeleteAllCategories ---\n");
    categorys_pointer list = NULL;

    addBookToCategory(&list, "Travel", "Paris Guide", "Rick Steves", "TravelBooks", 2);
    addBookToCategory(&list, "Travel", "Tokyo Guide", "Yuki Tanaka", "TravelBooks", 1);

    deleteAllCategories(&list);

    if (list == NULL) {
        printf("All categories deleted successfully.\n");
    }
}

void testDeleteBooks() {
    printf("\n--- testDeleteBooks ---\n");

    // Manually create a book list
    books_pointer bookList = NULL;

    // Add books manually
    books_pointer b1 = allocBook();
    setBookInfo(b1, "Book One", "Author A", "Publisher A", 2);
    bookList = b1;

    books_pointer b2 = allocBook();
    setBookInfo(b2, "Book Two", "Author B", "Publisher B", 3);
    b1->nextBookNode = b2;

    books_pointer b3 = allocBook();
    setBookInfo(b3, "Book Three", "Author C", "Publisher C", 1);
    b2->nextBookNode = b3;

    // Confirm list
    printf("Initial Book List:\n");
    books_pointer temp = bookList;
    while (temp != NULL) {
        printf("  - %s by %s\n", temp->Title, temp->Author);
        temp = temp->nextBookNode;
    }

    // Delete Book Two
    deleteBook(&bookList, "Book Two");

    // Print list after deletion
    printf("\nAfter deleting 'Book Two':\n");
    temp = bookList;
    while (temp != NULL) {
        printf("  - %s by %s\n", temp->Title, temp->Author);
        temp = temp->nextBookNode;
    }

    // Delete all books
    deleteAllBooks(&bookList);

    // Final list should be empty
    printf("\nAfter deleting all books:\n");
    if (bookList == NULL) {
        printf("  Book list is empty.\n");
    } else {
        printf("  Error: Book list not fully deleted.\n");
    }
}

void testAuthorFileFunctions() {
    categorys_pointer categoryList = NULL;

    // Step 1: Add books to category list
    addBookToCategory(&categoryList, "Fantasy", "The Hobbit", "J.R.R. Tolkien", "Allen & Unwin", 5);
    addBookToCategory(&categoryList, "Fantasy", "The Fellowship of the Ring", "J.R.R. Tolkien", "George Allen & Unwin",
                      7);
    addBookToCategory(&categoryList, "Fantasy", "The Two Towers", "J.R.R. Tolkien", "George Allen & Unwin", 6);
    addBookToCategory(&categoryList, "Fantasy", "The Return of the King", "J.R.R. Tolkien", "George Allen & Unwin", 8);
    addBookToCategory(&categoryList, "Sci-Fi", "Dune", "Frank Herbert", "Chilton Books", 4);

    // Step 2: Save Tolkien's books to a file
    saveBooksByAuthorToBinaryFile(categoryList, "J.R.R. Tolkien");

    // Step 3: List books in the binary file
    listBooksInFile("J.R.R. Tolkien_books.bin");

    // Step 4: Rename the binary file
    renameAuthorFile("J.R.R. Tolkien", "Tolkien");

    // Step 5: Import books from file into a new category
    importBooksFromFile(&categoryList, "Tolkien_books.bin", "Imported Tolkien");

    // Step 6: Show that books are added under the new category
    categorys_pointer importedCat = searchCategory(categoryList, "Imported Tolkien");
    if (importedCat != NULL) {
        printf("Books in 'Imported Tolkien' category:\n");
        books_pointer b = importedCat->Books;
        while (b != NULL) {
            printf("  Title: %s | Author: %s | Publisher: %s | Copies: %d\n",
                   b->Title, b->Author, b->Publisher, b->NumberExp);
            b = b->nextBookNode;
        }
    }

    // Step 7: Delete the file
    deleteAuthorFile("Tolkien");

    // Step 8: Try listing books again (should fail)
    listBooksInFile("Tolkien_books.bin");

    // Step 9: Cleanup memory
    deleteAllCategories(&categoryList);
}
