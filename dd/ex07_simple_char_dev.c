#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h> /*for character driver support */

int ex07_simple_module_init(void)
{
	printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
	/*Register with the kernel and indicate that we are registering a 		character device driver*/
	register_chrdev(/*major number*/
			/*Name of the driver*/
			/*File Operatirons 
	return 0;
}

void ex07_simple_module_exit(void)
{
	printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
}

module_init(ex07_simple_module_init);
module_exit(ex07_simple_module_exit);
