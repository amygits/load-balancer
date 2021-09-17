/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "InstanceHost.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t lock;
pthread_t tid;

void* runner(void *arg){
    
    struct job_node* ptr = arg;
    
    pthread_mutex_lock(&lock);
    while(!ptr == NULL) {
        printf("User #%d: Received result from data=%d as result =%d\n", ptr->user_id, ptr->data, (&ptr->data_result));
        ptr = ptr->next;
    }
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}

struct host {
    
    int instances;
    
};

/*  
 * Initializes host environment
 */
host* host_create(){
    
   printf("Host initialization...");
   host* newHost = (host*) malloc(sizeof(host));
   
   newHost->instances = 0;
   
   return newHost;
   printf("Host initialized.\n");
   
}

/*
 * Shuts down the host environment, ensures outstanding batches are completed
 */
void host_destroy(host** h) {
    
    printf("Destroying host instance..");
    
    
    printf("Host instance destroyed\n");
    
}

/*
 * Creates a new server instance(thread) to handle processing the items 
 * contained in a batch
 */
void host_request_instance(host* h, struct job_node* batch) {
    
    printf("LoadBalancer: Received batch and spinning up new instance...");
    pthread_mutex_init(&lock, NULL);
    
    pthread_create(tid, NULL, runner, batch);
    h->instances = h->instances++;
    pthread_join(tid, NULL);
    
    pthread_mutex_destroy(&lock);
    //printf("Instance created.\n");
    
}

