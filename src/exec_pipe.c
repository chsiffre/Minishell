/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:24:22 by luhumber          #+#    #+#             */
/*   Updated: 2023/04/25 11:47:53 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_end(t_data *data)
{
	int	i;

	i = 0;
	while (data->pipex->tab_pid[i])
		i++;
	while (i--)
		waitpid(data->pipex->tab_pid[i], NULL, 0);
	free(data->pipex->tab_pid);
	return (0);
}

int	ft_prepare_pipe(t_data *data, t_lst *tmp, char *content)
{
	char	**cmd;
	int		i;

	if (ft_builtins(data) == 1)
		return (1);
	i = 0;
	while (tmp->content[i])
		i++;
	cmd = malloc(sizeof(char *) * i);
	cmd = ft_cmd_options(data, tmp, cmd, content);
	if (execve(cmd[0], cmd, data->env_path) == -1)
		return (ft_printf("error execve\n"), 1);
	return (0);
}

int	ft_exec_pipe(t_data *data, t_lst *tmp)
{
	dup2(data->pipex->file_in, STDIN_FILENO);
	dup2(data->pipex->file_out, STDOUT_FILENO);
	if (ft_prepare_pipe(data, tmp, tmp->content[0]) == 1)
		exit (1);
	return (0);
}

int	ft_lstlen(t_lst *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

int	ft_pipe(t_data *data, t_lst *tmp)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 0;
	data->pipex->tab_pid = ft_calloc(ft_lstlen(tmp), sizeof(int));
	data->pipex->file_in = STDIN_FILENO;
	while (tmp)
	{
		if (pipe(fd) == -1)
			return (1);
		pid = fork();
		data->pipex->file_out = fd[0];
		if (!tmp->next)
			data->pipex->file_out = STDOUT_FILENO;
		if (pid == -1)
			return (1);
		else if (pid == 0)
			ft_exec_pipe(data, tmp);
		tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == REDIR)
		{
			ft_redirection(data, tmp);
			tmp = tmp->next;
		}
		data->pipex->tab_pid[i] = pid;
		i++;
		close(data->pipex->file_in);
		data->pipex->file_in = data->pipex->file_out;
	}
	ft_end(data);
	return (0);
}
