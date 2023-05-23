/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:39:01 by lucas             #+#    #+#             */
/*   Updated: 2023/05/23 10:46:00 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error(t_data *data, char *str, int exit_code)
{
	char	*join;

	join = ft_strjoin("bash: ", str);
	perror(join);
	free(join);
	ft_to_free(data);
	g_error_last = exit_code;
	exit(g_error_last);
}

int	ft_print_error(char *str)
{
	char	*join;

	join = ft_strjoin("bash: ", str);
	perror(join);
	free(join);
	return (1);
}

int	ft_cmd_error(char *str)
{
	char	*join;

	g_error_last = 127;
	join = ft_strjoin(str, ": command not found\n");
	write(2, join, ft_strlen(join));
	free(join);
	return (1);
}

int	ft_special_char(char *cmd)
{
	char	*join;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '.' && cmd[i] != '/')
			return (0);
		i++;
	}
	if (cmd[0] == '/')
	{
		join = ft_strjoin("bash: ", cmd);
		join = ft_strjoin(join, ": is a directory\n");
		write(2, join, ft_strlen(join));
		free(join);
	}
	else if (cmd[0] == '.')
		ft_cmd_error(cmd);
	return (1);
}
