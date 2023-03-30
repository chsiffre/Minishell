/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:09:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/29 18:19:18 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../libft/get_next_line_bonus.h"

typedef struct s_env {
	char			*name;
	char			*value;
	int				equal;
	struct s_env	*next;
}	t_env;

typedef struct s_data {
	char	*line;
	char	**env_path;
	char	*path;
	char	**split_path;
	char	**cmd;
	t_env	*env;
}	t_data;

int		ft_parsing(int ac, char **av);
void	ft_get_env(t_data *prompt);
char	*ft_try_path(t_data *data, char *line, char *cmd);
int		ft_exec(t_data *prompt, char **cmd);
char	**ft_parse(char *line);
void	ft_prompt(t_data *data);
char	*ft_builtins(t_data *data);

#endif