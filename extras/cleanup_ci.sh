echo "Cleaning up CI junk..."
git add *
ls -l
pwd
sudo rm -r *tar*
ls -l
git commit -m "Auto Cleanup"
git push
echo "Done!" 
