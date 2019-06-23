

#include<linux/init.h>
#include<linux/module.h>

#include<linux/fs.h>
#include<linux/slab.h>
//#include<asm/uaccess.h>
#include<linux/uaccess.h> 

#define BUFFER_SIZE 1024

MODULE_LICENSE("GPL");

/* Define device_buffer and other global data structures you will need here */
int openCount = 0;
int closeCount = 0;

void* device_buffer;

int simple_char_driver_open (struct inode *pinode, struct file *pfile)
{
	/* DONE --- print to the log file that the device is opened and also print the number of times this device has been opened until now*/
	printk(KERN_ALERT "Device opened! It has been opened %d times before this.\n", openCount);
	openCount++;

	return 0;
}

int simple_char_driver_close (struct inode *pinode, struct file *pfile)
{
	/* DONE --- print to the log file that the device is closed and also print the number of times this device has been closed until now*/
	printk(KERN_ALERT "Device closed! It has been closed %d times before this.\n", closeCount);
	closeCount++;

	return 0;
}

ssize_t simple_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
	/* length is the length of the userspace buffer*/
	/* offset will be set to current position of the opened file after read*/
	/* copy_to_user function: source is device_buffer and destination is the userspace buffer *buffer */

	int totalAmountToRead = BUFFER_SIZE - *offset;

	if(totalAmountToRead == 0)
	{
		printk(KERN_ALERT "End of file.\n");
		return totalAmountToRead;
	}
	if(totalAmountToRead > length)
	{
		totalAmountToRead = length;
		printk(KERN_ALERT "User buffer space insufficient, truncating read to %d bytes.\n", totalAmountToRead);
	}

	copy_to_user(buffer, device_buffer + *offset, totalAmountToRead);
	printk(KERN_ALERT "Reading %d bytes from device.\n", totalAmountToRead);

	*offset = *offset + totalAmountToRead;

	return totalAmountToRead;
}

ssize_t simple_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
	/* length is the length of the userspace buffer*/
	/* current position of the opened file*/
	/* copy_from_user function: destination is device_buffer and source is the userspace buffer *buffer */

	int totalAmountToWrite = length;
	int freeDeviceSpace = BUFFER_SIZE - *offset;

	if(freeDeviceSpace < length)
	{
		totalAmountToWrite = freeDeviceSpace;
		printk(KERN_ALERT "Device buffer space insufficient, truncating write to %d bytes.\n", totalAmountToWrite);
	}

	copy_from_user(device_buffer + *offset, buffer, totalAmountToWrite);
	printk(KERN_ALERT "Writing %d bytes to device.\n", totalAmountToWrite);

	*offset = *offset + totalAmountToWrite;

	return length;
}

loff_t simple_char_driver_seek (struct file *pfile, loff_t offset, int whence)
{
	/* DONE ---  Update open file position according to the values of offset and whence */
	loff_t seekPosition = 0;

	switch(whence)
	{
		case 0:
			seekPosition = offset;
			break;
		case 1:
			seekPosition = pfile -> f_pos + offset;
			break;
		case 2:
			seekPosition = BUFFER_SIZE - offset;
			break;
		default:
			printk(KERN_ALERT "Please enter a valid whence value.");
			return 0;
			break;
	}

	if(seekPosition < 0)
	{
		seekPosition = 0;
	}
	if(seekPosition > BUFFER_SIZE)
	{
		seekPosition = BUFFER_SIZE;
	}

	pfile->f_pos = seekPosition;


	return seekPosition;
}

struct file_operations simple_char_driver_file_operations = {

	.owner   = THIS_MODULE,
	/* DONE --- add the function pointers to point to the corresponding file operations. look at the file fs.h in the linux souce code*/
	.llseek = simple_char_driver_seek,
	.read = simple_char_driver_read,
	.write = simple_char_driver_write,
	.open = simple_char_driver_open,
	.release = simple_char_driver_close,
};

static int simple_char_driver_init(void)
{
	/* DONE --- print to the log file that the init function is called.*/
	/* DONE --- register the device */

	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	register_chrdev(300, "simple_char_driver", &simple_char_driver_file_operations);
	device_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);

	return 0;
}

static void simple_char_driver_exit(void)
{
	/* DONE --- print to the log file that the exit function is called.*/
	/* DONE --- unregister  the device using the register_chrdev() function. */

	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	unregister_chrdev(300, "simple_char_driver");
	kfree(device_buffer);
}

/* DONE --- add module_init and module_exit to point to the corresponding init and exit function*/
module_init(simple_char_driver_init);
module_exit(simple_char_driver_exit);