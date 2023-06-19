#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	// chdir(argv[1]);
	// execvp("ls", argv);
	if (!argv[1])
		printf("hello\n");
}
