File contents:

	PA2_helloModule.c:		Simple test module to test adding and removing a kernel module.
	PA2_simple_char_driver.c:	Simple character device driver that allows for reading, writing, and seeking of a device buffer. The driver
					is connected to a device file which allows for these operations to be used in accordance to standard file mapped
					I/O operation. Has init and exit functions for when the driver is loaded and removed, and open and close functions
					for opening and closing device files connected to the driver.
	Makefile:			Used to compile both PA2_helloModule.c and PA2_simple_char_driver.c into kernel modules
	test.cpp:			A test file that allows testing of file operations on the device file connected to PA2_simple_char_driver

Paths:

	PA2_helloModule.c:		~/modules/PA2_helloModule.c
	PA2_simple_char_driver.c:	~/modules/PA2_simple_char_driver.c
	Makefile:			~/modules/Makefile
	test.cpp:			Can be placed anywhere.

Buidling and installing modules and test program:

	Place the files in the corresponding paths given above. To build the kernel modules, enter the "modules" folder, and type the command:

		"sudo make -C /lib/modules/$(uname -r)/build M=$PWD modules"

	to insert the modules type:

		"sudo insmod PA2_helloModule.ko" or "sudo insmod PA2_simple_char_driver.ko"

	To create the device file named "simple_character_device" connected to PA2_simple_char_driver type:
	
		"sudo mknod -m 777 /dev/simple_character_device c 300 0"

	Build the test.cpp file in whatever directory you have placed it in with:

		"g++ -o test test.cpp"

	And then run with:

		"./test"


