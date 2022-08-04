#include <stdio.h>
#include <unistd.h>

#define PAGE_SIZE 4096

int main()
{
	void *first_a = sbrk(0); //sbrk return the previous address of the program break
	void *second_a = sbrk(PAGE_SIZE);
	void *third_a = sbrk(0);

	//Now random number
	void *fourth_a = sbrk(30);
	void *fifth_a = sbrk(0);

	printf("First: %p\n", first_a);
	printf("Second: %p\n", second_a);
	printf("Third: %p\n", third_a);

	printf("Fourth: %p\n", fourth_a);
	printf("Fifth: %p\n", fifth_a);
	return 0;
}
