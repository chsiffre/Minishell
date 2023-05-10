/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:24:22 by luhumber          #+#    #+#             */
/*   Updated: 2023/05/10 15:32:52 by luhumber         ###   ########.fr       */
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
		waitpid(data->pipex->tab_pid[i], NULL, -1);
		if (i >= 1)
		{
			printf("close -> %d\n", data->pipex->tab_fd[i]);
			close(data->pipex->tab_fd[i]);

		}
	}
	free(data->pipex->tab_pid);
	free(data->pipex->tab_fd);
	return (0);
}

int	ft_exec_pipe(t_data *data)
{
	char	**cmd;
	int		i;

	i = 0;
	if (dup2(data->pipex->prev_fd, STDIN_FILENO) == -1)
		return (write(2, "ERREUR : DUP2\n", 15), 1);
	if (dup2(data->pipex->file_out, STDOUT_FILENO) == -1)
		return (write(2, "ERREUR : DUP2\n", 15), 1);
	if (ft_builtins(data) == 1)
		exit (0);
	while (data->lst->content[i])
		i++;
	cmd = malloc(sizeof(char *) * (i + 1));
	cmd = ft_cmd_options(data, cmd, data->lst->content[0]);
	if (cmd[0] == NULL)
		exit (1);
	if (execve(cmd[0], cmd, data->env_path) == -1)
		return (ft_print_error("exec"), 1);
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

void	ft_pipe(t_data *data)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 0;
	data->pipex->tab_pid = ft_calloc(ft_lstlen(data->lst), sizeof(int));
	data->pipex->tab_fd = ft_calloc(ft_lstlen(data->lst), sizeof(int));
	while (data->lst)
	{
		if (pipe(fd) == -1)
			exit (1);
		if (i == 0)
			data->pipex->prev_fd = 0;
		data->pipex->file_out = fd[1];
		if (!data->lst->next)
			data->pipex->file_out = STDOUT_FILENO;
		printf("fd0 = %d && fd1 = %d\n", fd[0], fd[1]);
		printf("prev = %d && out = %d\n", data->pipex->prev_fd, data->pipex->file_out);
		pid = fork();
		if (pid == -1)
			exit (1);
		else if (pid == 0)
			ft_exec_pipe(data);
		printf("CLOSE = %d\n", fd[1]);
		close (fd[1]);
		data->pipex->tab_pid[i] = pid;
		//printf("pid -> %d\n", pid);
		data->pipex->tab_fd[i] = data->pipex->prev_fd;
		//printf("prev -> %d\n", data->pipex->prev_fd);
		data->pipex->prev_fd = fd[0];

		i++;
		data->lst = data->lst->next;
		if (data->lst && data->lst->type == PIPE)
			data->lst = data->lst->next;
		if (data->lst && data->lst->type == REDIR)
		{
			ft_redirection(data);
			data->lst = data->lst->next;
		}
	}
	ft_end(data);
	return ;
}
