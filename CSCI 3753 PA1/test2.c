#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

int main(void) 
{
	int num1 = 3;
	int num2 = 1;
	int result; //Stores our result

	int* point;	//Pointer to result
	point = &result;

	printf("num1: %d\n", num1);
	printf("num2: %d\n", num2);

	syscall(334, &num1, &num2, &point);

	printf("addition (USER): %d", result);

	return 0;
}