#include <expansion.h>
#include <parsing.h>

int	check_for_wildcard(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == -1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	unclosed_quote(int state)
{
	write(2, "Warning: unclosed quote ( ", 26);
	write(2, &state, 1);
	write(2, " ) was ignored\n", 16);
	return (EXIT_SUCCESS);
}

int	skip_quoted_state(char *s, int i, int quote)
{
	while (s[i] && s[i] != quote)
		i++;
	if (!s[i])
		return (EXIT_FAILURE);
	return (i + 1);
}

int	amount(t_str *s)
{
	int	count;

	count = 0;
	while (s)
	{
		if (s->str)
			count++;
		s = s->next;
	}
	return (count);
}

void	initialize_xp(t_exp *xp, t_env_info *e)
{
	xp->e = e;
	xp->result = NULL;
}
