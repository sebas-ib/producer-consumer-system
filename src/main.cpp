#include <unistd.h>
#include "Producer.h"
#include "Consumer.h"
#include "Broker.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <cerrno>
#include <iostream>
#include <semaphore.h>
#include "log.h"



int main(int argc, char **argv) {
    const int CONVERT_TO_MILLISECONDS = 1000;       // Times multiplied by 1000 to convert to milliseconds
    const int MAX_BUFFER = 20;                      // Maximum amount of items in the buffer at once
    const int MAX_SANDWICH = 8;                     // Maximum number of sandwiches at once in the buffer

    // Default values for optional arguments
    int delRequests = 100;
    int serviceAms = 0;
    int serviceBms = 0;
    int pizzaDelReq = 0;
    int sandwichDelReq = 0;


    //Parsing through command line input to search for optional arguments
    int opt = 0;
    while ((opt = getopt(argc, argv, "n:a:b:p:s:")) != -1) {
        switch (opt) {
            case 'n':
                delRequests = atoi(optarg);
                break;
            case 'a':
                serviceAms = atoi(optarg) * CONVERT_TO_MILLISECONDS;
                break;
            case 'b':
                serviceBms = atoi(optarg) * CONVERT_TO_MILLISECONDS;
                break;
            case 'p':
                pizzaDelReq = atoi(optarg) * CONVERT_TO_MILLISECONDS;
                break;
            case 's':
                sandwichDelReq = atoi(optarg) * CONVERT_TO_MILLISECONDS;
                break;
            default: /* '?' */
                fprintf(stderr,
                        "Usage: %s [-n Num of Delivery Requests] [-a Time for Service A to deliver (ms)] [-b Time for Service B to deliver (ms)] [-p Time for Pizza to be made (ms)] [-s Time for Sandwich to be made (ms)]\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }


    // Create broker
    Broker *broker = new Broker(delRequests, pizzaDelReq, sandwichDelReq, serviceAms, serviceBms, MAX_BUFFER, MAX_SANDWICH);

    //Create Threads
    pthread_t producer_thread1, consumer_thread1;
    pthread_t producer_thread2, consumer_thread2;

    pthread_create(&producer_thread1, NULL, producer1, broker);
    pthread_create(&producer_thread2, NULL, producer2, broker);
    pthread_create(&consumer_thread1, NULL, consumer1, broker);
    pthread_create(&consumer_thread2, NULL, consumer2, broker);


    // Wait until threads are finished and print log_production_history
    sem_wait(&broker->precedenceConstraint);
    log_production_history(broker->amProduced, broker->deliveryConsumed);


    return 0;
}
