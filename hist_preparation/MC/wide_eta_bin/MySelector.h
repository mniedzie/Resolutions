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

//   Float_t         cross_section;
//   ULong64_t       run;

//   std::vector<bool>    *allGenJet_patJetWithJetIDmatched;
   std::vector<bool>    *allGenJet_patJetmatched;
   std::vector<float>   *allGenJet_phi;
   std::vector<float>   *neutralEmEnergyFraction;
   std::vector<float>   *hoEnergyFraction;
   std::vector<float>   *HFEMEnergyFraction;
   std::vector<float>   *chargedMuEnergyFraction;
   std::vector<float>   *chargedHadronEnergyFraction;
   std::vector<float>   *dZ;
   std::vector<int>     *nTot;
   std::vector<int>     *PUJetId_cutBasedId;
   std::vector<float>   *betaStar;
   std::vector<std::map<std::string,float> > *jec_factors;
   std::vector<float>   *betaClassic;
   std::vector<float>   *jec_toraw;
//   std::vector<signed char> *hadronFlavor;
   std::vector<int>     *chargedMultiplicity;
   std::vector<float>   *gen_y;
   std::vector<float>   *y;
   std::vector<float>   *fRing1;
//   std::vector<signed char> *partonFlavor;
   std::vector<float>   *fRing3;
   std::vector<float>   *allGenJet_pt;
   std::vector<bool>    *has_gen_particle;
   std::vector<int>     *refpdgid;
//   std::vector<signed char> *gen_charge;
   std::vector<float>   *fRing2;
   std::vector<float>   *DRweighted;
   std::vector<float>   *photonEnergyFraction;
   std::vector<float>   *refarea;
   std::vector<float>   *jtarea;
   Int_t           p4_;
   Float_t         p4_fCoordinates_fPt[kMaxp4];   //[p4_]
   Float_t         p4_fCoordinates_fEta[kMaxp4];   //[p4_]
   Float_t         p4_fCoordinates_fPhi[kMaxp4];   //[p4_]
   Float_t         p4_fCoordinates_fE[kMaxp4];   //[p4_]
   std::vector<float>   *refdrjt;
   std::vector<float>   *neutralHadronEnergyFraction;
   std::vector<float>   *fRing4;
   std::vector<float>   *axisMinor;
   std::vector<float>   *fRing5;
   std::vector<float>   *electronEnergyFraction;
   std::vector<float>   *fRing6;
   std::vector<float>   *axisMajor;
   std::vector<float>   *betaStarClassic;
   std::vector<float>   *fRing7;
   std::vector<unsigned short> *nCh;
   std::vector<float>   *fRing0;
   std::vector<unsigned short> *nNeutrals;
   std::vector<float>   *allGenJet_m;
   std::vector<float>   *allGenJet_eta;
   std::vector<float>   *HFHadronEnergyFraction;
   Int_t           gen_p4_;
   Float_t         gen_p4_fCoordinates_fPt[kMaxgen_p4];   //[gen_p4_]
   Float_t         gen_p4_fCoordinates_fEta[kMaxgen_p4];   //[gen_p4_]
   Float_t         gen_p4_fCoordinates_fPhi[kMaxgen_p4];   //[gen_p4_]
   Float_t         gen_p4_fCoordinates_fE[kMaxgen_p4];   //[gen_p4_]
   std::vector<float>   *ptD;
   std::vector<float>   *PUJetId_fullDiscriminant;
   std::vector<int>     *PUJetId_fullId;
   std::vector<float>   *chargedEmEnergyFraction;
   std::vector<float>   *jetRchg;
//   std::vector<signed char> *charge;
   std::vector<float>   *QGTagger_qgLikelihood;
   std::vector<float>   *dRMatch;
   std::vector<float>   *muonEnergyFraction;
   std::vector<float>   *fRing8;
   std::vector<float>   *pull;
   std::vector<float>   *beta;
   std::vector<float>   *jetRneutral;
   std::vector<float>   *jetR;
   std::vector<float>   *Ttheta;
   std::vector<float>   *pfTrackCountingHighEffBJetTags;
   std::vector<float>   *pfTrackCountingHighPurBJetTags;
   std::vector<float>   *pfJetProbabilityBJetTags;
   std::vector<float>   *pfJetBProbabilityBJetTags;
   std::vector<float>   *pfSimpleSecondaryVertexHighEffBJetTags;
   std::vector<float>   *pfSimpleSecondaryVertexHighPurBJetTags;
   std::vector<float>   *pfCombinedSecondaryVertexV2BJetTags;
   std::vector<float>   *pfCombinedInclusiveSecondaryVertexV2BJetTags;

   // List of branches
