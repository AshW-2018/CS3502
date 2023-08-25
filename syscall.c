#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <asm/uaccess.h>
#include <linux/kallsyms.h>

#define __NR_syscall 335	/* system call: 335 */
unsigned long * sys_call_table;

unsigned int clear_and_return_cr0(void);
void setback_cr0(unsigned int val);
static int sys_mycall(void);

int orig_cr0;
unsigned long *sys_call_table = 0;
static int (*anything_saved)(void);
/*
 * set cr0 register No.17 as 0
 */
unsigned int clear_and_return_cr0(void)
{
   	unsigned int cr0 = 0;
   	unsigned int ret;
    /* The former is used in 32-bit systems. The latter is used in 64-bit systems, this system is 64-bit */
	//asm volatile ("movl %%cr0, %%eax" : "=a"(cr0));
	asm volatile ("movq %%cr0, %%rax" : "=a"(cr0));

	ret = cr0;
	cr0 &= 0xfffeffff;

	//asm volatile ("movl %%eax, %%cr0" :: "a"(cr0));
	asm volatile ("movq %%rax, %%cr0" :: "a"(cr0));
	return ret;
}


/* Read the value of val to the rax register, and then put the value of the rax register into cr0 */
void setback_cr0(unsigned int val)
{

	//asm volatile ("movl %%eax, %%cr0" :: "a"(val));
	asm volatile ("movq %%rax, %%cr0" :: "a"(val));
}


/* Our system call is here */
static int sys_mycall(void)
{
	int ret = 12345;
	printk("Here is my syscall in OS kerenl!\n");
	return ret;
}


static int __init init_addsyscall(void)
{
	printk("My syscall is starting。。。\n");
	sys_call_table = (unsigned long *)kallsyms_lookup_name("sys_call_table");
   	printk("sys_call_table: 0x%p\n", sys_call_table);
	anything_saved = (int(*)(void))(sys_call_table[__NR_syscall]);
	orig_cr0 = clear_and_return_cr0();
	sys_call_table[__NR_syscall] = (unsigned long)&sys_mycall;
	setback_cr0(orig_cr0);
	return 0;
}


static void __exit exit_addsyscall(void)
{
 	orig_cr0 = clear_and_return_cr0();
    sys_call_table[__NR_syscall] = (unsigned long)anything_saved;
    setback_cr0(orig_cr0);
   	printk("My syscall exit....\n");
}

module_init(init_addsyscall);
module_exit(exit_addsyscall);
MODULE_LICENSE("GPL");
