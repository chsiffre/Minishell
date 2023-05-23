/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:12:25 by lucas             #+#    #+#             */
/*   Updated: 2023/05/23 13:42:58 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec(t_data *prompt, char **cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error(prompt, "fork error\n", 1);
	else if (pid == 0)
	{
		if (execve(cmd[0], cmd, prompt->env_path) == -1)
			ft_error(prompt, "execve error\n", 1);
	}
	if (waitpid(pid, NULL, 0) == -1)
		ft_error(prompt, "waitpid error\n", 1);
	return (0);
}

char	*ft_try_path(t_data *data, char *cmd)
{
	int		i;
	char	*tmp;
	char	*tab;

	i = 0;
	if (access(cmd, X_OK) != -1)
		return (cmd);
	tmp = ft_strjoin("/", cmd);
	while (data->split_path[i])
	{
		tab = ft_strjoin(data->split_path[i], tmp);
		if (access(tab, F_OK) != -1)
			break ;
		free(tab);
		tab = NULL;
		i++;
	}
	free(tmp);
	if (!tab)
		return (ft_cmd_error(data->lst->content[0]), NULL);
	return (tab);
}

char	**ft_cmd_options(t_data *data, char **cmd, char *content)
{
	int	i;

	cmd[0] = ft_try_path(data, content);
	i = 1;
	while (data->lst->content[i])
	{
		cmd[i] = ft_strdup(data->lst->content[i]);
		i++;
	}
	cmd[i] = 0;
	return (cmd);
}

int	ft_execute_cmd(t_data *data, char *content)
{
	char	**cmd;
	int		i;

	signal(SIGINT, ft_ctrl_fork);
	signal(SIGTERM, ft_ctrl_fork);
	signal(SIGQUIT, ft_ctrl_fork);
	i = ft_builtins(data);
	if (i == -1 || i == 1)
		return (1);
	i = 0;
	if (ft_special_char(data->lst->content[0]) == 1)
		return (1);
	while (data->lst->content[i])
		i++;
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		ft_error(data, "malloc error\n", 1);
	cmd = ft_cmd_options(data, cmd, content);
	if (cmd[0] != NULL && ft_exec(data, cmd) == 1)
		return (1);
	return (0);
}

int	ft_make_dup(t_data *data)
{
	if (data->in_redir == -1 || data->out_redir == -1)
		ft_error(data, "dup error\n", 1);
	if (data->in_redir && dup2(data->in_redir, STDIN_FILENO) == -1)
		ft_error(data, "dup error\n", 1);
	if (data->out_redir && dup2(data->out_redir, STDOUT_FILENO) == -1)
		ft_error(data, "dup error\n", 1);
	return (0);
}

int	ft_check_type(t_data *data)
{
	t_lst	*tmp;

	tmp = data->lst;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (ft_pipe(data) == 1)
				return (1);
			return (0);
		}
		tmp = tmp->next;
	}
	if (data->lst->type == REDIR)
	{
		if (ft_which_redir(data) == 1)
			return (1);
		return (0);
	}
	else if (data->lst->type == CMD && !data->lst->next)
	{
		ft_make_dup(data);
		if (ft_execute_cmd(data, data->lst->content[0]) == 1)
			return (1);
		return (0);
	}
	else
		return (ft_error(data, "Unexepted command\n", 1), 2);
}
