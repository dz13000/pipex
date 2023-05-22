#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pack
{
	char	*infile;
	char	*outfile;
	int		prev_pipe;
	int		nb_cmd;
	int		*pid;
	int		fd[2];
	char	**line_cmd;
	char	**path;
	char	*cmd;
}			t_pack;

char		**ft_split(char const *s, char c);
int			main(int ac, char **av, char **env);
char		*ft_strjoin(char const *s1, char const *s2);

#endif