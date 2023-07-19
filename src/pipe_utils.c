/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:41:56 by luhumber          #+#    #+#             */
/*   Updated: 2023/07/19 14:58:40 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_end(t_data *data)
{
	int	i;
	int	ret;
	int	last;

	i = 0;
	while (data->pipex->tab_pid[i])
		i++;
	last = i - 1;
	while (i--)
	{
		ret = 0;
		if (waitpid(data->pipex->tab_pid[i], &ret, 0) == -1)
			ft_error(data, "waitpid error\n", 1, 1);
		if (WIFEXITED(ret) && i == last)
			g_error_last = WEXITSTATUS(ret);
		if (i > 0)
			close(data->pipex->tab_fd[i]);
	}
	free(data->pipex->tab_pid);
	free(data->pipex->tab_fd);
	return (0);
}

void	ft_restore_loop(t_data *data, pid_t pid, int *fd, int i)
{
	if (data->in_redir != 0)
	{
		if (data->in_redir > 0)
		{
			close(data->in_redir);
			if (dup2(data->savestdin, STDIN_FILENO) == -1)
				ft_error(data, "dup error\n", 1, 1);
		}
		data->in_redir = 0;
	}
	if (data->out_redir != 0)
	{
		if (data->out_redir > 0)
		{
			close(data->out_redir);
			if (dup2(data->savestdout, STDOUT_FILENO) == -1)
				ft_error(data, "dup error\n", 1, 1);
		}
		data->out_redir = 0;
	}
	data->pipex->tab_pid[i] = pid;
	data->pipex->tab_fd[i] = data->pipex->prev_fd;
	data->pipex->prev_fd = fd[0];
	close(fd[1]);
}
