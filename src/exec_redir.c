/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:22:56 by luhumber          #+#    #+#             */
/*   Updated: 2023/05/30 17:25:26 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_here_doc(t_data *data)
{
	char	*line;
	int		fd[2];
	int		exit_status;
	pid_t	pid;
	char	*res;
	int		i;

	if (pipe(fd) == -1)
		ft_error(data, "pipe error\n", 1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		ft_error(data, "fork error\n", 1);
	else if (pid == 0)
	{
		close(fd[0]);
		data->limiter = data->lst->content[1];
		signal(SIGINT, ft_here_sig);
		while (1)
		{
			line = readline("heredoc> ");
			if (line == NULL)
			{
				ft_write_error
					("warning: here-document delimited by end-of-file");
				break ;
			}
			if (ft_compare_str(line, data->limiter))
				break ;
			res = malloc(sizeof(char) * ft_strlen(line) + 2);
			i = -1;
			while (line[++i])
				res[i] = line[i];
			res[i++] = '\n';
			res[i] = '\0';
			write(fd[1], res, ft_strlen(res));
			free(line);
			free(res);
		}
		free(line);
		close(fd[1]);
		exit(0);
	}
	waitpid(pid, &exit_status, 2);
	if (WEXITSTATUS(exit_status) == 1)
		return (1);
	close(fd[1]);
	data->in_redir = fd[0];
	return (0);
}

int	ft_which_redir(t_data *data)
{
	if (data->lst->content[1] == NULL)
	{
		g_error_last = 2;
		return (ft_print_error
			("syntax error near unexpected token `newline'\n"), 1);
	}
	else if (ft_compare_str(data->lst->content[0], ">"))
	{
		data->out_redir = open
			(data->lst->content[1], O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (data->out_redir == -1)
			return (ft_print_error(data->lst->content[1]), 1);
	}
	else if (ft_compare_str(data->lst->content[0], "<"))
	{
		data->in_redir = open
			(data->lst->content[1], O_RDONLY, 0644);
		if (data->in_redir == -1)
			return (ft_print_error(data->lst->content[1]), 1);
	}
	else if (ft_compare_str(data->lst->content[0], "<<"))
	{	
		if (ft_here_doc(data) == 1)
			return (1);
	}
	else if (ft_compare_str(data->lst->content[0], ">>"))
	{
		data->out_redir = open
			(data->lst->content[1], O_RDWR | O_APPEND | O_CREAT, 0644);
		if (data->in_redir == -1)
			return (ft_print_error(data->lst->content[1]), 1);
	}
	return (0);
}
