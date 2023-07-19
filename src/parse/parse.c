
#include <minishell.h>

void	parse_input(char **input, t_ally *all)
{
	if (set_tokens(*input, &all->data))
		return ;
	check_syntax(all->data, input);
	parse(*input, &all->data); // fix leaks !! fic CMD!
	//print_test(*data, input);
	//print_tokens(*data, input);
	print_whole_list(all->data, *input);
}
