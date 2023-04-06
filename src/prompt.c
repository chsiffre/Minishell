/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/06 14:02:28 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec(t_data *prompt, char **cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_printf("bash error\n"));
	else if (pid == 0)
	{
		if (execve(cmd[0], cmd, prompt->env_path) == -1)
			return (ft_printf("error execve\n"));
	}
	waitpid(pid, NULL, 0);
	return (0);
}

char	*ft_try_path(t_data *data, char *line, char *cmd)
{
	int		i;
	char	*tmp;
	char	*tab;

	i = 0;
	if (access(cmd, F_OK) != -1)
		return (cmd);
	tmp = ft_strjoin("/", cmd);
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
		return (ft_printf("bash : command not found: %s\n", line), NULL);
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

int	ft_lsize(t_lst *lst)
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

void	ft_list_to_tab(t_data *data, t_lst *lst)
{
	t_lst	*tmp;
	int		i;
	int		j;

	tmp = lst;
	i = 0;
	data->cmd = malloc(sizeof(char *) * (ft_lsize(tmp) + 1));
	while (tmp)
	{
		j = 0;
		data->cmd[i] = malloc(sizeof(char) * ft_strlen((*tmp->content)));
		while (tmp->content[j])
		{
			data->cmd[i][j] = (*tmp->content[j]);
			j++;
		}
		i++;
		tmp = tmp->next;
	}
	data->cmd[i] = NULL;
}

void	ft_prompt(t_data *data)
{
	while (1)
	{
		//data->line = readline("prompt>");
		data->line = "ls";
		if (data->line)
			add_history(data->line);
		ft_parse(data);
		//return ;
		//ft_list_to_tab(data, lst);
		data->cmd = ft_split(data->line, ' ');
		if (!data->cmd)
			return ;
		if (data->cmd[0])
		{
			data->cmd[0] = ft_builtins(data);
			if (data->cmd[0] != NULL)
				data->cmd[0] = ft_try_path(data, data->line, data->cmd[0]);
			if (data->cmd[0])
				ft_exec(data, data->cmd);
		}
		free(data->line);
	}
	free(data->line);
}
