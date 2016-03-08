#define MySelector_cxx

// The class definition in MySelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("MySelector.C")
// Root > T->Process("MySelector.C","some options")
// Root > T->Process("MySelector.C+")



#include "MySelector.h"
#include <TH2.h>
#include <TStyle.h>
#include <TLorentzVector.h>
#include "MyJet.h"

bool sortFunct( MyJet a, MyJet b) { return ( a.Pt() > b.Pt() ); }

void MySelector::BuildEvent() 
{		//here I prepare vectors of reco and gen jets which I will later use
	int JetsNum = p4_;
	int GenJetsNum = gen_p4_;

   Jets.clear();
   for (int i = 0; i < JetsNum ; ++i)
	{
      MyJet jet(p4_fCoordinates_fPt[i], p4_fCoordinates_fEta[i], p4_fCoordinates_fPhi[i], p4_fCoordinates_fE[i]);
      Jets.push_back(jet);
   }
   GenJets.clear();
   for (int i = 0; i < GenJetsNum ; ++i) 
	{
      MyJet genjet( gen_p4_fCoordinates_fPt[i], gen_p4_fCoordinates_fEta[i], gen_p4_fCoordinates_fPhi[i], gen_p4_fCoordinates_fE[i]);
      GenJets.push_back(genjet);
   }
}


void MySelector::MakeWeight() 
{
//	instead of reading PU weight from .root file i print it once out and save it an array. Opening it for each event takes too long. However the code below does it by reading it from a .root file.

//	TH1F* fPuReweighting_histoname;	
//	TFile* file = new TFile ("PUscale.root");
//	fPuReweighting_histoname = (TH1F*) file -> Get("pileup");
//	unsigned    bin = 0;
//	for ( int i = 0; i < 61; i++)
//	{
//		bin = fPuReweighting_histoname -> FindBin(i);
//		std::cout << "pu = " << i << "scale factor = " << fPuReweighting_histoname -> GetBinContent(bin) << std::endl;
//	}
//	file -> Close();	

// full data 69000mb
	double weight_factor [] = { 1.51823, 1.4103, 0.395114, 0.170763, 0.108002, 0.0974589, 0.196369, 0.77833, 1.94869, 2.93908, 3.52498, 3.54391, 2.93381, 1.95475, 1.04688, 0.458862, 0.176078, 0.0739666, 0.0426934, 0.0273048, 0.0146278, 0.00594568, 0.00181273, 0.000436231, 0.000100473, 3.30495e-05, 1.63482e-05, 9.09873e-06, 5.00262e-06, 2.6689e-06, 1.36094e-06, 6.66538e-07, 3.13715e-07, 1.4255e-07, 6.11696e-08, 2.53426e-08, 1.00997e-08, 3.74358e-09, 1.31293e-09, 4.51706e-10, 1.40877e-10, 4.26562e-11, 1.17347e-11, 2.97937e-12, 7.09849e-13, 1.67401e-13, 3.38703e-14, 6.75834e-15, 1.55108e-15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 
// full data 80000mb
//	double weight_factor [] = { 0.856693, 0.975434, 0.381975, 0.117455, 0.0771141, 0.0529427, 0.0551823, 0.104707, 0.364054, 0.990113, 1.67715, 2.2458, 2.62312, 2.67712, 2.35442, 1.76176, 1.11659, 0.605681, 0.289489, 0.132829, 0.0710691, 0.0488042, 0.03573, 0.0231602, 0.0123169, 0.0053132, 0.00187149, 0.000571177, 0.000180117, 7.73981e-05, 4.56155e-05, 3.02356e-05, 2.01786e-05, 1.32545e-05, 8.34432e-06, 5.14442e-06, 3.09431e-06, 1.75569e-06, 9.55961e-07, 5.17878e-07, 2.57936e-07, 1.26496e-07, 5.71625e-08, 2.41787e-08, 9.73292e-09, 3.93348e-09, 1.3826e-09, 4.94281e-10, 1.58715e-10, 5.34017e-11, 1.43915e-11, 4.38993e-12, 1.28784e-12, 3.21072e-13, 8.69235e-14, 2.53129e-14, 6.44327e-15, 0, 0, 0, 0 }; 

	std::string filename;

	filename = std::string(fChain->GetDirectory()->GetPath());

	weight = Weight(filename) * weight_factor[npuIT];
}


void MySelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

	TotalEvents = 0;
}

void MySelector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

	h_PU = new TH1F( "PileUp" , "PU distribution" , 60 , 0 , 60 );
	h_PU -> SetXTitle( "PU" );
	h_PU -> Sumw2();
	histograms.push_back(h_PU);

}

Bool_t MySelector::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either MySelector::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
	
	++TotalEvents;

	GetEntry( entry );

	BuildEvent();

	if( TotalEvents%100000 == 0 )
	{
		std::cout << "			Analyzing event #" << TotalEvents << std::endl;
	}

	h_PU -> Fill( npuIT, 1 );

   return kTRUE;
}

void MySelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void MySelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

	std::cout <<"			Analyzed events #" <<  TotalEvents << std::endl;

	TFile *fprim = new TFile("PU.root","RECREATE"); ;
	fprim->cd();

	h_PU -> Write();

	fprim -> Close();
}


double Weight( std::string filename )
{
	if ( filename.std::string::find("Pt_5to10") != std::string::npos )		return 6.102e+10/3470511;
	if ( filename.std::string::find("Pt_10to15") != std::string::npos )		return 5.888e+09/3449170;
	if ( filename.std::string::find("Pt_15to30") != std::string::npos )		return 1.837e+09/4942232;
	if ( filename.std::string::find("Pt_30to50") != std::string::npos )		return 1.409e+08/4957245;
	if ( filename.std::string::find("Pt_50to80") != std::string::npos )		return 1.92e+07/4978425;
	if ( filename.std::string::find("Pt_80to120") != std::string::npos ) 	return 2.763e+06/3424782;
	if ( filename.std::string::find("Pt_120to170") != std::string::npos )	return 4.711e+05/3452896;
	if ( filename.std::string::find("Pt_170to300") != std::string::npos )	return 1.173e+05/3314544;
	if ( filename.std::string::find("Pt_300to470") != std::string::npos )	return 7823./2933611;
	if ( filename.std::string::find("Pt_470to600") != std::string::npos )	return 648.2/1936832;
	if ( filename.std::string::find("Pt_600to800") != std::string::npos )	return 186.9/199880;
	if ( filename.std::string::find("Pt_800to1000") != std::string::npos )	return 32.29/1937216;
	if ( filename.std::string::find("Pt_1000to1400") != std::string::npos )	return 9.418/1437216;
	if ( filename.std::string::find("Pt_1400to1800") != std::string::npos )	return 0.8426/197959;
	if ( filename.std::string::find("Pt_1800to2400") != std::string::npos )	return 0.1149/193608;
	if ( filename.std::string::find("Pt_2400to3200") != std::string::npos )	return 0.00683/194456; 
	if ( filename.std::string::find("Pt_3200toInf") != std::string::npos )	return 0.0001654/192944; 
	else 
	{
		std::cout << "failed to get pt_hat weight" << std::endl;
		return 1e+12;
	}
}
