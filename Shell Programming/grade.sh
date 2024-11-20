#!/bin/bash
echo "Enter the student's score (out of 100):"
read score
if ((score >= 90)); then
grade="A"
elif ((score >= 80)); then
grade="B"
elif ((score >= 70)); then
grade="C"
elif ((score >= 60)); then
grade="D"
else
grade="F"
fi
echo "Student's grade: $grade"
