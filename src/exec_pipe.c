/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:24:22 by luhumber          #+#    #+#             */
/*   Updated: 2023/04/24 16:56:10 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	dup2(data->pipex->file_in, STDOUT_FILENO);
	if (ft_prepare_pipe(data, tmp, tmp->content[0]) == 1)
		exit (1);
	return (0);
}

int	ft_pipe(t_data *data, t_lst *tmp)
{
	int		fd[2];
	pid_t	pid;

	//data->pipex->file_in = open
	//	(tmp->content[0], O_RDONLY);
	// if (tmp->next)
	// 	data->pipex->file_out = open
	// 		(tmp->content[0], O_RDONLY | O_TRUNC | O_CREAT, 0644);
	while (tmp)
	{
		if (pipe(fd) == -1)
			return (1);
		pid = fork();
		data->pipex->file_in = fd[1];
		close(fd[1]);
		data->pipex->file_out = fd[0];
		close(fd[0]);
		if (pid == -1)
			return (1);
		else if (pid == 0)
			ft_exec_pipe(data, tmp);
		tmp = tmp->next;
		if (tmp->type == PIPE)
			tmp = tmp->next;
		if (tmp->type == REDIR)
			ft_redirection(data, tmp);
		close(data->pipex->file_in);
		close(data->pipex->file_out);
	}
	waitpid(pid, NULL, 0);
	return (0);
}
