#include "../include/pipex.h"

void	ft_perror(char *str)
{
	perror(str);
	exit (0);
}

void	create_pipe(t_map *st)
{
	int	i;

	i = 0;
	while (i < st->argc)
	{
		if (pipe(st[i].fd) == -1)
			ft_perror("Error pipe");
		i++;
	}
}

void	open_file1(t_map *st, char *str)
{
	st->file1 = open(str, O_RDONLY);
	if (st->file1 == -1)
		ft_perror("Net file1");
	if (dup2(st->file1, 0) < 0)
		ft_perror("Couldn't write to the pipe");
}

void	open_file2(t_map *st, char *str)
{
	if (st->flag == 1)
		st->file2 = open(str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		st->file2 = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (st->file2 == -1)
		ft_perror("Net file2");
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1)
		return (1);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
