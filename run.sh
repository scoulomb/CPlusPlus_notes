#!/bin/bash
set -e
# Any subsequent(*) commands which fail will cause the shell script to exit immediately

# Generate top level SConstruct file
find . -mindepth 2 -name "SConstruct" | python generateSConstruct.py

# Call scons with the generated top level SConstruct file (will call SConstrcut files in subdirectories building and runnnig each sub project) 
scons 

# Clean 

# Will call SConstrcut files in subdirectories cleaning each sub project
scons -c
# Remove top level generated SConstruct file
rm -f ./SConstruct
