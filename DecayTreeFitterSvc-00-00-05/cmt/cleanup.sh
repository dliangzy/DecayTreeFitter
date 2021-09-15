# echo "cleanup DecayTreeFitterSvc DecayTreeFitterSvc-00-00-05 in /home/lliu/boss/Workarea-7.0.5/Analysis"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtDecayTreeFitterSvctempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtDecayTreeFitterSvctempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=DecayTreeFitterSvc -version=DecayTreeFitterSvc-00-00-05 -path=/home/lliu/boss/Workarea-7.0.5/Analysis  $* >${cmtDecayTreeFitterSvctempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=DecayTreeFitterSvc -version=DecayTreeFitterSvc-00-00-05 -path=/home/lliu/boss/Workarea-7.0.5/Analysis  $* >${cmtDecayTreeFitterSvctempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtDecayTreeFitterSvctempfile}
  unset cmtDecayTreeFitterSvctempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtDecayTreeFitterSvctempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtDecayTreeFitterSvctempfile}
unset cmtDecayTreeFitterSvctempfile
return $cmtcleanupstatus

