#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <csignal>

extern volatile sig_atomic_t has_received_signal;    ///< 0 if no signal has been received yet, a positive value corresponding to the received signal otherwise

void signal_handler(int signal);    ///< allows to handle the given signal

void set_handler (void);      ///< sets the handler


#endif

