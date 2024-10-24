export CURRENTDIR=$(pwd)
echo "Setting up GEANT4"
source /cvmfs/sft.cern.ch/lcg/releases/LCG_104/Geant4/11.1.2/x86_64-el9-gcc12-dbg/Geant4-env.sh
cd /cvmfs/sft.cern.ch/lcg/releases/LCG_104/Geant4/11.1.2/x86_64-el9-gcc12-dbg/share/Geant4/geant4make/
echo "Setting up Geant4make"
source /cvmfs/sft.cern.ch/lcg/releases/LCG_104/Geant4/11.1.2/x86_64-el9-gcc12-dbg/share/Geant4/geant4make/geant4make.sh
echo "Setting up ROOT"
source /cvmfs/sft.cern.ch/lcg/releases/LCG_104/ROOT/6.28.04/x86_64-el9-gcc12-dbg/ROOT-env.sh
echo "Setting up HepMC"
source /cvmfs/sft.cern.ch/lcg/releases/LCG_104/HepMC/2.06.11/x86_64-el9-gcc12-dbg/HepMC-env.sh
echo "Setting up jsoncpp"
source /cvmfs/sft.cern.ch/lcg/releases/LCG_104/jsoncpp/1.9.3/x86_64-el9-gcc12-dbg/jsoncpp-env.sh
echo "Setting up CMake"
source /cvmfs/sft.cern.ch/lcg/releases/LCG_104/CMake/3.26.2/x86_64-el9-gcc12-dbg/CMake-env.sh
echo "Setting up cmaketools"
source /cvmfs/sft.cern.ch/lcg/releases/LCG_104/cmaketools/1.8/x86_64-el9-gcc12-dbg/cmaketools-env.sh
echo "Setting up Pythia8"
source /cvmfs/sft.cern.ch/lcg/releases/LCG_104/MCGenerators/pythia8/309/x86_64-el9-gcc12-dbg/pythia8env-genser.sh
export PYTHIA8_HOME=/cvmfs/sft.cern.ch/lcg/releases/LCG_104/MCGenerators/pythia8/309/x86_64-el9-gcc12-dbg
export PYTHIA8DATA=$PYTHIA8_HOME/share/Pythia8/xmldoc
echo "Setting up FastJet"
source /cvmfs/sft.cern.ch/lcg/releases/LCG_104/fastjet/3.4.1/x86_64-el9-gcc12-dbg/fastjet-env.sh
cd $CURRENTDIR
