#include "../../../includes/minishell.h"


long double	ft_atold(const char *str)
{
	long double	result;
	int	i;
	int	sign;
	int	check;

	i = 0;
	result = 0;
	sign = 1;
	check = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - 48);
		check++;
	}
	return (result * sign);
}


int is_valid_exit(char *arg)
{
	int i;
	long double re;

	i = 0;
	if(arg[i] == '-' || arg[i] == '+')
		i++;
	if(!arg[i]) // in case we have just + or -
		return(-1);
	while (arg[i])
	{
		if((arg[i] < '0' || arg[i] > '9'))
			return(-1);
		i++;
	}
	re = ft_atold(arg); // to check overflow
	if(re < LLONG_MIN ||  re > LLONG_MAX)
		return(-1);
	return(0);
}


void ft_exit(char **args)
{
	int i;

	i = 0;
	while (args[i]) //count args
		i++;
	if(i == 1) // if just exit
	{
		ft_putstr_fd("exit\n", 2);
		exit(G_EXIT_STATUS);
	}
	else if(is_valid_exit(args[1]) == -1 )// if not numeric or exceed range  
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	else if(i > 2) // if many args
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		G_EXIT_STATUS = 1;
		return;
	}
	else // exit with the valid number
	{
		ft_putstr_fd("exit\n", 2);
		G_EXIT_STATUS = ft_atoi(args[1]);
		exit(G_EXIT_STATUS % 256); // to make sur exit correctly
	}
}



/*
exit N (with number):

Exits with the specified exit code N
Numbers are taken modulo 256 (so exit 300 becomes exit 44)
Negative numbers wrap around (exit -1 becomes exit 255)
*/


// to handle 
/* 
if out of rang (llong int) error -> exit(2)
exit 9223 3720 3685 4775 808 -> should give exit 9223372036854775808
exit -9223372036854775808 -> should exit(0)
--------------
ls | exit 1212 -> should not print exit in terminal
exit | ls --> same thing 


*/

