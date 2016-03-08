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
//

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


// not complete data 69000mb
//	double weight_factor [] = { 1.65592, 1.38078, 0.348198, 0.167867, 0.108966, 0.0961884, 0.195844, 0.84046, 2.13741, 3.15388, 3.66878, 3.57518, 2.87624, 1.8655, .970852, 0.409492, 0.142721, 0.0426954, 0.0116539, 0.0031621, 0.000949369, 0.000346797, 0.00016091, 8.97951e-05, 5.41041e-05, 3.29143e-05, 1.95054e-05, 1.11624e-05, 6.1546e-06, 3.28415e-06, 1.67469e-06, 8.202e-07, 3.86038e-07, 1.75414e-07, 7.52715e-08, 3.11851e-08, 1.24281e-08, 4.60662e-09, 1.6156e-09, 5.55842e-10, 1.73355e-10, 5.24901e-11, 1.44399e-11, 3.66622e-12, 8.73496e-13, 2.05993e-13, 4.16787e-14, 8.31639e-15, 1.90866e-15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 


// full data 69000mb
	double weight_factor [] = { 1.51823, 1.4103, 0.395114, 0.170763, 0.108002, 0.0974589, 0.196369, 0.77833, 1.94869, 2.93908, 3.52498, 3.54391, 2.93381, 1.95475, 1.04688, 0.458862, 0.176078, 0.0739666, 0.0426934, 0.0273048, 0.0146278, 0.00594568, 0.00181273, 0.000436231, 0.000100473, 3.30495e-05, 1.63482e-05, 9.09873e-06, 5.00262e-06, 2.6689e-06, 1.36094e-06, 6.66538e-07, 3.13715e-07, 1.4255e-07, 6.11696e-08, 2.53426e-08, 1.00997e-08, 3.74358e-09, 1.31293e-09, 4.51706e-10, 1.40877e-10, 4.26562e-11, 1.17347e-11, 2.97937e-12, 7.09849e-13, 1.67401e-13, 3.38703e-14, 6.75834e-15, 1.55108e-15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 


//	full data 80000mb
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

	h_JetAvePt = new TH1F( "JetAvePt" , "Inclusive Jet Ave Pt" , 50 , 0 , 2000 );
	h_JetAvePt -> SetXTitle( "Pt_{ave}[GeV]" );
	h_JetAvePt -> Sumw2();
	histograms.push_back(h_JetAvePt);

	h_Jet1Pt = new TH1F( "Jet1Pt" , "Inclusive Jet 1 Pt" , 50 , 0 , 2000 );
	h_Jet1Pt -> SetXTitle( "Pt_1[GeV]" );
	h_Jet1Pt -> Sumw2();
	histograms.push_back(h_Jet1Pt);

	h_Jet2Pt = new TH1F( "Jet2Pt" , "Inclusive Jet 2 Pt" , 50 , 0 , 2000 );
	h_Jet2Pt -> SetXTitle( "Pt_2[GeV]" );
	h_Jet2Pt -> Sumw2();
	histograms.push_back(h_Jet2Pt);

	h_Jet3Pt = new TH1F( "Jet3Pt" , "Inclusive Jet 3 Pt" , 50 , 0 , 2000 );
	h_Jet3Pt -> SetXTitle( "Pt_3[GeV]" );
	h_Jet3Pt -> Sumw2();
	histograms.push_back(h_Jet3Pt);

	h_FEJetAvePt = new TH1F( "FEJetAvePt" , "Inclusive FEJet Ave Pt" , 50 , 0 , 2000 );
	h_FEJetAvePt -> SetXTitle( "Pt_{ave}[GeV]" );
	h_FEJetAvePt -> Sumw2();
	histograms.push_back(h_FEJetAvePt);

	h_FEJet1Pt = new TH1F( "FEJet1Pt" , "Inclusive FEJet 1 Pt" , 50 , 0 , 2000 );
	h_FEJet1Pt -> SetXTitle( "Pt_1[GeV]" );
	h_FEJet1Pt -> Sumw2();
	histograms.push_back(h_FEJet1Pt);

	h_FEJet2Pt = new TH1F( "FEJet2Pt" , "Inclusive FEJet 2 Pt" , 50 , 0 , 2000 );
	h_FEJet2Pt -> SetXTitle( "Pt_2[GeV]" );
	h_FEJet2Pt -> Sumw2();
	histograms.push_back(h_FEJet2Pt);

	h_FEJet3Pt = new TH1F( "FEJet3Pt" , "Inclusive FEJet 3 Pt" , 50 , 0 , 2000 );
	h_FEJet3Pt -> SetXTitle( "Pt_3[GeV]" );
	h_FEJet3Pt -> Sumw2();
	histograms.push_back(h_FEJet3Pt);


	h_PU = new TH1F( "PileUp" , "PU distribution" , 60 , 0 , 60 );
	h_PU -> SetXTitle( "PU" );
	h_PU -> Sumw2();
	histograms.push_back(h_PU);

	EtaBinsNo = 11;
	EtaForwardBinsNo = 2;
	EtaFtBinsNo = 2;
	EtaFtControlBinsNo = 8;

	PtBinsNo = 9;
	PtFTBinsNo = 6;

	// I define histograms for the "normal" JER calculation
	
	for( int m = 0; m < EtaBinsNo; m++ )
	{
		std::vector< std::vector< TH1F* > > temp2, temp2pt, gen_temp2, gen_temp2pt;

		for( int p = 0; p < PtBinsNo; p++ )
		{
			std::vector< TH1F* > temp1, temp1pt, gen_temp1, gen_temp1pt;

			for( int r = 0; r < 5; r++ )
			{
				TString name_fw = "asymm_"; name_fw += "eta"; name_fw += (m+1); name_fw += "_pt"; name_fw += (p+1); name_fw += "_alpha"; name_fw += (r+1); 
				TString name_fw_pt = "asymmpt_"; name_fw_pt += "probe"; name_fw_pt += (m+1); name_fw_pt += "_pt"; name_fw_pt += (p+1); name_fw_pt += "_alpha"; name_fw_pt += (r+1); 
				TString gen_name_fw = "gen_asymm_"; gen_name_fw += "eta"; gen_name_fw += (m+1); gen_name_fw += "_pt"; gen_name_fw += (p+1); gen_name_fw += "_alpha"; gen_name_fw += (r+1); 
				TString gen_name_fw_pt = "gen_asymmpt_"; gen_name_fw_pt += "probe"; gen_name_fw_pt += (m+1); gen_name_fw_pt += "_pt"; gen_name_fw_pt += (p+1); gen_name_fw_pt += "_alpha"; gen_name_fw_pt += (r+1); 

				TH1F *h1 = new TH1F( name_fw, name_fw, 50, 0, 0.8 );
				h1 ->GetYaxis()->SetTitle("a.u.");	h1 ->GetXaxis()->SetTitle("Asymmetry");
				h1 -> Sumw2(); temp1.push_back(h1);

				TH1F *h2 = new TH1F( name_fw_pt, name_fw_pt, 50, 0, 1500 );
				h2 ->GetYaxis()->SetTitle("a.u.");	h2 ->GetXaxis()->SetTitle("Pt[GeV]");
				h2 -> Sumw2(); temp1pt.push_back(h2);

				TH1F *gen_h1 = new TH1F( gen_name_fw, gen_name_fw, 50, 0, 0.8 );
				gen_h1 ->GetYaxis()->SetTitle("a.u.");	gen_h1 ->GetXaxis()->SetTitle("Asymmetry");
				gen_h1 -> Sumw2(); gen_temp1.push_back(gen_h1);

				TH1F *gen_h2 = new TH1F( gen_name_fw_pt, gen_name_fw_pt, 50, 0, 1500 );
				gen_h2 ->GetYaxis()->SetTitle("a.u.");	gen_h2 ->GetXaxis()->SetTitle("Pt[GeV]");
				gen_h2 -> Sumw2(); gen_temp1pt.push_back(gen_h2);
			}
			temp2.push_back(temp1); temp2pt.push_back(temp1pt);
			gen_temp2.push_back(gen_temp1); gen_temp2pt.push_back(gen_temp1pt);
		}
		asymmetries_all.push_back(temp2); asymmetries_pt_all.push_back(temp2pt);
		asymmetries_gen_all.push_back(gen_temp2); asymmetries_gen_pt_all.push_back(gen_temp2pt);
	}

	for( int m = 0; m < EtaForwardBinsNo; m++ )
	{
		std::vector< std::vector< TH1F* > > temp2, temp2pt, gen_temp2, gen_temp2pt;

		for( int p = 0; p < PtFTBinsNo; p++ )
		{
			std::vector< TH1F* > temp1, temp1pt, gen_temp1, gen_temp1pt;

			for( int r = 0; r < 5; r++ )
			{
				TString name_fw = "asymm_"; name_fw += "eta"; name_fw += ( m + 1 + EtaBinsNo ); name_fw += "_pt"; name_fw += (p+1); name_fw += "_alpha"; name_fw += (r+1); 
				TString name_fw_pt = "asymmpt_"; name_fw_pt += "probe"; name_fw_pt += ( m + 1 + EtaBinsNo ); name_fw_pt += "_pt"; name_fw_pt += (p+1); name_fw_pt += "_alpha"; name_fw_pt += (r+1); 
				TString gen_name_fw = "gen_asymm_"; gen_name_fw += "eta"; gen_name_fw += ( m + 1 + EtaBinsNo ); gen_name_fw += "_pt"; gen_name_fw += (p+1); gen_name_fw += "_alpha"; gen_name_fw += (r+1); 
				TString gen_name_fw_pt = "gen_asymmpt_"; gen_name_fw_pt += "probe"; gen_name_fw_pt += ( m + 1 + EtaBinsNo ); gen_name_fw_pt += "_pt"; gen_name_fw_pt += (p+1); gen_name_fw_pt += "_alpha"; gen_name_fw_pt += (r+1); 

				TH1F *h1 = new TH1F( name_fw, name_fw, 50, 0, 0.8 );
				h1 ->GetYaxis()->SetTitle("a.u.");	h1 ->GetXaxis()->SetTitle("Asymmetry");
				h1 -> Sumw2(); temp1.push_back(h1);

				TH1F *h2 = new TH1F( name_fw_pt, name_fw_pt, 50, 0, 1500 );
				h2 ->GetYaxis()->SetTitle("a.u.");	h2 ->GetXaxis()->SetTitle("Pt[GeV]");
				h2 -> Sumw2(); temp1pt.push_back(h2);

				TH1F *gen_h1 = new TH1F( gen_name_fw, gen_name_fw, 50, 0, 0.8 );
				gen_h1 ->GetYaxis()->SetTitle("a.u.");	gen_h1 ->GetXaxis()->SetTitle("Asymmetry");
				gen_h1 -> Sumw2(); gen_temp1.push_back(gen_h1);

				TH1F *gen_h2 = new TH1F( gen_name_fw_pt, gen_name_fw_pt, 50, 0, 1500 );
				gen_h2 ->GetYaxis()->SetTitle("a.u.");	gen_h2 ->GetXaxis()->SetTitle("Pt[GeV]");
				gen_h2 -> Sumw2(); gen_temp1pt.push_back(gen_h2);
			}
			temp2.push_back(temp1); temp2pt.push_back(temp1pt);
			gen_temp2.push_back(gen_temp1); gen_temp2pt.push_back(gen_temp1pt);
		}
		asymmetries_all.push_back(temp2); asymmetries_pt_all.push_back(temp2pt);
		asymmetries_gen_all.push_back(gen_temp2); asymmetries_gen_pt_all.push_back(gen_temp2pt);
	}

	// I define histograms used in forward extension for reference eta ( 0, 1.3 )

	for( int m = 0; m < EtaFtBinsNo; m++ )
	{
		std::vector< std::vector< TH1F* > > temp2, temp2pt, gen_temp2, gen_temp2pt;

		for( int p = 0; p < PtFTBinsNo; p++ )
		{
			std::vector< TH1F* > temp1, temp1pt, gen_temp1, gen_temp1pt;

			for( int r = 0; r < 5; r++ )
			{
				TString name_fw = "forward_"; name_fw += "probe"; name_fw += ( m + 2 + EtaFtControlBinsNo) ; name_fw += "_pt"; name_fw += p+1; name_fw += "_alpha"; name_fw += r+1; 
				TString name_fw_pt = "forwardpt_"; name_fw_pt += "probe"; name_fw_pt += ( m + 2 + EtaFtControlBinsNo); name_fw_pt += "_pt"; name_fw_pt += p+1; name_fw_pt += "_alpha"; name_fw_pt += r+1; 
				TString gen_name_fw = "gen_forward_"; gen_name_fw += "probe"; gen_name_fw += ( m + 2 + EtaFtControlBinsNo); gen_name_fw += "_pt"; gen_name_fw += p+1; gen_name_fw += "_alpha"; gen_name_fw += r+1; 
				TString gen_name_fw_pt = "gen_forwardpt_"; gen_name_fw_pt += "probe"; gen_name_fw_pt += ( m + 2 + EtaFtControlBinsNo); gen_name_fw_pt += "_pt"; gen_name_fw_pt += p+1; gen_name_fw_pt += "_alpha"; gen_name_fw_pt += r+1; 

				TH1F *h1 = new TH1F( name_fw, name_fw, 50, 0, 0.8 );
				h1 ->GetYaxis()->SetTitle("a.u.");	h1 ->GetXaxis()->SetTitle("Asymmetry");
				h1 -> Sumw2(); temp1.push_back(h1);

				TH1F *h2 = new TH1F( name_fw_pt, name_fw_pt, 50, 0, 1500 );
				h2 ->GetYaxis()->SetTitle("a.u.");	h2 ->GetXaxis()->SetTitle("Pt[GeV]");
				h2 -> Sumw2(); temp1pt.push_back(h2);

				TH1F *gen_h1 = new TH1F( gen_name_fw, gen_name_fw, 50, 0, 0.8 );
				gen_h1 ->GetYaxis()->SetTitle("a.u.");	gen_h1 ->GetXaxis()->SetTitle("Asymmetry");
				gen_h1 -> Sumw2(); gen_temp1.push_back(gen_h1);

				TH1F *gen_h2 = new TH1F( gen_name_fw_pt, gen_name_fw_pt, 50, 0, 1500 );
				gen_h2 ->GetYaxis()->SetTitle("a.u.");	gen_h2 ->GetXaxis()->SetTitle("Pt[GeV]");
				gen_h2 -> Sumw2(); gen_temp1pt.push_back(gen_h2);
			}
			temp2.push_back(temp1); temp2pt.push_back(temp1pt);
			gen_temp2.push_back(gen_temp1); gen_temp2pt.push_back(gen_temp1pt);
		}
		forward_hist.push_back(temp2); forward_pt_hist.push_back(temp2pt);
		forward_gen_hist.push_back(gen_temp2); forward_gen_pt_hist.push_back(gen_temp2pt);
	}

	// I define histograms for the control eta bins for forward method calculation

	for( int m = 0; m < EtaFtControlBinsNo; m++ )
	{
		std::vector< std::vector< TH1F* > > temp2, temp2pt, gen_temp2, gen_temp2pt;

		for( int p = 0; p < PtBinsNo; p++ )
		{
			std::vector< TH1F* > temp1, temp1pt, gen_temp1, gen_temp1pt;
			for( int r = 0; r < 5; r++ )
			{
				TString name_fw = "forward_control_"; name_fw += "probe"; name_fw += ( m + 2 ); name_fw += "_pt"; name_fw += ( p + 1 ); name_fw += "_alpha"; name_fw += ( r + 1 ); 
				TString name_fw_pt = "forwardpt_control_"; name_fw_pt += "probe"; name_fw_pt += ( m + 2 ); name_fw_pt += "_pt"; name_fw_pt += ( p + 1 ); name_fw_pt += "_alpha"; name_fw_pt += ( r + 1 ); 
				TString gen_name_fw = "gen_forward_control_"; gen_name_fw += "probe"; gen_name_fw += ( m + 2 ); gen_name_fw += "_pt"; gen_name_fw += ( p + 1 ); gen_name_fw += "_alpha"; gen_name_fw += ( r + 1 ); 
				TString gen_name_fw_pt = "gen_forwardpt_control_"; gen_name_fw_pt += "probe"; gen_name_fw_pt += ( m + 2 ); gen_name_fw_pt += "_pt"; gen_name_fw_pt += ( p + 1 ); gen_name_fw_pt += "_alpha"; gen_name_fw_pt += ( r + 1 ); 

				TH1F *h1 = new TH1F( name_fw, name_fw, 50, 0, 0.8 );
				h1 ->GetYaxis()->SetTitle("a.u.");	h1 ->GetXaxis()->SetTitle("Asymmetry");
				h1 -> Sumw2(); temp1.push_back(h1);

				TH1F *h2 = new TH1F( name_fw_pt, name_fw_pt, 50, 0, 1500 );
				h2 ->GetYaxis()->SetTitle("a.u.");	h2 ->GetXaxis()->SetTitle("Pt[GeV]");
				h2 -> Sumw2(); temp1pt.push_back(h2);

				TH1F *gen_h1 = new TH1F( gen_name_fw, gen_name_fw, 50, 0, 0.8 );
				gen_h1 ->GetYaxis()->SetTitle("a.u.");	gen_h1 ->GetXaxis()->SetTitle("Asymmetry");
				gen_h1 -> Sumw2(); gen_temp1.push_back(gen_h1);

				TH1F *gen_h2 = new TH1F( gen_name_fw_pt, gen_name_fw_pt, 50, 0, 1500 );
				gen_h2 ->GetYaxis()->SetTitle("a.u.");	gen_h2 ->GetXaxis()->SetTitle("Pt[GeV]");
				gen_h2 -> Sumw2(); gen_temp1pt.push_back(gen_h2);
			}
			temp2.push_back(temp1); temp2pt.push_back(temp1pt);
			gen_temp2.push_back(gen_temp1); gen_temp2pt.push_back(gen_temp1pt);
		}
		forward_hist_dijet.push_back(temp2); forward_pt_hist_dijet.push_back(temp2pt);
		forward_gen_hist_dijet.push_back(gen_temp2); forward_pt_gen_hist_dijet.push_back(gen_temp2pt);
	}

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

	MakeWeight();

	int JetsNum = p4_;
	int GenJetsNum = gen_p4_;

	int p_bins [] = { 55, 77, 99, 165, 231, 298, 365, 451, 561, 1500 };
	int p_bins_FT [] = { 77, 99, 121, 187, 253, 342, 1500 };

	double eta_bins [] = { 0, 0.5, 0.8, 1.1, 1.3, 1.7, 1.9, 2.1, 2.3, 2.5, 2.8, 3.0 };
	double eta_ref_down [] = { 3.0, 3.2 };
	double eta_ref_up [] = { 3.2, 4.7 };
	double eta_bins_control [] = { 0, 1.3, 1.7, 1.9, 2.1, 2.3, 2.5, 2.8, 3.0 };
	double alpha_bins [] = { 0, 0.1, 0.15, 0.2, 0.25, 0.3 };

	if( TotalEvents%100000 == 0 )
	{
		std::cout << "			Analyzing event #" << TotalEvents << std::endl;
	}

	if( TotalEvents == 1 )
	{
		std::cout << "asymmetry lengthh " << asymmetries_all.size() << std::endl;
	}

	std::sort( GenJets.begin(), GenJets.end(), sortFunct );

	h_PU -> Fill( npuIT, 1 );

	double parallel, perpendicular, complete, alpha;
	double parallelGen, perpendicularGen, completeGen, alphaGen;

	// Below I choose what kind of asymmetries I want to study!

	bool excl_bin = false; // inclusive
//	bool excl_bin = true;  // exclusive

	int flag1 = 0; // 0 -> complete_alpha
						// 1 -> parallel
						// 2 -> perpendicular

	double gen_threshold = 10;

	if ( JetsNum > 1 )
	{
		if ( JetsNum > 2 && Jets[2].Pt() > 10 )
		{
			complete =  2 * Jets[2].Pt()/( Jets[0].Pt() + Jets[1].Pt() );
			parallel = (2*Jets[2]*(Jets[0]-Jets[1]))/((Jets[0]-Jets[1]).Pt()*( Jets[0].Pt() + Jets[1].Pt() ));
			perpendicular = TMath::Sqrt( TMath::Power( complete, 2 ) - TMath::Power( parallel, 2) );
		}
		else
		{
			complete = 0 ;
			parallel = 0 ;
			perpendicular = 0 ;
		}

		if (flag1 == 0 ) alpha = TMath::Abs(complete);
		if (flag1 == 1 ) alpha = TMath::Abs(parallel);
		if (flag1 == 2 ) alpha = TMath::Abs(perpendicular);

		if ( TMath::Abs(Jets[0].DeltaPhi( Jets[1] )) > 2.7 && Jets[0].Pt() < 2*pthat )
		{
		// I fill alpha_max histograms
			for ( int k = 0 ; k < PtBinsNo ; k++ )
			{
				if ( ( 0.5 * ( Jets[0].Pt() + Jets[1].Pt() ) < p_bins[ k + 1 ] ) &&
						( 0.5 * ( Jets[0].Pt() + Jets[1].Pt() ) > p_bins[ k ] ) )
				{
					for ( int r = 0 ; r < EtaBinsNo ; r++ )
					{
						if (TMath::Abs( Jets[1].Eta() ) > eta_bins[r] && 
							TMath::Abs( Jets[1].Eta() ) < eta_bins[r+1] && 
							TMath::Abs( Jets[0].Eta() ) > eta_bins[r] && 
							TMath::Abs( Jets[0].Eta() ) < eta_bins[r+1] )
						{
							for ( int m = 0 ; m < 5 ; m++ )
							{
								if ( alpha < alpha_bins[ m+1 ] )
								{
									asymmetries_all.at(r).at(k).at(m) -> Fill( ( Jets[0].Pt() - Jets[1].Pt() )/( Jets[0].Pt() + Jets[1].Pt() ) , weight );
									asymmetries_pt_all.at(r).at(k).at(m) -> Fill( 0.5 * ( Jets[0].Pt() + Jets[1].Pt() ), weight );
									if ( m == 4 )
									{
										h_JetAvePt -> Fill( 0.5 * ( Jets[0].Pt() + Jets[1].Pt() ), weight );
										h_Jet1Pt -> Fill( Jets[0].Pt(), weight );
										h_Jet2Pt -> Fill( Jets[1].Pt(), weight );
										h_Jet3Pt -> Fill( Jets[2].Pt(), weight );
									}
									if ( excl_bin ) break;
								}
							}
						}
					}
					for ( int r = 0 ; r < EtaFtControlBinsNo ; r++ )
					{
						if ((TMath::Abs( Jets[1].Eta() ) > 0. && 
							TMath::Abs( Jets[1].Eta() ) < 1.3 && 
							TMath::Abs( Jets[0].Eta() ) > eta_bins_control[r] && 
							TMath::Abs( Jets[0].Eta() ) < eta_bins_control[r+1]) || 
							(TMath::Abs( Jets[0].Eta() ) > 0. && 
							TMath::Abs( Jets[0].Eta() ) < 1.3 && 
							TMath::Abs( Jets[1].Eta() ) > eta_bins_control[r] && 
							TMath::Abs( Jets[1].Eta() ) < eta_bins_control[r+1]) )
						{
							for ( int m = 0 ; m < 5 ; m++ )
							{
								if ( alpha < alpha_bins[ m+1 ] )
								{
									forward_hist_dijet.at(r).at(k).at(m) -> Fill( TMath::Abs(( Jets[0].Pt() - Jets[1].Pt() )/( Jets[0].Pt() + Jets[1].Pt() )) , weight );
									forward_pt_hist_dijet.at(r).at(k).at(m) -> Fill( 0.5 * ( Jets[0].Pt() + Jets[1].Pt() ), weight );
									if ( m == 4 )
									{
										h_FEJetAvePt -> Fill( 0.5 * ( Jets[0].Pt() + Jets[1].Pt() ), weight );
										h_FEJet1Pt -> Fill( Jets[0].Pt(), weight );
										h_FEJet2Pt -> Fill( Jets[1].Pt(), weight );
										h_FEJet3Pt -> Fill( Jets[2].Pt(), weight );
									}
									if ( excl_bin ) break;
								}
							}
						}
					}	
					break;
				}
			}
			for ( int k = 0 ; k < PtFTBinsNo ; k++ )
			{
				if ( ( 0.5 * ( Jets[0].Pt() + Jets[1].Pt() ) < p_bins_FT[ k + 1 ] ) &&
						( 0.5 * ( Jets[0].Pt() + Jets[1].Pt() ) > p_bins_FT[ k ] ) )
				{
					for ( int r = 0 ; r < EtaFtBinsNo ; r++ )
					{
						if ((TMath::Abs( Jets[1].Eta() ) > 0. && 
							TMath::Abs( Jets[1].Eta() ) < 1.3 && 
							TMath::Abs( Jets[0].Eta() ) > eta_ref_down[r] && 
							TMath::Abs( Jets[0].Eta() ) < eta_ref_up[r]) || 
							(TMath::Abs( Jets[0].Eta() ) > 0. && 
							TMath::Abs( Jets[0].Eta() ) < 1.3 && 
							TMath::Abs( Jets[1].Eta() ) > eta_ref_down[r] && 
							TMath::Abs( Jets[1].Eta() ) < eta_ref_up[r]) )
						{
							for ( int m = 0 ; m < 5 ; m++ )
							{
								if ( alpha < alpha_bins[ m+1 ] )
								{
									forward_hist.at(r).at(k).at(m) -> Fill( TMath::Abs(( Jets[0].Pt() - Jets[1].Pt() )/( Jets[0].Pt() + Jets[1].Pt() )) , weight );
									forward_pt_hist.at(r).at(k).at(m) -> Fill( 0.5 * ( Jets[0].Pt() + Jets[1].Pt() ), weight );
									if ( m == 4 )
									{
										h_FEJetAvePt -> Fill( 0.5 * ( Jets[0].Pt() + Jets[1].Pt() ), weight );
										h_FEJet1Pt -> Fill( Jets[0].Pt(), weight );
										h_FEJet2Pt -> Fill( Jets[1].Pt(), weight );
										h_FEJet3Pt -> Fill( Jets[2].Pt(), weight );
									}
									if ( excl_bin ) break;
								}
							}
						}
					}
					break;
				}
			}
		}
	}

//	same part for GenJets

	if ( GenJetsNum > 1 )
	{
		if ( GenJetsNum > 2 && GenJets[2].Pt() > 5 )
		{
			completeGen =  2 * GenJets[2].Pt()/( GenJets[0].Pt() + GenJets[1].Pt() );
			parallelGen = (2*GenJets[2]*(GenJets[0]-GenJets[1]))/(((GenJets[0]-GenJets[1]).Pt())*( GenJets[0].Pt() + GenJets[1].Pt() ));

			perpendicularGen = TMath::Sqrt( TMath::Power( completeGen, 2 ) - TMath::Power( parallelGen, 2) );
		}
		else
		{
			completeGen = 0 ;
			parallelGen = 0 ;
			perpendicularGen = 0 ;
		}

		if (flag1 == 0 ) alphaGen = TMath::Abs(completeGen);
		if (flag1 == 1 ) alphaGen = TMath::Abs(parallelGen);
		if (flag1 == 2 ) alphaGen = TMath::Abs(perpendicularGen);

		if ( TMath::Abs(GenJets[0].DeltaPhi( GenJets[1] )) > 2.7 )
		{
			// I fill alpha_max histograms
			for ( int k = 0 ; k < PtBinsNo ; k++ )
			{
				if ( ( 0.5 * ( GenJets[0].Pt() + GenJets[1].Pt() ) < p_bins[ k + 1 ] ) &&
						( 0.5 * ( GenJets[0].Pt() + GenJets[1].Pt() ) > p_bins[ k ] ) )
				{
					for ( int r = 0 ; r < EtaBinsNo ; r++ )
					{
						if (TMath::Abs( GenJets[1].Eta() ) > eta_bins[r] && 
							TMath::Abs( GenJets[1].Eta() ) < eta_bins[r+1] && 
							TMath::Abs( GenJets[0].Eta() ) > eta_bins[r] && 
							TMath::Abs( GenJets[0].Eta() ) < eta_bins[r+1] )
						{
							for ( int m = 0 ; m < 5 ; m++ )
							{
								if ( alphaGen < alpha_bins[ m+1 ] )
								{
									asymmetries_gen_all.at(r).at(k).at(m) -> Fill( ( GenJets[0].Pt() - GenJets[1].Pt() )/( GenJets[0].Pt() + GenJets[1].Pt() ) , weight );
									asymmetries_gen_pt_all.at(r).at(k).at(m) -> Fill( 0.5 * ( GenJets[0].Pt() + GenJets[1].Pt() ), weight );
									if ( excl_bin ) break;
								}
							}
						}
					}
					for ( int r = 0 ; r < EtaFtControlBinsNo ; r++ )
					{
						if ((TMath::Abs( GenJets[1].Eta() ) > 0. && 
							TMath::Abs( GenJets[1].Eta() ) < 1.3 && 
							TMath::Abs( GenJets[0].Eta() ) > eta_bins_control[r] && 
							TMath::Abs( GenJets[0].Eta() ) < eta_bins_control[r+1]) || 
							(TMath::Abs( GenJets[0].Eta() ) > 0. && 
							TMath::Abs( GenJets[0].Eta() ) < 1.3 && 
							TMath::Abs( GenJets[1].Eta() ) > eta_bins_control[r] && 
							TMath::Abs( GenJets[1].Eta() ) < eta_bins_control[r+1]) )
						{
							for ( int m = 0 ; m < 5 ; m++ )
							{
								if ( alpha < alpha_bins[ m+1 ] )
								{
									forward_gen_hist_dijet.at(r).at(k).at(m) -> Fill( TMath::Abs(( GenJets[0].Pt() - GenJets[1].Pt() )/( GenJets[0].Pt() + GenJets[1].Pt() )) , weight );
									forward_pt_gen_hist_dijet.at(r).at(k).at(m) -> Fill( 0.5 * ( GenJets[0].Pt() + GenJets[1].Pt() ), weight );
									if ( excl_bin ) break;
								}
							}
						}
					}
					break;
				}
			}
			for ( int k = 0 ; k < PtFTBinsNo ; k++ )
			{
				if ( ( 0.5 * ( GenJets[0].Pt() + GenJets[1].Pt() ) < p_bins_FT[ k + 1 ] ) &&
						( 0.5 * ( GenJets[0].Pt() + GenJets[1].Pt() ) > p_bins_FT[ k ] ) )
				{
					for ( int r = 0 ; r < EtaFtBinsNo ; r++ )
					{
						if ((TMath::Abs( GenJets[1].Eta() ) > 0. && 
							TMath::Abs( GenJets[1].Eta() ) < 1.3 && 
							TMath::Abs( GenJets[0].Eta() ) > eta_ref_down[r] && 
							TMath::Abs( GenJets[0].Eta() ) < eta_ref_up[r]) || 
							(TMath::Abs( GenJets[0].Eta() ) > 0. && 
							TMath::Abs( GenJets[0].Eta() ) < 1.3 && 
							TMath::Abs( GenJets[1].Eta() ) > eta_ref_down[r] && 
							TMath::Abs( GenJets[1].Eta() ) < eta_ref_up[r]) )
						{
							for ( int m = 0 ; m < 5 ; m++ )
							{
								if ( alpha < alpha_bins[ m+1 ] )
								{
									forward_gen_hist.at(r).at(k).at(m) -> Fill( TMath::Abs(( GenJets[0].Pt() - GenJets[1].Pt() )/( GenJets[0].Pt() + GenJets[1].Pt() )) , weight );
									forward_gen_pt_hist.at(r).at(k).at(m) -> Fill( 0.5 * ( GenJets[0].Pt() + GenJets[1].Pt() ), weight );
									if ( excl_bin ) break;
								}
							}
						}
					}	
					break;
				}
			}
		}
	}

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

	TFile *fpt = new TFile("pt_mc_incl_full.root","RECREATE"); ;
	fpt->cd();
	h_FEJetAvePt -> Write();
	h_FEJet1Pt -> Write();
	h_FEJet2Pt -> Write();
	h_FEJet3Pt -> Write();
	h_JetAvePt -> Write();
	h_Jet1Pt -> Write();
	h_Jet2Pt -> Write();
	h_Jet3Pt -> Write();
	fpt->Close();

	TFile *fprim = new TFile("PU_incl_full.root","RECREATE"); ;
	fprim->cd();

	h_PU -> Write();

	fprim -> Close();

	TFile *f = new TFile("histograms_mc_incl_full.root","RECREATE"); ;

	for( int m = 0; m < EtaBinsNo; m++ )
	{
		for( int p = 0; p < PtBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				asymmetries_all.at(m).at(p).at(r) -> Write();
			}
		}
	}

	for( int m = 0; m < EtaBinsNo; m++ )
	{
		for( int p = 0; p < PtBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				asymmetries_pt_all.at(m).at(p).at(r) -> Write();
			}
		}
	}

	for( int m = 0; m < EtaBinsNo; m++ )
	{
		for( int p = 0; p < PtBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				asymmetries_gen_all.at(m).at(p).at(r) -> Write();
			}
		}
	}

	for( int m = 0; m < EtaBinsNo; m++ )
	{
		for( int p = 0; p < PtBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				asymmetries_gen_pt_all.at(m).at(p).at(r) -> Write();
			}
		}
	}

	for( int m = 0; m < EtaFtBinsNo; m++ )
	{
		for( int p = 0; p < PtFTBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				forward_hist.at(m).at(p).at(r) -> Write();
			}
		}
	}

	for( int m = 0; m < EtaFtBinsNo; m++ )
	{
		for( int p = 0; p < PtFTBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				forward_pt_hist.at(m).at(p).at(r) -> Write();
			}
		}
	}

	for( int m = 0; m < EtaFtBinsNo; m++ )
	{
		for( int p = 0; p < PtFTBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				forward_gen_hist.at(m).at(p).at(r) -> Write();
			}
		}
	}

	for( int m = 0; m < EtaFtBinsNo; m++ )
	{
		for( int p = 0; p < PtFTBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				forward_gen_pt_hist.at(m).at(p).at(r) -> Write();
			}
		}
	}

	for( int m = 0; m < EtaFtControlBinsNo; m++ )
	{
		for( int p = 0; p < PtBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				forward_hist_dijet.at(m).at(p).at(r) -> Write();
			}
		}
	}

	for( int m = 0; m < EtaFtControlBinsNo; m++ )
	{
		for( int p = 0; p < PtBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				forward_pt_hist_dijet.at(m).at(p).at(r) -> Write();
			}
		}
	}

	for( int m = 0; m < EtaFtControlBinsNo; m++ )
	{
		for( int p = 0; p < PtBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				forward_gen_hist_dijet.at(m).at(p).at(r) -> Write();
			}
		}
	}

	for( int m = 0; m < EtaFtControlBinsNo; m++ )
	{
		for( int p = 0; p < PtBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				forward_pt_gen_hist_dijet.at(m).at(p).at(r) -> Write();
			}
		}
	}

	f -> Close();
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
