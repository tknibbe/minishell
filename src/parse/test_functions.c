
#include <minishell.h>

void	print_class(int	num)
{
	//norm error not to forget to remove
	if (num == SQUOTE)
		printf("single quote: ");
	else if (num == DQUOTE)
		printf("double quote: ");
	else if (num == DOLLO)
		printf("Dollarsign  : ");
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
	else if (num == EXEC)
		printf("executable  : ");
	else if (num == OPTION)
		printf("option      : ");
	else if (num == INPUT)
		printf("input       : ");
	else if (num == EQUALS)
		printf("equals      : ");
	else if (num == VARIABLE)
		printf("variable    : ");
	else if (num == STRING)
		printf("string      : ");
	else if (num == SEMICOLON)
		printf("semicolom   : ");
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
