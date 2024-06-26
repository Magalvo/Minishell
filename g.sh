#!/bin/bash

# Ask for y/n input
echo "Do you want to GIT PUSH? (y/n): "
read response

# Check if the response is y or n
if [[ $response == "y" ]]; then
	# Run the command
	echo "Write commit message..."
	read message
	if [[ $message ]]; then
	git add . ; git commit -m "$message" ; git push
	else
	git add . ; git commit -am. ; git push
	fi
elif [[ $response == "n" ]]; then
	# Do nothing
	echo "code some more."
else
	# Invalid input
	echo "Please enter y or n."
fi
