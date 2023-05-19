#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pack
{
    char *infile;
    char *outfile;
    int prev_pipe;
    int nb_cmd;
    int *pid;
    int fd[2];

} t_pack;

#endif