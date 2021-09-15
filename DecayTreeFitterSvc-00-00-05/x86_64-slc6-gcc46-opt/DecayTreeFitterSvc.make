#-- start of make_header -----------------

#====================================
#  Library DecayTreeFitterSvc
#
#   Generated Sun Sep 12 22:20:41 2021  by lliu
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_DecayTreeFitterSvc_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_DecayTreeFitterSvc_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_DecayTreeFitterSvc

DecayTreeFitterSvc_tag = $(tag)

#cmt_local_tagfile_DecayTreeFitterSvc = $(DecayTreeFitterSvc_tag)_DecayTreeFitterSvc.make
cmt_local_tagfile_DecayTreeFitterSvc = $(bin)$(DecayTreeFitterSvc_tag)_DecayTreeFitterSvc.make

else

tags      = $(tag),$(CMTEXTRATAGS)

DecayTreeFitterSvc_tag = $(tag)

#cmt_local_tagfile_DecayTreeFitterSvc = $(DecayTreeFitterSvc_tag).make
cmt_local_tagfile_DecayTreeFitterSvc = $(bin)$(DecayTreeFitterSvc_tag).make

endif

include $(cmt_local_tagfile_DecayTreeFitterSvc)
#-include $(cmt_local_tagfile_DecayTreeFitterSvc)

ifdef cmt_DecayTreeFitterSvc_has_target_tag

cmt_final_setup_DecayTreeFitterSvc = $(bin)setup_DecayTreeFitterSvc.make
cmt_dependencies_in_DecayTreeFitterSvc = $(bin)dependencies_DecayTreeFitterSvc.in
#cmt_final_setup_DecayTreeFitterSvc = $(bin)DecayTreeFitterSvc_DecayTreeFitterSvcsetup.make
cmt_local_DecayTreeFitterSvc_makefile = $(bin)DecayTreeFitterSvc.make

else

cmt_final_setup_DecayTreeFitterSvc = $(bin)setup.make
cmt_dependencies_in_DecayTreeFitterSvc = $(bin)dependencies.in
#cmt_final_setup_DecayTreeFitterSvc = $(bin)DecayTreeFitterSvcsetup.make
cmt_local_DecayTreeFitterSvc_makefile = $(bin)DecayTreeFitterSvc.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)DecayTreeFitterSvcsetup.make

#DecayTreeFitterSvc :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'DecayTreeFitterSvc'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = DecayTreeFitterSvc/
#DecayTreeFitterSvc::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

DecayTreeFitterSvclibname   = $(bin)$(library_prefix)DecayTreeFitterSvc$(library_suffix)
DecayTreeFitterSvclib       = $(DecayTreeFitterSvclibname).a
DecayTreeFitterSvcstamp     = $(bin)DecayTreeFitterSvc.stamp
DecayTreeFitterSvcshstamp   = $(bin)DecayTreeFitterSvc.shstamp

DecayTreeFitterSvc :: dirs  DecayTreeFitterSvcLIB
	$(echo) "DecayTreeFitterSvc ok"

#-- end of libary_header ----------------

DecayTreeFitterSvcLIB :: $(DecayTreeFitterSvclib) $(DecayTreeFitterSvcshstamp)
	@/bin/echo "------> DecayTreeFitterSvc : library ok"

