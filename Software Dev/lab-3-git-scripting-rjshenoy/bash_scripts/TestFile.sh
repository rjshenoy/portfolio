#!/bin/bash
FILE=sample_text.txt
if test -f "$FILE"; then
        echo "$FILE exists"
	read -p "Options: " expression
	case $expression in
		count_lines|countLines)
			wc -l sample_text.txt
			;;
		count_words)
			wc -w sample_test.txt
			;;
		add_text)
			read -p "Enter line: " textInput
			echo $textInput  >> sample_text.txt
			;;
		copy)
			cp sample_text.txt sample_copy.txt
			;;
		exit)
			;;
		esac
		
else
        echo "$FILE does not exist"
        exit
fi
