
/*  BZU-ENCS4330 Project 2: POSIX threads under Linux:  Supermarket Product Shelving Simulation
*   Instructor: Dr. Hanna Bullata
*   Students: //Raghad Afghani 119243,  Yousra Qasem 1192131  , Arwa Doha 1190324
*
*   Run : gcc -o main main.c -lpthread  
*/

#include "constants.h"
#include "head.h"

Product products[MAX_PRODUCTS];
Team teams[MAX_SHELVING_TEAMS];
Cart carts[MAX_SHELVING_TEAMS];  // Carts for each shelving team
Customer customers[NUM_CUSTOMERS]; // Array of customer structures
int product_count = 0;
int team_count = 0;
volatile int terminate = 0;  // Flag to signal termination

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t cartMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t oneItemType = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t newProductMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t newProductCond = PTHREAD_COND_INITIALIZER;

void readFile(const char* filename) {
    // Check if the file exists
    if (access(filename, F_OK) == -1) {
        perror("Error opening file");
        printf("Failed to open file: %s\n", filename);
        return;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        printf("Failed to open file: %s\n", filename);
        return;
    }

    char line[256];
    printf("Reading file contents:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line); // Print each line as it is read
        if (strstr(line, "product_") != NULL) {
            Product p;
            sscanf(line, "product_%d, %d, %d", &p.id, &p.shelf_amount, &p.storage_amount);
            if (product_count < MAX_PRODUCTS) {
                products[product_count++] = p;
            }
        } else if (strstr(line, "team_") != NULL) {
            Team t;
            sscanf(line, "team_%d, %49[^,], %d", &t.team_id, t.manager_name, &t.number_of_employees);
            if (team_count < MAX_SHELVING_TEAMS) {
                teams[team_count++] = t;
            }
        }
    }
    fclose(file);
}

// This function is responsible for adding a product to a team's cart.
void addProductToCart(int teamId, int productIndex, int amount) {
    // Lock the cartMutex to ensure exclusive access to the cart data.
    pthread_mutex_lock(&cartMutex);
    // Update the cart with the productIndex and amount for the given team.
    carts[teamId].productIndex = productIndex;
    carts[teamId].amount = amount;

    printf("Added product to cart for team %d. Signaling...\n", teamId);
    // Signal all waiting threads using the newProductCond condition variable.
    pthread_cond_broadcast(&newProductCond);
    // Unlock the cartMutex to allow other threads to access the cart.
    pthread_mutex_unlock(&cartMutex);
}


// This is the thread function executed by each employee of a shelving team.
void *employee_function(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int teamId = args->teamId;
    int employeeId = teams->employee_counter++; 

    while (1) {
    if (employeeId >= 0 && employeeId <=13){
    employeeId = teams->employee_counter++; 
    }
    else{
    employeeId =0;
    }
        pthread_mutex_lock(&cartMutex);

        // Wait until there is a product to restock
        while (carts[teamId].amount == 0) {
            pthread_cond_wait(&newProductCond, &cartMutex);
        }

        int product_id = carts[teamId].productIndex;

        // Take one item from the cart to place on the shelf
        carts[teamId].amount--;
        int restockAmount = carts[teamId].amount;

        pthread_mutex_unlock(&cartMutex);

        // Proceed only if there are items to restock
        if (restockAmount > 0) {
            printf("Employee %d of team %d placing one unit of product %d on shelves\n", employeeId, teamId, product_id);

            pthread_mutex_lock(&products[product_id].mutex);
            products[product_id].shelf_amount++;
            products[product_id].storage_amount--;
            pthread_mutex_unlock(&products[product_id].mutex);

            printf("Product %d: Shelf amount: %d, Storage amount: %d\n",
                   product_id, products[product_id].shelf_amount, products[product_id].storage_amount);
        }

        // Check if all restocking is done
        if (restockAmount == 0) {
            // Reset the cart for this team
            pthread_mutex_lock(&mutex);
            carts[teamId].productIndex = -1; // Reset product index
            pthread_mutex_unlock(&mutex);
        }

        sleep(1); // Simulate the time taken to place a product on shelves
    }

    pthread_exit(NULL);
}

