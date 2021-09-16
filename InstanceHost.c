/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "InstanceHost.h"
#include <pthread.h>
#include <stdio.h>

/*  
 * Initializes host environment
 */
void host_create(){
     printf("Initializing host environment...");
     
     printf("Host initialization success\n");
}

/*
 * Shuts down the host environment, ensures outstanding batches are completed
 */
void host_destroy(host** h) {
    printf("Beginning host destruction...");
    printf("Host destruction success\n");
    
}

/*
 * Creates a new server instance(thread) to handle processing the items 
 * contained in a batch
 */
void host_request_instance(host* h, struct job_node* batch) {
    
    
}