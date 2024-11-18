#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Hash Table structure
struct HashTable {
    int table[TABLE_SIZE];
    int status[TABLE_SIZE]; // 0 = empty, 1 = occupied, -1 = deleted
};

// Hash function: Simple Modulo-based hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Function to initialize hash table
void initHashTable(struct HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = -1; // -1 represents empty slot
        ht->status[i] = 0;  // 0 represents empty
    }
}

// Insert function for Open Addressing (Linear Probing)
void insertOpenAddressing(struct HashTable* ht, int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (ht->status[index] == 1) {
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            printf("Table is full!\n");
            return;
        }
    }

    ht->table[index] = key;
    ht->status[index] = 1; // Mark the slot as occupied
}

// Search function for Open Addressing
int searchOpenAddressing(struct HashTable* ht, int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (ht->status[index] != 0) {
        if (ht->status[index] == 1 && ht->table[index] == key) {
            return 1; // Found
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            break;
        }
    }
    return 0; // Not found
}

// Delete function for Open Addressing
void deleteOpenAddressing(struct HashTable* ht, int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (ht->status[index] != 0) {
        if (ht->status[index] == 1 && ht->table[index] == key) {
            ht->status[index] = -1; // Mark the slot as deleted
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            break;
        }
    }
}

// Print function for Open Addressing
void printOpenAddressing(struct HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->status[i] == 1) {
            printf("Slot %d: %d\n", i, ht->table[i]);
        } else if (ht->status[i] == -1) {
            printf("Slot %d: DELETED\n", i);
        } else {
            printf("Slot %d: EMPTY\n", i);
        }
    }
}

int main() {
    struct HashTable ht;
    initHashTable(&ht);

    insertOpenAddressing(&ht, 15);
    insertOpenAddressing(&ht, 25);
    insertOpenAddressing(&ht, 35);
    insertOpenAddressing(&ht, 12);
    insertOpenAddressing(&ht, 22);

    printOpenAddressing(&ht);

    if (searchOpenAddressing(&ht, 25)) {
        printf("Key 25 found.\n");
    } else {
        printf("Key 25 not found.\n");
    }

    deleteOpenAddressing(&ht, 25);
    printOpenAddressing(&ht);

    return 0;
}
