#include <linux/fs.h>
#include <linux/module.h>
#include <linux/uaccess.h>	
#include <linux/miscdevice.h>

#pragma  pack(push)  //保存对齐状态  
#pragma  pack(1)  
typedef struct strcChange
{
    unsigned char user_ID;
    unsigned int allo_vec;
}STRU_CHANGE;
#pragma  pack(pop)

static int open_state;
static STRU_CHANGE strChangeData1;
static STRU_CHANGE timeSlack;

static STRU_CHANGE restrive_from_misc(void)
{
    return strChangeData1;
}
EXPORT_SYMBOL(restrive_from_misc);

static void restrive_from_wifi_driver(STRU_CHANGE time_slack)
{
	timeSlack = time_slack;
}
EXPORT_SYMBOL(restrive_from_wifi_driver);

static int misc_open(struct inode *inode, struct file *file)
{
	if(open_state==0)
	{
		open_state=1;
		printk("MISC OPENED...\n");
		return 0;
	}
	printk("MISC HAS BEEN OPENED..\n");
	return -1;
}

static int misc_release(struct inode *inode, struct file *file)
{
        if(open_state==1)
        {
                open_state=0;
                printk("MISC RELEASED...\n");
                return 0;
        }
        printk("MISC HAS NOT BEEN OPENED..\n");
        return -1;
}
static ssize_t misc_read(struct file *filp, char * buffer, size_t count, loff_t *fpos)
{
	int retvalue;
	unsigned char databuf[10];
	//STRU_CHANGE strChangeData1;
	// timeSlack.user_ID = 0x01;
    // timeSlack.allo_vec = 0x07060504;
    	
    memcpy(databuf, &timeSlack, sizeof(timeSlack));
    retvalue = copy_to_user(buffer, databuf, count);

    if(retvalue < 0) {
		printk("kernel read failed!\r\n");
		return -EFAULT;
	}
    	
	printk("misc read..\n");
	return 0;
}
static ssize_t misc_write(struct file *filp, const char * buffer, size_t count, loff_t *fpos)
{
	int retvalue;
	unsigned char databuf[10];
	STRU_CHANGE * pstrChangeData1;
	
	retvalue = copy_from_user(databuf, buffer, count);
	if(retvalue < 0) {
		printk("kernel write failed!\r\n");
		return -EFAULT;
	}

	pstrChangeData1 = (STRU_CHANGE *)((char*)databuf);
	//beepstat = databuf[0];   获取状态值 
	printk("The data from userspace user_ID: 0x%x \r\n", pstrChangeData1->user_ID); 
	printk("The data from userspace allo_vec: 0x%08x \r\n", pstrChangeData1->allo_vec); 

	strChangeData1.user_ID = pstrChangeData1->user_ID;
	strChangeData1.allo_vec = pstrChangeData1->allo_vec;

	printk("misc write..\n");
	return 0;
}
/*
static int misc_ioctl(struct inode * inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk("misc ioctl is called..\n");
	printk("cmd:%d arg:%ld\n", cmd, arg);
	return 0;
}
*/
struct file_operations fops =   
{  
	.owner      =   THIS_MODULE,  
	.open       =   misc_open,  
	.release    =   misc_release,  
	.write      =   misc_write,  
	.read       =   misc_read
	//.ioctl      =   misc_ioctl  
};

struct miscdevice dev={
	.minor	=	MISC_DYNAMIC_MINOR,
	.fops	=	&fops,
	.name	=	"my_misc",
};

static int __init misc_init(void)
{
	printk("MISC DEV IS REGISTERED..\n");
	misc_register(&dev);
	return 0;
}

static void __exit misc_exit(void)
{
	printk("MISC DEV HAS BEEN DEREGISTERED..\n");
	misc_deregister(&dev);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LUCIEN");
module_init(misc_init);  
module_exit(misc_exit);  
