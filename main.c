#include "get_next_line.h"

void print_yellow(char *str) {
	printf("\033[33m%s\033[0m", str);
}

void	print_read_str(char *str) {
	for (int i = 0; i < strlen(str); ++i) {
		printf("%02x %c ", str[i], str[i]);
	}
	putchar('\n');
}

int main(void) {
	char	*ret;
	int		fd;

	fd = open("./gnlTester/files/43_with_nl", 0);
	// printf("fd  : %d\n", fd);
	// fd = STDIN_FILENO; // stdin
	// fd = STDOUT_FILENO; // stdout
	// fd = STDERR_FILENO; // stderr
	// printf("_SC_OPEN_MAX %ld\n", sysconf(_SC_OPEN_MAX));
	// printf("_SC_OPEN_MAX %ld\n", _SC_OPEN_MAX);
	// printf("OPEN_MAX - _SC_OPEN_MAX %ld\n", OPEN_MAX - _SC_OPEN_MAX);
	fd = 0;
	do {
		ret = get_next_line(fd);
		print_yellow(ret);
		free(ret);
	} while (ret != NULL);
	close(fd);
	// system("leaks a.out");
}
