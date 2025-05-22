#include "../../includes/minishell.h"


int	heredoce(char *limiter)
{
	char *line;
	int fds[2]; // array of two elements 

	pipe(fds);
	while (1)
	{
		line = readline("> ");
		//printf("%s\n", line);
		if(!line || ft_strcmp(line, limiter) == 0) // if null(read line detect the end of file ) or limiter
			break;
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	//free(line);
	close(fds[1]); // close the write end

	return(fds[0]); // return the read end
}

