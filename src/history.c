#include <minishell.h>

int	history_management(const char *s)
{
	if (ft_strncmp(s, "", 1) > 0)
	{
		add_history(s);
		printf("--> %s: added to history\n", s);
	}
	else
		printf("not added\n");
	return (0);
}