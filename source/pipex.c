#include "../include/pipex.h"

void	pars_envp(char **envp, char	**first_argv, int i, int k)
{
	char	**out;
	char	*search_PATH;

	while (envp[i])
	{
		search_PATH = ft_strnstr(envp[i], "PATH=", 5);
		if (search_PATH)
		{
			search_PATH = ft_strrchr(search_PATH, '=');
			out = ft_split(search_PATH, ':');
			while (out[k])
			{
				i = 0;
				out[k] = ft_strjoin(out[k], "/");
				out[k] = ft_strjoin(out[k], first_argv[0]);
				execve(out[k], first_argv, NULL);
				k++;
			}
			ft_perror("Wrong command");
		}
		i++;
	}
}

void	pid_children_osn(t_map *st, char **envp, int *fd)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (dup2(st->file1, 0) < 0)
		ft_perror("Couldn't open the read  file1");
	if (dup2(fd[1], 1) < 0)
		ft_perror("Couldn't write the pipe");
	close(fd[0]);
	close(fd[1]);
	close(st->file1);
	pars_envp(envp, st->first_argv, i, k);
}

void	pid_parent_osn(t_map *st, char **envp, int *fd)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (dup2(fd[0], 0) < 0)
		ft_perror("Couldn't read with pipe");
	if (dup2(st->file2, 1) < 0)
		ft_perror("Couldn't write the file2");
	close(fd[0]);
	close(fd[1]);
	close(st->file2);
	pars_envp(envp, st->second_argv, i, k);
}

void	check_argv(int argc, t_map *st, char **argv)
{
	if (argc != 5)
	{
		ft_perror("argc != 5");
		exit(0);
	}
	st->first_argv = ft_split(argv[2], ' ');
	st->second_argv = ft_split(argv[3], ' ');
	st->file1 = open(argv[1], O_RDONLY);
	if (st->file1 == -1)
		ft_perror("Error open file1");
	st->file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (st->file2 == -1)
		ft_perror("Error open file2");
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pid;
	int		fd[2];
	t_map	st;

	if (pipe(fd) == -1)
		ft_perror("Error pipe create");
	check_argv(argc, &st, argv);
	pid = fork();
	if (pid == -1)
		ft_perror("Error pid(fork)");
	if (pid == 0)
		pid_children_osn(&st, envp, fd);
	else
		pid_parent_osn(&st, envp, fd);
	return (0);
}
