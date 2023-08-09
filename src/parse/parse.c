
#include <minishell.h>

void	free_list_struct(t_list *list);
void	free_cmd(t_char *cmd);
void	free_rdr(t_rdr	*rdr);

void	parse_input(char **input, t_ally *all)
{
	tokenize(*input, all->list);
	check_syntax(all->list, input);
	parse(*input, all->list);
	//print_test(*list, input);
	//print_tokens(all->list, *input);
	//print_whole_list(all->list, *input);
	//free_list_struct(all->list);
}

void	free_list_struct(t_list *list)
{
	t_exec	*exec;
	t_exec	*temp;
	t_list	*templist;

	templist = list;
	while (templist)
	{
		free (list->token);
		//free (list->input); //TODO when its malloced by cris func
		exec = list->exec;
		//printf("exec = %p\n", exec);
		while (exec)
		{
			free_cmd(exec->cmd);
			free_rdr(exec->rdr);
			temp = exec;
			exec = exec->next;
			//printf("temp = %p, exec = %p\n", temp, exec);
			free(temp);
		}
		templist = templist->next;
	}
	list->next = NULL;
	list->exec = NULL;
}

void	free_rdr(t_rdr *rdr)
{
	t_rdr	*temp;

	if (!rdr)
		return ;
	while (rdr)
	{
		temp = rdr;
		rdr = rdr->next;
		free(temp->file);
		free(temp);
	}
}

void	free_cmd(t_char *cmd)
{
	t_char	*temp;

	if (!cmd)
		return ;
	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		free (temp->s);
		free(temp);
	}
}
