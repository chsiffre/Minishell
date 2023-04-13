/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:24:22 by luhumber          #+#    #+#             */
/*   Updated: 2023/04/13 13:34:37 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec_pipe(t_data *data, t_lst *tmp, int fd[2])
{
	close(data->pipex->file_out);
	write(2, "OK\n", 3);
	if (dup2(data->pipex->file_in, STDIN_FILENO) == -1)
		return (1);
	printf("BON\n");
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (1);
	close(fd[1]);
	ft_execute_cmd(data, tmp, tmp->content[0]);
	return (0);
}

int	ft_pipe(t_data *data, t_lst *tmp)
{
	int		fd[2];
	pid_t	pid;

	while (tmp)
	{
		printf("%s\n", tmp->content[0]);
		if (pipe(fd) == -1)
			return (1);
		pid = fork();
		if (pid == -1)
			return (1);
		else if (pid == 0)
			ft_exec_pipe(data, tmp, fd);
		tmp = tmp->next;
		if (tmp->type == PIPE)
			tmp = tmp->next;
		if (tmp->type == REDIR)
			ft_redirection(data, tmp);
	}
	return (0);
}
