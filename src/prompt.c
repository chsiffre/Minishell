/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/27 17:03:36 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec(t_data *prompt, char *line)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (ft_printf("bash error\n"));
	pid = fork();
	if (pid == -1)
		return (ft_printf("bash error\n"));
	else if (pid == 0)
        //exit(1);
	    execve(line, NULL, prompt->env_path);
    waitpid(pid, NULL, 0);
	return (0);
}

char	*ft_try_path(t_data *prompt, char *line)
{
	int		i;
	char	*tmp;
	char	*tab;

	i = 0;
	line[ft_strlen(line)] = '\0';
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

void	ft_get_env(t_data *data)
{
	while (data->env_path)
	{
		if (ft_strnstr(*data->env_path, "PATH", 5))
		{
			data->path = *data->env_path + 5;
			data->split_path = ft_split(data->path, ':');
			if (!data->split_path)
				exit (1);
			return ;
		}
		data->env_path++;
	}
}