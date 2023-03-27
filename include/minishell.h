/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:09:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/27 16:46:36 by chsiffre         ###   ########.fr       */
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


typedef struct s_data {
	char	*line;
	char	**env_path;
	char	*path;
	char	**split_path;
}	t_data;

int	ft_parsing(int ac, char **av);
void	ft_get_env(t_data *prompt);
char	*ft_try_path(t_data *prompt, char *line);
int	ft_exec(t_data *prompt, char *line);
int ft_parse(char *line);

#endif