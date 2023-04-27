/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:22:56 by luhumber          #+#    #+#             */
/*   Updated: 2023/04/27 15:05:46 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_here_doc(t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc>");
		if (ft_compare_str(line, data->limiter))
			break ;
		free(line);
	}
	free(line);
	return (0);
}

int	ft_which_redir(t_data *data, t_lst *tmp)
{
	if (ft_compare_str(tmp->content[0], ">"))
	{
		data->fd = open(tmp->content[1], O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (dup2(data->fd, STDOUT_FILENO) == -1)
			return (printf("ERREUR\n"), 1);
	}
	else if (ft_compare_str(tmp->content[0], "<"))
	{
		data->fd = open(tmp->content[1], O_RDONLY, 0644);
		if (dup2(data->fd, STDIN_FILENO) == -1)
			return (printf("ERREUR\n"), 1);
	}
	else if (ft_compare_str(tmp->content[0], "<<"))
	{
		data->limiter = tmp->content[1];
		ft_here_doc(data);
	}
	else if (ft_compare_str(tmp->content[0], ">>"))
	{
		data->fd = open(tmp->content[1], O_RDWR | O_APPEND | O_CREAT, 0644);
		if (dup2(data->fd, STDOUT_FILENO) == -1)
			return (printf("ERREUR\n"), 1);
	}
	return (0);
}

int	ft_redirection(t_data *data, t_lst *tmp)
{
	ft_which_redir(data, tmp);
	tmp = tmp->next;
	if (tmp->type == CMD)
		ft_execute_cmd(data, tmp, tmp->content[0]);
	dup2(STDIN_FILENO, STDOUT_FILENO);
	return (0);
}
