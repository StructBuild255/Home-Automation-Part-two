# Falco Backend Makefile
# Server: Falco (Debian Dell 7050 MFF)

CC = gcc
CFLAGS = -Wall -Wextra

# ---------------------------------------------------------
# STAGE 1: Hardcoded Prototype (Day 1)
# ---------------------------------------------------------
TARGET_V1 = falco_v1
SRC_V1 = falco_backend_v1.c

$(TARGET_V1): $(SRC_V1)
	$(CC) $(CFLAGS) -o $(TARGET_V1) $(SRC_V1)
	@echo "✅ Build successful: $(TARGET_V1) (Prototype)"

# ---------------------------------------------------------
# STAGE 2: Full Backend with MariaDB (Day 2+)
# ---------------------------------------------------------
# Uses mysql_config to auto-detect library paths on Debian
TARGET_DB = falco_backend
SRC_DB = falco_backend.c
DB_FLAGS = $(shell mysql_config --cflags)
DB_LIBS = $(shell mysql_config --libs)

$(TARGET_DB): $(SRC_DB)
	$(CC) $(CFLAGS) $(DB_FLAGS) -o $(TARGET_DB) $(SRC_DB) $(DB_LIBS)
	@echo "✅ Build successful: $(TARGET_DB) (MariaDB Enabled)"

# ---------------------------------------------------------
# Utilities
# ---------------------------------------------------------
all: $(TARGET_V1) $(TARGET_DB)

clean:
	rm -f $(TARGET_V1) $(TARGET_DB)
	@echo "🧹 Cleaned up executables."

# Shortcuts to run
run_v1: $(TARGET_V1)
	./$(TARGET_V1)

run_db: $(TARGET_DB)
	./$(TARGET_DB)