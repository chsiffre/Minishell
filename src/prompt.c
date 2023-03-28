/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/27 18:50:48 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec(t_data *prompt, char **cmd)
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
	    execve(cmd[0], cmd, prompt->env_path);
    waitpid(pid, NULL, 0);
	return (0);
}

char	**ft_try_path(t_data *data, char *line, char **cmd)
{
	int		i;
	char	*tmp;
	char	*tab;

	i = 0;
	line[ft_strlen(line)] = '\0';
    cmd = ft_split(line, ' ');
    if (!cmd)
        return (NULL);
	tmp = ft_strjoin("/", line);
	while (data->split_path[i])
	{
		tab = ft_strjoin(data->split_path[i], tmp);
		if (access(tab, F_OK) != -1)
			break ;
		free(tab);
		tab = NULL;
		i++;
	}
	free(tmp);
	if (!tab)
		return (ft_printf("bash : command not found: %s\n", line), line);
	//free(line);
	return (cmd);
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