#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/irq.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>

#include <asm/uaccess.h>
#include <linux/fs.h>

#include "command.h"

#define DEVICE_NAME "test" 
#define DEV_MAJOR 	123

//#define SYSPATH		"/sys/class/misc/fuse/power/control"

#define SYSPATH		"/tmp/myfile"

char buff[16] = {'0'};

int read_file_kernelspace(char*path,char*buff,int size)
{
	struct file *fptr =NULL;
	mm_segment_t old_addr;
	old_addr = get_fs();
	set_fs(KERNEL_DS);
	
	printk("before filp_open(path,O_RDONLY,0)\n");

	fptr = filp_open(path,O_RDONLY,0);
	if( fptr == NULL)
	{
		printk("filp_open failed\n");
		return -1;
	}

	int readLen = fptr->f_op->read(fptr,buff, size, &fptr->f_pos);	//eeeeeeeeeeeeeee

	if ( readLen != size)
	{

		printk("readLen != size,anyway:");
		printk("buff:%s\n",buff);
	
		filp_close(fptr,NULL);
		set_fs(old_addr);
		
		return -1;
	}

	filp_close(fptr,NULL);
	set_fs(old_addr);
	
	printk("buff:%s\n",buff);

	return 0;
}
int write_file_kernelspace(char*path,char*buff,int size)
{
	struct file *fptr =NULL;
	mm_segment_t old_addr;
	old_addr = get_fs();
	set_fs(KERNEL_DS);
	
	printk("before filp_open(SYSPATH,O_WRONLY,0)\n");
//	fptr = filp_open(SYSPATH,O_WRONLY|O_CREAT,0644);
	fptr = filp_open(SYSPATH,O_WRONLY|O_CREAT,0644);
	if( NULL == fptr )
	{
		printk("filp_open failed\n");
		return -1;
	}
	printk("after filp_open(SYSPATH,O_WRONLY,0)\n");
	
	printk("before writeLen = fptr->f_op->write(fptr,buff,size,&fptr->f_pos)\n");
	int writeLen = fptr->f_op->write(fptr,buff,size,&fptr->f_pos);				//problem? Ð´È¨ÏÞ 
	printk("after writeLen = fptr->f_op->write(fptr,buff,size,&fptr->f_pos)\n");
	
	if ( writeLen != size)
		printk("writeLen != size,anyway:writeLen:%d\n",writeLen);

	filp_close(fptr,NULL);
	set_fs(old_addr);

	return 0;
}

static struct class *test_class;

static int open_test(struct inode *inode, struct file *file)
{
	int res;

	res = simple_strtol("0x20",NULL,0);
	printk("this is the result:%d\n",res);

	char arry[64]={'0'};

	sprintf(arry,"%s","this is sprintf in the kernel space!");
	printk("buff:%s\n",arry);

/*	struct file *fileptr;
	mm_segment_t old_addr = get_fs(); //get the current address the process can access.
	char buf[16]={'\0'};
	int len = 16;
	int retlen=0;

	set_fs(KERNEL_DS);
	
	fileptr = filp_open("./test.txt",O_RDWR|O_CREAT,0644);
	
	if(IS_ERR(fileptr)){
		printk("filp_open :failed to open\n");
		return -1;
	}
	do{
		if((fileptr->f_op == NULL) || (fileptr->f_op->read == NULL))
		{
			printk("file coule not read\n");
			break;
		}else{
			fileptr->f_pos = 0;
		}
		retlen = fileptr->f_op->read(fileptr,buf,len,&fileptr->f_pos);
	}while(false);

	filp_close(fileptr,NULL);

	set_fs(old_addr);
	
	printk("read from user space file ./test.txt %s:\n",buf);
*/
	return 0;
}
static int release_test(struct inode *inode, struct file *file)
{
	return 0;
}
static int ioctl_test( struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	int data=16;
	bool err=0;
	
	if(_IOC_TYPE(cmd) != TESTMAGIC)
		return -ENOTTY;
	if(_IOC_NR(cmd) > MAX_CMD_NUM) 
		return -ENOTTY;	
	
	if(_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE,(void __user*)arg , _IOC_SIZE(cmd));
	else if(_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ,(void __user*)arg , _IOC_SIZE(cmd));
	if (err)
		return -EFAULT; 

	//printk("%s(): cmd=%s, arg=%ld\n", __func__, (cmd==GET_TEST)?"get":"set", arg);
	//dump_stack();

	switch(cmd)
	{
		case GET_TEST:
			put_user(data,(int __user*)arg);
		//	read_file_kernelspace(SYSPATH,buff,6);
			write_file_kernelspace(SYSPATH,"hello\\n",6);
		case SET_TEST:
			get_user(data,(int __user*)arg);
			printk("data:%d\n",data);
			break;
		default:
			break;
	};     //this ; is special.
	
	return 0;
}

struct file_operations test_ops =
{
	.owner = THIS_MODULE,
	.open = open_test,
	.release = release_test,
	.ioctl = ioctl_test,	
};

static int __init test_init(void)
{
	int ret;

	ret = register_chrdev(DEV_MAJOR, DEVICE_NAME, &test_ops);
	if (ret < 0)
	{
		printk(DEVICE_NAME " can't register major number\n");
		return ret;
	}

	test_class = class_create(THIS_MODULE, DEVICE_NAME);
	if(test_class == NULL)
	{
		printk("Err: failed in class_create. \n");
		return -1;
	}
	device_create(test_class, NULL, MKDEV(DEV_MAJOR, 0), NULL, DEVICE_NAME);
	printk(DEVICE_NAME " initialized\n");

	return 0;
}

static void __exit test_exit(void)
{
	unregister_chrdev(DEV_MAJOR, DEVICE_NAME);
	device_destroy(test_class, MKDEV(DEV_MAJOR, 0));
	class_destroy(test_class);    
}

module_init(test_init);
module_exit(test_exit);

MODULE_AUTHOR("peter.gu");
MODULE_DESCRIPTION("for test");
MODULE_LICENSE("GPL");
