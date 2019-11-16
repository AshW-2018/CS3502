#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define MAX_LEN       4096
static struct proc_dir_entry *proc_entry;


ssize_t read_proc(struct file *f, char *user_buf, size_t count, loff_t *off )
{
	//output the content of info to user's buffer pointed by page
	printk(KERN_INFO "procfs_read: read %lu bytes\n", count);
	return count;
}


ssize_t write_proc(struct file *f, const char *user_buf, size_t count, loff_t *off)
{
	//copy the written data from user space and save it in info
	printk(KERN_INFO "procfs_write: write %lu bytes\n", count);
	return count;
}


struct file_operations proc_fops = {
	read: read_proc,
	write: write_proc
};


int init_module( void )
{
	int ret = 0;
	//create the entry and allocated memory space for the proc entry

	printk(KERN_INFO "test_proc created.\n");

	return ret;
}


void cleanup_module( void )
{
	//remove the proc entry and free info space
	
	printk(KERN_INFO "test_proc deleted.\n");
}


