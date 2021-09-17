/**
 * A file containing a set of functions to simulate a cloud-like server instance host
 * 
 * @author Amy Ma
 * @version 1.1
 */

#include "InstanceHost.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t lock;
pthread_t tid;

void* runner(void *arg){
    
    
    struct job_node* ptr = arg;
    //printf("entering runner lock\n");
    pthread_mutex_lock(&lock);
    while(!ptr == NULL) {
        printf("User #%d: Received result from data=%d as result = %d\n", ptr->user_id, ptr->data, &(ptr->data_result));
        ptr = ptr->next;
    }
    pthread_mutex_unlock(&lock);
    //printf("exiting running lock\n");
    pthread_exit(0);
}


/*  
 * Initializes host environment
*/


host* host_create(){
    
   //printf("Host initialization...");
   pthread_mutex_init(&lock, NULL);
   host* newHost = (host*) malloc(sizeof(newHost));
   int nun = 1;
   newHost->instances = nun;
   
   //printf("Host initialized.\n");
   return newHost;
   
}

/*
 * Shuts down the host environment, ensures outstanding batches are completed
 */
void host_destroy(host** h) {
    //printf("Beginning host destruction...");
    
    host *temp = h;
    free(h);
    temp = NULL;
    
    pthread_mutex_destroy(&lock);
    //printf("Host instance destroyed\n");
    
}

/*
 * Creates a new server instance(thread) to handle processing the items 
 * contained in a batch
 */
void host_request_instance(host* h, struct job_node* batch) {
    
    
    printf("LoadBalancer: Received batch and spinning up new instance..\n");
    
    pthread_create(&tid, NULL, runner, batch);
    h->instances = ++(h->instances);
    pthread_join(tid, NULL);
    
    //printf("Instance created.\n");
    
}