$(DecayTreeFitterSvclib) :: $(bin)ErrCode.o $(bin)RecoPhoton.o $(bin)BField.o $(bin)DecayTreeFitterSvc.o $(bin)RecoComposite.o $(bin)FitParams.o $(bin)Resonance.o $(bin)InternalParticle.o $(bin)RootParticle.o $(bin)KalmanCalculator.o $(bin)DecayTree.o $(bin)Constraint.o $(bin)ParticleBase.o $(bin)HelixUtils.o $(bin)RecoTrack.o $(bin)DecayTreeFitterSvc_load.o $(bin)DecayTreeFitterSvc_entries.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(DecayTreeFitterSvclib) $?
	$(lib_silent) $(ranlib) $(DecayTreeFitterSvclib)
	$(lib_silent) cat /dev/null >$(DecayTreeFitterSvcstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(DecayTreeFitterSvclibname).$(shlibsuffix) :: $(DecayTreeFitterSvclib) $(DecayTreeFitterSvcstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" DecayTreeFitterSvc $(DecayTreeFitterSvc_shlibflags)

$(DecayTreeFitterSvcshstamp) :: $(DecayTreeFitterSvclibname).$(shlibsuffix)
	@if test -f $(DecayTreeFitterSvclibname).$(shlibsuffix) ; then cat /dev/null >$(DecayTreeFitterSvcshstamp) ; fi

DecayTreeFitterSvcclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)ErrCode.o $(bin)RecoPhoton.o $(bin)BField.o $(bin)DecayTreeFitterSvc.o $(bin)RecoComposite.o $(bin)FitParams.o $(bin)Resonance.o $(bin)InternalParticle.o $(bin)RootParticle.o $(bin)KalmanCalculator.o $(bin)DecayTree.o $(bin)Constraint.o $(bin)ParticleBase.o $(bin)HelixUtils.o $(bin)RecoTrack.o $(bin)DecayTreeFitterSvc_load.o $(bin)DecayTreeFitterSvc_entries.o

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

ifeq ($(INSTALLAREA),)
installarea = $(CMTINSTALLAREA)
else
ifeq ($(findstring `,$(INSTALLAREA)),`)
installarea = $(shell $(subst `,, $(INSTALLAREA)))
else
installarea = $(INSTALLAREA)
endif
endif

install_dir = ${installarea}/${CMTCONFIG}/lib
DecayTreeFitterSvcinstallname = $(library_prefix)DecayTreeFitterSvc$(library_suffix).$(shlibsuffix)

DecayTreeFitterSvc :: DecayTreeFitterSvcinstall

install :: DecayTreeFitterSvcinstall

DecayTreeFitterSvcinstall :: $(install_dir)/$(DecayTreeFitterSvcinstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(DecayTreeFitterSvcinstallname) :: $(bin)$(DecayTreeFitterSvcinstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(DecayTreeFitterSvcinstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(DecayTreeFitterSvcinstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DecayTreeFitterSvcinstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DecayTreeFitterSvcinstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(DecayTreeFitterSvcinstallname) $(install_dir)/$(DecayTreeFitterSvcinstallname); \
	      echo `pwd`/$(DecayTreeFitterSvcinstallname) >$(install_dir)/$(DecayTreeFitterSvcinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(DecayTreeFitterSvcinstallname), no installation directory specified"; \
	  fi; \
	fi

DecayTreeFitterSvcclean :: DecayTreeFitterSvcuninstall

uninstall :: DecayTreeFitterSvcuninstall

DecayTreeFitterSvcuninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(DecayTreeFitterSvcinstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DecayTreeFitterSvcinstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DecayTreeFitterSvcinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(DecayTreeFitterSvcinstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)ErrCode.d

$(bin)$(binobj)ErrCode.d :

$(bin)$(binobj)ErrCode.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)ErrCode.o : $(src)ErrCode.cxx
	$(cpp_echo) $(src)ErrCode.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(ErrCode_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(ErrCode_cppflags) $(ErrCode_cxx_cppflags)  $(src)ErrCode.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(ErrCode_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)ErrCode.cxx

$(bin)$(binobj)ErrCode.o : $(ErrCode_cxx_dependencies)
	$(cpp_echo) $(src)ErrCode.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(ErrCode_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(ErrCode_cppflags) $(ErrCode_cxx_cppflags)  $(src)ErrCode.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)RecoPhoton.d

$(bin)$(binobj)RecoPhoton.d :

$(bin)$(binobj)RecoPhoton.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)RecoPhoton.o : $(src)RecoPhoton.cxx
	$(cpp_echo) $(src)RecoPhoton.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(RecoPhoton_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(RecoPhoton_cppflags) $(RecoPhoton_cxx_cppflags)  $(src)RecoPhoton.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(RecoPhoton_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)RecoPhoton.cxx

$(bin)$(binobj)RecoPhoton.o : $(RecoPhoton_cxx_dependencies)
	$(cpp_echo) $(src)RecoPhoton.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(RecoPhoton_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(RecoPhoton_cppflags) $(RecoPhoton_cxx_cppflags)  $(src)RecoPhoton.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)BField.d

$(bin)$(binobj)BField.d :

$(bin)$(binobj)BField.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)BField.o : $(src)BField.cxx
	$(cpp_echo) $(src)BField.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(BField_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(BField_cppflags) $(BField_cxx_cppflags)  $(src)BField.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(BField_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)BField.cxx

$(bin)$(binobj)BField.o : $(BField_cxx_dependencies)
	$(cpp_echo) $(src)BField.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(BField_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(BField_cppflags) $(BField_cxx_cppflags)  $(src)BField.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DecayTreeFitterSvc.d

$(bin)$(binobj)DecayTreeFitterSvc.d :

$(bin)$(binobj)DecayTreeFitterSvc.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)DecayTreeFitterSvc.o : $(src)DecayTreeFitterSvc.cxx
	$(cpp_echo) $(src)DecayTreeFitterSvc.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(DecayTreeFitterSvc_cppflags) $(DecayTreeFitterSvc_cxx_cppflags)  $(src)DecayTreeFitterSvc.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(DecayTreeFitterSvc_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)DecayTreeFitterSvc.cxx

$(bin)$(binobj)DecayTreeFitterSvc.o : $(DecayTreeFitterSvc_cxx_dependencies)
	$(cpp_echo) $(src)DecayTreeFitterSvc.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(DecayTreeFitterSvc_cppflags) $(DecayTreeFitterSvc_cxx_cppflags)  $(src)DecayTreeFitterSvc.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)RecoComposite.d

$(bin)$(binobj)RecoComposite.d :

$(bin)$(binobj)RecoComposite.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)RecoComposite.o : $(src)RecoComposite.cxx
	$(cpp_echo) $(src)RecoComposite.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(RecoComposite_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(RecoComposite_cppflags) $(RecoComposite_cxx_cppflags)  $(src)RecoComposite.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(RecoComposite_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)RecoComposite.cxx

$(bin)$(binobj)RecoComposite.o : $(RecoComposite_cxx_dependencies)
	$(cpp_echo) $(src)RecoComposite.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(RecoComposite_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(RecoComposite_cppflags) $(RecoComposite_cxx_cppflags)  $(src)RecoComposite.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)FitParams.d

$(bin)$(binobj)FitParams.d :

$(bin)$(binobj)FitParams.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)FitParams.o : $(src)FitParams.cxx
	$(cpp_echo) $(src)FitParams.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(FitParams_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(FitParams_cppflags) $(FitParams_cxx_cppflags)  $(src)FitParams.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(FitParams_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)FitParams.cxx

$(bin)$(binobj)FitParams.o : $(FitParams_cxx_dependencies)
	$(cpp_echo) $(src)FitParams.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(FitParams_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(FitParams_cppflags) $(FitParams_cxx_cppflags)  $(src)FitParams.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Resonance.d

$(bin)$(binobj)Resonance.d :

$(bin)$(binobj)Resonance.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)Resonance.o : $(src)Resonance.cxx
	$(cpp_echo) $(src)Resonance.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(Resonance_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(Resonance_cppflags) $(Resonance_cxx_cppflags)  $(src)Resonance.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(Resonance_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)Resonance.cxx

$(bin)$(binobj)Resonance.o : $(Resonance_cxx_dependencies)
	$(cpp_echo) $(src)Resonance.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(Resonance_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(Resonance_cppflags) $(Resonance_cxx_cppflags)  $(src)Resonance.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)InternalParticle.d

$(bin)$(binobj)InternalParticle.d :

$(bin)$(binobj)InternalParticle.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)InternalParticle.o : $(src)InternalParticle.cxx
	$(cpp_echo) $(src)InternalParticle.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(InternalParticle_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(InternalParticle_cppflags) $(InternalParticle_cxx_cppflags)  $(src)InternalParticle.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(InternalParticle_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)InternalParticle.cxx

$(bin)$(binobj)InternalParticle.o : $(InternalParticle_cxx_dependencies)
	$(cpp_echo) $(src)InternalParticle.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(InternalParticle_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(InternalParticle_cppflags) $(InternalParticle_cxx_cppflags)  $(src)InternalParticle.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)RootParticle.d

$(bin)$(binobj)RootParticle.d :

$(bin)$(binobj)RootParticle.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)RootParticle.o : $(src)RootParticle.cxx
	$(cpp_echo) $(src)RootParticle.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(RootParticle_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(RootParticle_cppflags) $(RootParticle_cxx_cppflags)  $(src)RootParticle.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(RootParticle_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)RootParticle.cxx

$(bin)$(binobj)RootParticle.o : $(RootParticle_cxx_dependencies)
	$(cpp_echo) $(src)RootParticle.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(RootParticle_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(RootParticle_cppflags) $(RootParticle_cxx_cppflags)  $(src)RootParticle.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)KalmanCalculator.d

$(bin)$(binobj)KalmanCalculator.d :

$(bin)$(binobj)KalmanCalculator.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)KalmanCalculator.o : $(src)KalmanCalculator.cxx
	$(cpp_echo) $(src)KalmanCalculator.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(KalmanCalculator_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(KalmanCalculator_cppflags) $(KalmanCalculator_cxx_cppflags)  $(src)KalmanCalculator.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(KalmanCalculator_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)KalmanCalculator.cxx

$(bin)$(binobj)KalmanCalculator.o : $(KalmanCalculator_cxx_dependencies)
	$(cpp_echo) $(src)KalmanCalculator.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(KalmanCalculator_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(KalmanCalculator_cppflags) $(KalmanCalculator_cxx_cppflags)  $(src)KalmanCalculator.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DecayTree.d

$(bin)$(binobj)DecayTree.d :

$(bin)$(binobj)DecayTree.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)DecayTree.o : $(src)DecayTree.cxx
	$(cpp_echo) $(src)DecayTree.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(DecayTree_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(DecayTree_cppflags) $(DecayTree_cxx_cppflags)  $(src)DecayTree.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(DecayTree_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)DecayTree.cxx

$(bin)$(binobj)DecayTree.o : $(DecayTree_cxx_dependencies)
	$(cpp_echo) $(src)DecayTree.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(DecayTree_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(DecayTree_cppflags) $(DecayTree_cxx_cppflags)  $(src)DecayTree.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Constraint.d

$(bin)$(binobj)Constraint.d :

$(bin)$(binobj)Constraint.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)Constraint.o : $(src)Constraint.cxx
	$(cpp_echo) $(src)Constraint.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(Constraint_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(Constraint_cppflags) $(Constraint_cxx_cppflags)  $(src)Constraint.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(Constraint_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)Constraint.cxx

$(bin)$(binobj)Constraint.o : $(Constraint_cxx_dependencies)
	$(cpp_echo) $(src)Constraint.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(Constraint_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(Constraint_cppflags) $(Constraint_cxx_cppflags)  $(src)Constraint.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)ParticleBase.d

$(bin)$(binobj)ParticleBase.d :

$(bin)$(binobj)ParticleBase.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)ParticleBase.o : $(src)ParticleBase.cxx
	$(cpp_echo) $(src)ParticleBase.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(ParticleBase_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(ParticleBase_cppflags) $(ParticleBase_cxx_cppflags)  $(src)ParticleBase.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(ParticleBase_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)ParticleBase.cxx

$(bin)$(binobj)ParticleBase.o : $(ParticleBase_cxx_dependencies)
	$(cpp_echo) $(src)ParticleBase.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(ParticleBase_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(ParticleBase_cppflags) $(ParticleBase_cxx_cppflags)  $(src)ParticleBase.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)HelixUtils.d

$(bin)$(binobj)HelixUtils.d :

$(bin)$(binobj)HelixUtils.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)HelixUtils.o : $(src)HelixUtils.cxx
	$(cpp_echo) $(src)HelixUtils.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(HelixUtils_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(HelixUtils_cppflags) $(HelixUtils_cxx_cppflags)  $(src)HelixUtils.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(HelixUtils_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)HelixUtils.cxx

$(bin)$(binobj)HelixUtils.o : $(HelixUtils_cxx_dependencies)
	$(cpp_echo) $(src)HelixUtils.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(HelixUtils_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(HelixUtils_cppflags) $(HelixUtils_cxx_cppflags)  $(src)HelixUtils.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)RecoTrack.d

$(bin)$(binobj)RecoTrack.d :

$(bin)$(binobj)RecoTrack.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)RecoTrack.o : $(src)RecoTrack.cxx
	$(cpp_echo) $(src)RecoTrack.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(RecoTrack_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(RecoTrack_cppflags) $(RecoTrack_cxx_cppflags)  $(src)RecoTrack.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(RecoTrack_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)RecoTrack.cxx

$(bin)$(binobj)RecoTrack.o : $(RecoTrack_cxx_dependencies)
	$(cpp_echo) $(src)RecoTrack.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(RecoTrack_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(RecoTrack_cppflags) $(RecoTrack_cxx_cppflags)  $(src)RecoTrack.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DecayTreeFitterSvc_load.d

$(bin)$(binobj)DecayTreeFitterSvc_load.d :

$(bin)$(binobj)DecayTreeFitterSvc_load.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)DecayTreeFitterSvc_load.o : $(src)components/DecayTreeFitterSvc_load.cxx
	$(cpp_echo) $(src)components/DecayTreeFitterSvc_load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(DecayTreeFitterSvc_load_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(DecayTreeFitterSvc_load_cppflags) $(DecayTreeFitterSvc_load_cxx_cppflags) -I../src/components $(src)components/DecayTreeFitterSvc_load.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(DecayTreeFitterSvc_load_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)components/DecayTreeFitterSvc_load.cxx

$(bin)$(binobj)DecayTreeFitterSvc_load.o : $(DecayTreeFitterSvc_load_cxx_dependencies)
	$(cpp_echo) $(src)components/DecayTreeFitterSvc_load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(DecayTreeFitterSvc_load_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(DecayTreeFitterSvc_load_cppflags) $(DecayTreeFitterSvc_load_cxx_cppflags) -I../src/components $(src)components/DecayTreeFitterSvc_load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DecayTreeFitterSvcclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DecayTreeFitterSvc_entries.d

$(bin)$(binobj)DecayTreeFitterSvc_entries.d :

$(bin)$(binobj)DecayTreeFitterSvc_entries.o : $(cmt_final_setup_DecayTreeFitterSvc)

$(bin)$(binobj)DecayTreeFitterSvc_entries.o : $(src)components/DecayTreeFitterSvc_entries.cxx
	$(cpp_echo) $(src)components/DecayTreeFitterSvc_entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(DecayTreeFitterSvc_entries_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(DecayTreeFitterSvc_entries_cppflags) $(DecayTreeFitterSvc_entries_cxx_cppflags) -I../src/components $(src)components/DecayTreeFitterSvc_entries.cxx
endif
endif

else
$(bin)DecayTreeFitterSvc_dependencies.make : $(DecayTreeFitterSvc_entries_cxx_dependencies)

$(bin)DecayTreeFitterSvc_dependencies.make : $(src)components/DecayTreeFitterSvc_entries.cxx

$(bin)$(binobj)DecayTreeFitterSvc_entries.o : $(DecayTreeFitterSvc_entries_cxx_dependencies)
	$(cpp_echo) $(src)components/DecayTreeFitterSvc_entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DecayTreeFitterSvc_pp_cppflags) $(lib_DecayTreeFitterSvc_pp_cppflags) $(DecayTreeFitterSvc_entries_pp_cppflags) $(use_cppflags) $(DecayTreeFitterSvc_cppflags) $(lib_DecayTreeFitterSvc_cppflags) $(DecayTreeFitterSvc_entries_cppflags) $(DecayTreeFitterSvc_entries_cxx_cppflags) -I../src/components $(src)components/DecayTreeFitterSvc_entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: DecayTreeFitterSvcclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(DecayTreeFitterSvc.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

DecayTreeFitterSvcclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library DecayTreeFitterSvc
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)DecayTreeFitterSvc$(library_suffix).a $(library_prefix)DecayTreeFitterSvc$(library_suffix).s? DecayTreeFitterSvc.stamp DecayTreeFitterSvc.shstamp
#-- end of cleanup_library ---------------
