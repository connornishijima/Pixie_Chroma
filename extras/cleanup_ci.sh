echo "Cleaning up CI junk..."
ls -l
pwd
sudo rm -r *tar*
git commit -m "Auto Cleanup"
git push
echo "Done." 
