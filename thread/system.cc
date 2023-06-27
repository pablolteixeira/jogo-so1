#include "system.h"
#include "thread.h"
#include <iostream>

__BEGIN_API

void System::init(void (*main)(void *)) {
    db<System>(TRC) << "System::init() called\n";

    setvbuf(stdout, 0,_IONBF, 0);    

	std::cout << "in system init\n";

    Thread::init(main);

	std::cout << "after thread init\n" << std::flush;
}

__END_API
