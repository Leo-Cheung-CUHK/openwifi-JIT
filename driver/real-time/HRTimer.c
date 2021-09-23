#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hrtimer.h>
#include <linux/jiffies.h>
 
static struct hrtimer timer;
ktime_t kt;

static void
print_elapsed_time(void)
{
     static struct timespec start;
     struct timespec curr;
     static int first_call = 1;
     int secs, nsecs;

     if (first_call) {
          first_call = 0;
		  getrawmonotonic(&start);
     }
     getrawmonotonic(&curr);
     secs = curr.tv_sec - start.tv_sec;
     nsecs = curr.tv_nsec - start.tv_nsec;
     if (nsecs < 0) {
         secs--;
         nsecs += 1000000000;
     }
	 start.tv_sec = curr.tv_sec ;
     start.tv_nsec = curr.tv_nsec ;
     //printf("%d.%06d: ", secs, (nsecs + 500) / 1000);
     printk("%d.%09d: ", secs, nsecs);
 }

static enum hrtimer_restart  hrtimer_hander(struct hrtimer *timer)
{
    printk("hrtimer up\r\n");
 
    kt = ktime_set(0,1000);    
    hrtimer_forward_now(timer, kt);
    print_elapsed_time();
 
    return HRTIMER_RESTART;  
}
 
static int __init hrtimer_demo_init(void)
{
    printk("hello hrtimer \r\n");
 
    kt = ktime_set(1,10);
 
    hrtimer_init(&timer,CLOCK_MONOTONIC,HRTIMER_MODE_REL);
 
    hrtimer_start(&timer,kt,HRTIMER_MODE_REL);
 
    timer.function = hrtimer_hander;
 
    return 0;
}
 
static void __exit hrtimer_demo_exit(void)
{
    hrtimer_cancel(&timer);
    printk("bye hrtimer\r\n");
}
 
 
module_init(hrtimer_demo_init);
module_exit(hrtimer_demo_exit);
MODULE_LICENSE("GPL");
