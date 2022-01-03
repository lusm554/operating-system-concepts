#include <linux/init.h>
#include <linuxkernel.h/>
#include <linux/module.h>
#include <linux/prof_fs.h>
#include <linux/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_NAME "hello"

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);

static struct file_operations proc_ops = {
  .owner = THIS_MODULE,
  .read = proc_read,
};


/* This function is called when the module is loaded. */
int proc_init(void) {
  /* create the "/proc/hello" entry */
  proc_create(PROC_NAME, 0666, NULL, &proc_ops);
  
  return 0;
}

/* This function is called when the module is removed. */
void proc_exit(void) {
  /* removes the "/proc/hello" entry. */
  remove_proc_entry(PROC_NAME, NULL);
}

/* This function is called each time "/proc/hello" is read. */
ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {

}

