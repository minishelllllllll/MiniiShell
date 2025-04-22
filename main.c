#include "includes/minishell.h"
#include "../libft/libft.h"

int main()
{
	char *str;

	str = "hello world !";
	printf("%ld", ft_strlen(str));
}