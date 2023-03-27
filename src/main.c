/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:20:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/27 13:55:26 by lucas            ###   ########.fr       */
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
		if (strnstr(*prompt->env_path, "PATH", 5))
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

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	int			fd[2];

	prompt.env_path = envp;
	ft_get_env(&prompt);
	if (pipe(fd) == -1)
		return (1);
	while (1)
	{
		write(1, "prompt>", 8);
		prompt.line = get_next_line(1);
		if (!ft_strncmp(prompt.line, "exit", ft_strlen(prompt.line) - 1))
			break ;
		write(fd[1], prompt.line, ft_strlen(prompt.line));
		write(fd[1], "\n", 1);
		prompt.line = ft_try_path(&prompt, prompt.line);
		if (prompt.line)
			ft_exec(&prompt, prompt.line);
		free(prompt.line);
	}
	free(prompt.line);
	close(fd[1]);
	return (0);
}