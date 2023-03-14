#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/timekeeping.h>
#include <linux/sched/signal.h>

#define_AUTHOR "sudo bros"
MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);

/////////////////////////////// Data Declaration

	// Initialize params   
static int uid = 0;
static int buff_size = 0;
static int p = 0;
static int c = 0;

	// takes input arguments and assigns to respective variables
module_param(buff_size, int, 0); 	// The buffer size
module_param(p, int, 0);		// number of producers(0 or 1)
module_param(c, int, 0);     	// number of consumers(a non-negative number)
module_param(uuid, int, 0);		// The UID of the user

	// Declare producer and consumer functions
static int consumer(void *arg);
static int producer(void *arg);

  // Semaphore declaration
struct semaphore empty;
struct semaphore full;
struct semaphore mutex;

	// A consumer pointer variable
struct task_struct *consumer;
	// producer pointer
struct task_struct *producer;

// Define a global int to track total task time and error  variable
long total_time;
int error;

	// consumer struct
struct consumer{
	struct task_struct *consumer_thread;
	struct consumer_node *next;
} consumer;

// buffer struct declaration
struct buffer{
	int capacity;	// buffers capacity
	struct task_node *head;
} buffer;

// Linked List declaration 
struct task_node{
	struct task_struct *task;
	struct task_node *next;
} task_list;

///////////////////////////////////
	// needs work
static int __init sema_init(void)
{

    	  // Initialize semaphores
    	sema_init(&empty, buff_size);	// set to buffer size
    	sema_init(&full, 0); 		// set to 0
    	sema_init(&mutex, 1);		// lock
  
    	  // set the initial values to NULL in the linked list
    	task_list.task = NULL;
    	task_list.next = NULL;
	
	buffer.capacity = buff_size;	// this is passed in as an argument
	buffer.head = &task_list;
	
		// check if there is no producers or consumers
	if(c == 0 || p == 0){
		return 0;
	}
	
		// start the consumer thread
	if(c != 0){
	
			// create a new consumer
		consumer = kthread_run(consumer, NULL, "consumer");
	
		if (IS_ERR(consumer))
    		{
			error = PTR_ERR(consumer);	
			consumer = NULL:
			return error;
		}

	}
	
		// start the producer thread
	if(p != 0){
		
		producer = kthread_run(producer, NULL, "producer");
		
		if (IS_ERR(producer)){
			error = PTR_ERR(producer);	
			producer = NULL:
			return error;
		}
		
	}	
	
	return 0;
  
}

// Semaphore Definition
sema_init(&empty, 5); // init the semaphore as 5
// if the thread works in an infinite loop, this is how it knows when to stop. Check (4) module_exit for more information.

	// needs work
static int producer(void *arg)
{
	struct task_struct* p;
	size_t process_counter = 0;
	for_each_process(p){
		if (task->cred->uid.val == uuid < buff_size) {
				//increment counter
			++process_counter;
			
				// busy wait until empty nodes are available in the buffer
			if(down_interruptible(&empty)) 
	            	{
	            	    break;
	            	}
	
            		if(down_interruptible(&mutex)) 
            		{
            		    break;
            		}
			
				//create a new node in the linked list
			struct task_node* prodNode; 
           		prodNode = kmalloc(sizeof (struct task_node), GFP_KERNEL);
			
			if(!prodNode)
            		{
                		printk(KERN_INFO "Error allocating memory");
            		}
			
			prodNode->task = p;
			prodNode->next = NULL;
			
				// add to the linked list
			if(){
			
			}else{
			
			}
			
			++process_counter;
			
				// print statement (example) - [Producer-1] Produced Item#-12 at buffer index:1 for PID:136042
			printk(KERN_INFO "[%s] Produced Item#-%d at buffer index:%d for PID:%d", //[Producer-1], value, index,  p->pid);
			
				// increment the semaphores
			up(&mutex);
			up(&full);
		}
	}
	
	
	return 0;
}
  
static int consumer(void *arg)
{
		// when kthread_stop() is called, this function will return true
	while (!kthread_should_stop())
	{
			// busy wait
		if (down_interruptible(&full))
		{
			break;
		}
		else if (down_interruptible(&mutex))
		{
			break;
		}
			// if the consumer attempts to take from an empty buffer
		if(buffer.head == NULL)
		{
          	  printk(KERN_INFO "error");
        	}else
		{
		struct task_node *temp;
		temp = buffer.head;
		
		// traverse temp linked list
		if(temp->next != NULL){
			buffer.head = buffer.head->next;
		}else{
			printk(KERN_INFO "" )
		}
			
		long current_time = ktime_get_ns();	// current time in nanoseconds.
		long start_time = temp->task->start_time;	// start time
		long task_time = current_time - start_time;	// time task took to complete
		long base = task_time/1000000000; //total time in secs
		int hours = base/3600; 	// hours
		int minutes = (base - (hours*3600))/60;	// minutes
		int seconds = base - (hours*3600) - (minutes*60);	// seconds
		total_time += task_time;	// total time sum
			
			// add print statement
		printk(KERN_INFO "[%s] consumed Item#-%d on buffer index: %d PID:%d Elapsed Time- %02d:%02d:%02d\n", enter variables here)
			
			// increment semaphores
	        up(&mutex);
        	up(&empty);
		}
	
	return 0;
}


// stop the kernel thread pointed by task_struct k
//kthread_stop(struct task_struct *k)

	
static void __exit sema_exit(){
	
printk(KERN_INFO "" )
	
}
  
module_init(sema_init);
module_exit(sema_exit);
	
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
