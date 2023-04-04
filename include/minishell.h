/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:09:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/04 17:07:21 by chsiffre         ###   ########.fr       */
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

typedef struct s_lst {
	char			**content;
	struct s_lst	*next;
	int				type;
}	t_lst;

typedef struct s_data {
	t_lst	*lst;
	char	*line;
	char	**env_path;
	char	*path;
	char	**split_path;
	char	**cmd;
	char	**result;
	t_env	*env;
}	t_data;



//***********parsing***************//
void	ft_parse(t_data *data);
t_lst	*ft_lstnew_t(char **strs, int type, size_t i);
t_lst	*ft_last(t_lst *lst);
void	ft_add_lst(t_data *data, char **strs, int type, size_t i);
ssize_t ft_check_redir(t_data *data, char **strs, ssize_t i);
void	ft_check_cmd(t_data *data, ssize_t i);
ssize_t    ft_check_builtins(t_data *data, ssize_t i);
void	ft_add_back(t_lst **lst, t_lst *new);
int		ft_is_builtins(char *str);
void	ft_init_data(t_data *data, char **envp);
t_env	*ft_envlast(t_env *lst);
void	ft_envadd_back(t_env **env, t_env *new);
int		ft_has_equal(char *str);
t_env	*ft_new_env(char *str);
void	ft_get_env(t_data *prompt);
char	*ft_try_path(t_data *data, char *line, char *cmd);
int		ft_exec(t_data *prompt, char **cmd);
void	ft_prompt(t_data *data);
char	*ft_builtins(t_data *data);
void	ft_conv_lst(char *line);
t_data	ft_init_struct(t_data data);

void	ft_struct_env(t_data *data);
void	ft_unset(t_data *data, char *name);
void	ft_export(t_data *data, char *name);

#endif