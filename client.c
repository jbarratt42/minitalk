/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarratt <jbarratt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:22 by jbarratt          #+#    #+#             */
/*   Updated: 2025/05/22 14:30:23 by jbarratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_bit(int pid, int b)
{
	if (b)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
	pause();
}

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
		send_bit(pid, c >> i++ & 1);
}

void	ack(int signal)
{
	write(1, ".", 1);
	(void)signal;
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		return (1);
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, ack);
	while (*argv[2])
	{
		send_char(pid, *argv[2]);
		argv[2]++;
	}
	send_char(pid, '\0');
}
