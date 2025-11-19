#include <stdio.h>
#include <string.h> // For strcmp() to compare book names

// --- 1. Define the Book Data Structure ---
struct Book {
    const char* name;
    int isAvailable; // 1 = Available, 0 = Borrowed
};

// --- 2. Global Library Database & Settings ---
// We use a global array so the functions can access it
// without arguments, as per the problem's function signatures.
struct Book library[] = {
    {"A Tale of Two Cities", 1},
    {"The Lord of the Rings", 1},
    {"Pride and Prejudice", 1},
    {"The Catcher in the Rye", 0}, // This one is already borrowed
    {"To Kill a Mockingbird", 1}
};
// Calculate the total number of books in the array
int totalBookCount = sizeof(library) / sizeof(library[0]);
float finePerDay = 1.50; // Fine is 1.50 per day

/* --- 3. Function Implementations as per the Table --- */

/**
 * Method Type:   No arguments, no return value
 * Scenario:    Display list of available books
 */
void displayBooks() {
    printf("\n--- Available Books in the Library ---\n");
    int availableCount = 0;

    // Loop through the entire library
    for (int i = 0; i < totalBookCount; i++) {
        // Check the 'isAvailable' flag
        if (library[i].isAvailable == 1) {
            printf("- %s\n", library[i].name);
            availableCount++;
        }
    }

    if (availableCount == 0) {
        printf("All books are currently borrowed.\n");
    }
    printf("--------------------------------------\n");
}

/**
 * Method Type:   No arguments, return value
 * Scenario:    Get total number of books
 */
int getTotalBooks() {
    // Returns the global count
    return totalBookCount;
}

/**
 * Method Type:   Argument passed, no return value
 * Scenario:    Borrow a book
 */
void borrowBook(char* bookName) {
    int foundBook = 0;

    // Loop through the library to find the book
    for (int i = 0; i < totalBookCount; i++) {
        // Use strcmp to compare the bookName with the library's book name
        if (strcmp(library[i].name, bookName) == 0) {
            foundBook = 1; // We found the book

            // Check if it's available
            if (library[i].isAvailable == 1) {
                library[i].isAvailable = 0; // Mark as borrowed
                printf("Update: You have successfully borrowed '%s'.\n", bookName);
            } else {
                printf("Update: Sorry, '%s' is already checked out.\n", bookName);
            }
            break; // Stop searching once the book is found
        }
    }

    if (foundBook == 0) {
        printf("Update: Sorry, a book with the name '%s' was not found.\n", bookName);
    }
}

/**
 * Method Type:   Argument passed, return value
 * Scenario:    Calculate fine for overdue book
 */
float calculateFine(int daysLate) {
    if (daysLate <= 0) {
        return 0.0;
    }
    float totalFine = (float)daysLate * finePerDay;
    return totalFine;
}

/* --- 4. Main Function to Demonstrate the System --- */
int main() {
    printf("--- Library Management System ---\n");

    // --- Test Function 2: getTotalBooks() ---
    printf("\nTotal books in catalog: %d\n", getTotalBooks());

    // --- Test Function 1: displayBooks() ---
    displayBooks();

    // --- Test Function 3: borrowBook() ---
    printf("\n--- Simulating Book Borrowing ---\n");
    // Try to borrow a book that is available
    borrowBook("Pride and Prejudice");

    // Try to borrow a book that is already checked out
    borrowBook("The Catcher in the Rye");

    // Try to borrow a book that doesn't exist
    borrowBook("Moby Dick");

    // --- Test Function 1 again to show updated inventory ---
    displayBooks();

    // --- Test Function 4: calculateFine() ---
    printf("\n--- Simulating Fine Calculation ---\n");
    int lateDays = 5;
    float fine = calculateFine(lateDays);
    // "%.2f" formats the float to 2 decimal places
    printf("The fine for %d days late is: $%.2f\n", lateDays, fine);

    int lateDays2 = 10;
    float fine2 = calculateFine(lateDays2);
    printf("The fine for %d days late is: $%.2f\n", lateDays2, fine2);

    return 0;
}
