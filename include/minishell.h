/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:09:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/13 17:02:11 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PATH_MAX 256

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
	char	**res_split;
	char	**res_parse;
	ssize_t	i;
	ssize_t	y;
	t_env	*env;
	int		signal;
	int		fd;
}	t_data;

//***********prompt***************//
int		ft_compare_str(char *s1, char *s2);

//***********parsing***************//
t_lst	*ft_parse(t_data *data);
char *ft_pre_split(char *str);
char *ft_str_replace(char *str, char *copy, int new_size);
int		ft_is_redir(char *str);
t_lst	*ft_lstnew_t(char **strs, int type, ssize_t i, int size);
t_lst	*ft_convert_in_lst(t_lst *lst, t_data *data);
int	ft_len_parse(char **strs, int i);
int ft_is_redir(char *str);
t_lst	*ft_last(t_lst *lst);
t_lst	*ft_add_lst(t_lst *lst,t_data *data, int type, int size);
char **ft_check_redir(char **res_parse, t_data *data, char **strs, int start);
ssize_t	ft_strs_len(char **strs);
char **ft_check_cmd(char **res_parse, t_data *d, char **strs, int start);
t_lst	*ft_check_builtins(t_lst *lst, t_data *data, ssize_t i);
void	ft_add_back(t_lst **lst, t_lst *new);
int		ft_is_builtins(char *str);
void    ft_free(t_data *data);
//***********builtins***************//
void	ft_echo(t_data *data);

//***********t_env***************//
void	ft_struct_env(t_data *data);
int		ft_has_equal(char *str);
void	ft_add_var(t_data *data, char *str, int exist);
t_env	*ft_envlast(t_env *lst);
t_env	*ft_new_env(char *str);
void	ft_envadd_back(t_env **env, t_env *new);
int		ft_unset(t_data *data, char *name);
void	ft_export(t_data *data, char *name);

//***********prompt***************//
void	ft_init_data(t_data *data, char **envp);
t_data	ft_init_struct(t_data data);
int		ft_builtins(t_data *data);
char	*ft_try_path(t_data *data, char *line, char *cmd);
void	ft_prompt(t_data *data);
int		ft_exec(t_data *prompt, char **cmd);
void	ft_conv_lst(char *line);

void	ft_check_type(t_data *data);

#endif