#!/bin/bash
# This is just for GitHub, and is used to clean up leftover files after automatic testing has completed! ;)

echo "Cleaning up CI junk..."
git add *
ls -l
pwd
sudo rm -r *tar*
sudo rm -r examples/*/build
ls -l
git commit -a -m "Auto Cleanup"
git push

echo "Done!" 
