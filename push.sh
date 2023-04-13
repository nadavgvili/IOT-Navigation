#!/bin/bash

git add .

read -p "Enter commit message: " message

git commit -m "$message"

#basically the line below performs manual push to both remotes: orgini-gihub & origin-gitlab.
#on leetcode/.git/hooks/post-commit there is a hook doing the push after every commit
#git push --all origin-github && git push --all origin-gitlab && git push --tags origin-github && git push --tags origin-gitlab
#in order to do hook :

##!/bin/bash

#git push --all origin-github
#git push --all origin-gitlab
#git push --tags origin-github
#git push --tags origin-gitlab

#Note: The --all option will push all branches and tags
