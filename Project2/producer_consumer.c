#include <linux/init.h>           
#include <linux/kernel.h>    
#include <linux/sched/signal.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/init.h>
#include <linux/timekeeping.h>
#include <linux/module.h>       
#include <linux/ktime.h> 
#include <linux/slab.h>

MODULE_LICENSE("GPL");              
MODULE_AUTHOR("Sudo bros");      
MODULE_DESCRIPTION("CSE330 Project 2");  
MODULE_VERSION("1");              ///< The version of the module
    
/////////////////////////////// Data Declaration
    
// Initialize params to make it compile    
static int uid = 0;
static int buff_size = 0;
static int p = 0;
static int c = 0;

module_param(uid, int, 0);  // Parameter which stores the the user ID of a given user
module_param(buff_size, int, 0); // Parameter which stores the size of the buffer, must be a positive int
module_param(p, int, 0); // Parameter which stores the number of producer threads, must be 1 or 0
module_param(c, int, 0); // Parameter which stores the number of consumer threads, a non-negative int)

// Declare producer and consumer functions
static int consumerFunction(void *arg);
static int producerFunction(void *arg);

// Declare global pointer of consumer functions so all consumer threads can be stopped
struct task_struct *consumer;
struct task_struct *producer1;

// Semaphore declaration
struct semaphore empty;
struct semaphore full;
struct semaphore mutex;

// Linked List declaration 
struct task_node{
	struct task_struct *task;
	struct task_node *next;
} empty_list;

// Buffer struct declaration
struct buffer{
	int capacity;
	struct task_node *head;
} buffer;

// Define a global int to track total task time
long total_time;

///////////////////////////////////

static int __init hello_init(void){

    sema_init(&empty, buff_size);
    sema_init(&full, 0); 
    sema_init(&mutex, 1);

    	  // set the initial values to NULL in the linked list
    empty_list.task = NULL;
    empty_list.next = NULL;

    buffer.capacity = buff_siz	// this is passed in as an argumente;
    buffer.head = &empty_list;

    // Make producer and consumer threads 
    struct task_struct *producer;
    int error;



		// check if there is no producers or consumers
    if(c == 0 && p == 0){
	    printk(KERN_INFO "There is no producers or consumers\n");
	    return 0;
    }
        // Start consumer threads
    if(c != 0){
	int i;
	for (i = 0; i < c; i++){
	
			// create a new consumer
    		consumer = kthread_run(consumerFunction, NULL, "consumer");

    		if (IS_ERR(consumer)){
    	    		printk(KERN_INFO "Cannot create consumer thread\n");
    	    		error = PTR_ERR(consumer);
    	    		consumer = NULL;
    	    		return error;
		}
	}
    }

    	// Start the producer thread
    if(p != 0){
    	producer = kthread_run(producerFunction, NULL, "producer");
    	if (IS_ERR(producer)){
    	    printk(KERN_INFO "Cannot create producer thread\n");
    	    error = PTR_ERR(producer);
    	    producer = NULL;
    	    return error;
	}
    }
    return 0;
}
 
