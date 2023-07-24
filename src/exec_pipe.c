/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:24:22 by luhumber          #+#    #+#             */
/*   Updated: 2023/07/24 10:08:35 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_dup_built(t_data *data)
{
	int	i;

	if (ft_make_dup(data) == 1)
		exit (1);
	ft_dup_pipe(data);
	i = ft_builtins(data);
	if (i == -1 || i == 1)
		return (1);
	return (0);
}

int	ft_exec_pipe(t_data *data, int fd[2])
{
	char	**cmd;
	int		i;

	close(fd[0]);
	i = 0;
	while (data->iterator->content[i])
		i++;
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		ft_error(data, "malloc error\n", 1, 1);
	cmd = ft_cmd_options(data, cmd, data->iterator->content[0]);
	if ((cmd[0] != NULL) && (is_executable(cmd[0]) == 0))
	{
		if (ft_dup_built(data) == 1)
			exit (0);
		if (execve(cmd[0], cmd, data->env_path) == -1)
			ft_error(data, "execve error\n", 1, 1);
		g_error_last = 0;
	}
	else
	{
		free_cmd(cmd);
		close(fd[1]);
		data->pipex->error = 1;
		g_error_last = 127;
		free(data->pipex->tab_pid);
		free(data->pipex->tab_fd);
		ft_to_free(data);
		free_data(data);
		ft_free_for_end(data);
		exit (1);
	}
	free_cmd(cmd);
	return (0);
}

int	ft_loop_pipe(t_data *data)
{
	int		fd[2];
	pid_t	pid;

	while (data->iterator)
	{
		data->pipex->error = 0;
		if (pipe(fd) == -1)
			ft_error(data, "pipe error\n", 1, 1);
		data->pipex->file_out = fd[1];
		if (!data->iterator->next)
		{
			close(fd[0]);
			data->pipex->file_out = STDOUT_FILENO;
		}
		pid = fork();
		if (pid == -1)
			ft_error(data, "fork error\n", 1, 1);
		else if (pid == 0)
			ft_exec_pipe(data, fd);
		ft_restore_loop(data, pid, fd, data->pipex->count);
		if (data->pipex->error == 0)
			data->pipex->count++;
		data->iterator = data->iterator->next;
		list_progress(data);
	}
	return (0);
}

int	ft_pipe(t_data *data)
{
	data->pipex->tab_pid = ft_calloc(ft_lstlen(data->iterator), sizeof(int));
	if (data->pipex->tab_pid == NULL)
		ft_error(data, "malloc error\n", 1, 1);
	data->pipex->tab_fd = ft_calloc(ft_lstlen(data->iterator), sizeof(int));
	if (data->pipex->tab_fd == NULL)
		ft_error(data, "malloc error\n", 1, 1);
	data->pipex->prev_fd = 0;
	data->pipex->count = 0;
	data->pipex->error = 0;
	check_signal(data);
	list_progress(data);
	g_error_last = 0;
	ft_loop_pipe(data);
	ft_end(data);
	return (0);
}
