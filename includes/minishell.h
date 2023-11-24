/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:48:45 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/22 15:57:40 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <termios.h>
# include <string.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>

# include "libft.h"
# include "structs.h"
# include "expansion.h"
# include "built_ins.h"
# include "parsing.h"
# include "exec.h"
# include "utils.h"

# define SET 0
# define GET 1

# define PROMPT "ez_game -> "

/*
	hey crissie baby <3
	hey tymoo daddy 8=D
	hey crissie deel 2 80085
	hey tymoo bicep baby muscle mommy
	heck yeah muscle mommy <3333
*/

#endif