static int producerFunction(void *arg){

    struct task_struct* p;
    size_t process_counter=0;
    int index = 1;
    for_each_process(p){
        if(p->cred->uid.val == uid && process_counter < buff_size){
        
		// busy wait until empty nodes are available in the buffer
            if(down_interruptible(&empty)){
                break;
            }

            if(down_interruptible(&mutex)){
                break;
            }

		//create a new node in the linked list, append to the end
            struct task_node* prodNode; 
            prodNode = kmalloc(sizeof (struct task_node), GFP_KERNEL);

            if(!prodNode){
                printk(KERN_INFO "memory error");
            }

            prodNode->task = p;
            prodNode->next = NULL;


            //add to empty list
            if(buffer.head == &empty_list){
                buffer.head = prodNode;
            } 
            else{ //add to list containing nodes
                struct task_node *temp = buffer.head;

                while(temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = prodNode;
            }

            ++process_counter;

            printk(KERN_INFO "[%s] Produced Item#-%d at buffer index:%d for PID:%d", current->comm, p->cred->uid.val, index,  p->pid);
	    index++;

            // Increment the mutex
            up(&mutex);
            // Increment the full semaphore
            up(&full); 
        }
    }
    return 0;
}

static int consumerFunction(void *arg)
{

    int counter = 0, index = 1;
    //breaks if kthread_stop() is called
    while(!kthread_should_stop()){

		// busy wait until the buffer is full
        if(down_interruptible(&full)){
            break;
        }

        // Loop until mutex is available
        if(down_interruptible(&mutex)){
            break;
        }

        // Remove the head of the linked list
        if(buffer.head == NULL){
            // This only happens if the semaphores aren't working right
            printk(KERN_INFO "Consumer is pulling from an empty buffer");

        }
        else{
            struct task_node *temp;

            temp = buffer.head;
            if(temp->next != NULL){
                buffer.head = buffer.head->next;
            }
            else{
                printk(KERN_INFO "Reached a NULLl\n");
            }

            long start_time = temp->task->start_time;
            long current_time = ktime_get_ns();
            long task_time = current_time - start_time;
	    u64 base = task_time/1000000000; //base time in seconds
	    int hours = base/3600;
	    int minutes = (base - (hours*3600))/60;
	    int seconds = base - (hours*3600) - (minutes*60);

            total_time += task_time;

            printk(KERN_INFO "[%s] consumed Item#-%d on buffer index: %d PID:%d Elapsed Time- %02d:%02d:%02d", current->comm, temp->task->cred->uid.val, index, temp->task->pid, hours, minutes, seconds);
	    index++;
        }
        counter++;
        // Increment the mutex
        up(&mutex);
        up(&empty);
    }
    return 0;
}
 
static void __exit hello_exit(void){
	u64 base = total_time/1000000000;//base total time in secs
	int hours = base/3600;
	int minutes = (base - (hours*3600))/60;
	int seconds = base - (hours*3600) - (minutes*60);
    printk(KERN_INFO "The total elapsed time of all processes for UID %d is %02d:%02d:%02d\n", uid, hours, minutes, seconds);
}

module_init(hello_init);
module_exit(hello_exit);
	
	//Defined in include/linux/timekeeping.h
	
/* Project Requirments
	// Test cases
This criterion is linked to a Learning OutcomeTest Case -1
./test.sh 10 5 1 0 25
This criterion is linked to a Learning OutcomeTest Case -2
./test.sh 10 5 0 1 25
This criterion is linked to a Learning OutcomeTest Case -3
./test.sh 10 50 1 1 25
Test Case -4
./test.sh 100 50 1 1 25
Test Case -5
./test.sh 1000 50 1 1 100
	// Must be included
Code: module_init and semaphore initialization
Code: thread creation.
Code: semaphore usage by the producer
Code: semaphore usage by the consumer
Code: task list iteration
Code: buffer consumption
Code: kthread_should_stop()
Code: module_exit()
ReadMe
No Binaries
For each item your kernel module produces, print the following information in the mentioned format in the kernel log:
[<Producer-thread-name>] Produced Item#-<Item-Num> at buffer index:
<buffer-index> for PID:<PID of the process>
Example:
[Producer-1] Produced Item#-12 at buffer index:1 for PID:136042
*/
	
/* Notes
IS_ERR - used to check, Returns non-0 value if the ptr is an error. Otherwise 0 if it’s not an error.
if (IS_ERR(ptr))
     printk("Error here: %ld", PTR_ERR(ptr));
     
static inline long __must_check IS_ERR(const void *ptr)
{
    return IS_ERR_VALUE((unsigned long)ptr);
}
     
PTR_ERR - used to print. Current value of the pointer.
static inline long __must_check PTR_ERR(const void *ptr)
{
    return (long) ptr;
}
##############
kthread_should_stop - When someone calls kthread_stop on your kthread, it will be woken and this will return true. You should then return, and your return value will be passed through to kthread_stop.
kthread_run - create and wake a thread.
down_interruptible() - it means if semaphore is not available the respective process will be put on the semaphore wait-queue. And task state will be change to TASK_INTERRUPTIBLE and scheduler will invoked to run any other process. Now the sleeping process can be wake up either by the event for it waiting (semaphore) or by the signal.
The kmalloc() function's operation is very similar to that of user-space's familiar malloc() routine, with the exception of the addition of a flags parameter. The kmalloc() function is a simple interface for obtaining kernel memory in byte-sized chunks. If you need whole pages, the previously discussed interfaces might be a better choice. For most kernel allocations, however, kmalloc() is the preferred interface.
format --> ptr = kmalloc(sizeof(struct dog), GFP_KERNEL);
*/
