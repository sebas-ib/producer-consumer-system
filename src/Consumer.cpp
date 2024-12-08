#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>
#include "Broker.h"
#include <iostream>
#include <semaphore.h>
#include "fooddelivery.h"
#include "log.h"

void *consumer1(void *arg) {
    // Create the broker
    Broker *broker = static_cast<Broker *>(arg);

    // All deliveries will be done by DeliveryServiceA
    ConsumerType consumers;
    consumers = DeliveryServiceA;

    while (1) {

        // Calculates the amount of deliveries consumed so far
        int sum = 0;
        for (int i = 0; i < RequestTypeN; ++i) {
            for (int j = 0; j < RequestTypeN; ++j) {
                sum += broker->deliveryConsumed[i][j];
            }
        }

        // If the amount of deliveries consumed is equal to the maximum requests allowed,
        // we return to the main thread.
        if (sum == broker->requestsMax)
            sem_post(&broker->precedenceConstraint);

        // Removes an item from the broker queue
        broker->remove_item(broker, consumers, broker->delAConsumeTime);
    }

    return nullptr;
}

void *consumer2(void *arg) {
    // Create the broker
    Broker *broker = static_cast<Broker *>(arg);

    // All deliveries will be done by DeliveryServiceB
    Consumers consumers;
    consumers = DeliveryServiceB;


    while (1) {

        // Calculates the amount of deliveries consumed so far
        int sum = 0;
        for (int i = 0; i < RequestTypeN; ++i) {
            for (int j = 0; j < RequestTypeN; ++j) {
                sum += broker->deliveryConsumed[i][j];
            }
        }

        // If the amount of deliveries consumed is equal to the maximum requests allowed,
        // we return to the main thread.
        if (sum == broker->requestsMax)
            sem_post(&broker->precedenceConstraint);

        // Removes an item from the broker queue
        broker->remove_item(broker, consumers, broker->delBConsumeTime);
    }

    return nullptr;
}
