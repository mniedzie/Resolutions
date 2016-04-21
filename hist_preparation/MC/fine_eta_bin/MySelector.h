//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug 13 16:05:52 2015 by ROOT version 5.34/32
// from TTree t/t
// found on file: /pnfs/desy.de/cms/tier2/store/user/mniedzie/Spring15_QCD_Pt-binned/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/JERmcSpring15/150810_142114/0000/output_mc_1.root
//////////////////////////////////////////////////////////

#ifndef MySelector_h
#define MySelector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <TH1F.h>
#include <TH2F.h>
#include <TMath.h>


#include "MyJet.h"


// Header file for the classes stored in the TTree if any.
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxp4 = 164;
   const Int_t kMaxgen_p4 = 164;

	double Weight( std::string filename );

class MySelector : public TSelector {
public :

   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   TTree          *fEvent;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types

   Float_t         weight;
   Float_t         pthat;
   Int_t           npuIT;
	Float_t         rho;

   Int_t           p4_;
   Float_t         p4_fCoordinates_fPt[kMaxp4];   //[p4_]
   Float_t         p4_fCoordinates_fEta[kMaxp4];   //[p4_]
   Float_t         p4_fCoordinates_fPhi[kMaxp4];   //[p4_]
   Float_t         p4_fCoordinates_fE[kMaxp4];   //[p4_]
   Int_t           gen_p4_;
   Float_t         gen_p4_fCoordinates_fPt[kMaxgen_p4];   //[gen_p4_]
   Float_t         gen_p4_fCoordinates_fEta[kMaxgen_p4];   //[gen_p4_]
   Float_t         gen_p4_fCoordinates_fPhi[kMaxgen_p4];   //[gen_p4_]
   Float_t         gen_p4_fCoordinates_fE[kMaxgen_p4];   //[gen_p4_]

   // List of branches
   TBranch        *b_weight;   //!
   TBranch        *b_pthat;   //!
   TBranch        *b_npuIT;   //!
	TBranch        *b_rho;

   TBranch        *b_p4_;   //!
   TBranch        *b_p4_fCoordinates_fPt;   //!
   TBranch        *b_p4_fCoordinates_fEta;   //!
   TBranch        *b_p4_fCoordinates_fPhi;   //!
   TBranch        *b_p4_fCoordinates_fE;   //!
   TBranch        *b_gen_p4_;   //!
   TBranch        *b_gen_p4_fCoordinates_fPt;   //!
   TBranch        *b_gen_p4_fCoordinates_fEta;   //!
   TBranch        *b_gen_p4_fCoordinates_fPhi;   //!
   TBranch        *b_gen_p4_fCoordinates_fE;   //!

   MySelector(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~MySelector() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) {
	  if(! fEvent) return 0;
	  int treeentry = entry;
	  fEvent->GetEntry(treeentry);
	  return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; 
	}
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

	void BuildEvent();
	void MakeWeight();

	std::vector<std::vector<double> > resolutions, scalefactors;

	int TotalEvents, unmachedJets;
	int EtaForwardBinsNo;
	int EtaBinsNo;
	int EtaFtBinsNo;
	int EtaFtControlBinsNo;
	int PtBinsNo;
	int PtFTBinsNo;
 	std::vector<MyJet> Jets;
 	std::vector<MyJet> SmearedJets;
	std::vector<MyJet> GenJets;

	std::vector< std::vector< std::vector< TH1F* > > > forward_hist, forward_gen_hist;
	std::vector< std::vector< std::vector< TH1F* > > > asymmetries_all, asymmetries_gen_all;

	std::vector< std::vector< std::vector< TH1F* > > > forward_hist_dijet, forward_gen_hist_dijet;
	std::vector< std::vector< std::vector< TH1F* > > > forward_pt_hist_dijet, forward_pt_gen_hist_dijet;

	std::vector< std::vector< std::vector< TH1F* > > > forward_pt_hist, forward_gen_pt_hist;
	std::vector< std::vector< std::vector< TH1F* > > > asymmetries_pt_all, asymmetries_gen_pt_all;

	std::vector<TH1F*> histograms;

	TH1F *make_histogram( TString name, int bin_no, double range_min, double range_max, TString xaxis, TString yaxis );

	TH1F *h_JetPt;
	TH1F *h_PU;

