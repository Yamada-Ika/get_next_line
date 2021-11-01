#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
	int fd1;
	char *ret;

	// fd1 = open("./get_next_line.c", 0);
	fd1 = 1;
	while (ret = get_next_line(fd1))
	{
		printf("%s", ret);
		free(ret);
	}
	close(fd1);
}
