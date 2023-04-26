/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:09:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/25 10:58:01 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PATH_MAX 256
# define REDIR 0
# define CMD 1
# define PIPE 2

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

typedef struct s_pipe {
	int	file_out;
	int	file_in;
	int	*tab_pid;
}	t_pipe;

typedef struct s_data {
	t_lst	*lst;
	char	*line;
	char	**env_path;
	char	*path;
	char	**split_path;
	char	**cmd;
	char	**result;
	ssize_t	i;
	t_env	*env;
	int		signal;
	int		fd;
	char	*limiter;
	t_pipe	*pipex;
}	t_data;

//***********prompt***************//
int		ft_compare_str(char *s1, char *s2);

//***********parsing***************//
void	ft_parse(t_data *data);
t_lst	*ft_lstnew_t(char **strs, int type, ssize_t i);
t_lst	*ft_last(t_lst *lst);
void	ft_add_lst(t_data *data, char **strs, int type, ssize_t i);
void	ft_check_redir(t_data *data, char **strs, ssize_t i);
ssize_t	ft_strs_len(char **strs);
void	ft_check_cmd(t_data *data, ssize_t i);
ssize_t	ft_check_builtins(t_data *data, ssize_t i);
void	ft_add_back(t_lst **lst, t_lst *new);
int		ft_is_builtins(char *str);
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
void	ft_export(t_data *data);
int		ft_has_equal(char *str);

//***********prompt***************//
void	ft_init_data(t_data *data, char **envp);
t_data	ft_init_struct(t_data data);
int		ft_builtins(t_data *data);
char	*ft_try_path(t_data *data, char *line, char *cmd);
void	ft_prompt(t_data *data);
int		ft_exec(t_data *prompt, char **cmd);
void	ft_conv_lst(char *line);

//***********exec***************//
void	ft_check_type(t_data *data, t_lst *tmp);
int		ft_redirection(t_data *data, t_lst *tmp);
int		ft_pipe(t_data *data, t_lst *tmp);
int		ft_execute_cmd(t_data *data, t_lst *tmp, char *content);
char	**ft_cmd_options(t_data *data, t_lst *tmp, char **cmd, char *content);

#endif