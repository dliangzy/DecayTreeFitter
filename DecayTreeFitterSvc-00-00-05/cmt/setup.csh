# echo "setup DecayTreeFitterSvc DecayTreeFitterSvc-00-00-05 in /home/lliu/boss/Workarea-7.0.5/Analysis"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtDecayTreeFitterSvctempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtDecayTreeFitterSvctempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=DecayTreeFitterSvc -version=DecayTreeFitterSvc-00-00-05 -path=/home/lliu/boss/Workarea-7.0.5/Analysis  -no_cleanup $* >${cmtDecayTreeFitterSvctempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=DecayTreeFitterSvc -version=DecayTreeFitterSvc-00-00-05 -path=/home/lliu/boss/Workarea-7.0.5/Analysis  -no_cleanup $* >${cmtDecayTreeFitterSvctempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtDecayTreeFitterSvctempfile}
  unset cmtDecayTreeFitterSvctempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtDecayTreeFitterSvctempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtDecayTreeFitterSvctempfile}
unset cmtDecayTreeFitterSvctempfile
exit $cmtsetupstatus

