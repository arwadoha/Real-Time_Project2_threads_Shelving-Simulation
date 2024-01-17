#ifndef CONSTANTS_H
#define CONSTANTS_H

// General Supermarket Settings
#define MAX_PRODUCTS 100           // Maximum number of different products in the supermarket
#define MAX_SHELVING_TEAMS 3       // Maximum number of shelving teams
#define NUM_CUSTOMERS 10


#define MIN_RESTOCK 5     // Minimum amount to restock
#define MAX_RESTOCK 20    // Maximum amount to restock
#define CHECK_INTERVAL 10 // Time interval for manager to check shelves in seconds
#define THRESHOLD 10      // Threshold amount for restocking

#define MAX_QUANTITY_PER_ITEM 5
#define MAX_ITEMS_PER_CUSTOMER 5
#define NUM_SHELVING_TEAMS 3

//new
#define MAX_EMPLOYEES_PER_TEAM 3
#define RESTOCK_THRESHOLD 50 // Adjust as needed

// Customer Behavior Settings
#define MIN_CUSTOMER_ARRIVAL 1     // Minimum rate of customer arrival (customers per minute)
#define MAX_CUSTOMER_ARRIVAL 5     // Maximum rate of customer arrival (customers per minute)

// Simulation Settings
#define SIMULATION_DURATION 0.5    // Duration of the simulation in minutes (0 for indefinite)
#define LOW_STOCK_THRESHOLD 10     // Threshold for restocking products

#define SHARED_MEMORY_KEY 1234
#define MIN_STOCK_THRESHOLD 3
#define NUM_PRODUCTS_CART 3
#define NUM_OF_MANAGERS 3
//======//
#define SHM_KEY 0x12345
#define NUM_PRODUCTS 5
#define MANAGER_ID 0
#define MANAGER_ADD_AMOUNT 10
#define PERMISSIBLE_LIMIT 5

#endif // CONSTANTS_H
