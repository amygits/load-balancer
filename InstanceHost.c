/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "InstanceHost.h"
#include <pthread.h>

/*  
 * Initializes host environment
 */
void host_create(){
    
    
}

/*
 * Shuts down the host environment, ensures outstanding batches are completed
 */
void host_destroy(host** h) {
    
    
}

/*
 * Creates a new server instance(thread) to handle processing the items 
 * contained in a batch
 */
void host_request_instance(host* h, struct job_node* batch) {
    
    
}