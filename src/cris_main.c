#include <minishell.h>
#include <built_ins.h>
#include <exec.h>

void	leaks(void)
{
	system("leaks -q minishell");
}


t_ally	*minishell_init(char *envp[])
{
	t_ally	*all;

/*	create everything that needs to be initialized here and store it in all	*/

	all = malloc(sizeof(t_ally));
	if (!all)
		ft_exit("Malloc error\n", errno);
	all->list = malloc(sizeof(t_list));
	if (!all->list)
		ft_exit("Malloc error\n", errno);
	all->list->next = NULL;
	all->list->exit_code = 0;
	all->list->exec = NULL;
	all->env = env_init(envp);
	return (all);
}

void	tymon(t_ally *all, char *input)
{

	//pre_parse(input, all);
	all->list = parse_input(input);
	print_whole_list(all->list);
	//printf("pipeline exited with code : %d\n", all->list->exit_code);
	//free (*input);
	//leaks();
}

void	cris(t_ally *all, char *input)
{
	// if (!ft_strncmp(input, "> ", 2))
	// 	test_env_expansion_shit(all, &input[2]);
	if (!ft_strncmp(input, "echo ", 5))
		echo(ft_split(input, ' '));
	if (!ft_strncmp(input, "env", 4))
		env(all->env->head);
	if (!ft_strncmp(input, "unset ", 6))
		unset(all->env, ft_split(input, ' '));
	if (!ft_strncmp(input, "export ", 6))
		export(all->env, ft_split(input, ' '));
	// if (!ft_strncmp(input, "pwd", 4))
	// 	pwd();
	// if (!ft_strncmp(input, "cd ", 3))
	// 	cd(&input[3], all->env->head);
}

int	run_shell(t_ally *all, char *prompt)
{
	char	*string;

	//set_signals_inter();
	string = readline(prompt);
	//set_signals_non_inter();
	if (!string)
		exit(0);
	if (!strncmp(string, "", 1))
	{
		free(string);
		return (1);
	}
	add_history(string);
	if (ft_strncmp(string, "exit", 4) == 0)
		exit(0);
	tymon(all, string);
	//cris(all, string);
	return (0);
	//exit(0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_ally	*all;

	if (argc != 1)
		ft_exit("just ./minishell is enough\n", 1);
	all = minishell_init(envp);
	while (1)
		run_shell(all, PROMPT);
	//free(prompt);
}
