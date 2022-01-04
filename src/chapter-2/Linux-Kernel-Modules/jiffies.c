#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/jiffies.h> // jiffies

#define BUFFER_SIZE 128
#define PROC_NAME "jiffies"

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);

/* .read – name of the function that will be called whenever /proc/jiffies is read. */
static struct file_operations proc_ops = {
  .owner = THIS_MODULE,
  .read = proc_read,
};

/* This function is called when the module is loaded. */
int proc_init(void) {
  /* create the "/proc/jiffies" entry */
  proc_create(PROC_NAME, 0666, NULL, &proc_ops);
  
  printk(KERN_INFO "Loading Kernel Module \"jiffies\"\n");

  return 0;
}

/* This function is called when the module is removed. */
void proc_exit(void) {
  /* removes the "/proc/jiffies" entry. */
  remove_proc_entry(PROC_NAME, NULL);

  printk(KERN_INFO "Removing Kernel Module \"jiffies\"\n"); 
}

/*
 * Each time "/proc/jiffies" file is read, this function is called repeatedly until it returns 0.
 * So there must be logic to ensure that this function returns 0 once it has called.
 */ 
ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {
  int rv = 0;
  char buffer[BUFFER_SIZE];
  static int completed = 0;

  // save from infinity loop
  if (completed) {
    completed = 0;
    return 0;
  }

  completed = 1;

  rv = sprintf(buffer, "%lu\n", jiffies);

  /* copies kernel space buffer to user space usr_buf */
  copy_to_user(usr_buf, buffer, rv);

  printk(KERN_INFO "Reading \"jiffies\"\n");

  return rv;
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Jiffies Module");
MODULE_AUTHOR("SGG");