//   TBranch        *b_cross_section;   //!
//   TBranch        *b_run;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_pthat;   //!
   TBranch        *b_npuIT;   //!

//   TBranch        *b_allGenJet_patJetWithJetIDmatched;   //!
   TBranch        *b_allGenJet_patJetmatched;   //!
   TBranch        *b_allGenJet_phi;   //!
   TBranch        *b_neutralEmEnergyFraction;   //!
   TBranch        *b_hoEnergyFraction;   //!
   TBranch        *b_HFEMEnergyFraction;   //!
   TBranch        *b_chargedMuEnergyFraction;   //!
   TBranch        *b_chargedHadronEnergyFraction;   //!
   TBranch        *b_dZ;   //!
   TBranch        *b_nTot;   //!
   TBranch        *b_PUJetId_cutBasedId;   //!
   TBranch        *b_betaStar;   //!
   TBranch        *b_jec_factors;   //!
   TBranch        *b_betaClassic;   //!
   TBranch        *b_jec_toraw;   //!
//   TBranch        *b_hadronFlavor;   //!
   TBranch        *b_chargedMultiplicity;   //!
   TBranch        *b_gen_y;   //!
   TBranch        *b_y;   //!
   TBranch        *b_fRing1;   //!
//   TBranch        *b_partonFlavor;   //!
   TBranch        *b_fRing3;   //!
   TBranch        *b_allGenJet_pt;   //!
   TBranch        *b_has_gen_particle;   //!
   TBranch        *b_refpdgid;   //!
//   TBranch        *b_gen_charge;   //!
   TBranch        *b_fRing2;   //!
   TBranch        *b_DRweighted;   //!
   TBranch        *b_photonEnergyFraction;   //!
   TBranch        *b_refarea;   //!
   TBranch        *b_jtarea;   //!
   TBranch        *b_p4_;   //!
   TBranch        *b_p4_fCoordinates_fPt;   //!
   TBranch        *b_p4_fCoordinates_fEta;   //!
   TBranch        *b_p4_fCoordinates_fPhi;   //!
   TBranch        *b_p4_fCoordinates_fE;   //!
   TBranch        *b_refdrjt;   //!
   TBranch        *b_neutralHadronEnergyFraction;   //!
   TBranch        *b_fRing4;   //!
   TBranch        *b_axisMinor;   //!
   TBranch        *b_fRing5;   //!
   TBranch        *b_electronEnergyFraction;   //!
   TBranch        *b_fRing6;   //!
   TBranch        *b_axisMajor;   //!
   TBranch        *b_betaStarClassic;   //!
   TBranch        *b_fRing7;   //!
   TBranch        *b_nCh;   //!
   TBranch        *b_fRing0;   //!
   TBranch        *b_nNeutrals;   //!
   TBranch        *b_allGenJet_m;   //!
   TBranch        *b_allGenJet_eta;   //!
   TBranch        *b_HFHadronEnergyFraction;   //!
   TBranch        *b_gen_p4_;   //!
   TBranch        *b_gen_p4_fCoordinates_fPt;   //!
   TBranch        *b_gen_p4_fCoordinates_fEta;   //!
   TBranch        *b_gen_p4_fCoordinates_fPhi;   //!
   TBranch        *b_gen_p4_fCoordinates_fE;   //!
   TBranch        *b_ptD;   //!
   TBranch        *b_PUJetId_fullDiscriminant;   //!
   TBranch        *b_PUJetId_fullId;   //!
   TBranch        *b_chargedEmEnergyFraction;   //!
   TBranch        *b_jetRchg;   //!
//  TBranch        *b_charge;   //!
   TBranch        *b_QGTagger_qgLikelihood;   //!
   TBranch        *b_dRMatch;   //!
   TBranch        *b_muonEnergyFraction;   //!
   TBranch        *b_fRing8;   //!
   TBranch        *b_pull;   //!
   TBranch        *b_beta;   //!
   TBranch        *b_jetRneutral;   //!
   TBranch        *b_jetR;   //!
   TBranch        *b_Ttheta;   //!
   TBranch        *b_pfTrackCountingHighEffBJetTags;   //!
   TBranch        *b_pfTrackCountingHighPurBJetTags;   //!
   TBranch        *b_pfJetProbabilityBJetTags;   //!
   TBranch        *b_pfJetBProbabilityBJetTags;   //!
   TBranch        *b_pfSimpleSecondaryVertexHighEffBJetTags;   //!
   TBranch        *b_pfSimpleSecondaryVertexHighPurBJetTags;   //!
   TBranch        *b_pfCombinedSecondaryVertexV2BJetTags;   //!
   TBranch        *b_pfCombinedInclusiveSecondaryVertexV2BJetTags;   //!

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

	int TotalEvents;
	int EtaBinsNo;
	int EtaFtBinsNo;
	int EtaFtControlBinsNo;
	int PtBinsNo;
	int PtFTBinsNo;
 	std::vector<MyJet> Jets;
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

