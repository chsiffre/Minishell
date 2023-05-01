/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:24:22 by luhumber          #+#    #+#             */
/*   Updated: 2023/05/01 16:36:24 by lucas            ###   ########.fr       */
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

int	ft_prepare_pipe(t_data *data, char *content)
{
	char	**cmd;
	int		i;

	if (ft_builtins(data) == 1)
		return (1);
	i = 0;
	while (data->lst->content[i])
		i++;
	cmd = malloc(sizeof(char *) * i);
	cmd = ft_cmd_options(data, cmd, content);
	if (execve(cmd[0], cmd, data->env_path) == -1)
		return (ft_printf("error execve\n"), 1);
	return (0);
}

int	ft_exec_pipe(t_data *data)
{
	dup2(data->pipex->file_in, STDIN_FILENO);
	dup2(data->pipex->file_out, STDOUT_FILENO);
	if (ft_prepare_pipe(data, data->lst->content[0]) == 1)
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

int	ft_pipe(t_data *data)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 0;
	data->pipex->tab_pid = ft_calloc(ft_lstlen(data->lst), sizeof(int));
	data->pipex->file_in = STDIN_FILENO;
	while (data->lst)
	{
		if (pipe(fd) == -1)
			return (1);
		pid = fork();
		data->pipex->file_out = fd[1];
		data->pipex->file_in = fd[0];
		if (!data->lst->next)
			data->pipex->file_out = STDOUT_FILENO;
		if (pid == -1)
			return (1);
		else if (pid == 0)
			ft_exec_pipe(data);
		data->lst = data->lst->next;
		if (data->lst && data->lst->type == PIPE)
			data->lst = data->lst->next;
		if (data->lst && data->lst->type == REDIR)
		{
			ft_redirection(data);
			data->lst = data->lst->next;
		}
		data->pipex->tab_pid[i] = pid;
		i++;
		close(data->pipex->file_in);
		data->pipex->file_in = data->pipex->file_out;
	}
	dup2(STDOUT_FILENO, data->pipex->file_out);
	ft_end(data);
	return (0);
}
