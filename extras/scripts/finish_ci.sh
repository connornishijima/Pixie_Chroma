#!/bin/bash
# This is just for GitHub, and is used to clean up leftover files after automatic testing has completed! ;)
# TODO: Port finish_ci.sh from Bash to Python

python ./extras/scripts/generate_doxygen_report.py
python ./extras/scripts/generate_keywords_report.py
python ./extras/scripts/generate_icons_report.py
python ./extras/scripts/generate_overview_report.py

echo "Cleaning up CI junk..."
git add *
sudo rm -r *tar*
sudo rm -r examples/*/build
git commit -a -m "Auto Cleanup"
git push

echo "Done!" 
