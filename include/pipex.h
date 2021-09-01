#ifndef PIPEX_H
# define PIPEX_H
# define BUFFER_SIZE 1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct st_pam
{
	int		floating_i;
	int		i;
	int		argc;
	int		fd[2];
	int		file1;
	int		file2;
	int		flag;
	char	**floating_argv;
	char	**last_argv;
	char	**first_argv;
	char	**second_argv;
}	t_map;

char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *dst, const char *src);
int		get_next_line(int fd, char **line);

char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *p1, const char *p2, size_t n);
void	pars_envp(char **envp, char	**first_argv, int i, int k);
void	pid_parent(t_map *st, char **envp, char **argv, int argc);
void	pid_children(t_map *st, char **envp);
void	create_pipe(t_map *st);
void	ft_perror(char *str);
void	open_file1(t_map *st, char *str);
void	open_file2(t_map *st, char *str);
int		ft_strcmp(const char *s1, const char *s2);

#endif