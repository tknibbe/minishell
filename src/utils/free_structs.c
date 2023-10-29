
# include "minishell.h"

void	free_str(t_str *str)
{
	t_str	*to_free;

	while (str)
	{
		to_free = str;
		str = str->next;
		if (to_free->str)
			free(to_free->str);
		free(to_free);
	}
}

void	free_rdr(t_rdr *rdr)
{
	t_rdr	*to_free;

	while (rdr)
	{
		to_free = rdr;
		rdr = rdr->next;
		free_str(to_free->file);
		free(to_free);
	}
}

void	free_exec(t_exec *exec)
{
	t_exec	*to_free;

	while (exec)
	{
		to_free = exec;
		exec = exec->next;
		free_list(to_free->subshell);
		free_str(to_free->cmd);
		free_rdr(to_free->rdr);
		free(to_free);
	}
}

/*Description:
This function frees memory associated with a linked list of tokens and
their related data structures. It iterates through the list and releases
memory for each element, including the input string, token array, and the
exec structure. The function does not return any value.

Parameters:

    t_list *lst: A pointer to the head of a linked list containing tokens
	and related data structures to be freed.*/
void	free_list(t_list *lst)
{
	t_list	*to_free;

	while (lst)
	{
		to_free = lst;
		lst = lst->next;
		free(to_free->input);
		free(to_free->token);
		free_exec(to_free->exec);
		free(to_free);
	}
}
