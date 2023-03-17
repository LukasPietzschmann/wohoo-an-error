#define _GNU_SOURCE

#include <ctype.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum { uninitialized = -1 };

static unsigned int rand_seed;

static int pipe_fds[2];
static int old_stderr = uninitialized;
static pthread_t reader_thread;

static const char* reactions[] = {
	"😳 ",
	"😕 ",
	"😔 ",
	"😡 ",
	"🥲 ",
	"🤫 ",
	"🤨 ",
	"🚨 ",
	"💥 ",
	"🤮 ",
	"🤯 ",
	"😵 ",
	"🤦 ",
	"🤕 ",
	"🧐 ",
	"🥺 ",
	"😖 ",
	"💀 ",
	"🙀 ",
	"🙊 ",
	"🤷 ",
	"📉 ",
};

// https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html
#define random_element_from(field)                                \
	({                                                            \
		const size_t field_size = sizeof(field) / sizeof(*field); \
		field[rand_r(&rand_seed) * field_size / RAND_MAX];        \
	})

static void* listener(void*) {
	char read_character;
	bool newline = true;

	const char* reaction = random_element_from(reactions);
	while(read(pipe_fds[0], &read_character, 1) != 0) {
		if(read_character == '\n') {
			newline = true;
		} else if(newline && isprint(read_character)) {
			newline = false;
			write(old_stderr, reaction, strlen(reaction));
		}
		write(old_stderr, &read_character, 1);
	}
	pthread_exit(NULL);
}

void init(void) {
	if(!isatty(STDERR_FILENO))
		return;

	rand_seed = getpid();

	pipe2(pipe_fds, O_CLOEXEC);
	old_stderr = dup(STDERR_FILENO);
	dup2(pipe_fds[1], STDERR_FILENO);

	pthread_create(&reader_thread, NULL, listener, NULL);
}

void finish(void) {
	if(old_stderr == uninitialized)
		return;

	close(pipe_fds[1]);
	dup2(old_stderr, STDERR_FILENO);
	pthread_join(reader_thread, NULL);
	close(pipe_fds[0]);
}