//   cross_section = 0;
//   run = 0;

   // Set object pointer
//   allGenJet_patJetWithJetIDmatched = 0;
   allGenJet_patJetmatched = 0;
   allGenJet_phi = 0;;

   neutralEmEnergyFraction = 0;
   hoEnergyFraction = 0;
   HFEMEnergyFraction = 0;
   chargedMuEnergyFraction = 0;
   chargedHadronEnergyFraction = 0;
   dZ = 0;
   nTot = 0;
   PUJetId_cutBasedId = 0;
   betaStar = 0;
   jec_factors = 0;
   betaClassic = 0;
   jec_toraw = 0;
//   hadronFlavor = 0;
   chargedMultiplicity = 0;
   gen_y = 0;
   y = 0;
   fRing1 = 0;
//   partonFlavor = 0;
   fRing3 = 0;
   allGenJet_pt = 0;
   has_gen_particle = 0;
   refpdgid = 0;
//   gen_charge = 0;
   fRing2 = 0;
   DRweighted = 0;
   photonEnergyFraction = 0;
   refarea = 0;
   jtarea = 0;
   refdrjt = 0;
   neutralHadronEnergyFraction = 0;
   fRing4 = 0;
   axisMinor = 0;
   fRing5 = 0;
   electronEnergyFraction = 0;
   fRing6 = 0;
   axisMajor = 0;
   betaStarClassic = 0;
   fRing7 = 0;
   nCh = 0;
   fRing0 = 0;
   nNeutrals = 0;
   allGenJet_m = 0;
   allGenJet_eta = 0;
   HFHadronEnergyFraction = 0;
   ptD = 0;
   PUJetId_fullDiscriminant = 0;
   PUJetId_fullId = 0;
   chargedEmEnergyFraction = 0;
   jetRchg = 0;
//   charge = 0;
   QGTagger_qgLikelihood = 0;
   dRMatch = 0;
   muonEnergyFraction = 0;
   fRing8 = 0;
   pull = 0;
   beta = 0;
   jetRneutral = 0;
   jetR = 0;
   Ttheta = 0;
   pfTrackCountingHighEffBJetTags = 0;
   pfTrackCountingHighPurBJetTags = 0;
   pfJetProbabilityBJetTags = 0;
   pfJetBProbabilityBJetTags = 0;
   pfSimpleSecondaryVertexHighEffBJetTags = 0;
   pfSimpleSecondaryVertexHighPurBJetTags = 0;
   pfCombinedSecondaryVertexV2BJetTags = 0;
   pfCombinedInclusiveSecondaryVertexV2BJetTags = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

//   fChain->SetBranchAddress("cross_section", &cross_section, &b_cross_section);
//   fChain->SetBranchAddress("run", &run, &b_run);
	TFile* currentFile = ((TChain*)fChain)->GetFile();
	fEvent = (TTree*)currentFile->Get("event/t");

	fEvent -> SetMakeClass(1);

   fEvent->SetBranchAddress("pthat", &pthat, &b_pthat);
   fEvent->SetBranchAddress("npuIT", &npuIT, &b_npuIT);
   fEvent->SetBranchAddress("weight", &weight, &b_weight);


