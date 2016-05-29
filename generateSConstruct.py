########################################################################
# Here is an example of a SConstruct generated file by this script
#
# http://scons.org/doc/1.2.0/HTML/scons-user/x3129.html
# I call SConstruct (and not SConscript) scons file in subdir in order to launch them separately
# SConscript(['lambda/SConstruct',
#            'iterator/SConstruct'
#           ])
# Goal is to launch scons file in all subdirectories
########################################################################


# Usage find . -mindepth 2 -name "SConstruct" | python generateSConstruct.py
# http://stackoverflow.com/questions/6106437/how-to-receive-arguments-via-shell-pipe-in-python
import sys

sconsFileList = ""
for line in sys.stdin:
    sconsFileList+= "'" + line.strip('\n') + "',"

genFile = "SConscript([" + sconsFileList + "])"

# Write global SConstruct file
fo = open("SConstruct", "wb")
fo.write(genFile);
fo.close()


