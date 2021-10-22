#!/bin/bash
# This is just for GitHub, and is used to clean up leftover files after automatic testing has completed! ;)

echo "TOK 0$10"

echo "Cleaning up CI junk..."
git add *
ls -l
pwd
sudo rm -r *tar*
sudo rm -r examples/*/build
ls -l
git commit -a -m "Auto Cleanup"
git push

echo "Installing gh to open Doxygen issues..."
curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo gpg --dearmor -o /usr/share/keyrings/githubcli-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null
sudo apt update
sudo apt install dirmngr
sudo apt install gh

echo "Authenticating"
gh auth login --with-token $1
echo "Creating issue"
gh issue create --title "(TESTING) Does this script automatically open an issue?" --body "If it does, this baby is working."

echo "Done!" 
