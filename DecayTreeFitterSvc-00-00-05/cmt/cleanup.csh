# echo "cleanup DecayTreeFitterSvc DecayTreeFitterSvc-00-00-05 in /home/lliu/boss/Workarea-7.0.5/Analysis"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtDecayTreeFitterSvctempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtDecayTreeFitterSvctempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=DecayTreeFitterSvc -version=DecayTreeFitterSvc-00-00-05 -path=/home/lliu/boss/Workarea-7.0.5/Analysis  $* >${cmtDecayTreeFitterSvctempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=DecayTreeFitterSvc -version=DecayTreeFitterSvc-00-00-05 -path=/home/lliu/boss/Workarea-7.0.5/Analysis  $* >${cmtDecayTreeFitterSvctempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtDecayTreeFitterSvctempfile}
  unset cmtDecayTreeFitterSvctempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtDecayTreeFitterSvctempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtDecayTreeFitterSvctempfile}
unset cmtDecayTreeFitterSvctempfile
exit $cmtcleanupstatus