void* manager(void* arg) {
    struct Shelves* shelves = (struct Shelves*)arg;
    int team_id = *(int*)arg; // Get team ID from argument
    while (1) {
        // Loop through all products.
        for (int i = 1; i < NUM_PRODUCTS; i++) {
            // If the quantity of a product is too low...
            if (shelves->products[i].quantity < PERMISSIBLE_LIMIT) {
                //pthread_mutex_lock(&(shelves->lock)); // Lock before modifying the shelves
                // Print a message about restocking the product.
                printf("Manager is restocking Product %d\n", shelves->products[i].id);
                // Increase the quantity of the product.
                shelves->products[i].quantity += MANAGER_ADD_AMOUNT;
                // Print a message about the new quantity.
                printf("Manager restocked Product %d to %d\n", shelves->products[i].id, shelves->products[i].quantity);
                //pthread_mutex_unlock(&(shelves->lock)); // Unlock after modifying the shelves

                // Add the restocked product to a team's cart.
                addProductToCart(team_id, shelves->products[i].id, shelves->products[i].quantity);
            }
        }
        sleep(2); // Manager checks every 2 seconds
    }

    return NULL;
}


// Function for customers to take products from the shelves
void* customer(void* arg, Customer customer) {
    struct Shelves* shelves = (struct Shelves*)arg;

    // Simulate random arrival time within the defined range
    int arrivalTime = MIN_CUSTOMER_ARRIVAL + rand() % (MAX_CUSTOMER_ARRIVAL - MIN_CUSTOMER_ARRIVAL + 1);
    // Simulate the customer arriving after some time
    sleep(arrivalTime);
    printf("Customer %d arrived at the supermarket after %d minutes.\n", customer.customerId, arrivalTime);


    while (1) {

        // Randomly pick a product to take.
        int product_id = 1 + rand() % product_count;
       
        pthread_mutex_lock(&(shelves->lock)); // Lock before accessing the shelves
        // Check if the chosen product is available.
        if (shelves->products[product_id-1].quantity > 0 ) {
            // Take one unit of the product.
            printf("Customer %d is taking Product %d\n",customer.customerId, shelves->products[product_id-1].id);
            shelves->products[product_id-1].quantity--;
            // Print the updated quantity of the product.
            printf("Customer %d took Product %d, remaining: %d\n",customer.customerId, shelves->products[product_id-1].id, shelves->products[product_id-1].quantity);
        } else if (shelves->products[product_id-1].quantity <= 0 && shelves->products[product_id-1].id > 0){
            // Inform if the product is out of stock.
            printf("Customer %d found Product %d out of stock\n", customer.customerId,shelves->products[product_id-1].id);
        }
        
        pthread_mutex_unlock(&(shelves->lock)); // Unlock after accessing the shelves
        sleep(1); // Customer takes products every 1 second
    }

    return NULL;
}

// This function signals to end the program.
void end_program() {
    pthread_mutex_lock(&mutex);
    // Signal to all threads that termination is required
    terminate = 1;
    // Send a signal to all threads that are waiting on this condition.
    pthread_cond_broadcast(&condition);
    pthread_mutex_unlock(&mutex);
}

