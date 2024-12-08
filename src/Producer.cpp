#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>
#include "Broker.h"
#include <iostream>
#include <semaphore.h>
#include "fooddelivery.h"
#include "log.h"

void *producer1(void *arg) {
    // Create the broker
    Broker *broker = static_cast<Broker *>(arg);

    // All products created by this thread will be pizzas
    RequestType request;
    request = Pizza;

    while (1) {
        // Inserts items in to broker queue
        broker->insert_item(broker, request, broker->pizzaRequestTime);
    }
    return nullptr;
}

void *producer2(void *arg) {
    // Create the broker
    Broker *broker = static_cast<Broker *>(arg);

    // All products created by this thread will be sandwiches
    RequestType request;
    request = Sandwich;


    while (1) {
        // Checks if the max amount of sandwiches has been reached in the broker queue
        // Once a sandwich has been removed, a new one can be added
        sem_wait(&broker->sandwichesAvailable);
        broker->insert_item(broker, request, broker->sandwichRequestTime);
    }
    return nullptr;
}



