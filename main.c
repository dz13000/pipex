#include "pipex.h"

void init_value(int ac, char **av, t_pack *pack)
{
    memset(pack, 0, sizeof(t_pack));
    pack->infile = av[1];
    pack->outfile = av[4];
    pack->nb_cmd = 2;
    pack->pid = malloc(sizeof(int) * 2);
}

int	main(int ac, char **av, char **env)
{
    t_pack pack;

    int i;

    i = 0;
    if (ac != 5)
        return (write(1, "Pas le bon nombre d'arguments\n", 30), 1);
    init_value(ac, av, &pack);
    while(i < pack.nb_cmd)
    {
        if (i != 1)
            pipe(pack.fd);
        pack.pid[i] = fork();
        if (pack.pid[0] == -1)
            exit(1);
        i++;
    }

    if (i == 0)
	{
		fd = open(pack.infile, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close_(&fd);
	}
    printf("%d\n", pack.fd[0]);
    printf("%d\n", pack.fd[1]);
}