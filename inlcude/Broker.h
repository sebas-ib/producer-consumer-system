#ifndef BROKER_H
#define BROKER_H

#include <semaphore.h>
#include <pthread.h>
#include "ItemType.h"
#include <iostream>
#include "log.h"
#include <unistd.h>

struct Broker {
    // Max number of items that can be held in the buffer

    sem_t precedenceConstraint;         // Semaphore that returns to main function
    sem_t availableSlots;               // Semaphore that shows if slots are available in buffer
    sem_t unconsumed;                   // Semaphore that shows if items are available to consume
    sem_t sandwichesAvailable;          // Semaphore that shows if sandwich limit has been reached
    sem_t maxRequests;                  // Semaphore that shows if maximum amount of production requests has ben reached
    pthread_mutex_t mutex;              // Lock

    unsigned int *currInBrokerQueue;    // Shows how many of each item is in the broker queue
    unsigned int *amProduced;           // How many of each item has been produced
    unsigned int **deliveryConsumed;    // How many pizzas and sandwiches each delivery service has delivered

    int pizzaRequestTime;               // Time for pizza to be made
    int sandwichRequestTime;            // Time for sandwich to be made
    int delAConsumeTime;                // Time for DeliveryA to make a delivery
    int delBConsumeTime;                // Time for DeliveryB to make a delivery
    int requestsMax;                    // Max amount of requests that can be made
    int in;                             // The front of the queue
    int out;                            // The back of the queue

    int bufferMax;
    int sandwichMax;

    ItemType *buffer;         // Buffer

    Broker(int requests, int pizzaTime, int sandwichTime, int delATime, int delBTime, int maxBuffer, int maxSandwich){
        // Initialize all variables
        bufferMax = maxBuffer;
        sandwichMax = maxSandwich;

        sem_init(&availableSlots, 0, maxBuffer);
        sem_init(&unconsumed, 0, 0);
        sem_init(&sandwichesAvailable, 0, maxSandwich);
        sem_init(&precedenceConstraint, 0, 0);
        sem_init(&maxRequests, 0, requests);
        pthread_mutex_init(&mutex, NULL);

        currInBrokerQueue = new unsigned int[RequestTypeN]();
        amProduced = new unsigned int[RequestTypeN]();
        deliveryConsumed = new unsigned int *[RequestTypeN];

        for (int i = 0; i < RequestTypeN; ++i) {
            deliveryConsumed[i] = new unsigned int[RequestTypeN];
        }

        requestsMax = requests;
        pizzaRequestTime = pizzaTime;
        sandwichRequestTime = sandwichTime;
        delAConsumeTime = delATime;
        delBConsumeTime = delBTime;

        // Both start at the beginning of the queue
        in = 0;
        out = 0;

        buffer = new ItemType[20];
    }

    void insert_item(Broker *broker, RequestType product, int timeToProduce) {
        // Sleeps for a certain amount of time
        usleep(timeToProduce);

        // Waits for slots to be available and below the max amount of requests
        sem_wait(&broker->maxRequests);
        sem_wait(&broker->availableSlots);

        // Locks
        pthread_mutex_lock(&broker->mutex);

        // Checks the type of product
        ItemType item;
        if (product == Pizza) {
            item.data = 0;
        } else {
            item.data = 1;
        }

        // Increments the correct indexes to keep track of amounts
        amProduced[item.data]++;
        currInBrokerQueue[item.data]++;

        // Logs the insertion of the item
        RequestAdded added;
        added.type = product;
        added.inBrokerQueue = currInBrokerQueue;
        added.produced = amProduced;
        log_added_request(added);

        // Insert item into the correct slot of the queue
        broker->buffer[broker->in] = item;
        // Increment 'in' to the next slot of the queue
        broker->in = (broker->in + 1) % broker->bufferMax;

        // Unlock
        pthread_mutex_unlock(&broker->mutex);

        // Increment unconsumed to let delivery services know they can begin taking from queue
        sem_post(&broker->unconsumed);
    }

    ItemType remove_item(Broker *broker, ConsumerType consumer, int timeToRemove) {

        //Sleep for a certain amount of time
        usleep(timeToRemove);

        //Wait for items to be able to be consumed
        sem_wait(&broker->unconsumed);
        //Lock
        pthread_mutex_lock(&broker->mutex);


        // Save item about to be removed
        ItemType item = broker->buffer[broker->out];

        // Properly increment and decrement data stored in arrays
        currInBrokerQueue[item.data]--;
        deliveryConsumed[consumer][item.data]++;

        // Log the removal of item from queue
        RequestRemoved removed;
        removed.consumed = deliveryConsumed[consumer];
        removed.inBrokerQueue = currInBrokerQueue;
        removed.consumer = consumer;
        removed.type = (item.data == 0) ? Pizza : Sandwich;
        log_removed_request(removed);

        // Remove item from broker queue
        broker->buffer[broker->out] = ItemType();
        // Increase 'out' to reference the next item in the queue
        broker->out = (broker->out + 1) % broker->bufferMax;

        // Unlock
        pthread_mutex_unlock(&broker->mutex);

        // If item removed was a sandwich, update the semaphore accordingly
        if (item.data == 1)
            sem_post(&broker->sandwichesAvailable);

        // Let producers know they cna produce and extra item
        sem_post(&broker->availableSlots);

        return item;
    }
};

#endif /* BROKER_H */
