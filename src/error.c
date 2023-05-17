/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:39:01 by lucas             #+#    #+#             */
/*   Updated: 2023/05/18 00:53:53 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
