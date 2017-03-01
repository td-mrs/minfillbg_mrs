#include "signal_handler.h"

volatile sig_atomic_t has_received_signal = 0;

void signal_handler(int signal)
{
  has_received_signal = signal;
}


void set_handler (void)
{
  //~ has_received_signal = 0;
  signal(SIGTERM, signal_handler);  
  signal(SIGINT, signal_handler);  
}
