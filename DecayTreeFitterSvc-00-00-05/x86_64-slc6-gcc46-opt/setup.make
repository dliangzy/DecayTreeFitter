----------> uses
# use BesPolicy BesPolicy-01-* 
#   use BesCxxPolicy BesCxxPolicy-* 
#     use GaudiPolicy v*  (no_version_directory)
#       use LCG_Settings *  (no_version_directory)
#       use Python * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.7.3)
#         use LCG_Configuration v*  (no_version_directory)
#         use LCG_Settings v*  (no_version_directory)
#       use tcmalloc * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=1.7p3)
#         use LCG_Configuration v*  (no_version_directory)
#         use LCG_Settings v*  (no_version_directory)
#         use libunwind v* LCG_Interfaces (no_version_directory) (native_version=5c2cade)
#           use LCG_Configuration v*  (no_version_directory)
#           use LCG_Settings v*  (no_version_directory)
#   use BesFortranPolicy BesFortranPolicy-* 
#     use LCG_Settings v*  (no_version_directory)
# use GaudiInterface GaudiInterface-01-* External
#   use GaudiKernel *  (no_version_directory)
#     use GaudiPolicy *  (no_version_directory)
#     use Reflex * LCG_Interfaces (no_version_directory)
#       use LCG_Configuration v*  (no_version_directory)
#         use LCG_Platforms *  (no_version_directory)
#       use LCG_Settings v*  (no_version_directory)
#       use ROOT v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=5.34.09)
#     use Boost * LCG_Interfaces (no_version_directory) (native_version=1.50.0_python2.7)
#       use LCG_Configuration v*  (no_version_directory)
#       use LCG_Settings v*  (no_version_directory)
#       use Python v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.7.3)
#   use GaudiSvc *  (no_version_directory)
#     use GaudiKernel *  (no_version_directory)
#     use CLHEP * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.0.4.5)
#     use Boost * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=1.50.0_python2.7)
#     use ROOT * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=5.34.09)
# use BesCLHEP BesCLHEP-* External
#   use CLHEP v* LCG_Interfaces (no_version_directory) (native_version=2.0.4.5)
#     use LCG_Configuration v*  (no_version_directory)
#     use LCG_Settings v*  (no_version_directory)
#   use HepMC * LCG_Interfaces (no_version_directory) (native_version=2.06.08)
#     use LCG_Configuration v*  (no_version_directory)
#     use LCG_Settings v*  (no_version_directory)
#   use HepPDT * LCG_Interfaces (no_version_directory) (native_version=2.06.01)
#     use LCG_Configuration v*  (no_version_directory)
#     use LCG_Settings v*  (no_version_directory)
#   use BesExternalArea BesExternalArea-* External
# use VertexFit VertexFit-* Analysis
#   use BesPolicy BesPolicy-01-* 
#   use GaudiInterface GaudiInterface-* External
#   use BesCLHEP BesCLHEP-* External
#   use MYSQL MYSQL-* External
#     use mysql * LCG_Interfaces (no_version_directory) (native_version=5.5.14)
#       use LCG_Configuration v*  (no_version_directory)
#       use LCG_Settings v*  (no_version_directory)
#   use DstEvent DstEvent-* Event
#     use BesPolicy BesPolicy-* 
#     use GaudiInterface GaudiInterface-* External
#     use BesCLHEP BesCLHEP-* External
#     use EventModel EventModel-* Event
#       use BesPolicy BesPolicy-* 
#       use GaudiInterface GaudiInterface-* External
#   use MdcRecEvent MdcRecEvent-* Mdc
#     use BesPolicy BesPolicy-01-* 
#     use GaudiInterface GaudiInterface-01-* External
#     use MdcGeomSvc MdcGeomSvc-* Mdc
#       use BesPolicy BesPolicy-01-* 
#       use GaudiInterface GaudiInterface-* External
#       use calibUtil * Calibration
#         use GaudiInterface GaudiInterface-01-* External
#         use facilities * Calibration
#           use BesPolicy BesPolicy-* 
#         use xmlBase * Calibration
#           use BesPolicy * 
#           use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#           use facilities * Calibration
#         use rdbModel * Calibration
#           use BesPolicy * 
#           use facilities * Calibration
#           use xmlBase * Calibration
#           use MYSQL * External
#         use BesROOT BesROOT-00-* External
#           use CASTOR v* LCG_Interfaces (no_version_directory) (native_version=2.1.13-6)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#           use ROOT v* LCG_Interfaces (no_version_directory) (native_version=5.34.09)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#             use GCCXML v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=0.9.0_20120309p2)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#             use Python v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.7.3)
#             use xrootd v* LCG_Interfaces (no_version_directory) (native_version=3.2.7)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#         use DatabaseSvc DatabaseSvc-* Database
#           use BesPolicy BesPolicy-* 
#           use GaudiInterface GaudiInterface-* External
#           use mysql * LCG_Interfaces (no_version_directory) (native_version=5.5.14)
#           use sqlite * LCG_Interfaces (no_version_directory) (native_version=3070900)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#           use BesROOT * External
#       use CalibData * Calibration
#         use facilities facilities-* Calibration
#         use GaudiInterface * External
#         use BesROOT BesROOT-00-* External
#       use EventModel EventModel-* Event
#     use RelTable RelTable-* Event
#       use BesPolicy BesPolicy-01-* 
#       use GaudiInterface GaudiInterface-01-* External
#     use EventModel EventModel-* Event
#     use Identifier Identifier-* DetectorDescription
#       use BesPolicy BesPolicy-* 
#     use DstEvent DstEvent-* Event
#   use EmcRecEventModel EmcRecEventModel-* Emc
#     use BesPolicy BesPolicy-* 
#     use Identifier Identifier-* DetectorDescription
#     use BesCLHEP BesCLHEP-* External
#     use EventModel EventModel-* Event
#     use DstEvent DstEvent-* Event
#     use EmcRecGeoSvc EmcRecGeoSvc-* Emc
#       use BesPolicy BesPolicy-* 
#       use Identifier Identifier-* DetectorDescription
#       use ROOTGeo ROOTGeo-* DetectorDescription
#         use BesPolicy BesPolicy-01-* 
#         use GaudiInterface GaudiInterface-* External
#         use BesCLHEP BesCLHEP-* External
#         use BesROOT BesROOT-* External
#         use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#         use GdmlToRoot GdmlToRoot-* External
#           use BesExternalArea BesExternalArea-* External
#           use BesROOT BesROOT-* External
#         use GdmlManagement GdmlManagement-* DetectorDescription
#           use BesExternalArea BesExternalArea-* External
#       use BesCLHEP BesCLHEP-* External
#       use GaudiInterface GaudiInterface-* External
#   use MagneticField MagneticField-* 
#     use BesPolicy BesPolicy-01-* 
#     use GaudiInterface GaudiInterface-* External
#     use BesCLHEP * External
#     use BesROOT * External
#     use EventModel EventModel-* Event
#     use rdbModel * Calibration
#     use DatabaseSvc * Database
#     use BesTimerSvc BesTimerSvc-* Utilities
#       use BesPolicy BesPolicy-* 
#       use GaudiInterface GaudiInterface-* External
#   use EventModel EventModel-* Event
#   use EvtRecEvent EvtRecEvent-* Event
#     use BesPolicy BesPolicy-* 
#     use GaudiInterface GaudiInterface-* External
#     use BesCLHEP BesCLHEP-* External
#     use EventModel EventModel-* Event
#     use EvTimeEvent EvTimeEvent-* Event
#       use BesPolicy BesPolicy-01-* 
#       use GaudiInterface GaudiInterface-01-* External
#       use BesCLHEP BesCLHEP-* External
#       use MdcGeomSvc MdcGeomSvc-* Mdc
#       use RelTable RelTable-* Event
#       use EventModel EventModel-* Event
#       use Identifier Identifier-* DetectorDescription
#     use MdcRecEvent MdcRecEvent-* Mdc
#     use TofRecEvent TofRecEvent-* Tof
#       use BesPolicy BesPolicy-01-* 
#       use GaudiInterface GaudiInterface-01-* External
#       use Identifier Identifier-* DetectorDescription
#       use EventModel EventModel-* Event
#       use DstEvent * Event
#     use EmcRecEventModel EmcRecEventModel-* Emc
#     use MucRecEvent MucRecEvent-* Muc
#       use BesPolicy BesPolicy-01-* 
#       use GaudiInterface GaudiInterface-01-* External
#       use Identifier Identifier-* DetectorDescription
#       use EventModel EventModel-* Event
#       use ExtEvent ExtEvent-* Event
#         use BesPolicy BesPolicy-01-* 
#         use GaudiInterface GaudiInterface-01-* External
#         use BesCLHEP BesCLHEP-* External
#         use EventModel EventModel-* Event
#         use DstEvent DstEvent-* Event
#       use MucGeomSvc MucGeomSvc-* Muc
#         use BesPolicy BesPolicy-01-* 
#         use GaudiInterface GaudiInterface-* External
#         use Identifier Identifier-* DetectorDescription
#         use ROOTGeo ROOTGeo-* DetectorDescription
#         use BesCLHEP BesCLHEP-* External
#         use BesROOT BesROOT-* External
#         use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#         use GdmlToRoot GdmlToRoot-* External
#         use G4Geo G4Geo-* DetectorDescription
#           use BesPolicy BesPolicy-01-* 
#           use GaudiInterface GaudiInterface-* External
#           use BesCLHEP BesCLHEP-* External
#           use BesGeant4 BesGeant4-* External
#             use BesExternalArea BesExternalArea-00-* External
#             use BesCLHEP BesCLHEP-00-* External
#           use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#           use GdmlToG4 GdmlToG4-* External
#             use BesExternalArea BesExternalArea-* External
#             use BesGeant4 BesGeant4-* External
#             use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#           use GdmlManagement GdmlManagement-* DetectorDescription
#           use Identifier Identifier-* DetectorDescription
#           use SimUtil SimUtil-* Simulation/BOOST
#             use BesPolicy BesPolicy-01-* 
#             use BesGeant4 BesGeant4-00-* External
#       use DstEvent DstEvent-* Event
#     use ExtEvent ExtEvent-* Event
#     use DstEvent DstEvent-* Event
#   use DatabaseSvc DatabaseSvc-* Database
#
# Selection :
use CMT v1r25 (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib)
use BesExternalArea BesExternalArea-00-00-22 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use GdmlManagement GdmlManagement-00-00-43 DetectorDescription (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use LCG_Platforms v1  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use LCG_Configuration v1  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use LCG_Settings v1  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use sqlite v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use CASTOR v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use XercesC v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use mysql v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use MYSQL MYSQL-00-00-09 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use HepPDT v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use HepMC v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use CLHEP v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use BesCLHEP BesCLHEP-00-00-11 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use BesGeant4 BesGeant4-00-00-11 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use GdmlToG4 GdmlToG4-00-00-11 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use xrootd v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use GCCXML v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a) (no_auto_imports)
use BesFortranPolicy BesFortranPolicy-00-01-03  (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use libunwind v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a) (no_auto_imports)
use tcmalloc v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a) (no_auto_imports)
use Python v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a) (no_auto_imports)
use Boost v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use ROOT v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use BesROOT BesROOT-00-00-08 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use GdmlToRoot GdmlToRoot-00-00-14 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use Reflex v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use GaudiPolicy v12r7  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/gaudi/GAUDI_v23r9)
use GaudiKernel v28r8  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/gaudi/GAUDI_v23r9)
use GaudiSvc v19r4  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/gaudi/GAUDI_v23r9)
use GaudiInterface GaudiInterface-01-03-07 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use BesCxxPolicy BesCxxPolicy-00-01-01  (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use BesPolicy BesPolicy-01-05-05  (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use SimUtil SimUtil-00-00-37 Simulation/BOOST (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use BesTimerSvc BesTimerSvc-00-00-12 Utilities (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use ROOTGeo ROOTGeo-00-00-15 DetectorDescription (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use Identifier Identifier-00-02-17 DetectorDescription (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use G4Geo G4Geo-00-00-13 DetectorDescription (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use MucGeomSvc MucGeomSvc-00-02-25 Muc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EmcRecGeoSvc EmcRecGeoSvc-01-01-07 Emc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use RelTable RelTable-00-00-02 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use DatabaseSvc DatabaseSvc-00-00-26 Database (/home/lliu/boss/Workarea-7.0.5)
use facilities facilities-00-00-04 Calibration (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use CalibData CalibData-00-01-22 Calibration (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use xmlBase xmlBase-00-00-03 Calibration (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use rdbModel rdbModel-00-01-01 Calibration (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use calibUtil calibUtil-00-00-43 Calibration (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EventModel EventModel-01-05-34 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use MagneticField MagneticField-00-02-03  (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use MdcGeomSvc MdcGeomSvc-00-01-37 Mdc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EvTimeEvent EvTimeEvent-00-00-08 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use DstEvent DstEvent-00-02-51 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use ExtEvent ExtEvent-00-00-13 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use MucRecEvent MucRecEvent-00-02-52 Muc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use TofRecEvent TofRecEvent-00-02-14 Tof (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EmcRecEventModel EmcRecEventModel-01-01-18 Emc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use MdcRecEvent MdcRecEvent-00-05-14 Mdc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EvtRecEvent EvtRecEvent-00-02-03 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use VertexFit VertexFit-01-02-86 Analysis (/home/lliu/boss/Workarea-7.0.5)
----------> tags
CMTv1 (from CMTVERSION)
CMTr25 (from CMTVERSION)
CMTp0 (from CMTVERSION)
Linux (from uname) package [CMT LCG_Platforms BesPolicy] implies [Unix host-linux]
x86_64-linux (from HOSTTYPE)
x86_64-slc6-gcc46-opt (from CMTCONFIG) package [LCG_Platforms] implies [target-x86_64 target-slc6 target-gcc46 target-opt]
boss_no_config (from PROJECT) excludes [boss_config]
boss_root (from PROJECT) excludes [boss_no_root]
boss_cleanup (from PROJECT) excludes [boss_no_cleanup]
boss_scripts (from PROJECT) excludes [boss_no_scripts]
boss_prototypes (from PROJECT) excludes [boss_no_prototypes]
boss_with_installarea (from PROJECT) excludes [boss_without_installarea]
boss_with_version_directory (from PROJECT) excludes [boss_without_version_directory]
boss (from PROJECT)
BOSS_no_config (from PROJECT) excludes [BOSS_config]
BOSS_root (from PROJECT) excludes [BOSS_no_root]
BOSS_cleanup (from PROJECT) excludes [BOSS_no_cleanup]
BOSS_scripts (from PROJECT) excludes [BOSS_no_scripts]
BOSS_no_prototypes (from PROJECT) excludes [BOSS_prototypes]
BOSS_with_installarea (from PROJECT) excludes [BOSS_without_installarea]
BOSS_with_version_directory (from PROJECT) excludes [BOSS_without_version_directory]
GAUDI_no_config (from PROJECT) excludes [GAUDI_config]
GAUDI_root (from PROJECT) excludes [GAUDI_no_root]
GAUDI_cleanup (from PROJECT) excludes [GAUDI_no_cleanup]
GAUDI_scripts (from PROJECT) excludes [GAUDI_no_scripts]
GAUDI_prototypes (from PROJECT) excludes [GAUDI_no_prototypes]
GAUDI_with_installarea (from PROJECT) excludes [GAUDI_without_installarea]
GAUDI_without_version_directory (from PROJECT) excludes [GAUDI_with_version_directory]
LCGCMT_no_config (from PROJECT) excludes [LCGCMT_config]
LCGCMT_no_root (from PROJECT) excludes [LCGCMT_root]
LCGCMT_cleanup (from PROJECT) excludes [LCGCMT_no_cleanup]
LCGCMT_scripts (from PROJECT) excludes [LCGCMT_no_scripts]
LCGCMT_prototypes (from PROJECT) excludes [LCGCMT_no_prototypes]
LCGCMT_without_installarea (from PROJECT) excludes [LCGCMT_with_installarea]
LCGCMT_with_version_directory (from PROJECT) excludes [LCGCMT_without_version_directory]
x86_64 (from package CMT) package [LCG_Platforms] implies [host-x86_64]
slc78 (from package CMT)
gcc463 (from package CMT)
Unix (from package CMT) package [LCG_Platforms] implies [host-unix] excludes [WIN32 Win32]
c_native_dependencies (from package CMT) activated GaudiPolicy
cpp_native_dependencies (from package CMT) activated GaudiPolicy
target-unix (from package LCG_Settings) activated LCG_Platforms
target-x86_64 (from package LCG_Settings) activated LCG_Platforms
target-gcc46 (from package LCG_Settings) package [LCG_Platforms] implies [target-gcc4 target-lcg-compiler lcg-compiler] activated LCG_Platforms
host-x86_64 (from package LCG_Settings) activated LCG_Platforms
target-slc (from package LCG_Settings) package [LCG_Platforms] implies [target-linux] activated LCG_Platforms
target-gcc (from package LCG_Settings) activated LCG_Platforms
target-gcc4 (from package LCG_Settings) package [LCG_Platforms] implies [target-gcc] activated LCG_Platforms
target-lcg-compiler (from package LCG_Settings) activated LCG_Platforms
host-linux (from package LCG_Platforms) package [LCG_Platforms] implies [host-unix]
host-unix (from package LCG_Platforms)
target-opt (from package LCG_Platforms)
target-slc6 (from package LCG_Platforms) package [LCG_Platforms] implies [target-slc]
target-linux (from package LCG_Platforms) package [LCG_Platforms] implies [target-unix]
lcg-compiler (from package LCG_Platforms)
ROOT_GE_5_15 (from package LCG_Configuration)
ROOT_GE_5_19 (from package LCG_Configuration)
HasAthenaRunTime (from package BesPolicy)
ROOTBasicLibs (from package BesROOT)
----------> CMTPATH
# Add path /home/lliu/boss/Workarea-7.0.5 from initialization
# Add path /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5 from initialization
# Add path /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/gaudi/GAUDI_v23r9 from initialization
# Add path /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a from initialization
