#include "get_next_line.h"

void print_yellow(char *str) {
	printf("\033[33m%s\033[0m\n", str);
}

int main(void) {
	char	*ret;
	int		fd;
	int		i = 0;

	fd = open("./case_7.txt", 0);
	// printf("fd  : %d\n", fd);
	// fd = STDIN_FILENO; // stdin
	// fd = STDOUT_FILENO; // stdout
	// fd = STDERR_FILENO; // stderr
	// printf("_SC_OPEN_MAX %ld\n", sysconf(_SC_OPEN_MAX));
	do {
		ret = get_next_line(fd);
		print_yellow(ret);
		free(ret);
		i++;
	} while (ret != NULL);
	// } while (ret != NULL && i < 5);
	close(fd);
}
