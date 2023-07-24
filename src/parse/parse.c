
#include <minishell.h>

void	parse_input(char **input, t_ally *all)
{
	tokenize(*input, &all->list);
	check_syntax(all->list, input);
	parse(*input, all->list);
	//print_test(*list, input);
	//print_tokens(all->list, *input);
	// print_whole_list(all->list, *input);
}
