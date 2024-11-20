#!/bin/bash
echo "Enter the numbers..."
read num1
read num2
temp=$num1
num1=$num2
num2=$temp
echo "After swapping:"
echo "Value 1: $num1"
echo "Value 2: $num2"
