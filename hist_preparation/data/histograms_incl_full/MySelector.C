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
#include <algorithm>

bool sortFunct( MyJet a, MyJet b) { return ( a.Pt() > b.Pt() ); }

void MySelector::BuildEvent() 
{		//here I prepare vectors of reco and gen jets which I will later use

	int JetsNum = p4_;

   Jets.clear();
   for (int i = 0; i < JetsNum ; ++i)
	{
      MyJet jet(p4_fCoordinates_fPt[i], p4_fCoordinates_fEta[i], p4_fCoordinates_fPhi[i], p4_fCoordinates_fE[i]);
      Jets.push_back(jet);
   }

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

	h_alpha_raw = new TH1F( "Alpha_raw" , "#alpha before selection" , 50 , 0 , 0.5 );
	h_alpha_raw -> SetXTitle( "#alpha_raw" );
	h_alpha_raw -> Sumw2();

	h_alpha_select = new TH1F( "Alpha" , "#alpha after selection" , 50 , 0 , 0.5 );
	h_alpha_select -> SetXTitle( "#alpha" );
	h_alpha_select -> Sumw2();

	EtaBinsNo = 6;
	EtaFtBinsNo = 2;
	EtaFtControlBinsNo = 4;

	PtBinsNo = 9;
	PtFTBinsNo = 6;

	// I define histograms for the "normal" JER calculation

	for( int m = 0; m < EtaBinsNo; m++ )
	{
		std::vector< std::vector< TH1F* > > temp2;
		std::vector< std::vector< TH1F* > > temp2pt;

		for( int p = 0; p < PtBinsNo; p++ )
		{
			std::vector< TH1F* > temp1;
			std::vector< TH1F* > temp1pt;
			for( int r = 0; r < 5; r++ )
			{
				TString name_fw = "asymm_";
				name_fw += "eta"; name_fw += m+1; name_fw += "_pt"; name_fw += p+1; name_fw += "_alpha"; name_fw += r+1; 

				TString name_fw_pt = "asymmpt_";
				name_fw_pt += "probe"; name_fw_pt += m+1; name_fw_pt += "_pt"; name_fw_pt += p+1; name_fw_pt += "_alpha"; name_fw_pt += r+1; 

				TH1F *h1 = new TH1F( name_fw, name_fw, 50, 0, 0.8 );
				h1 ->GetYaxis()->SetTitle("a.u.");	h1 ->GetXaxis()->SetTitle("Asymmetry");
				h1 -> Sumw2();
				temp1.push_back(h1);

				TH1F *h2 = new TH1F( name_fw_pt, name_fw_pt, 50, 0, 1500 );
				h2 ->GetYaxis()->SetTitle("a.u.");	h2 ->GetXaxis()->SetTitle("Pt[GeV]");
				h2 -> Sumw2();
				temp1pt.push_back(h2);
			}
			temp2.push_back(temp1);
			temp2pt.push_back(temp1pt);
		}
		asymmetries_all.push_back(temp2);
		asymmetries_pt_all.push_back(temp2pt);
	}

	// I define histograms used in forward extension for reference eta ( 0, 1.3 )

	for( int m = 0; m < EtaFtBinsNo; m++ )
	{
		std::vector< std::vector< TH1F* > > temp2, temp2pt;

		for( int p = 0; p < PtFTBinsNo; p++ )
		{
			std::vector< TH1F* > temp1, temp1pt;
			for( int r = 0; r < 5; r++ )
			{
				TString name_fw = "forward_";
				name_fw += "probe"; name_fw += m+6; name_fw += "_pt"; name_fw += p+1; name_fw += "_alpha"; name_fw += r+1; 

				TString name_fw_pt = "forwardpt_";
				name_fw_pt += "probe"; name_fw_pt += m+6; name_fw_pt += "_pt"; name_fw_pt += p+1; name_fw_pt += "_alpha"; name_fw_pt += r+1; 

				TH1F *h1 = new TH1F( name_fw, name_fw, 50, 0, 0.8 );
				h1 ->GetYaxis()->SetTitle("a.u.");	h1 ->GetXaxis()->SetTitle("Asymmetry");
				h1 -> Sumw2();
				temp1.push_back(h1);

				TH1F *h2 = new TH1F( name_fw_pt, name_fw_pt, 50, 0, 1500 );
				h2 ->GetYaxis()->SetTitle("a.u.");	h2 ->GetXaxis()->SetTitle("Pt[GeV]");
				h2 -> Sumw2();
				temp1pt.push_back(h2);
			}
			temp2.push_back(temp1);
			temp2pt.push_back(temp1pt);
		}
		forward_hist.push_back(temp2);
		forward_pt_hist.push_back(temp2pt);
	}

	// I define histograms for the control eta bins for forward method calculation

	for( int m = 0; m < EtaFtControlBinsNo; m++ )
	{
		std::vector< std::vector< TH1F* > > temp2, temp2pt;

		for( int p = 0; p < PtBinsNo; p++ )
		{
			std::vector< TH1F* > temp1, temp1pt;
			for( int r = 0; r < 5; r++ )
			{
				TString name_fw = "forward_control_";
				name_fw += "probe"; name_fw += m+2; name_fw += "_pt"; name_fw += p+1; name_fw += "_alpha"; name_fw += r+1; 

				TString name_fw_pt = "forwardpt_control_";
				name_fw_pt += "probe"; name_fw_pt += m+2; name_fw_pt += "_pt"; name_fw_pt += p+1; name_fw_pt += "_alpha"; name_fw_pt += r+1; 

				TH1F *h1 = new TH1F( name_fw, name_fw, 50, 0, 0.8 );
				h1 ->GetYaxis()->SetTitle("a.u.");	h1 ->GetXaxis()->SetTitle("Asymmetry");
				h1 -> Sumw2();
				temp1.push_back(h1);

				TH1F *h2 = new TH1F( name_fw_pt, name_fw_pt, 50, 0, 1500 );
				h2 ->GetYaxis()->SetTitle("a.u.");	h2 ->GetXaxis()->SetTitle("Pt[GeV]");
				h2 -> Sumw2();
				temp1pt.push_back(h2);
			}
			temp2.push_back(temp1);
			temp2pt.push_back(temp1pt);
		}
		forward_dijet_hist.push_back(temp2);
		forward_dijet_pt_hist.push_back(temp2pt);
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

	int JetsNum = p4_;
	
	int p_bins [] = { 55, 77, 99, 165, 231, 298, 365, 451, 561, 1500 };
	int p_bins_FT [] = { 77, 99, 121, 187, 253, 342, 1500 };

	double eta_bins [] = { 0, 0.8, 1.3, 1.9, 2.5, 3.0, 3.2 };
	double eta_ref_down [] = { 3.0, 3.2 };
	double eta_ref_up [] = { 3.2, 4.7 };
	double eta_bins_control [] = { 0, 1.3, 1.9, 2.5, 3.0 };
	double alpha_bins [] = { 0, 0.1, 0.15, 0.2, 0.25, 0.3 };

	std::string trigger_names[]={"HLT_DiPFJetAve40","HLT_DiPFJetAve60","HLT_DiPFJetAve60","HLT_DiPFJetAve60","HLT_DiPFJetAve200","HLT_DiPFJetAve260","HLT_DiPFJetAve320","HLT_DiPFJetAve400","HLT_DiPFJetAve500"};
	std::string ft_trigger_names[]={"HLT_DiPFJetAve60_HFJEC","HLT_DiPFJetAve80_HFJEC ","HLT_DiPFJetAve100_HFJEC","HLT_DiPFJetAve160_HFJEC","HLT_DiPFJetAve220_HFJEC","HLT_DiPFJetAve300_HFJEC"};

	bool trigger[9];
	bool ftrigger[6];

	std::fill_n(trigger, 9, false);
	std::fill_n(ftrigger, 6, false);

	for( int i = 0; i < PtBinsNo; i++ )
	{
		for(std::vector<std::string>::iterator it = paths->begin(); it != paths->end(); ++it)
		{
			if((*it).std::string::find(trigger_names[i])!=std::string::npos)
			{
				trigger[i] = true;
			}
		}
	}
	for( int i = 0; i < PtFTBinsNo; i++ )
	{
		for(std::vector<std::string>::iterator it = paths->begin(); it != paths->end(); ++it)
		{
			if((*it).std::string::find(ft_trigger_names[i])!=std::string::npos)
			{
				ftrigger[i] = true;
			}
		}
	}

	double weight;

	weight = 1.0;

	if( TotalEvents%100000 == 0 )
	{
		std::cout << "			Analyzing event #" << TotalEvents << std::endl;
	}

	h_PU -> Fill( npuIT, 1 );

	double alpha_raw;
	if ( JetsNum > 2 && Jets[2].Pt() > 10 )
		{
			alpha_raw =  2 * Jets[2].Pt()/( Jets[0].Pt() + Jets[1].Pt() );
		}

	h_alpha_raw -> Fill( alpha_raw, 1 );

	double parallel, perpendicular, complete, alpha;

	// Below I choose what kind of asymmetries I want to study!

//	bool excl_bin = true;  // exclusive
	bool excl_bin = false; // inclusive

	int flag1 = 0; // 0 -> complete_alpha
						// 1 -> parallel
						// 2 -> perpendicular

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

		if ( TMath::Abs(Jets[0].DeltaPhi( Jets[1] )) > 2.7 )
		{
		// I fill alpha_max histograms
			for ( int k = 0 ; k < PtBinsNo ; k++ )
			{
			if(trigger[k])
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
							h_alpha_select -> Fill( alpha, 1 );

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
									forward_dijet_hist.at(r).at(k).at(m) -> Fill( TMath::Abs(( Jets[0].Pt() - Jets[1].Pt() )/( Jets[0].Pt() + Jets[1].Pt() )) , weight );
									forward_dijet_pt_hist.at(r).at(k).at(m) -> Fill( 0.5 * ( Jets[0].Pt() + Jets[1].Pt() ), weight );
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
			for ( int k = 0 ; k < PtFTBinsNo ; k++ )
			{
			if(ftrigger[k])
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
	}

   return kTRUE;
}

void MySelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

	std::cout <<"			Analyzed events #" <<  TotalEvents << std::endl;
	TFile *fpt = new TFile("pt_data_incl_full.root","NEW"); ;
	fpt->cd();
	h_alpha_raw -> Write();
	h_alpha_select -> Write();
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


	TFile *f = new TFile("histograms_data_incl_full.root","NEW"); ;
	f->cd();

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
	for( int m = 0; m < EtaFtControlBinsNo; m++ )
	{
		for( int p = 0; p < PtBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				forward_dijet_hist.at(m).at(p).at(r) -> Write();
			}
		}
	}
	for( int m = 0; m < EtaFtControlBinsNo; m++ )
	{
		for( int p = 0; p < PtBinsNo; p++ )
		{
			for( int r = 0; r < 5; r++ )
			{
				forward_dijet_pt_hist.at(m).at(p).at(r) -> Write();
			}
		}
	}

	f -> Close();

}

void MySelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}


