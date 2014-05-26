wsu-wtojpsids-analysis
======================

#WSU W to J/Psi+Ds analysis code repository

##Current checkout (including PAT)

cmsrel CMSSW_5_3_18
cd CMSSW_5_3_18/src
cmesnv
###Core (PAT) packages
'''python
git cms-addpkg PhysicsTools/PatAlgos
'''
'''python
git cms-addpkg CommonTools/Utils
'''
'''python
git cms-addpkg PhysicsTools/Configuration
'''
'''python
git cms-addpkg PhysicsTools/PatExamples
'''
'''python
git cms-addpkg PhysicsTools/PatUtils
'''
'''python
git cms-addpkg PhysicsTools/SelectorUtils
'''
'''python
git cms-addpkg PhysicsTools/UtilAlgos
'''
'''python
git cms-addpkg RecoBTag/SoftLepton
'''
'''python
git cms-addpkg RecoMET/METFilters
'''
'''python
git cms-merge-topic -u cms-analysis-tools:5_3_13-newJetFlavour
'''
'''python
git cms-merge-topic -u cms-analysis-tools:5_3_13-updatedPATConfigs
'''
'''python
git cms-merge-topic -u cms-analysis-tools:5_3_16_patch1-testNewTau
'''

###Core (generation) packages
'''
git cms-addpkg GeneratorInterface/ExternalDecays
'''
'''
cp /afs/cern.ch/user/s/sturdy/work/public/WSUAnalysis/W*.dec $CMSSW_BASE/src/GeneratorInterface/ExternalDecays/data/
'''

###Analysis code
'''
git clone git@github.com:jsturdy/wsu-wtojpsids-analysis.git
'''

