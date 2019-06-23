#include <linux/kernel.h>
#include <linux/linkage.h>

#include <linux/uaccess.h>

asmlinkage long sys_cs3753_add(int* num1, int* num2, int** point)
{
	int* internal_point;
	int internal_1;
	int internal_2;
	int addition;

	get_user(internal_1, num1);
	get_user(internal_2, num2);
	get_user(internal_point, point);

	addition = internal_1 + internal_2;

	put_user(addition, internal_point);

 	printk(KERN_INFO "num1: %d\n", internal_1);
	printk(KERN_INFO "num2: %d\n", internal_2);
	printk(KERN_INFO "addition (KERNEL): %d\n", addition);
 	
	return 0;
} 
