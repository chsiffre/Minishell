/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/27 14:10:21 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec(t_prompt *prompt, char *line)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (ft_printf("bash error\n"));
	pid = fork();
	if (pid == -1)
		return (ft_printf("bash error\n"));
	else if (pid == 0)
		execve(line, NULL, prompt->env_path);
	return (0);
}

char	*ft_try_path(t_prompt *prompt, char *line)
{
	int		i;
	char	*tmp;
	char	*tab;

	i = 0;
	line[ft_strlen(line + 1)] = '\0';
	tmp = ft_strjoin("/", line);
	while (prompt->split_path[i])
	{
		tab = ft_strjoin(prompt->split_path[i], tmp);
		if (access(tab, F_OK) != -1)
			break ;
		free(tab);
		tab = NULL;
		i++;
	}
	free(tmp);
	if (!tab)
		return (ft_printf("bash : command not found: %s\n", line), line);
	free(line);
	return (tab);
}

void	ft_get_env(t_prompt *prompt)
{
	while (prompt->env_path)
	{
		if (ft_strnstr(*prompt->env_path, "PATH", 5))
		{
			prompt->path = *prompt->env_path + 5;
			prompt->split_path = ft_split(prompt->path, ':');
			if (!prompt->split_path)
				exit (1);
			return ;
		}
		prompt->env_path++;
	}
}