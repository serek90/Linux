#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096

int main()
{
	void *pbrk = sbrk(0);
	printf("Addres before mmap: %p\n", pbrk);
	void *first = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	pbrk = sbrk(0);
        printf("Addres after first mmap: %p\n", pbrk);

        void *second = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE,
                                MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        pbrk = sbrk(0);
        printf("Addres after all mmap: %p\n", pbrk);



	printf("First mmap: %p\n", first);
	printf("Second mmap: %p\n", second);

	return 0;
}
