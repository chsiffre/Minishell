/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:12:25 by lucas             #+#    #+#             */
/*   Updated: 2023/04/11 11:38:57 by luhumber         ###   ########.fr       */
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

int	ft_execute_cmd(t_data *data, char *content)
{
	char	**cmd;

	if (ft_builtins(data) == 1)
		return (1);
	cmd = malloc(sizeof(char *) * 10000);
	cmd[0] = ft_try_path(data, data->line, content);
	ft_exec(data, cmd);
	return (0);
}

int	ft_redirection(t_data *data)
{
	data->fd = open(data->lst->content[1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (dup2(data->fd, STDOUT_FILENO) == -1)
		return (printf("ERREUR\n"), 1);
	return (0);
}

		//dup2(STDIN_FILENO, STDOUT_FILENO);

void	ft_check_type(t_data *data, t_lst *tmp)
{
	if (tmp->type == 0)
		ft_redirection(data);
	else if (tmp->type == 1)
		ft_execute_cmd(data, tmp->content[0]);
}