	TH1F *h_JetAvePt;
	TH1F *h_Jet1Pt;
	TH1F *h_Jet2Pt;
	TH1F *h_Jet3Pt;

	TH1F *h_FEJetAvePt;
	TH1F *h_FEJet1Pt;
	TH1F *h_FEJet2Pt;
	TH1F *h_FEJet3Pt;


 //  ClassDef(MySelector,0);
};

#endif

#ifdef MySelector_cxx
void MySelector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer

	std::ifstream myfile, myfileSF;
	myfile.open("../AuxFiles/Fall15_25nsV2_MC_PtResolution_AK4PFchs.txt");
//	myfileSF.open("../AuxFiles/Fall15_25nsV2_MC_SF_AK4PFchs.txt");
	myfileSF.open("../AuxFiles/Fall15_25nsV2_MC_SF_AK4PFchs_corrected.txt");
	std::string temp;

	while (std::getline(myfile, temp)) {
		std::istringstream buffer(temp);
		std::vector<double> line((std::istream_iterator<double>(buffer)),
	                             std::istream_iterator<double>());

		resolutions.push_back(line);
	}
	while (std::getline(myfileSF, temp)) {
		std::istringstream buffer(temp);
		std::vector<double> line((std::istream_iterator<double>(buffer)),
	                             std::istream_iterator<double>());

		scalefactors.push_back(line);
	}

   // Set branch addresses and branch pointers

   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

	TFile* currentFile = ((TChain*)fChain)->GetFile();
	fEvent = (TTree*)currentFile->Get("event/t");

	fEvent -> SetMakeClass(1);

   fEvent->SetBranchAddress("pthat", &pthat, &b_pthat);
   fEvent->SetBranchAddress("npuIT", &npuIT, &b_npuIT);
   fEvent->SetBranchAddress("rho", &rho, &b_rho);
   fEvent->SetBranchAddress("weight", &weight, &b_weight);


   fChain->SetBranchAddress("p4", &p4_, &b_p4_);
   fChain->SetBranchAddress("p4.fCoordinates.fPt", p4_fCoordinates_fPt, &b_p4_fCoordinates_fPt);
   fChain->SetBranchAddress("p4.fCoordinates.fEta", p4_fCoordinates_fEta, &b_p4_fCoordinates_fEta);
   fChain->SetBranchAddress("p4.fCoordinates.fPhi", p4_fCoordinates_fPhi, &b_p4_fCoordinates_fPhi);
   fChain->SetBranchAddress("p4.fCoordinates.fE", p4_fCoordinates_fE, &b_p4_fCoordinates_fE);
   fChain->SetBranchAddress("gen_p4", &gen_p4_, &b_gen_p4_);
   fChain->SetBranchAddress("gen_p4.fCoordinates.fPt", gen_p4_fCoordinates_fPt, &b_gen_p4_fCoordinates_fPt);
   fChain->SetBranchAddress("gen_p4.fCoordinates.fEta", gen_p4_fCoordinates_fEta, &b_gen_p4_fCoordinates_fEta);
   fChain->SetBranchAddress("gen_p4.fCoordinates.fPhi", gen_p4_fCoordinates_fPhi, &b_gen_p4_fCoordinates_fPhi);
   fChain->SetBranchAddress("gen_p4.fCoordinates.fE", gen_p4_fCoordinates_fE, &b_gen_p4_fCoordinates_fE);
}

Bool_t MySelector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

	TFile* currentFile = ((TChain*)fChain)->GetFile();
	fEvent = (TTree*)currentFile->Get("event/t");

	fEvent -> SetMakeClass(1);

   fEvent->SetBranchAddress("weight", &weight, &b_weight);
   fEvent->SetBranchAddress("pthat", &pthat, &b_pthat);
   fEvent->SetBranchAddress("npuIT", &npuIT, &b_npuIT);
   fEvent->SetBranchAddress("rho", &rho, &b_rho);
   fEvent->SetBranchStatus("*",0);
	fEvent->SetBranchStatus("weigh*",1);
	fEvent->SetBranchStatus("pthat*",1);
	fEvent->SetBranchStatus("npuIT*",1);
	fEvent->SetBranchStatus("rho*",1);

   return kTRUE;
}

#endif // #ifdef MySelector_cxx
