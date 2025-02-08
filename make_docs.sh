# !/bin/zsh

mkdir -p html

XSDocgen --source ./dev/ --output ./html --undocumented --project-name "Compiler Services" --enable-c++ --project-copyright "Amlal El Mahrouss. &copy; %Y - All rights Reserved" --project-version "930.2024.1" --company-name "Amlal El Mahrouss."
