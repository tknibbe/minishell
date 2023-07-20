# include <expansion.h>
#include <sys/errno.h>
#include <minishell.h>

int	check_for_first_matching_string(char **file, char **input, int w_card)
{
	int	i;

	while (*(*file))
	{
		i = 0;
		if (w_card)
			while (*(*file) && *(*file) != *(*input))
				(*file)++;
		while ((*file)[i] && (*file)[i] == (*input)[i])
			i++;
		if ((*input)[i] == '*' || (!(*file)[i] && !(*input)[i]))
		{
			*input += i;
			*file += i;
			return (1);
		}
		if (!((*file)[i]) || !w_card)
			break ;
		*file += i;
	}
	return (0);
}

int	pattern_match(char *f, char *input)
{
	int	w_mode;

	while (*f)
	{
		w_mode = 0;
		if (*input == '*')
		{
			input++;
			w_mode = 1;
		}
		if (!check_for_first_matching_string(&f, &input, w_mode))
			return (0);
	}
	return (1);
}

void	expand_wildcard(char **result, int count)
{
	DIR				*dir_p;
	struct dirent	*dir_info;

	dir_p = opendir(".");
	if (dir_p < 0)
		ft_exit("opendir()\n", errno);
	while (1)
	{
		dir_info = readdir(dir_p);
		if (!dir_info)
			break ;
		if (pattern_match(dir_info->d_name, *result))
			printf("%s ", dir_info->d_name);
	}
	closedir(dir_p);
}
