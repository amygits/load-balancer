/**
 * A file containing a set of functions to simulate a load balancer
 * 
 * @author Amy Ma
 * @version 1.1
 */


#include "InstanceHost.h"
#include "LoadBalancer.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t *lock;
pthread_t tid;

struct balancer{
    
    struct job_node* head;
    int cur_size;
    int max_size;
};

void* lbrunner(void* args){
    
    balancer *lb = args;
    host* host = host_create();
    //printf("passing host init.\n");
    //printf("host instances = %d\n", host->instances);
    //printf("lb size: %d\n", lb->cur_size);
    //printf("head->next at lb data: %d\n", lb->head->next->data);
    host_request_instance(host,lb->head); 
    host_destroy(host);   
    pthread_exit(0);
    
}

/*
 * Initializes the load balancer
 * @param int batch size
 */
balancer* balancer_create(int batch_size) {
    
    //printf("\nEntering balancer creation...");
    balancer* lb = (balancer*)malloc(sizeof(balancer));
    struct job_node* head = (struct job_node*) malloc(batch_size * sizeof(struct job_node));
    lb->head = head;
    lb->cur_size = 0;
    lb->max_size = batch_size;
    pthread_mutex_init(&lock, NULL);
    
    //printf("Balancer creation success\n");
    return lb;
}

/* 
 * Shuts down the load balancer and ensures outstanding batches are completed
 * @param double pointer to load balancer
 */
void balancer_destroy(balancer** lb){
    //printf("Entering balancer destruction..");
    balancer *temp = lb;
    
    free(lb);
    temp = NULL;
    //printf("Balancer successfully destroyed.\n");
    pthread_mutex_destroy(&lock);
}

/*
 * Adds a job to the load balancer (job must be protected by mutex)
 */
void balancer_add_job(balancer *lb, int user_id, int data, int* data_return){
    
    printf("LoadBalancer: Received new job from user# %d to process data=%d and store it at %p.\n", user_id, data, data_return);
    
    // If current load batch size is less than max batch size
   // printf("entering lock\n");
    pthread_mutex_lock(&lock);
    if (lb->cur_size < lb->max_size){
        
        //printf("current lb size: %d\n", lb->cur_size);
        struct job_node *newJob = malloc(sizeof(struct job_node));
        newJob->user_id = user_id;
        newJob->data = data;
        newJob->data_result = data_return;
        //printf("created new node and added data to node..\n");
        
        struct job_node *temp = lb->head;
        //printf("lb->head = %d\n", lb->head);
        while(temp->next != NULL) {
            //printf("entering while loop to traverse job list + 1...\n");
            temp = temp->next;
        }
        
        //printf("after while loop\n");
        temp->next = newJob;      
        //printf("adding to the end of load balancer batch..\n");
        lb->cur_size = ++(lb->cur_size);
        //printf("current lb size: %d\n", lb->cur_size);
        //printf("Job add successful.\n");
        //pthread_mutex_unlock(&lock);
        //printf("exiting lock\n");
    } 
     pthread_mutex_unlock(&lock);
     //printf("exiting lock\n");
    
    if (lb->cur_size == lb->max_size){
        
        //printf("entering host creation section..\n");
        pthread_create(&tid, NULL, lbrunner, lb);
    }
 
     

    
}