//   fChain->SetBranchAddress("allGenJet_patJetWithJetIDmatched", &allGenJet_patJetWithJetIDmatched, &b_allGenJet_patJetWithJetIDmatched);
   fChain->SetBranchAddress("allGenJet_patJetmatched", &allGenJet_patJetmatched, &b_allGenJet_patJetmatched);
   fChain->SetBranchAddress("allGenJet_phi", &allGenJet_phi, &b_allGenJet_phi);
   fChain->SetBranchAddress("neutralEmEnergyFraction", &neutralEmEnergyFraction, &b_neutralEmEnergyFraction);
   fChain->SetBranchAddress("hoEnergyFraction", &hoEnergyFraction, &b_hoEnergyFraction);
   fChain->SetBranchAddress("HFEMEnergyFraction", &HFEMEnergyFraction, &b_HFEMEnergyFraction);
   fChain->SetBranchAddress("chargedMuEnergyFraction", &chargedMuEnergyFraction, &b_chargedMuEnergyFraction);
   fChain->SetBranchAddress("chargedHadronEnergyFraction", &chargedHadronEnergyFraction, &b_chargedHadronEnergyFraction);
   fChain->SetBranchAddress("dZ", &dZ, &b_dZ);
   fChain->SetBranchAddress("nTot", &nTot, &b_nTot);
   fChain->SetBranchAddress("PUJetId_cutBasedId", &PUJetId_cutBasedId, &b_PUJetId_cutBasedId);
   fChain->SetBranchAddress("betaStar", &betaStar, &b_betaStar);
   fChain->SetBranchAddress("jec_factors", &jec_factors, &b_jec_factors);
   fChain->SetBranchAddress("betaClassic", &betaClassic, &b_betaClassic);
   fChain->SetBranchAddress("jec_toraw", &jec_toraw, &b_jec_toraw);
//   fChain->SetBranchAddress("hadronFlavor", &hadronFlavor, &b_hadronFlavor);
   fChain->SetBranchAddress("chargedMultiplicity", &chargedMultiplicity, &b_chargedMultiplicity);
   fChain->SetBranchAddress("gen_y", &gen_y, &b_gen_y);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("fRing1", &fRing1, &b_fRing1);
//   fChain->SetBranchAddress("partonFlavor", &partonFlavor, &b_partonFlavor);
   fChain->SetBranchAddress("fRing3", &fRing3, &b_fRing3);
   fChain->SetBranchAddress("allGenJet_pt", &allGenJet_pt, &b_allGenJet_pt);
   fChain->SetBranchAddress("has_gen_particle", &has_gen_particle, &b_has_gen_particle);
   fChain->SetBranchAddress("refpdgid", &refpdgid, &b_refpdgid);
//   fChain->SetBranchAddress("gen_charge", &gen_charge, &b_gen_charge);
   fChain->SetBranchAddress("fRing2", &fRing2, &b_fRing2);
   fChain->SetBranchAddress("DRweighted", &DRweighted, &b_DRweighted);
   fChain->SetBranchAddress("photonEnergyFraction", &photonEnergyFraction, &b_photonEnergyFraction);
   fChain->SetBranchAddress("refarea", &refarea, &b_refarea);
   fChain->SetBranchAddress("jtarea", &jtarea, &b_jtarea);
   fChain->SetBranchAddress("p4", &p4_, &b_p4_);
   fChain->SetBranchAddress("p4.fCoordinates.fPt", p4_fCoordinates_fPt, &b_p4_fCoordinates_fPt);
   fChain->SetBranchAddress("p4.fCoordinates.fEta", p4_fCoordinates_fEta, &b_p4_fCoordinates_fEta);
   fChain->SetBranchAddress("p4.fCoordinates.fPhi", p4_fCoordinates_fPhi, &b_p4_fCoordinates_fPhi);
   fChain->SetBranchAddress("p4.fCoordinates.fE", p4_fCoordinates_fE, &b_p4_fCoordinates_fE);
   fChain->SetBranchAddress("refdrjt", &refdrjt, &b_refdrjt);
   fChain->SetBranchAddress("neutralHadronEnergyFraction", &neutralHadronEnergyFraction, &b_neutralHadronEnergyFraction);
   fChain->SetBranchAddress("fRing4", &fRing4, &b_fRing4);
   fChain->SetBranchAddress("axisMinor", &axisMinor, &b_axisMinor);
   fChain->SetBranchAddress("fRing5", &fRing5, &b_fRing5);
   fChain->SetBranchAddress("electronEnergyFraction", &electronEnergyFraction, &b_electronEnergyFraction);
   fChain->SetBranchAddress("fRing6", &fRing6, &b_fRing6);
   fChain->SetBranchAddress("axisMajor", &axisMajor, &b_axisMajor);
   fChain->SetBranchAddress("betaStarClassic", &betaStarClassic, &b_betaStarClassic);
   fChain->SetBranchAddress("fRing7", &fRing7, &b_fRing7);
   fChain->SetBranchAddress("nCh", &nCh, &b_nCh);
   fChain->SetBranchAddress("fRing0", &fRing0, &b_fRing0);
   fChain->SetBranchAddress("nNeutrals", &nNeutrals, &b_nNeutrals);
   fChain->SetBranchAddress("allGenJet_m", &allGenJet_m, &b_allGenJet_m);
   fChain->SetBranchAddress("allGenJet_eta", &allGenJet_eta, &b_allGenJet_eta);
   fChain->SetBranchAddress("HFHadronEnergyFraction", &HFHadronEnergyFraction, &b_HFHadronEnergyFraction);
   fChain->SetBranchAddress("gen_p4", &gen_p4_, &b_gen_p4_);
   fChain->SetBranchAddress("gen_p4.fCoordinates.fPt", gen_p4_fCoordinates_fPt, &b_gen_p4_fCoordinates_fPt);
   fChain->SetBranchAddress("gen_p4.fCoordinates.fEta", gen_p4_fCoordinates_fEta, &b_gen_p4_fCoordinates_fEta);
   fChain->SetBranchAddress("gen_p4.fCoordinates.fPhi", gen_p4_fCoordinates_fPhi, &b_gen_p4_fCoordinates_fPhi);
   fChain->SetBranchAddress("gen_p4.fCoordinates.fE", gen_p4_fCoordinates_fE, &b_gen_p4_fCoordinates_fE);
   fChain->SetBranchAddress("ptD", &ptD, &b_ptD);
   fChain->SetBranchAddress("PUJetId_fullDiscriminant", &PUJetId_fullDiscriminant, &b_PUJetId_fullDiscriminant);
   fChain->SetBranchAddress("PUJetId_fullId", &PUJetId_fullId, &b_PUJetId_fullId);
   fChain->SetBranchAddress("chargedEmEnergyFraction", &chargedEmEnergyFraction, &b_chargedEmEnergyFraction);
   fChain->SetBranchAddress("jetRchg", &jetRchg, &b_jetRchg);
