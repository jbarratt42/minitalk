/* server.c */
void	handler(int signal, siginfo_t *info, void *ucontext);
/* client.c */
void	send_bit(int pid, int b);
void	send_char(int pid, char c);
void	ack(int signal);
