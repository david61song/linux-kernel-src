#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(my_syscall)
{
	printk(KERN_INFO "This is my first system call! Wow! \n");
	return 0;
}
