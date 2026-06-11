CC := gcc

CFLAGS := -O2 -Wall -Wextra -std=gnu11
INCLUDES := -I..

ISAFLAGS := -mavx2 -mavx512vl -mavx512vnni

SRCS := basic_dpbusd_vnni.c basic_vpmaddwd.c stress_dpbusd_vnni.c
BINS := basic_dpbusd_vnni basic_vpmaddwd stress_dpbusd_vnni

.PHONY: all clean run list

all: $(BINS)

basic_dpbusd_vnni: basic_dpbusd_vnni.c ../common.h
	$(CC) $(CFLAGS) $(INCLUDES) $(ISAFLAGS) $< -o $@

basic_vpmaddwd: basic_vpmaddwd.c ../common.h
	$(CC) $(CFLAGS) $(INCLUDES) $(ISAFLAGS) $< -o $@

stress_dpbusd_vnni: stress_dpbusd_vnni.c ../common.h
	$(CC) $(CFLAGS) $(INCLUDES) $(ISAFLAGS) $< -o $@

run: all
	@for bin in $(BINS); do \
		echo "===================================="; \
		echo "Running $$bin"; \
		echo "===================================="; \
		./$$bin; \
	done

list:
	@echo "Sources: $(SRCS)"
	@echo "Binaries: $(BINS)"

clean:
	rm -f $(BINS) *.o
