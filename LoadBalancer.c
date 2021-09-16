/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "LoadBalancer.h"
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;

struct balancer{
    
    struct job_node* head;
    int cur_size;
    int max_size;
};

/*
 * Initializes the load balancer
 * @param int batch size
 */
balancer* balancer_create(int batch_size) {
    
    printf("Entering balancer creation...");
    balancer* lb = malloc(balancer*) sizeof(balancer);
    lb->cur_size = 0;
    lb->max_size = batch_size;
    
    printf("Balancer creation success\n");
    return lb;
}

/* 
 * Shuts down the load balancer and ensures outstanding batches are completed
 * @param double pointer to load balancer
 */
void balancer_destroy(balancer** lb){
    printf("Entering balancer destruction..");
    balancer *temp = lb;
    free(lb);
    temp = NULL;
    printf("Balancer successfully destroyed.\n");
}

/*
 * Adds a job to the load balancer (job must be protected by mutex)
 */
void balancer_add_job(balancer **lb, int user_id, int data, int* data_return){
    
    printf("Attempting to add job to load balancer..");

    pthread_mutex_init(&lock, NULL);
    // If current load batch size is less than max batch size
    if (lb->cur_size < lb->max_size){
        pthread_mutex_lock*(&lock);
        struct job_node newJob = (job_node) malloc(sizeof(job_node));
        newJob->user_id = user_id;
        newJob->data = data;
        newJob->data_result = data_return;
        
        struct job_node* temp = lb->head;
        lb->head = newJob;
        temp->next = newJob;
        
        lb->cur_size = lb->cur_size++;
        printf("Job add successful.\n");
        pthread_mutex_unlock(&lock);
    } 
    
    else if (lb->cur_size == lb->max_size){
        
        host *session = host_create();
        host_request_instance(session, lb->head);
        host_destroy(session);
        
    }
    
    pthread_mutex_destroy(&lock);
}
