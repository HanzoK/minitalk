/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:41:21 by hanjkim           #+#    #+#             */
/*   Updated: 2024/09/26 16:45:00 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

//Global variable to track server communication
volatile sig_atomic_t	g_bit_tracker = 0;

/* Function takes a char and sends it to the server bit-by-bit. 
For each bit in a char, function sends either SIGUSR1 (for '1' bit) 
or SIGUSR2 (for '0' bit) to server. After sending each bit, it waits for 
acknowledgment from the server before proceeding to the next bit.*/
void	send_char_to_server(char c, pid_t pid)
{
	int	bit;

	bit = CHAR_BIT * sizeof(c) - 1;
	while (bit >= 0)
	{
		if (kill(pid, 0) < 0)
			(write(2, "Failed to send PID Signal. Pathetic.", 31), exit(1));
		g_bit_tracker = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_bit_tracker == 0)
			usleep(100);
		bit--;
	}
}

void	send_string_to_server(const char *str, pid_t pid)
{
	while (*str)
	{
		send_char_to_server(*str, pid);
		str++;
	}
	send_char_to_server(0, pid);
}

/*Function for signal handler of the client. When SIGUSR1 is received, 
it sets `g_bit_tracker` to 1, indicating that the server received
the last bit of a char. When SIGUSR2 is sent, then the server has 
successfully received the entire message, and client exits.*/
void	handle_signal_client(int sig)
{
	if (sig == SIGUSR1)
		g_bit_tracker = 1;
	else if (sig == SIGUSR2)
		(write(1, "Well done Mortal. You have sent a message\n", 42), exit(0));
}

/*Function sets up signal handlers for SIGUSR1 and SIGUSR2 
via `sigaction()`. 
SIGUSR1 to indicate that bit was successfully received by server. 
SIGUSR2 to indicate that the entire message was received.*/
void	set_signal_client(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal_client;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) < 0)
	{
		write(2, "Failed to set SIGUSR1 handler. Pathetic.\n", 41);
		exit(1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) < 0)
	{
		write(2, "Failed to set SIGUSR2 handler. Pathetic.\n", 41);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		write(2, "Really? Try it like this: ./client <PID> <string>\n", 50);
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || ((unsigned int)pid > UINT_MAX))
	{
		write(2, "NICE TRY. GO AGAIN FOOL.\n", 25);
		exit(1);
	}
	set_signal_client();
	send_string_to_server(argv[2], pid);
	while (1)
		pause();
	return (0);
}
