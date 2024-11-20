#!/bin/bash
echo "Enter a character: "
read -n 1 char
char_lower=$(echo "$char" | tr '[:upper:]' '[:lower:]')
case "$char_lower" in
    [aeiou]) echo -e "\nThe character '$char' is a vowel." ;;
    [bcdfghjklmnpqrstvwxyz]) echo -e "\nThe character '$char' is a consonant." ;;
    *) echo -e "\nInvalid input. Please enter a single alphabetic character." ;;
esac

