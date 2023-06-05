/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:24:22 by luhumber          #+#    #+#             */
/*   Updated: 2023/06/05 11:16:42 by luhumber         ###   ########.fr       */
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
	{
		if (waitpid(data->pipex->tab_pid[i], NULL, 0) == -1)
			ft_error(data, "waitpid error\n", 1);
		if (i > 0)
			close(data->pipex->tab_fd[i]);
	}
	free(data->pipex->tab_pid);
	free(data->pipex->tab_fd);
	return (0);
}

void	ft_restore_loop(t_data *data, pid_t pid, int *fd, int i)
{
	if (data->in_redir > 0)
	{
		if (dup2(data->savestdin, STDIN_FILENO) == -1)
			ft_error(data, "dup error\n", 1);
		data->in_redir = 0;
	}
	if (data->out_redir > 0)
	{
		if (dup2(data->savestdout, STDOUT_FILENO) == -1)
			ft_error(data, "dup error\n", 1);
		data->out_redir = 0;
	}
	data->pipex->tab_pid[i] = pid;
	data->pipex->tab_fd[i] = data->pipex->prev_fd;
	data->pipex->prev_fd = fd[0];
	close(fd[1]);
}

int	ft_exec_pipe(t_data *data, int fd[2])
{
	char	**cmd;
	int		i;

	close(fd[0]);
	ft_make_dup(data);
	ft_dup_pipe(data);
	i = ft_builtins(data);
	if (i == 1 || i == -1)
		exit (1);
	i = 0;
	while (data->lst->content[i])
		i++;
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		ft_error(data, "malloc error\n", 1);
	cmd = ft_cmd_options(data, cmd, data->lst->content[0]);
	if (cmd[0] == NULL)
		exit (127);
	if (execve(cmd[0], cmd, data->env_path) == -1)
		ft_error(data, "execve error\n", 1);
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
			ft_error(data, "pipe error\n", 1);
		data->pipex->file_out = fd[1];
		if (!data->lst->next)
			data->pipex->file_out = STDOUT_FILENO;
		pid = fork();
		if (pid == -1)
			ft_error(data, "fork error\n", 1);
		else if (pid == 0)
			if (ft_exec_pipe(data, fd) == 1)
				exit (1);
		ft_restore_loop(data, pid, fd, i);
		i++;
		data->lst = data->lst->next;
		if (list_progress(data) == 1)
			return (1);
	}
	return (0);
}

int	ft_pipe(t_data *data)
{
	data->pipex->tab_pid = ft_calloc(ft_lstlen(data->lst), sizeof(int));
	data->pipex->tab_fd = ft_calloc(ft_lstlen(data->lst), sizeof(int));
	data->pipex->prev_fd = 0;
	signal(SIGINT, ft_ctrl_fork);
	signal(SIGTERM, ft_ctrl_fork);
	signal(SIGQUIT, ft_ctrl_fork);
	if (list_progress(data) == 1)
		return (1);
	if (ft_loop_pipe(data) == 1)
		return (1);
	ft_end(data);
	return (0);
}
