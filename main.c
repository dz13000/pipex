#include "pipex.h"

void	close_fd(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
}

void	init_value(char **av, t_pack *pack)
{
	memset(pack, 0, sizeof(t_pack));
	pack->prev_pipe = -1;
	pack->infile = av[1];
	pack->outfile = av[4];
	pack->nb_cmd = 2;
	pack->pid = malloc(sizeof(int) * 2);
}

void	redirect(t_pack *pack, int i)
{
	int	fd;

	fd = -1;
	if (i == 0)
	{
		fd = open(pack->infile, O_RDONLY);
		fprintf(stderr, "haja3\n");
		dup2(fd, STDIN_FILENO);
	}
	if (i == 1)
	{
		fprintf(stderr, "haja3\n");
		fd = open(pack->outfile, O_CREAT | O_TRUNC | O_WRONLY , 0666);
		dup2(fd, STDOUT_FILENO);
	}
	if (i != 0)
	{
		dup2(pack->prev_pipe, STDIN_FILENO);
	}
	if (i != 1)
	{
		dup2(pack->fd[1], STDOUT_FILENO);
		close(pack->fd[1]);
	}
	if (fd != -1)
	{

		fprintf(stderr, "haja4\n");
		close(fd);
	}
}

void	copy_path(t_pack *pack, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], "PATH=", 5))
		{
			pack->path = ft_split(env[i] + 5, ':');
			if (!pack->path)
            {
				free(pack->path);
                exit(1);
            }
		}
		i++;
	}
}

char *verif_path(t_pack *pack, char **line_cmd)
{
    int i;
    char *tmp;
    char *ret;

    i = 0;
    while(pack->path[i])
    {
        tmp = ft_strjoin(pack->path[i], "/");
        ret = ft_strjoin(tmp, line_cmd[0]);
        if (access(ret, F_OK | X_OK))
		{
			fprintf(stderr, "ret >> %s\n", ret);
            return(free(tmp), ret);
		}
        free(tmp);
        free(ret);
        i++;
    }
    return (NULL);
}

void	creat_nino(t_pack *pack, int i, char **env, char *cmd)
{
	redirect(pack, i);
	pack->line_cmd = ft_split(cmd, ' ');
	if (!strrchr(cmd, '/'))
	{
		copy_path(pack, env);
        pack->cmd = verif_path(&*pack, pack->line_cmd);
	}
    else
        pack->cmd = strdup(pack->line_cmd[0]);
    if (pack->cmd)
	{
		printf("haja2\n");
        execve(pack->cmd, pack->line_cmd, env);
	}
	exit(1);
}

void creat_parent(t_pack *pack)
{
	close_fd(&pack->fd[1]);
	if (pack->prev_pipe != -1)
		close_fd(&pack->prev_pipe);
	pack->prev_pipe = pack->fd[0];
}

int	main(int ac, char **av, char **env)
{
	t_pack pack;

	int i;

	i = 0;
	(void)ac;
	if (ac != 5)
		return (write(1, "Pas le bon nombre d'arguments\n", 30), 1);
	init_value(av, &pack);
	while (i < 2)
	{
		if (i != 1)
			pipe(pack.fd);
		pack.pid[i] = fork();
		if (pack.pid[i] == -1)
			exit(1);
		if (pack.pid[i] == 0)
			creat_nino(&pack, i, env, av[i + 2]);
		else
			creat_parent(&pack);
		i++;
	}
	i = 0;
	while (i < 2)
		waitpid(pack.pid[i++], &pack.status, 0);
	return (free(pack.pid), pack.status);
}