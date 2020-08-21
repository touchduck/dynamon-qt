#!/usr/bin/env bash
find . -name ".DS_Store" -type f -print -delete
git add . && git commit -m "auto push" && git push
