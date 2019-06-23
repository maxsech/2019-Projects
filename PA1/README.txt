File contents:
cs3753_add.c:	System Call that adds two variables stored in User space, and stores the result at an address that is also in User space.
		The system call is passed pointers to the two variables in user space to be added, as well as a pointer to the pointer to
		the address at which it is supposed to store the result.
helloworld.c	Test system call, a simple printk statement that prints to the syslog.
Makefile:	Instructs the compilier on how to compile the kernel, includes the new system call file.
syscall_64.tbl:	The system call table, with our new system call added.
syscalls.h:	The header file for system calls, includes our new system call
syslog:		System log after our new system call has been run, the last three lines show the output of our new system call: num1 is
		the first number to be added, num2 is the second number to be added, and addition (KERNEL) is the output calculated
		inside the system call.
test2.c:	The test program that runs our new system call.

Paths:
cs3753_add.c:	arch/x86/kernel/cs3753_add.c
helloworld.c:	arch/x86/kernel/helloworld.c
Makefile:	arch/x86/kernel/Makefile
syscall_64.tbl:	arch/x86/entry/entry/syscalls/syscall_64.tbl
syscalls.h:	include/linux/syscalls.h 
test2.c:	Can be placed anywhere

Buidling:

Add s3753_add.c, syscall_64.tbl, syscalls.h, and the Makefile to the standard build tree at the given paths above. Compile the kernel 
with the files added. Compile test2.c at what ever location you have stored it, and then run test2. 


