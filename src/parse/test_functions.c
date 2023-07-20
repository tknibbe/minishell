
#include <minishell.h>


void print_whole_list(t_data *data, char *input)
{
	int	i = 0;
	int	node_amnt = 0;
	while (data->list)
	{
		t_exec *list =  data->list;
		t_rdr	*rdr = data->list->rdr;
		printf("\nnode %d\n", node_amnt);
		printf("[\n");
		printf("CMD: ");
		while (list->cmd[i])
		{
			printf("%s, ", list->cmd[i]);
			i++;
		}
		i = 0;
		printf("\n");
		printf("RDR: ");
		while (rdr)
		{
			printf("{%s} [%d], ", rdr->file, rdr->type);
			rdr = rdr->next;
		}
		node_amnt++;
		printf("\n]\n\n");
		data->list = data->list->next;
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

void print_test(t_data *data, char *input)
{
	int	i = 0; //remove func later
	int	num;

	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		num = data->token[i];
		print_class(data->token[i]);
		while (data->token[i] == num && input[i])
		{
			printf("%c", input[i]);
			i++;
		}
		printf("\n");
	}
}

void	print_tokens(t_data *data, char *input)
{
	int i = 0;
	while (i < ft_strlen(input))
	{
		printf("[%d]", data->token[i]);
		i++;
	}
	printf("\n");
}
