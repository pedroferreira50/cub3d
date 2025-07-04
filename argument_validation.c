#include "cub3d_parsing.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static int	is_cub_file(const char *filename)
{
	int	len;
	int	fd;

	len = ft_strlen(filename);
	if (len > 4 && ft_strcmp(filename + len - 4, ".cub") != 0)
	{
		ft_printf("Error: File must have a .cub extension.\n");
		return (1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("The file does not exist\n");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

void	check_arguments(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf("Error: No file provided. Usage: ./program <map.cub>\n");
		exit(1);
	}
	else if (argc > 2)
	{
		ft_printf("Error: Too many arguments. Usage: ./program <map.cub>\n");
		exit(1);
	}
	else if (is_cub_file(argv[1]))
		exit(1);
	ft_printf("File %s is valid.\n", argv[1]); // remove
}
