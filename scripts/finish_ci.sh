#!/bin/bash
# This is just for GitHub, and is used to clean up leftover files after automatic testing has completed! ;)

python ./scripts/generate_doxy_report.py
python ./scripts/generate_keyword_report.py

echo "Cleaning up CI junk..."
git add *
sudo rm -r *tar*
sudo rm -r examples/*/build
git commit -a -m "Auto Cleanup"
git push

echo "Done!" 
