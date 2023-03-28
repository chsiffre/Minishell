/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:09:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/28 15:33:51 by luhumber         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>


typedef struct s_data {
	char	*line;
	char	**env_path;
	char	*path;
	char	**split_path;
	char	**cmd;
}	t_data;

int		ft_parsing(int ac, char **av);
void	ft_get_env(t_data *prompt);
char	*ft_try_path(t_data *data, char *line, char *cmd);
int		ft_exec(t_data *prompt, char **cmd);
char	**ft_parse(char *line);

#endif