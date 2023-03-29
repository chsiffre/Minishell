/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:20:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/29 15:43:54 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)**argv;
	data.env_path = envp;
	data = ft_init_struct(data);
	ft_get_env(&data);
	ft_prompt(&data);
	return (0);
}
