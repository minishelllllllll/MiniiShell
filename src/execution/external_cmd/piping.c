#include "../../../includes/minishell.h"

void	error_msg(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	null_error(char *str)
{
	write(2, "error :", 8);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}


void	close_pipes(int nbr_pipes, int **ends)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
	{
		close(ends[i][0]);
		close(ends[i][1]);
		i++;
	}
}

void	waiting_childs(int childs)
{
	int	i;

	i = 0;
	while (i < childs)
	{
		wait(NULL);
		i++;
	}
}

int	**piping(int lines)
{
	int	**pip;
	int	i;

	i = 0;
	pip = (int **)malloc((lines + 1) * sizeof(int *));
	if (!pip)
		return (NULL);
	while (i < lines)
	{
		pip[i] = (int *)malloc(2 * sizeof(int));
		if (!pip[i])
		{
			free_arr_b((void **)pip);
			return (NULL);
		}
		if (pipe(pip[i]) == -1)
		{
			free_arr_b((void **)pip);
			error_msg("error 🥴8");
		}
		i++;
	}
	pip[i] = NULL;
	return (pip);
}