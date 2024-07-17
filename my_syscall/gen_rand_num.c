#include <linux/kernel.h>
#include <linux/limits.h>
#include <linux/syscalls.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

SYSCALL_DEFINE2(gen_rand_num, int *, arr, int, max)
{
    int *kbuffer;
    if (max <= 0)
        return -EINVAL;

    kbuffer = (int *) kmalloc(sizeof(int) * max, GFP_KERNEL);

    /* Memory check*/
    if (!kbuffer)
        return -ENOMEM;

    /* Generate Random byte patterns */
    get_random_bytes(kbuffer, sizeof(int) * max);

    /* Convert to positive integers and ensure they don't exceed max */
    for (int i = 0; i < max; i++) {
        kbuffer[i] = (unsigned int)kbuffer[i] % (max + 1);
    }

    /* failed to copy to user */
    if (copy_to_user(arr, kbuffer, sizeof(int) * max)){
        kfree(kbuffer);
        return -EFAULT;
    }

    /* Free'ing memory */
    kfree(kbuffer);
    return 0;
}