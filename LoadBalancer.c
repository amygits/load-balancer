/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "LoadBalancer.h"


/*
 * Initializes the load balancer
 * @param int batch size
 */
balancer* balancer_create(int batch_size) {
 
    
}

/* 
 * Shuts down the load balancer and ensures outstanding batches are completed
 * @param double pointer to load balancer
 */
void balancer_destroy(balancer** lb){
    
    
}

/*
 * Adds a job to the load balancer (job must be protected by mutex)
 */
void balancer_add_job(balancer **lb, int user_id, int data, int* data_return){
    
    
}
