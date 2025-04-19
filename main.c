#include "tests.h"
// ---- Main ----
int main(void) {
    testAddCategoryAndSearch();
    testAddBookToCategory();
    testSearchBookByAuthor();
    testSearchBookByTitle();
    testDeleteCategory();
    testDeleteAllCategories();
    testDeleteBooks();
    testAuthorFileFunctions();
}
