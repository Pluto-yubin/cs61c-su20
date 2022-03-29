/*
 * @Descripttion: Learn something about C_Cpp
 * @version: 1.0
 * @Author: Zhang Yubin
 * @Date: 2022-03-27 16:56:59
 * @LastEditors: Zhang Yubin
 * @LastEditTime: 2022-03-28 23:32:52
 */
#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
HashTable *createHashTable(int size, unsigned int (*hashFunction)(void *),
                           int (*equalFunction)(void *, void *))
{
  HashTable *newTable = (HashTable *)malloc(sizeof(HashTable));
  newTable->size = size;
  newTable->data = (struct HashBucket **)malloc(sizeof(struct HashBucket *) * size);
  // if (newTable->data == NULL)
  // {
  //   printf("test");
  // }
  // for (int i = 0; i < newTable->size; i++)
  // {
  //   newTable->data[i] = (struct HashBucket *)malloc(sizeof(struct HashBucket *));
  //   if (newTable->data[i] == NULL)
  //   {
  //     printf("test");
  //   }
  // }

  newTable->hashFunction = hashFunction;
  newTable->equalFunction = equalFunction;
  return newTable;
}

/*
 * This inserts a key/data pair into a hash table.  To use this
 * to store strings, simply cast the char * to a void * (e.g., to store
 * the string referred to by the declaration char *string, you would
 * call insertData(someHashTable, (void *) string, (void *) string).
 * Because we only need a set data structure for this spell checker,
 * we can use the string as both the key and data.
 */
void insertData(HashTable *table, void *key, void *data)
{

  // HINT:
  // 1. Find the right hash bucket location with table->hashFunction.
  // 2. Allocate a new hash bucket struct.
  // 3. Append to the linked list or create it if it does not yet exist.
  int hash = table->hashFunction(key);
  struct HashBucket *p = table->data[hash];
  if (table->data[hash] == NULL)
  {
    table->data[hash] = (struct HashBucket *)malloc(sizeof(struct HashBucket));
    table->data[hash]->key = key;
    table->data[hash]->data = data;
    return;
  }
  while (p->next != NULL)
  {
    p = p->next;
  }
  p->next = (struct HashBucket *)malloc(sizeof(struct HashBucket));
  p->next->key = key;
  p->next->data = data;
}

/*
 * This returns the corresponding data for a given key.
 * It returns NULL if the key is not found.
 */
void *findData(HashTable *table, void *key)
{
  // HINT:
  // 1. Find the right hash bucket with table->hashFunction.
  // 2. Walk the linked list and check for equality with table->equalFunction.
  int hash = table->hashFunction(key);
  struct HashBucket *p = table->data[hash];
  while (p != NULL && !table->equalFunction(p->key, key))
  {
    p = p->next;
  }
  return p == NULL ? p : p->data;
}
