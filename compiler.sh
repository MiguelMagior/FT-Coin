#!/bin/bash

# Compiler
COMPILER="g++"

# Source files
SOURCES=(
    "main.cpp"
    "Controller.cpp"
    "Menu.cpp"
    "Utils.cpp"
    "Wallet.cpp"
    "WalletDAO.cpp"
    "WalletMemoryDAO.cpp"
    "WalletDBDAO.cpp"
    "Transaction.cpp"
    "TransactionDAO.cpp"
    "TransactionMemoryDAO.cpp"
    "TransactionDBDAO.cpp"
    "Oracle.cpp"
    "OracleDAO.cpp"
    "OracleMemoryDAO.cpp"
    "OracleDBDAO.cpp"
)

# Compiler flags
CFLAGS="-Wall -Wextra -std=c++11"

# Libraries to link (MariaDB C++ Connector)
LIBS="-lmariadbcpp"

# Output executable
OUTPUT="main"

# Compile command
echo "Compiling..."
$COMPILER ${SOURCES[@]} $CFLAGS $LIBS -o $OUTPUT

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation successful! Executable: ./$OUTPUT"
else
    echo "Compilation failed."
    exit 1
fi