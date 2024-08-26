#!/bin/bash

# Test Interactive Mode
echo "Testing Interactive Mode..."
./hsh <<EOF
/bin/ls
exit
EOF

# Separator
echo "-----------------------------------"

# Test Non-Interactive Mode with Echo
echo "Testing Non-Interactive Mode with Echo..."
echo "/bin/ls" | ./hsh

# Separator
echo "-----------------------------------"

# Create a Test File with Commands
echo "/bin/ls" > test_ls_2

# Test Non-Interactive Mode with File Input
echo "Testing Non-Interactive Mode with File Input..."
cat test_ls_2 | ./hsh

# Cleanup
rm test_ls_2

