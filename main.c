#include "pipex.h"

void init_value(int ac, char **av, t_pack *pack)
{
    memset(pack, 0, sizeof(t_pack));
    pack->prev_pipe = -1;
    pack->infile = av[1];
    pack->outfile = av[4];
    pack->nb_cmd = 2;
    pack->pid = malloc(sizeof(int) * 2);
}

void redirect (t_pack *pack, int i)
{
    int fd;

    if (i == 0)
    {
        fd = open(pack->infile, O_RDONLY);
        dup2(fd, STDIN_FILENO);
    }
    if (i == 1)
    {
        fd = open(pack->outfile, O_CREAT | O_TRUNC |O_WRONLY | 0666);
        dup2(fd, STDOUT_FILENO);
    }
    if (i == 1)
    {
        dup2(pack->prev_pipe, STDIN_FILENO);
    }
    if (i == 0)
    {
        dup2(pack->fd[2], STDOUT_FILENO);
    }
}

void copy_path(t_pack *pack, char **env)
{
    
}

void  creat_nino(t_pack *pack, int i, char **env, char *cmd)
{
    redirect(&*pack, i);
    pack->line_cmd = ft_split(cmd, ' ');
    if (!strrchr(cmd, '/'))
    {
        copy_path(&*pack, env);

    }
}

int	main(int ac, char **av, char **env)
{
    t_pack pack;

    int i;

    i = 0;
    if (ac != 5)
        return (write(1, "Pas le bon nombre d'arguments\n", 30), 1);
    init_value(ac, av, &pack);
    while(i < 2)
    {
        if (i != 1)
            pipe(pack.fd);
        pack.pid[i] = fork();
        if (pack.pid[0] == -1)
            exit(1);
        if (pack.pid[0] == 0)
            creat_nino(&pack, i, env, av[i + 2]);
        i++;
    }
}