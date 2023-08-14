#include <expansion.h>
#include <parsing.h>

int	check_for_wildcard(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == -1)
			return (1);
		i++;
	}
	return (0);
}

int	unclosed_quote(int state)
{
	write(2, "Warning: unclosed quote ( ", 26);
	write(2, &state, 1);
	write(2, " ) was ignored\n", 16);
	return (0);
}

int	skip_quoted_state(char *s, int i, int quote)
{
	while (s[i] && s[i] != quote)
		i++;
	if (!s[i])
		return (1);
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

void	initialize_xp(t_exp *xp, char *input, t_env *head)
{
	xp->star = 0;
	xp->head = head;
	xp->result = NULL;
}
