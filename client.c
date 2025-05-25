/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarratt <jbarratt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:22 by jbarratt          #+#    #+#             */
/*   Updated: 2025/05/25 13:24:39 by jbarratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
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
*/

/* send the bits_sent-th bit of message
 * - on first invocation, set message and pid
 * - on subsequent invocations, ignore the parameters
 * - if the last byte sent was NUL, exit normally
 * (increment bits_sent before kill() to avoid a race condition)
 */
void	send_next_bit(char *set_message, int set_pid)
{
	static char	*message;
	static int	pid;
	static int	bits_sent;
	int			bits_sent_before;

	if (!message)
	{
		message = set_message;
		pid = set_pid;
	}
	if (bits_sent / 8 && !message[bits_sent / 8 - 1])
		exit(0);
	bits_sent_before = bits_sent++;
	if (message[bits_sent_before / 8] >> bits_sent_before % 8 & 1)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
}

void	handle_ack(int signal)
{
	(void)signal;
	send_next_bit(NULL, 0);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("usage: client <server_pid> <message>\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (!pid)
		return (1);
	signal(SIGUSR1, handle_ack);
	send_next_bit(argv[2], pid);
	while (1)
		sleep(1);
}
