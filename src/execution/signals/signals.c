#include "../../../includes/minishell.h"


void set_signals_dfl()
{
	signal(SIGINT, SIG_DFL);       // default ctrl+c kills it
	signal(SIGQUIT, SIG_DFL);
}

