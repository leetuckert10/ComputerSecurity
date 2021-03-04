#!/bin/bash_shellshock

echo "content-type: text/plain"
echo
echo "****** Environment Variables ******"
strings /proc/$$/environ
