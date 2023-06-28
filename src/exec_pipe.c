/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:24:22 by luhumber          #+#    #+#             */
/*   Updated: 2023/06/28 11:23:19 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dup_built(t_data *data)
{
	int	i;

	if (ft_make_dup(data) == 1)
		exit (0);
	ft_dup_pipe(data);
	i = ft_builtins(data);
	if (i == 1 || i == -1)
		exit (0);
}

int	ft_exec_pipe(t_data *data, int fd[2])
{
	char	**cmd;
	int		i;

	close(fd[0]);
	ft_dup_built(data);
	i = 0;
	while (data->lst->content[i])
		i++;
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		ft_error(data, "malloc error\n", 1, 1);
	cmd = ft_cmd_options(data, cmd, data->lst->content[0]);
	if ((cmd[0] == NULL) || (is_executable(cmd[0]) != 0))
	{
		g_error_last = 127;
		exit (127);
	}
	if (execve(cmd[0], cmd, data->env_path) == -1)
		ft_error(data, "execve error\n", 1, 1);
	g_error_last = 0;
	return (0);
}

int	ft_loop_pipe(t_data *data)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 0;
	while (data->lst)
	{
		if (pipe(fd) == -1)
			ft_error(data, "pipe error\n", 1, 1);
		data->pipex->file_out = fd[1];
		if (!data->lst->next)
			data->pipex->file_out = STDOUT_FILENO;
		pid = fork();
		if (pid == -1)
			ft_error(data, "fork error\n", 1, 1);
		else if (pid == 0)
			if (ft_exec_pipe(data, fd) == 1)
				exit (1);
		ft_restore_loop(data, pid, fd, i);
		i++;
		data->lst = data->lst->next;
		list_progress(data);
	}
	return (0);
}

int	ft_pipe(t_data *data)
{
	data->pipex->tab_pid = ft_calloc(ft_lstlen(data->lst), sizeof(int));
	if (data->pipex->tab_pid == NULL)
		ft_error(data, "malloc error\n", 1, 1);
	data->pipex->tab_fd = ft_calloc(ft_lstlen(data->lst), sizeof(int));
	if (data->pipex->tab_fd == NULL)
		ft_error(data, "malloc error\n", 1, 1);
	data->pipex->prev_fd = 0;
	signal(SIGINT, ft_ctrl_fork);
	signal(SIGTERM, ft_ctrl_fork);
	signal(SIGQUIT, ft_ctrl_fork);
	list_progress(data);
	g_error_last = 0;
	if (ft_loop_pipe(data) == 1)
		return (1);
	ft_end(data);
	return (0);
}
