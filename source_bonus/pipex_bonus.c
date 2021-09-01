#include "../include/pipex.h"

void	have_here_doc(t_map *st, char **argv)
{
	char	*buf;

	buf = NULL;
	while (ft_strcmp(buf, argv[2]))
	{
		write(1, "pipe heredoc> ", 14);
		if (get_next_line(0, &buf) && ft_strncmp(buf, argv[2],
				ft_strlen(argv[2])))
		{
			write(st[st->i].fd[1], buf, ft_strlen(buf));
			write(st[st->i].fd[1], "\n", 1);
		}
		free(buf);
	}
	exit (0);
}

int	many_command(t_map *st, char **envp, char **argv)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_perror("Error pid(fork)");
	if (pid == 0)
	{
		if (st->i == 0 && st->flag == 1)
			have_here_doc(st, argv);
		pid_children(st, envp);
		return (3);
	}
	else
	{
		wait(NULL);
		close((st[st->i].fd[1]));
		if (st->i)
			close(st[st->i - 1].fd[0]);
	}
	return (0);
}

void	check_argc(int argc, char **argv, t_map *st)
{
	if (argc < 5)
		ft_perror("argc < 5");
	if (argc >= 5)
	{
		if (ft_strcmp("here_doc", argv[1]) == 0)
		{
			if (argc == 6)
			{
				st->flag = 1;
				st->floating_i = 3;
				create_pipe(st);
			}
			else
				ft_perror("here_doc, argc != 6");
		}
		else
		{
			create_pipe(st);
			open_file1(st, argv[1]);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_map	*st;

	st = malloc(sizeof(t_map) * (argc - 4));
	st->floating_i = 2;
	st->i = 0;
	st->flag = 0;
	st->argc = argc - 4;
	check_argc(argc, argv, st);
	while (st->i < st->argc)
	{
		st->floating_argv = ft_split(argv[st->floating_i], ' ');
		many_command(st, envp, argv);
		st->i++;
		if (st->flag == 1)
			st->floating_i = 3;
		else
			st->floating_i++;
	}
	pid_parent(st, envp, argv, argc);
	free(st);
	return (0);
}
