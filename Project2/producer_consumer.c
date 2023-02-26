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

module_param(buff_size, int, 1);
module_param(p, int, 0);
module_param(c, int, 0);
module_param(uuid, int, 1);

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


struct task_struct* p;
size_t process_counter = 0;
for_each_process(p) {
++process_counter;
}

struct semaphore name; // Defines a semaphore with a given name
static inline void sema_init(struct semaphore *sem, int val) // a
function to initialize a semaphore structure
void down_interruptible(struct semaphore *sem) // acquire a lock
void up(struct semaphore *sem) // release a lock

struct semaphore name; // Defines a semaphore with a given name
static inline void sema_init(struct semaphore *sem, int val) // a
function to initialize a semaphore structure
void down_interruptible(struct semaphore *sem) // acquire a lock
void up(struct semaphore *sem) // release a lock

// Semaphore Definition
struct semaphore empty; // define a semaphore named 'empty'
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

task_struct *task;
task->start_time // start time of the process (in nanoseconds)
ktime_get_ns() // current time in nanoseconds.
//Defined in include/linux/timekeeping.h

// stop the kernel thread pointed by task_struct k
kthread_stop(struct task_struct *k)
// when kthread_stop() is called, this function will return true
kthread_should_stop(void)

module_exit();
