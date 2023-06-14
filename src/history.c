#include <minishell.h>

int	history_management(const char *s)
{
	if (strcmp(s, "") > 0)
	{
		add_history(s);
		printf("--> %s: added to history\n", s);
	}
	else
		printf("not added\n");
	return (0);
}