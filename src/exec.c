/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:12:25 by lucas             #+#    #+#             */
/*   Updated: 2023/04/24 16:53:53 by luhumber         ###   ########.fr       */
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
			return (ft_printf("error execve\n"), 1);
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

char	**ft_cmd_options(t_data *data, t_lst *tmp, char **cmd, char *content)
{
	int	i;
	int	j;
	int	k;

	cmd[0] = ft_try_path(data, data->line, content);
	i = 1;
	while (tmp->content[i])
	{
		cmd[i] = malloc(sizeof(char) * ft_strlen(tmp->content[i]));
		j = 0;
		k = 0;
		while (tmp->content[i][j])
		{
			cmd[i][k] = tmp->content[i][j];
			j++;
			k++;
		}
		cmd[i][k] = '\0';
		i++;
	}
	return (cmd);
}

int	ft_execute_cmd(t_data *data, t_lst *tmp, char *content)
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
	if (ft_exec(data, cmd) == 1)
		return (1);
	return (0);
}

void	ft_check_type(t_data *data, t_lst *tmp)
{
	if (tmp->type == REDIR)
		ft_redirection(data, tmp);
	else if (tmp->next && tmp->next->type == PIPE)
		ft_pipe(data, tmp);
	else if (tmp->type == CMD)
		ft_execute_cmd(data, tmp, tmp->content[0]);
}
