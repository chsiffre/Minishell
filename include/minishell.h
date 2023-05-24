/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:09:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/24 16:33:25 by luhumber         ###   ########.fr       */
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
# include <string.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../libft/get_next_line_bonus.h"

extern int	g_error_last;

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
	int	prev_fd;
	int	*tab_fd;
	int	*tab_pid;
}	t_pipe;

typedef struct s_data {
	t_lst	*lst;
	char	**fake_envp;
	char	*line;
	char	**env_path;
	char	*path;
	char	**split_path;
	char	**cmd;
	int		savestdin;
	int		savestdout;
	char	**res_split;
	char	**res_parse;
	ssize_t	i;
	ssize_t	y;
	t_env	*env;
	int		signal;
	int		fd;
	char	*limiter;
	t_pipe	*pipex;
	int		is_redir;
	int		in_redir;
	int		out_redir;
}	t_data;

//***********prompt***************//
int		ft_compare_str(char *s1, char *s2);

//***********parsing***************//
t_lst	*ft_parse(t_data *data);
char	*ft_pre_split(char *str);
char	*ft_str_replace(char *str, char *copy, int new_size);
int		ft_is_redir(char *str);
t_lst	*ft_lstnew_t(char **strs, int type, ssize_t i, int size);
t_lst	*ft_convert_in_lst(t_lst *lst, t_data *data);
int		ft_len_parse(char **strs, int i);
int		ft_is_redir(char *str);
t_lst	*ft_last(t_lst *lst);
t_lst	*ft_add_lst(t_lst *lst, t_data *data, int type, int size);
char	**ft_check_redir(char **res_parse,
t_data *data, char **strs, int start);
ssize_t	ft_strs_len(char **strs);
char	**ft_check_cmd(char **res_parse, t_data *d, char **strs, int start);
t_lst	*ft_check_builtins(t_lst *lst, t_data *data, ssize_t i);
void	ft_add_back(t_lst **lst, t_lst *new);
char	*copy_str(int *index, char *str, int len, char *ret);

char	*is_quote(char *str);
int		ft_nb_quote(char *str);
char	*del_quote(char *str, char *ret, int i, char c);
void	ft_free(t_data *data);
int check_pipe(char *str);
//***********builtins***************//
int		ft_is_builtins(char *str);
void	ft_echo(t_data *data);
int		ft_unset(t_data *data);
int		ft_export(t_data *data);
void	ft_cd(t_data *data);

//***********t_env***************//
void	ft_struct_env(t_data *data);
int		ft_has_equal(char *str);
void	ft_add_var(t_data *data, char *str, int exist);
char	*ft_switch_value(char *val, char *str);
t_env	*ft_envlast(t_env *lst);
t_env	*ft_new_env(char *str);
void	ft_envadd_back(t_env **env, t_env *new);
int		ft_has_equal(char *str);
int		ft_check_exist(t_data *data, t_env *env, char *str);

//***********prompt***************//
void	ft_ctrl(int signal);
void	ft_ctrl_fork(int signal);
void	ft_init_data(t_data *data, char **envp);
t_data	ft_init_struct(t_data data);
int		ft_builtins(t_data *data);
char	*ft_try_path(t_data *data, char *cmd);
void	ft_prompt(t_data *data);
int		ft_exec(t_data *prompt, char **cmd);
void	ft_conv_lst(char *line);

//***********exec***************//
int		ft_check_type(t_data *data);
int		ft_which_redir(t_data *data);
int		ft_make_dup(t_data *data);
int		ft_pipe(t_data *data);
int		ft_execute_cmd(t_data *data, char *content);
char	**ft_cmd_options(t_data *data, char **cmd, char *content);

//***********error***************//
void	ft_to_free(t_data *data);
int		ft_print_error(char	*str);
int		ft_cmd_error(char	*str);
void	ft_error(t_data *data, char *str, int exit_code);
int		ft_free_for_end(t_data *data);
int		ft_special_char(char *cmd);

#endif