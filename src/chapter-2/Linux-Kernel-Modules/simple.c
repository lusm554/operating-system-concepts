#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h> // GOLDEN_RATIO_PRIME
#include <linux/gcd.h> // gcd
#include <asm/param.h> // HZ
#include <linux/jiffies.h> // jiffies

unsigned long int JIFFIES_AT_INIT;

/* This function is called when the module is loaded. */
int simple_init(void) {
  printk(KERN_INFO "Loading Kernel Module\n");

  unsigned long int a = 3300;
  unsigned int b = 24;
  JIFFIES_AT_INIT = jiffies;

  /* Print GOLDEN_RATIO_PRIME and GCD of a and b. */
  printk(KERN_INFO "GOLDEN_RATIO_PRIME: %u\n", GOLDEN_RATIO_PRIME);
  printk(KERN_INFO "Greatest common divisor of %u and %u: %llu\n", a, b, gcd(a, b));

  /* Print jiffies and HZ. */
  printk(KERN_INFO "Jiffies in init: %u\n", jiffies);
  printk(KERN_INFO "HZ: %u\n", HZ);

  return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
  int time = (JIFFIES_AT_INIT - jiffies) * 1000 / HZ; // TODO: FIX

  /* Print jiffies and number of seconds that have elapsed since module loaded. */
  printk(KERN_INFO "Jiffies in exit: %u\n", time);
  printk(KERN_INFO "Number of seconds since module loaded: %u\n", jiffies);

  printk(KERN_INFO "Removing Kernel Module\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

