#include <stdlib.h>
#include <string.h>

#include "utils.h"

// structure describing a book
struct book {
    int id;
    char name[50];
    char author[40];
    char genre[20];
    int noOfCopies;
    struct copy *copies;
};

struct book *getBookByID(struct book books[], int n, int id) {
    // returns book with ID -1 whenever it is not found

    for (int i = 0; i < n; i++) {
        if (books[i].id == id)
            return &(books[i]);
    }
    struct book *voidBook=malloc(sizeof(struct book));
    voidBook->id = -1;
    return voidBook;
}

int addBook(struct book books[], int n, struct book book1) {
    // returns 0 whenever the book is added successfully and -1 whenever it is not
    // increment n whenever this function is called

    if (n >= 100) {
        printf("Too many books added already!\n");
        return -1;
    }
    books[n] = book1;
    return 0;
}

int removeBook(struct book books[], int n, int index) {
    // returns 0 whenever the book is removed successfully and -1 whenever it is not
    // decrement n whenever this function is called

    if (n == 0) {
        printf("No books present; books cannot be removed!\n");
        return -1;
    }
    if (index < 0 || index >= n) {
        printf("Index is too large; there are only %d books!\n", n);
        return -1;
    }
    for (int i = index; i < n; i++) {
        books[i] = books[i+1];
    }
    return 0;
}

int addCopy(struct book books[], int n, int id) {
    // returns 0 whenever the copy is removed successfully and -1 whenever it is not

    for (int i = 0; i < n; i++) {
        if (books[i].id == id) {
            if (books[i].noOfCopies < 10) {
                books[i].noOfCopies++;
                books[i].copies[books[i].noOfCopies-1] = (struct copy) {.bookID = books[i].id, .copyID = books[i].noOfCopies, .isIssued = 0, .dateIssued = ""};
                return 0;
            } else {
                printf("Too many copies already! The maximum the library can hold is 10.\n");
                return -1;
            }
        }
    }
    return -1;
}

int removeCopy(struct book books[], int n, int id) {
    // returns 0 whenever the copy is removed successfully and -1 whenever it is not

    for (int i = 0; i < n; i++) {
        if (books[i].id == id) {
            books[i].noOfCopies--;
            if (books[i].noOfCopies == 0) {
                removeBook(books, n, i);
                return 1;
            }
            return 0;
        }
    }
    return -1;
}

int copiesAvailable(struct book book1) {
    int count = 0;
    for (int i = 0; i < book1.noOfCopies; i++) {
        if (!book1.copies[i].isIssued)
            count++;
    }
    return count;
}
