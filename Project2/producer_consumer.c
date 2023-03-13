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
module_param(buff_size, int, 0644); 	// The buffer size
module_param(p, int, 0644);		// number of producers(0 or 1)
module_param(c, int, 0644);     	// number of consumers(a non-negative number)
module_param(uuid, int, 0644);		// The UID of the user

	// Declare producer and consumer functions
static int consumer_func(void *arg);
static int producer_func(void *arg);

  // Semaphore declaration
struct semaphore empty;
struct semaphore full;
struct semaphore mutex;

// Define a global int to track total task time and error 
long total_time;
int error;

struct consumer{
	struct task_struct *consumer_thread;
	struct consumer_node *next;
} consumer;

// buffer struct declaration
struct buffer{
	int capacity;
	struct task_node *head;
} buffer;

// Linked List declaration 
struct task_node{
	struct task_struct *task;
	struct task_node *next;
} task_list;

static inline void sema_init(struct semaphore *sem, int val) // a function to initialize a semaphore structure
  
  // acquire lock (down, release a lock (up)
void down_interruptible(struct semaphore *sem) // acquire a lock
void up(struct semaphore *sem) // release a lock

struct semaphore name; // Defines a semaphore with a given name
static inline void sema_init(struct semaphore *sem, int val) // a function to initialize a semaphore structure
void down_interruptible(struct semaphore *sem) // acquire a lock
void up(struct semaphore *sem) // release a lock


///////////////////////////////////
	// needs work
static int __init sema_init(void)
{

    	  // Initialize semaphores
    	sema_init(&empty, buff_size);
    	sema_init(&full, 0); 
    	sema_init(&mutex, 1);
  
    	  // set the initial values to NULL in the linked list
    	task_list.task = NULL;
    	task_list.next = NULL;
	
	buffer.capacity = buff_size;
	buffer.head = &task_list;
	

return 0;
  
}

// Semaphore Definition
sema_init(&empty, 5); // init the semaphore as 5
// if the thread works in an infinite loop, this is how it knows when to stop. Check (4) module_exit for more information.

	// needs work
static int producer_func(void *arg)
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
			
			
				// increment the semaphores
			up(&mutex);
			up(&full);
		}
	}
	
	
	return 0;
}
  
static int consumer_func(void *arg)
{
	
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
			
		long current_time = ktime_get_ns();
		long start_time = temp->task->start_time;
		long task_time = current_time - start_time;
		u64 base = task_time/1000000000;
		int hours = base/3600;
		int minutes = (base - (hours*3600))/60;
		int seconds = base - (hours*3600) - (minutes*60);
		total_time += task_time;
		
		printk()
			
				  // increment semaphores
	        up(&mutex);
	
        	up(&empty);
		}
	
	return 0;
}

task_struct *task;
task->start_time // start time of the process (in nanoseconds)
ktime_get_ns() // current time in nanoseconds.
//Defined in include/linux/timekeeping.h

// stop the kernel thread pointed by task_struct k
kthread_stop(struct task_struct *k)
// when kthread_stop() is called, this function will return true
kthread_should_stop(void)
	
static void __exit sema_exit(){
	
printk(KERN_INFO "" )
	
}
  
module_init(sema_init);
module_exit(sema_exit);
