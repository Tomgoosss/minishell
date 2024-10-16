#include "minishell.h"

int g_signal = 0;

void handle_sigint(int sig)
{
    (void)sig;
    g_signal = 1;  // Set to 1 for Ctrl+C
    write(STDERR_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void handle_sigquit(int sig)
{
    (void)sig;
}

void setup_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}

void reset_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
