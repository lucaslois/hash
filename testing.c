#include "testing.h"
#include <stdio.h>
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KRST "\x1B[0m"

static int _failure_count;

void real_print_test(const char* mensaje, bool ok,
		     const char* file, int line, const char* failed_expr) {
    if (ok) {
	printf("%s... "KGRN"OK\n", mensaje);
	printf(KRST);
    } else {
	printf("%s: "KRED"ERROR\n"  "%s:%d: %s\n",
	       mensaje, file, line, failed_expr);
   printf(KRST);
    }
    fflush(stdout);
    _failure_count += !ok;
}

int failure_count() {
    return _failure_count;
}