//   fChain->SetBranchAddress("charge", &charge, &b_charge);
   fChain->SetBranchAddress("QGTagger_qgLikelihood", &QGTagger_qgLikelihood, &b_QGTagger_qgLikelihood);
   fChain->SetBranchAddress("dRMatch", &dRMatch, &b_dRMatch);
   fChain->SetBranchAddress("muonEnergyFraction", &muonEnergyFraction, &b_muonEnergyFraction);
   fChain->SetBranchAddress("fRing8", &fRing8, &b_fRing8);
   fChain->SetBranchAddress("pull", &pull, &b_pull);
   fChain->SetBranchAddress("beta", &beta, &b_beta);
   fChain->SetBranchAddress("jetRneutral", &jetRneutral, &b_jetRneutral);
   fChain->SetBranchAddress("jetR", &jetR, &b_jetR);
   fChain->SetBranchAddress("Ttheta", &Ttheta, &b_Ttheta);
   fChain->SetBranchAddress("pfTrackCountingHighEffBJetTags", &pfTrackCountingHighEffBJetTags, &b_pfTrackCountingHighEffBJetTags);
   fChain->SetBranchAddress("pfTrackCountingHighPurBJetTags", &pfTrackCountingHighPurBJetTags, &b_pfTrackCountingHighPurBJetTags);
   fChain->SetBranchAddress("pfJetProbabilityBJetTags", &pfJetProbabilityBJetTags, &b_pfJetProbabilityBJetTags);
   fChain->SetBranchAddress("pfJetBProbabilityBJetTags", &pfJetBProbabilityBJetTags, &b_pfJetBProbabilityBJetTags);
   fChain->SetBranchAddress("pfSimpleSecondaryVertexHighEffBJetTags", &pfSimpleSecondaryVertexHighEffBJetTags, &b_pfSimpleSecondaryVertexHighEffBJetTags);
   fChain->SetBranchAddress("pfSimpleSecondaryVertexHighPurBJetTags", &pfSimpleSecondaryVertexHighPurBJetTags, &b_pfSimpleSecondaryVertexHighPurBJetTags);
   fChain->SetBranchAddress("pfCombinedSecondaryVertexV2BJetTags", &pfCombinedSecondaryVertexV2BJetTags, &b_pfCombinedSecondaryVertexV2BJetTags);
   fChain->SetBranchAddress("pfCombinedInclusiveSecondaryVertexV2BJetTags", &pfCombinedInclusiveSecondaryVertexV2BJetTags, &b_pfCombinedInclusiveSecondaryVertexV2BJetTags);
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
   fEvent->SetBranchStatus("*",0);
	fEvent->SetBranchStatus("weigh*",1);
	fEvent->SetBranchStatus("pthat*",1);
	fEvent->SetBranchStatus("npuIT*",1);

   return kTRUE;
}

#endif // #ifdef MySelector_cxx
