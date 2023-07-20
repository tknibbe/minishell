
#include <minishell.h>

void	parse_input(char **input, t_ally *all)
{
	tokenize(*input, &all->data);
	check_syntax(all->data, input);
	parse(*input, &all->data);
	//print_test(*data, input);
	//print_tokens(all->data, *input);
	print_whole_list(all->data, *input);
}
