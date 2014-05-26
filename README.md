wsu-wtojpsids-analysis
======================

#WSU W to J/Psi+Ds analysis code repository

##Current checkout (including PAT)

cmsrel CMSSW_5_3_18
cd CMSSW_5_3_18/src
cmesnv
###Core (PAT) packages
```git cms-addpkg PhysicsTools/PatAlgos

git cms-addpkg CommonTools/Utils

git cms-addpkg PhysicsTools/Configuration

git cms-addpkg PhysicsTools/PatExamples

git cms-addpkg PhysicsTools/PatUtils

git cms-addpkg PhysicsTools/SelectorUtils

git cms-addpkg PhysicsTools/UtilAlgos

git cms-addpkg RecoBTag/SoftLepton

git cms-addpkg RecoMET/METFilters

git cms-merge-topic -u cms-analysis-tools:5_3_13-newJetFlavour

git cms-merge-topic -u cms-analysis-tools:5_3_13-updatedPATConfigs

git cms-merge-topic -u cms-analysis-tools:5_3_16_patch1-testNewTau```


###Core (generation) packages
```git cms-addpkg GeneratorInterface/ExternalDecays

cp /afs/cern.ch/user/s/sturdy/work/public/WSUAnalysis/W*.dec $CMSSW_BASE/src/GeneratorInterface/ExternalDecays/data/```

###Analysis code
```git clone git@github.com:jsturdy/wsu-wtojpsids-analysis.git```


