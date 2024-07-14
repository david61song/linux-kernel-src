#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE2(gen_rand_num, int *, arr, int, max)
{
    void * kbuffer;

    kbuffer = kmalloc(sizeof(int) * max, GFP_KERNEL);

    if (copy_from_user(kbuffer, arr, sizeof(int) * max))
        return -EFAULT;

    /* Generate Random byte patterns */
    get_random_bytes(kbuffer, sizeof(int) * max);

    if (copy_to_user(arr, kbuffer, sizeof(int) * max))
        return -EFAULT;

    /* Free'ing memory */
    kfree(kbuffer);

    return 0;
}