int main() {

    const char* filename = "text.txt";
    readFile(filename);

    struct timeval start, current;
    gettimeofday(&start, NULL);
    pid_t pid, shelving_pids[NUM_SHELVING_TEAMS], customer_pids[NUM_CUSTOMERS];
    int shm_id;
    pthread_t manager_thread, customer_thread;
    struct Shelves* shared_shelves;

    int pidt = fork();
    // Create interface processes
    if (pidt == 0) {
        execlp("./interface", "./interface", 0, (char * ) NULL);
       perror("exec failure");
        exit(-2);
    }


    // Create the shared memory segment
    shm_id = shmget(SHM_KEY, sizeof(struct Shelves), IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment
    shared_shelves = (struct Shelves*)shmat(shm_id, NULL, 0);
    if ((void*)shared_shelves == (void*)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }


// After readFile(filename); in the main function
    for (int i = 0; i < product_count; ++i) {
        int id = products[i].id; // ID as read from the file
        if (id < NUM_PRODUCTS) {
            shared_shelves->products[id].id = id;
            shared_shelves->products[id].quantity = products[i].shelf_amount; // Initial quantity from file
        } else {
            printf("Error: Product ID %d exceeds the maximum number of products.\n", id);
        }
    }
    // Initialize mutex
    pthread_mutex_init(&(shared_shelves->lock), NULL);



    Customer customers[NUM_CUSTOMERS];

// Assign unique customer IDs to each customer
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        customers[i].customerId = i + 1;
        // Store customer data in shared_shelves or another shared memory structure as needed
    }

// Initialize mutex before fork()
    pthread_mutex_init(&(shared_shelves->lock), NULL);

// Create customer processes
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            srand(time(NULL) ^ getpid()); // Seed for random number generation
            customer(shared_shelves, customers[i]);
            exit(0);
        } else if (pid < 0) {
            perror("fork customer");
            exit(EXIT_FAILURE);
        }
        // Parent process continues
    }

// Create shelving team processes
    for (int i = 0; i < team_count; i++) {
        pid_t pid = fork();
        if (pid == 0) {  // Child process: Shelving Team
            pthread_t manager_thread,employee_thread;
            ThreadArgs *args = malloc(sizeof(ThreadArgs));
            args->shelves = shared_shelves;
            args->teamId = i;

            if (pthread_create(&manager_thread, NULL, manager, (void*)shared_shelves) != 0)
            {
                perror("pthread_create");
                exit(EXIT_FAILURE);
            }

            if (pthread_create(&employee_thread, NULL, employee_function, args) != 0) {
                perror("pthread_create");
                exit(EXIT_FAILURE);
            }

            if (pthread_join(manager_thread, NULL) != 0) {
                perror("pthread_join");
                exit(EXIT_FAILURE);
            }
            if (pthread_join(employee_thread, NULL) != 0)
            {
                perror("pthread_join");
                exit(EXIT_FAILURE);

            }
            exit(0);  // Ensure child process exits after completion
        } else if (pid < 0) {
            perror("fork shelving team");
            exit(EXIT_FAILURE);
        }
        // Parent process continues
    }


// Wait for all child processes to complete
    for (int i = 0; i < NUM_CUSTOMERS + team_count; i++) {
        wait(NULL);
    }




    // Detach and remove shared memory segment
    if (shmdt(shared_shelves) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }


    // Monitor and control the simulation duration
    while (!terminate) {
        gettimeofday(&current, NULL);
        long elapsed = (current.tv_sec - start.tv_sec);

        // Check for time threshold
        if (elapsed >= SIMULATION_DURATION * 60) { // Convert minutes to seconds
            printf("Simulation ended due to running for more than the threshold duration.\n");
            end_program();  // Signal all threads to terminate
            break;
        }

        // Check for stock availability
        int outOfStock = 1;
        pthread_mutex_lock(&mutex);
        for (int i = 0; i < product_count; i++) {
            if (products[i].storage_amount > 0) {
                outOfStock = 0;  // Found a product with stock
                break;
            }
        }
        pthread_mutex_unlock(&mutex);

        if (outOfStock) {
            printf("Ending simulation: Storage area is out of stock.\n");
            break;
        }

        // Sleep for a short duration to prevent the loop from consuming too much CPU
        sleep(1);
    }

    // Signal termination and clean up
    
    sleep(5);  // Give time for threads to finish up

    // Terminate all child processes
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        kill(customer_pids[i], SIGTERM);
    }
    for (int i = 0; i < NUM_SHELVING_TEAMS; i++) {
        kill(shelving_pids[i], SIGTERM);
    }

    return 0;
}

