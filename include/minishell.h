/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:09:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/27 14:30:10 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../libft/get_next_line_bonus.h"
# include "../libft/ft_printf.h"


typedef struct s_prompt {
	char	*line;
	char	**env_path;
	char	*path;
	char	**split_path;
}	t_prompt;

int	ft_parsing(int ac, char **av);
void	ft_get_env(t_prompt *prompt);
char	*ft_try_path(t_prompt *prompt, char *line);
int	ft_exec(t_prompt *prompt, char *line);

#endif