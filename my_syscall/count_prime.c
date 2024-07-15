#include <linux/syscalls.h>
#include <linux/kernel.h>


// Helper function to get the nearest square root
static int get_nearest_sqrt(int num) {
    int iter = 1;
    while (iter * iter <= num) {
        iter++;
    }
    return iter - 1;
}

// Helper function to check if a number is prime
static int check_if_prime(int num) {
    // If we get a number less than 0, make positive
    if (num < 0)
        num *= -1;
    // Numbers less than 2 are not prime
    if (num < 2) 
        return 0; 
    int sqrt_of_num = get_nearest_sqrt(num);
    for (int iter = 2; iter <= sqrt_of_num; iter++) {
        if (num % iter == 0)
            return 0;
    }
    return 1;
}

// System call implementation
SYSCALL_DEFINE2(count_prime, int __user *, arr, int, max) {
    int *kbuffer;
    int count = 0;
    int i;

    if (max <= 0)
        return -EINVAL;

    kbuffer = kmalloc(sizeof(int) * max, GFP_KERNEL);
    if (!kbuffer)
        return -ENOMEM;

    if (copy_from_user(kbuffer, arr, sizeof(int) * max)) {
        kfree(kbuffer);
        return -EFAULT;
    }

    for (i = 0; i < max; i++) {
        if (check_if_prime(kbuffer[i]))
            count++;
    }

    kfree(kbuffer);
    return count;
}