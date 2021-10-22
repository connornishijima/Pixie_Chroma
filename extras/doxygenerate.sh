#!/bin/sh

# Fetch the first argument (Doxygen configuratuin file path)
DOXYGENCONF="docs/Doxyfile"
if [ -f "$DOXYGENCONF" ]; then
    echo "Doxygen confiugration file path: $DOXYGENCONF"
else
    echo "Doxygen confiugration file cannot be found at: $DOXYGENCONF"
    exit 1;
fi

# Install Doxygen, GIT, and OpenSSH packages
apk add doxygen git openssh graphviz ttf-freefont

# Try to generate code documentation
# Exit with error if the document generation failed
doxygen "$DOXYGENCONF" > ./doxy.log || exit 1

echo "------------------------/"
ls -l
cat ./doxy.log
echo "------------------------/"

# Fetch the second agument (Generated HTML documents output folder) and
# strip the '/' character from the end of the directory path (if there is any)
HTMLOUTPUT='./docs'
if [ -d "$HTMLOUTPUT" ]; then
    echo "Generated HTML documents output folder: $HTMLOUTPUT"
else
    echo "HTML documents output folder cannot be found at: $HTMLOUTPUT"
    exit 1;
fi

# Set Git user configuration
git config user.name github-actions[bot]
git config user.email github-actions[bot]@users.noreply.github.com

# Get the current branch name
CURRENTBRANCH="$(git rev-parse --abbrev-ref HEAD)"

# Fetch the third argument (GitHub Pages branch name)
GHPAGESBRANCH='main'

# Fetch the forth argument (GitHub Pages directory path)
GHPAGESDIR='./docs/'

# Stash changes in the current branch and move them to the GitHub pages branch
if [ "$CURRENTBRANCH" != "$GHPAGESBRANCH" ]; then
    # Add the generated code documentation to the Git even they are ignored
    git add --force "$HTMLOUTPUT"
    git add --force "./doxy.log"

    # Stash the generated code documentation
    git stash save "$HTMLOUTPUT"
    git stash save "./doxy.log"

    # Synchronize with the remote repository
    git remote update

    # Try to switch to the GitHub Pages branch
    # Exit with error if the checkout failed
    git checkout "$GHPAGESBRANCH" || exit 1

    if [ -d "$GHPAGESDIR" ]; then
        # Remove all the files in GitHub Pages directory (if the directory exists)
        git rm -rf "$GHPAGESDIR"
    else
        # Make the GitHub Pages directory if it does not exist
        mkdir "$GHPAGESDIR"
    fi

    # Pop the stashed generated code documentation
    git stash pop
fi

# Move the the generated code documentation to the GitHub Pages directory
# if two directories are not the same.
if [ ! "$(realpath "$GHPAGESDIR")" -ef "$(realpath "$HTMLOUTPUT")" ]; then
    mv "$HTMLOUTPUT"/* "$GHPAGESDIR"
fi

# Add all the changes to the GIT
git add --all

# Commit all the changed to the the GitHub Pages branch
git commit -m "Auto commit"

# Push the changes to the remote GitHub Pages branch
git push