double Weight( std::string filename )
{
	if ( filename.std::string::find("Pt_5to10") != std::string::npos )		return 6.102e+10/3422691;
	if ( filename.std::string::find("Pt_10to15") != std::string::npos )		return 5.888e+09/3490055;
	if ( filename.std::string::find("Pt_15to30") != std::string::npos )		return 1.837e+09/4936496;
	if ( filename.std::string::find("Pt_30to50") != std::string::npos )		return 1.409e+08/4899251;
	if ( filename.std::string::find("Pt_50to80") != std::string::npos )		return 1.92e+07/4966990;
	if ( filename.std::string::find("Pt_80to120") != std::string::npos ) 	return 2.763e+06/3465021;
	if ( filename.std::string::find("Pt_120to170") != std::string::npos )	return 4.711e+05/3446207;
	if ( filename.std::string::find("Pt_170to300") != std::string::npos )	return 1.173e+05/3438066;
	if ( filename.std::string::find("Pt_300to470") != std::string::npos )	return 7823./2930578;
	if ( filename.std::string::find("Pt_470to600") != std::string::npos )	return 648.2/1939229;
	if ( filename.std::string::find("Pt_600to800") != std::string::npos )	return 186.9/1890256;
	if ( filename.std::string::find("Pt_800to1000") != std::string::npos )	return 32.29/1911296;
	if ( filename.std::string::find("Pt_1000to1400") != std::string::npos )	return 9.418/1461216;
	if ( filename.std::string::find("Pt_1400to1800") != std::string::npos )	return 0.8426/197959;
	if ( filename.std::string::find("Pt_1800to2400") != std::string::npos )	return 0.1149/194924;
	if ( filename.std::string::find("Pt_2400to3200") != std::string::npos )	return 0.00683/198383; 
	if ( filename.std::string::find("Pt_3200toInf") != std::string::npos )	return 0.0001654/188696; 
	else 
	{
		std::cout << "fail" << std::endl;
		return 0.0;
	}
}
