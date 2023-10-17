//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************

#include "OutputRunAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "HepMCG4Pythia8Interface.hh"
#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorMessenger.hh"
#include "G4GeneralParticleSource.hh"

// #include "DataStorage.hh"

#include "G4RunManager.hh"

#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction()
	: G4VUserPrimaryGeneratorAction()
{
	// default generator is particle gun.
	fCurrentGenerator = fParticleGun = new G4ParticleGun();
	//fCurrentGenerator= fParticleGun= new G4GeneralParticleSource();
	fCurrentGeneratorName = "particleGun";
	// fHepmcAscii = new HepMCG4AsciiReader();
	//#ifdef G4LIB_USE_PYTHIA
	fPythiaGen = new HepMCG4Pythia8Interface();
	//#else
	//  fPythiaGen= 0;
	//#endif

	fParticleGun_ = new G4ParticleGun(1);

	fGentypeMap["particleGun"] = fParticleGun;
	// fGentypeMap["hepmcAscii"] = fHepmcAscii;
	fGentypeMap["pythia8"] = fPythiaGen;

	fMessenger = new PrimaryGeneratorMessenger(this);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fMessenger;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
	// auto runAction = (OutputRunAction *)G4RunManager::GetRunManager()->GetUserRunAction();
	if (fCurrentGenerator)
	{
		//* doublePionGun
		if (fCurrentGeneratorName == "particleGun")
		{
			fParticleGun_ = new G4ParticleGun(1);

			/// choose the principal direction
			double phi    = 2*(0.5 - G4UniformRand())*TMath::Pi();
			double eta    = 2*(0.5 - G4UniformRand())*2.5;
			double pt     =   (20 + 30 * G4UniformRand())*GeV;
			double px     = pt * cos(phi);
			double py     = pt * sin(phi);
			double pz     = pt * sinh(eta);
			double shoot_first = (G4UniformRand() > 0.25);

			if (shoot_first)
			{
				/// shoot the primary particle
				fParticleGun_->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("e-"));
				fParticleGun_->SetParticleMomentum(G4ThreeVector(px, py, pz));
				fParticleGun_->GeneratePrimaryVertex(anEvent);
			}

			/// uniformly sample the number of additional particles to shoot from 0, 1, 2, 3
			int n_add_particles = floor(4 * G4UniformRand());
			if (n_add_particles == 0 && !shoot_first) n_add_particles = 1;

			/// shoot the additional particles
			for(int i = 0; i < n_add_particles; i++)
			{
				double sign_dphi = (G4UniformRand() > 0.5) ? 1.0 : -1.0;
				double sign_deta = (G4UniformRand() > 0.5) ? 1.0 : -1.0;

				/// choose the direction of the additional particle
				double dphi_cell = 2 * TMath::Pi() / 256;
				double deta_cell = 2 * 3.0 / 256;
				double dphi    = sign_dphi*G4RandGauss::shoot(4*dphi_cell, dphi_cell);
				double deta    = sign_deta*G4RandGauss::shoot(4*deta_cell, deta_cell);
				double pt0     = (5 + 20 * G4UniformRand())*GeV;
				double phi0    = phi + dphi;
				while(abs(phi0) > TMath::Pi())
				{
					if(phi0 < 0)   phi0 += TMath::Pi();
					else phi0 -= TMath::Pi();
				}
				double eta0    = eta + deta;
				double px0     = pt0 * cos(phi0);
				double py0     = pt0 * sin(phi0);
				double pz0     = pt0 * sinh(eta0);

				fParticleGun_->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("gamma"));

				/// shoot it
				fParticleGun_->SetParticleMomentum(G4ThreeVector(px0, py0, pz0));
				fParticleGun_->GeneratePrimaryVertex(anEvent);
			}
		}
		//* doublePionGun end
		//* pythia8
		else if (fCurrentGeneratorName == "pythia8")
		{
			fGentypeMap["pythia8"]->GeneratePrimaryVertex(anEvent);
		}
		//* Pythia8 end
	}
	else
		G4Exception("PrimaryGeneratorAction::GeneratePrimaries",
					"InvalidSetup", FatalException,
					"Generator is not instanciated.");
}
