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

module_param(buff_size, int, 0);
module_param(p, int, 0);
module_param(c, int, 0);
module_param(uuid, int, 0);

// Declare producer and consumer functions
static int consumer_func(void *arg);
static int producer_func(void *arg);

// the function to run in the thead
static int kthread_func(void *arg) {

}
// Create and run "thread-1"
ts1 = kthread_run(kthread_func, NULL, "thread-1");

for_each_process(struct task_struct *p) // On each iteration, p
points to the next task in the list.
task_struct *task;
task->pid // PID of the process
task->cred->uid.val // UID of the user of the process

  // Semaphore declaration
struct semaphore empty;
struct semaphore full;
struct semaphore mutex;

// Define a global int to track total task time
long total_time;

struct task_struct* p;
size_t process_counter = 0;
for_each_process(p) {
++process_counter;
}


// Linked List declaration 
struct task_node
{
	struct task_struct *task;
	struct task_node *next;

} task_list;

static inline void sema_init(struct semaphore *sem, int val) // a function to initialize a semaphore structure
  
  // acquire lock (down, release a lock (up)
void down_interruptible(struct semaphore *sem) // acquire a lock
void up(struct semaphore *sem) // release a lock

struct semaphore name; // Defines a semaphore with a given name
static inline void sema_init(struct semaphore *sem, int val) // a
function to initialize a semaphore structure
void down_interruptible(struct semaphore *sem) // acquire a lock
void up(struct semaphore *sem) // release a lock


///////////////////////////////////

static int sema_init(void)
{

      // Initialize semaphores
    sema_init(&empty, buff_size);
    sema_init(&full, 0); 
    sema_init(&mutex, 1);
  
      // set the initial values to NULL in the linked list
    task_list.task = NULL;
    task_list.next = NULL;
  
}

// Semaphore Definition
sema_init(&empty, 5); // init the semaphore as 5
// if the thread works in an infinite loop, this is how it knows when
to stop. Check (4) module_exit for more information.
while (!kthread_should_stop())
{
if (down_interruptible(&empty))
/* down_interruptible allows the calling thread to be
interrupted even if it has not acquired the semaphore that
it has been waiting for */
break; // exit
// Critical section
up(empty)
// signal the semaphore
}

static int producer_func(void *arg)
{
}
  
static int consumer_func(void *arg)
{
}

task_struct *task;
task->start_time // start time of the process (in nanoseconds)
ktime_get_ns() // current time in nanoseconds.
//Defined in include/linux/timekeeping.h

// stop the kernel thread pointed by task_struct k
kthread_stop(struct task_struct *k)
// when kthread_stop() is called, this function will return true
kthread_should_stop(void)
  
module_init();
module_exit();
