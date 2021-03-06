#include "NeuTrackingAction.hh"

#include "G4RunManager.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"

#include <string>

NeuFlux::NeuTrackingAction::NeuTrackingAction() : NeuOutputtingComponent(),  fTrackID(0), fParentID(0), fX(0), fY(0), fZ(0), fLT(0), fGT(0), fPT(0), fVolume(0), fNextVolume(0)
{
}

NeuFlux::NeuTrackingAction::~NeuTrackingAction()
{
}

void NeuFlux::NeuTrackingAction::PreUserTrackingAction(const G4Track* theTrack)
{
	fTrackID = theTrack->GetTrackID();
	fParentID = theTrack->GetParentID();
	fX = theTrack->GetPosition().x();
	fY = theTrack->GetPosition().y();
	fZ = theTrack->GetPosition().z();
	fLT = theTrack->GetLocalTime();
	fGT = theTrack->GetGlobalTime();
	fPT = theTrack->GetProperTime();


	std::string name = theTrack->GetVolume()->GetName();
	if(name == "World")
		fVolume = 1;
	else if(name == "Rock")
		fVolume = 2;
	else if(name == "Concrete")
		fVolume = 3;
	else if (name == "Detector")
		fVolume = 4;

	std::string nextname = theTrack->GetNextVolume()->GetName();
	if(nextname == "World")
		fNextVolume = 1;
	else if(nextname == "Rock")
		fNextVolume = 2;
	else if(nextname == "Concrete")
		fNextVolume = 3;
	else if (nextname == "Detector")
		fNextVolume = 4;

	NeuFlux::NeuRootOutput::GetInstance()->FillTree("NeuTrackingAction");
}

void NeuFlux::NeuTrackingAction::OnNewFileCreate()
{
	NeuFlux::NeuRootOutput::GetInstance()->AddTree("NeuTrackingAction");
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," fTrackID", &fTrackID );              
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," fParentID", &fParentID);               
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," fX", &fX       );        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," fY", &fY       );        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," fZ", &fZ       );        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," fLT", &fLT      );         
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," fGT", &fGT      );         
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," fPT", &fPT      );
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," fVolume", &fVolume      );
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," fNextVolume", &fNextVolume      );         
}


