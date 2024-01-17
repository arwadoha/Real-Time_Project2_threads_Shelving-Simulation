#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include <sys/wait.h>

#include <pthread.h>
#include <sys/time.h>

#include <pthread.h>
#include <mqueue.h>
#include <sys/ipc.h>
#include <sys/shm.h>



// Shared data structures (in shared memory)
typedef struct {
    int id;
    int shelf_amount; // Current amount available on the shelf
    int storage_amount;
    int threshold; // User-defined threshold for restocking
    pthread_mutex_t mutex; // Mutex for each product
} Product;

typedef struct {
    int productIndex;  // Index of the product to be shelved
    int amount;        // Amount to be shelved
    int ready;         // Flag to indicate if the product is ready for shelving
    pthread_mutex_t mutex; // Mutex for the structure
    pthread_cond_t cond;   // Condition variable for signaling
} ShelvingTask;


// Structure to represent a product on the shelf
struct Product {
    int id;
    int quantity;
};

// Shared memory structure to represent the shelves
struct Shelves {
    struct Product products[NUM_PRODUCTS];
    pthread_mutex_t lock; // Mutex to control access to the shelves
};


typedef struct {
    int team_id;
    char manager_name[50];
    int number_of_employees;
    int current_product; // ID of the current product the team is handling
    pthread_t manager_thread;
    pthread_t employee_threads[MAX_EMPLOYEES_PER_TEAM];
    ShelvingTask shelvingTask; // Task for the team
    int employee_counter; 
} Team;



typedef struct {
    int customerId;
    int selectedProductIds[MAX_PRODUCTS]; // Array to hold IDs of selected products
    int selectedQuantities[MAX_PRODUCTS]; // Array to hold quantities of selected products
} Customer;

typedef struct {
    int productIndex;  // Index of the product being restocked
    int amount;        // Amount of the product on the cart
} Cart;


typedef struct {
    struct Shelves *shelves;
    int teamId;
    int employeeId;
} ThreadArgs;

