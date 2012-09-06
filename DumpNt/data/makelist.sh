#!/bin/bash

FLAG_POOLSOURCE=0;

LIST=3_TIBFlange_MC.list
TMPLIST=tmp
DIR=/gpfs/gpfsddn/srm/cms/store/user/sandro/3_TIBFlange/SingleElectronPt35/fast/rec/

ls -l $DIR | grep root > $TMPLIST

COUNT=0

for i in `gawk '{print $9}' $TMPLIST`; do

if [ $COUNT -eq 0 ] ; then
echo $DIR$i > $LIST
COUNT=1
else
if [ $FLAG_POOLSOURCE -eq 0 ] ; then
echo $DIR$i >> $LIST
else
echo "'file:"$DIR$i"'," >> $LIST
fi
fi
done;
