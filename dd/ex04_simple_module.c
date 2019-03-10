#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

__initdata int count=5;

__init int ex04_simple_module_init(void)
{
	int index = 0;
	printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);

	for(index=0;index < count ;index++)
	{
		printk(KERN_ALERT "index : %d\n",index);
	}

	return 0;
}

void ex04_simple_module_exit(void)
{
	printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
}

module_init(ex04_simple_module_init);
module_exit(ex04_simple_module_exit);
