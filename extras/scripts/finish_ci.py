# This is just for GitHub, and is used to clean up leftover files after
# automatic testing has completed, and generate developer reports about
# anything left undocumented!

# run: "sudo python ./extras/scripts/finish_ci.py"

import os
import sys

os.system("sudo python ./extras/scripts/generate_doxygen_report.py")
os.system("sudo python ./extras/scripts/generate_keywords_report.py")
os.system("sudo python ./extras/scripts/generate_overview_report.py")

print("Cleaning up CI junk...")
os.system("ls .")
os.system("git add *")
os.system("sudo rm -r *tar*")
os.system("sudo rm -r examples/*/build")
os.system("git commit -a -m 'Automated Cleanup'")
os.system("git push")

print("Done!" )
