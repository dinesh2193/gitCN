#include<linux/init.h>
#include<linux/module.h>

int ex01_simple_module_init(void)
{
	printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
	return 0;
}

module_init(ex01_simple_module_init);

