#include "timer.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void proc(void) {
	struct timeval now;
	gettimeofday(&now, NULL);
	printf("[timer callback] cur_time: sec %ld, msec %ld\n", now.tv_sec, now.tv_usec/1000);
}

int main() {
	std::function<void(void)> f = proc;
	Timer timer;
	timer.RunAfter(1, f);
	timer.Start();
	return 0;
}
