
#include <minishell.h>

 void print_whole_list(t_list *list, char *input)
 {
 	int	node_amnt = 0;
 	while (list->exec)
 	{
 		t_exec	*exec =  list->exec;
 		t_rdr	*rdr = list->exec->rdr;
		t_char	*cmd = list->exec->cmd;
 		printf("\nnode %d\n", node_amnt);
 		printf("[\n");
 		printf("CMD: ");
 		while (cmd)
 		{
 			printf("%s, ", cmd->s);
 			cmd = cmd->next;
 		}
 		printf("\n");
 		printf("RDR: ");
 		while (rdr)
 		{
 			printf("{%s} [%d], ", rdr->file, rdr->type);
 			rdr = rdr->next;
 		}
 		node_amnt++;
 		printf("\n]\n\n");
 		list->exec = list->exec->next;
 	}
 }

void	print_class(int	num)
{
	//norm error not to forget to remove
	if (num == WORD)
		printf("word        : ");
	else if (num == REDIRLEFT)
		printf("redir left  : ");
	else if (num == REDIRRIGHT)
		printf("redirright  : ");
	else if (num == APPLEFT)
		printf("append left : ");
	else if (num == APPRIGHT)
		printf("append right: ");
	else if (num == PIPESYMBOL)
		printf("pipe        : ");
	else
		printf("BLANK %d: ", num);
}

void print_test(t_list *list, char *input)
{
	int	i = 0; //remove func later
	int	num;

	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		num = list->token[i];
		print_class(list->token[i]);
		while (list->token[i] == num && input[i])
		{
			printf("%c", input[i]);
			i++;
		}
		printf("\n");
	}
}

void	print_tokens(t_list *list, char *input)
{
	int i = 0;
	while (i < ft_strlen(input))
	{
		printf("[%d]", list->token[i]);
		i++;
	}
	printf("\n");
}
