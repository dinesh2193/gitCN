#include<linux/init.h>
#include<linux/module.h>

int hello_module_init(void)
{
	printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
	return 0;
}

void hello_module_exit(void)
{
	printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
}

module_init(hello_module_init);
module_exit(hello_module_exit);
