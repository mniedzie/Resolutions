#include <iostream>
#include <TChain.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1F.h>
#include <TLatex.h>
#include <TFile.h>
#include <TLine.h>
#include <TStyle.h>
#include <string>
#include <TMath.h>
#include <TLegend.h>
#include <TPaveStats.h>
#include <TGraphAsymmErrors.h>
#include <functions.C>

#include "TFrame.h"
#include "plotting/CMS_lumi.C"
#include "plotting/tdrstyle.C"

	// in below function, fitType 0 -> gaussian fit (mean fixed to 0), 1 -> RMS (100% of points), 2 -> shifted gaussian
	//void fitAsym( TH1F &hist, double &width, double &error , double &centre, double &centre_error, double &chisqr, int fitType );

void histLoadAsym( TFile &f, bool data, TString name, std::vector< std::vector< std::vector< TH1F* > > > &Asymmetry , std::vector< std::vector< std::vector< TH1F* > > > &GenAsymmetry , int ptbin, int etabin );
void histLoadFE1( TFile &f, bool data, TString name, std::vector< std::vector< std::vector< TH1F* > > > &forward_hist , std::vector< std::vector< std::vector< TH1F* > > > &forward_gen_hist, int ptbin , int etabin);
void histMeanFE_Pt( std::vector< std::vector< std::vector< TH1F* > > > &Asymmetry ,std::vector< std::vector< std::vector< double > > > &Widths );
void histWidthAsym( std::vector<std::vector<std::vector<TH1F*> > > &Asymmetry , std::vector<std::vector<std::vector<double> > > &Widths, std::vector<std::vector<std::vector<double> > > &WidthsError  );
void correctPLIbinbybin(std::vector<std::vector<std::vector<double> > > &Output, std::vector<std::vector<std::vector<double> > > &OutputError, std::vector<std::vector<std::vector<double> > > Widths, std::vector<std::vector<std::vector<double> > > WidthsError, std::vector<std::vector<std::vector<double> > > PLI, std::vector<std::vector<std::vector<double> > > PLIError);
void fill_PLI_hist( TString name1, std::vector< std::vector< TH1F* > > &widths_FE1, std::vector< std::vector< std::vector< double > > > Widths, std::vector< std::vector< std::vector< double > > > WidthsError, std::vector< std::vector< std::vector< double > > > pt_binning);
void fit_NSC_PLI( std::vector< std::vector< TF1* > > &functions, std::vector< std::vector< TH1F* > > PLI_hists );
void def_fill_PLI( TString name1, std::vector<std::vector<TH1F*> > &widths_FE1, std::vector<std::vector<TF1*> > functions, std::vector<std::vector<std::vector<double> > > WidthsError, std::vector<std::vector<std::vector<double> > > pt_binning );
void def_fill_widths( TString name1, std::vector< std::vector< TH1F* > > &widths_FE1 , std::vector< std::vector< std::vector< double > > > Widths, std::vector< std::vector< std::vector< double > > > WidthsError );
void correctForPLI( TString name1, std::vector<std::vector<TH1F*> > widths_FE1, std::vector<std::vector<TH1F*> > &output, std::vector<std::vector<TF1*> > functions, std::vector<std::vector<std::vector<double> > > pt_binning);
void histLinFit( std::vector< std::vector< TH1F* > > widths_hist_all , std::vector< std::vector< double > > &Widths, std::vector< std::vector< double > > &WidthsError );
void fill_widths_pt( TString name1, std::vector<TH1F*> &widths, std::vector<std::vector<double> > Widths, std::vector<std::vector<double> > WidthsError, std::vector<std::vector<std::vector<double> > > forward_width_pt );
void KFSR_ratios( TString name1, std::vector<TH1F*> &widths, std::vector<std::vector<double> > Widths, std::vector<std::vector<double> > WidthsError, std::vector<std::vector<double> > WidthsTwo, std::vector<std::vector<double> > WidthsTwoError, std::vector<std::vector<std::vector<double> > > forward_width_pt);
void widths_015_ratios( TString name1, std::vector<TH1F*> &widths, std::vector<std::vector<std::vector<double> > > Widths, std::vector<std::vector<std::vector<double> > > WidthsError, std::vector<std::vector<std::vector<double> > > WidthsTwo, std::vector<std::vector<std::vector<double> > > WidthsTwoError, std::vector<std::vector<std::vector<double> > > forward_width_pt );
void KNFS_line_fit( TString name1, std::vector<TH1F*> widths, std::vector< TF1* > &functions );
void correctKFSR( std::vector<std::vector<double> > &Output, std::vector<std::vector<double> > &OutputError, std::vector<std::vector<std::vector<double> > > Widths, std::vector<std::vector<std::vector<double> > > WidthsError, std::vector<TF1*> functions, std::vector<std::vector<std::vector<double> > > forward_width_pt );
void correctJERwithPLI( std::vector<std::vector<double> > &Output, std::vector<std::vector<double> > &OutputError, std::vector<std::vector<double> > Widths, std::vector<std::vector<double> > WidthsError, std::vector<std::vector<double> > PLI, std::vector<std::vector<double> > PLIError);
void correctJERwithPLI015(std::vector<std::vector<double> > &Output, std::vector<std::vector<double> > &OutputError, std::vector<std::vector<std::vector<double> > > Widths, std::vector<std::vector<std::vector<double> > > WidthsError, std::vector<std::vector<std::vector<double> > > PLI, std::vector<std::vector< std::vector< double > > > PLIError);
void correctForRef( TString name1, std::vector< std::vector< double > > &Output, std::vector< std::vector< double > > &OutputError, std::vector< std::vector< double > > Input, std::vector< std::vector< double > > InputError, std::vector<std::vector<std::vector<double> > > width_pt  );
void makeScales( std::vector< std::vector< double > > &Output, std::vector< std::vector< double > > &OutputError, std::vector< std::vector< double > > Input1, std::vector< std::vector< double > > Input1Error, std::vector< std::vector< double > > Input2, std::vector< std::vector< double > > Input2Error );
void fill_hist( TString name1, std::vector< TH1F* > &output, std::vector< std::vector< double > > Widths, std::vector< std::vector< double > > WidthsError, std::vector< std::vector< std::vector< double > > > pt_binning, double range);




void fitAsym( TH1F &hist, double &width, double &error , double &centre, double &centre_error, double &chisqr, int fitType, double position , bool fix ); // linear fit for general use ( extrapolating to alpha = 0 e.g.)
void fitConst( TH1F &hist, double &value, double &error );
void fitShift( TH1F &hist, double &a, double &errora, double &b, double &errorb ); //gaussian fit, used for MC-Truth
void fitMCTruth( TH1F &hist, double &width, double &error ); // truncated RMS, points from xq_IQW to yq_IQW, rejectes xq_IQW of all points from left, and points above yq_IQW of all points. Both variables from 0 to 1, xq < yq.  




int mainRun( bool data, const char* filename, const char* filename_data )		// filename is input .root file, data determines if we work on data or mc (no gen level info in data)
{

////////////////////////////////////////////////////////////////////////////
//		I load all histograms I will need                                   //
////////////////////////////////////////////////////////////////////////////

//	bool data = true;
						
	std::vector< std::vector< std::vector< TH1F* > > > asymmetries_all, asymmetries_gen_all, asymmetries_all_data;
	std::vector< std::vector< std::vector< TH1F* > > > asymmetries_all_pt, asymmetries_gen_all_pt, asymmetries_all_data_pt;

	std::vector< std::vector< std::vector< TH1F* > > > forward_hist, forward_gen_hist, forward_hist_data;
	std::vector< std::vector< std::vector< TH1F* > > > forward_hist_pt, forward_gen_hist_pt, forward_hist_data_pt;

	std::vector< std::vector< std::vector< TH1F* > > > forward_gen_hist_data, asymmetries_gen_all_data;

	int pt_bins = 9, pt_bins_fe = 6, eta_bins = 11, eta_bins_fe = 2, eta_bins_fec = 8;

//	int mode = 3;	// mode of the analysis:
						//		0 -> exclusive, full def				3 -> inclusive, full def
						//		1 -> exclusive, parallel part			4 -> inclusive, parallel part
						//		2 -> exclusive, perp. part				5 -> inclusive, perp. part   
						//		actualy it's now just for my information. doesn't make a difference...
	
	TFile *f, *f_data;

	f = new TFile( filename, "READ");
	f_data = new TFile( filename_data, "READ");

	histLoadAsym( *f_data, 	true, "asymm_eta", asymmetries_all_data, asymmetries_gen_all_data, pt_bins, eta_bins );	// load asymm from data
	histLoadAsym( *f, 	data, "asymm_eta", asymmetries_all, asymmetries_gen_all, pt_bins, eta_bins );		// load asymm from mc (all)

	histLoadAsym( *f_data, 	true, "asymmpt_probe", asymmetries_all_data_pt, asymmetries_gen_all_data, pt_bins, eta_bins );	// load asymm pt from data
	histLoadAsym( *f, 	data, "asymmpt_probe", asymmetries_all_pt, asymmetries_gen_all_pt, pt_bins, eta_bins );		// load asymm pt from mc (all)

	histLoadFE1( *f_data, 	true, "forward_control_probe", forward_hist_data , forward_gen_hist_data , pt_bins, eta_bins_fec );
	histLoadFE1( *f, 	data, "forward_control_probe", forward_hist , forward_gen_hist, pt_bins, eta_bins_fec );

	histLoadFE1( *f_data, 	true, "forward_probe", forward_hist_data , forward_gen_hist_data , pt_bins_fe, eta_bins_fe );
	histLoadFE1( *f, 	data, "forward_probe", forward_hist , forward_gen_hist, pt_bins_fe, eta_bins_fe );

	histLoadFE1( *f_data, 	true, "forwardpt_control_probe", forward_hist_data_pt , forward_gen_hist_data , pt_bins, eta_bins_fec );
	histLoadFE1( *f, 	data, "forwardpt_control_probe", forward_hist_pt , forward_gen_hist_pt, pt_bins, eta_bins_fec );

	histLoadFE1( *f_data, 	true, "forwardpt_probe", forward_hist_data_pt , forward_gen_hist_data , pt_bins_fe, eta_bins_fe );
	histLoadFE1( *f, 	data, "forwardpt_probe", forward_hist_pt , forward_gen_hist_pt, pt_bins_fe, eta_bins_fe );

////////////////////////////////////////////////////////////////////////////
//		End of loading histograms                                           //
////////////////////////////////////////////////////////////////////////////
//		I calculate pt_mean for each alpha and pt bin and eta bin.          //
////////////////////////////////////////////////////////////////////////////

	std::vector< std::vector< std::vector< double > > > forward_width_pt, forward_gen_width_pt, forward_width_data_pt;
	std::vector< std::vector< std::vector< double > > > asymmetries_width_pt, asymmetries_gen_width_pt, asymmetries_width_data_pt;

	histMeanFE_Pt( forward_hist_pt , forward_width_pt );
	histMeanFE_Pt( forward_gen_hist_pt , forward_gen_width_pt );
	histMeanFE_Pt( forward_hist_data_pt , forward_width_data_pt );

	histMeanFE_Pt( asymmetries_all_pt , asymmetries_width_pt);
	histMeanFE_Pt( asymmetries_gen_all_pt , asymmetries_gen_width_pt);
	histMeanFE_Pt( asymmetries_all_data_pt , asymmetries_width_data_pt);


////////////////////////////////////////////////////////////////////////////
//		End of alpha_mean calc.                                             //
////////////////////////////////////////////////////////////////////////////
//		I calculate width of asymmetry distributions                        //
////////////////////////////////////////////////////////////////////////////

	std::vector< std::vector< std::vector< double > > > forward_width, forward_gen_width, forward_width_data;
	std::vector< std::vector< std::vector< double > > > forward_width_error, forward_gen_width_error, forward_width_error_data;

	std::vector< std::vector< std::vector< double > > > asymmetries_width, asymmetries_gen_width, asymmetries_width_data;
	std::vector< std::vector< std::vector< double > > > asymmetries_width_error, asymmetries_gen_width_error, asymmetries_width_error_data;

	histWidthAsym( asymmetries_all , asymmetries_width, asymmetries_width_error );
	histWidthAsym( asymmetries_gen_all , asymmetries_gen_width, asymmetries_gen_width_error );
	histWidthAsym( asymmetries_all_data , asymmetries_width_data, asymmetries_width_error_data );

	histWidthAsym( forward_hist , forward_width, forward_width_error );
	histWidthAsym( forward_gen_hist , forward_gen_width, forward_gen_width_error );
	histWidthAsym( forward_hist_data , forward_width_data, forward_width_error_data );

////////////////////////////////////////////////////////////////////////////
// 	End of asymmetry fitting                                            //
////////////////////////////////////////////////////////////////////////////
//		I define width(alpha_max) histograms                                //
////////////////////////////////////////////////////////////////////////////

	std::vector< std::vector< TH1F* > > widths_hist_FE, widths_hist_FE_gen, widths_hist_FE_data;
	std::vector< std::vector< TH1F* > > widths_hist_all, widths_hist_all_gen, widths_hist_all_data;

	def_fill_widths( "widths", widths_hist_all , asymmetries_width, asymmetries_width_error );
	def_fill_widths( "widths_gen", widths_hist_all_gen , asymmetries_gen_width, asymmetries_gen_width_error );
	def_fill_widths( "widths_data", widths_hist_all_data , asymmetries_width_data, asymmetries_width_error_data );

	def_fill_widths( "widths_fe", widths_hist_FE , forward_width, forward_width_error );
	def_fill_widths( "widths_gen_fe", widths_hist_FE_gen , forward_gen_width, forward_gen_width_error );
	def_fill_widths( "widths_data_fe", widths_hist_FE_data , forward_width_data, forward_width_error_data );

////////////////////////////////////////////////////////////////////////////
//		histograms filled                                                   //
////////////////////////////////////////////////////////////////////////////
//		I fit line or const to width(alpha_max)                             //
////////////////////////////////////////////////////////////////////////////

	std::vector< std::vector< double > > widths_all, widths_gen_all, widths_all_data;
	std::vector< std::vector< double > > widths_all_error, widths_gen_all_error, widths_all_error_data;

	std::vector< std::vector< double > > widths_FE, widths_gen_FE, widths_FE_data;
	std::vector< std::vector< double > > widths_FE_error, widths_gen_FE_error, widths_FE_error_data;

	histLinFit( widths_hist_all , widths_all, widths_all_error );
	histLinFit( widths_hist_all_gen , widths_gen_all, widths_gen_all_error );
	histLinFit( widths_hist_all_data , widths_all_data, widths_all_error_data );

	histLinFit( widths_hist_FE , widths_FE, widths_FE_error );
	histLinFit( widths_hist_FE_gen , widths_gen_FE, widths_gen_FE_error );
	histLinFit( widths_hist_FE_data , widths_FE_data, widths_FE_error_data );

////////////////////////////////////////////////////////////////////////////
//		End of lin-fit                                                      //
////////////////////////////////////////////////////////////////////////////
//		I make histograms ratio of widths(alpha=0.15)                       //
////////////////////////////////////////////////////////////////////////////

	std::vector< TH1F* > widths_015_ratios_all, widths_015_ratios_FE;/////////////

	widths_015_ratios( "widths_015_ratios", widths_015_ratios_all, asymmetries_width_data, asymmetries_width_error_data, asymmetries_width, asymmetries_width_error, asymmetries_width_data_pt );
	widths_015_ratios( "widths_015_FE_ratios", widths_015_ratios_FE, forward_width_data, forward_width_error_data, forward_width, forward_width_error, forward_width_data_pt );

////////////////////////////////////////////////////////////////////////////
//		Finished histograms for method check (for Mikkos check)             //
////////////////////////////////////////////////////////////////////////////
//		I correct for PLI using b parameter from line fit to sigma_A(alpha) //
////////////////////////////////////////////////////////////////////////////

	std::vector< std::vector< double > > JER_MC, JER_data;
	std::vector< std::vector< double > > JER_MC_error, JER_data_error;

	std::vector< std::vector< double > > JER_uncor_FE_MC, JER_uncor_FE_data;
	std::vector< std::vector< double > > JER_uncor_FE_MC_error, JER_uncor_FE_data_error;

	correctJERwithPLI( JER_MC, JER_MC_error, widths_all, widths_all_error, widths_gen_all, widths_gen_all_error);
	correctJERwithPLI( JER_data, JER_data_error, widths_all_data, widths_all_error_data, widths_gen_all, widths_gen_all_error);

	correctJERwithPLI( JER_uncor_FE_MC, JER_uncor_FE_MC_error, widths_FE, widths_FE_error, widths_gen_FE, widths_gen_FE_error);
	correctJERwithPLI( JER_uncor_FE_data, JER_uncor_FE_data_error, widths_FE_data, widths_FE_error_data, widths_gen_FE, widths_gen_FE_error);

////////////////////////////////////////////////////////////////////////////
//		PLI corrected using b parameters                                    //
////////////////////////////////////////////////////////////////////////////
//		I do the same for widths at alpha = 0.15                            //
////////////////////////////////////////////////////////////////////////////

	std::vector< std::vector< double > > JER015_MC, JER015_data;
	std::vector< std::vector< double > > JER015_MC_error, JER015_data_error;

	std::vector< std::vector< double > > JER015_uncor_FE_MC, JER015_uncor_FE_data;
	std::vector< std::vector< double > > JER015_uncor_FE_MC_error, JER015_uncor_FE_data_error;

	correctJERwithPLI015(JER015_MC, JER015_MC_error, asymmetries_width, asymmetries_width_error, asymmetries_gen_width, asymmetries_gen_width_error);
	correctJERwithPLI015(JER015_data, JER015_data_error, asymmetries_width_data, asymmetries_width_error_data, asymmetries_gen_width, asymmetries_gen_width_error);

	correctJERwithPLI015(JER015_uncor_FE_MC, JER015_uncor_FE_MC_error, forward_width, forward_width_error, forward_gen_width, forward_gen_width_error);
	correctJERwithPLI015(JER015_uncor_FE_data, JER015_uncor_FE_data_error, forward_width_data, forward_width_error_data, forward_gen_width, forward_gen_width_error);

////////////////////////////////////////////////////////////////////////////
//		I corrected alpha = 0.15 widhs for PLI correct way                  //
////////////////////////////////////////////////////////////////////////////
//		I correct forward widths for Ref region.                            //
////////////////////////////////////////////////////////////////////////////

	std::vector< std::vector< double > > JER_FE_MC, JER_FE_data;
	std::vector< std::vector< double > > JER_FE_MC_error, JER_FE_data_error;

	correctForRef( "mccorrected", JER_FE_MC, JER_FE_MC_error, JER_uncor_FE_MC, JER_uncor_FE_MC_error, forward_width_pt  );
	correctForRef( "datacorrect", JER_FE_data, JER_FE_data_error, JER_uncor_FE_data, JER_uncor_FE_data_error, forward_width_data_pt  );

////////////////////////////////////////////////////////////////////////////
//		forward widths corrected for Ref widths!                            //
////////////////////////////////////////////////////////////////////////////
//		and again, Ref region for widths at alpha = 0.15                    //
////////////////////////////////////////////////////////////////////////////

	std::vector< std::vector< double > > JER015_FE_MC, JER015_FE_data;
	std::vector< std::vector< double > > JER015_FE_MC_error, JER015_FE_data_error;

	correctForRef( "mccorrected015", JER015_FE_MC, JER015_FE_MC_error, JER015_uncor_FE_MC, JER015_uncor_FE_MC_error, forward_width_pt  );
	correctForRef( "datacorrect015", JER015_FE_data, JER015_FE_data_error, JER015_uncor_FE_data, JER015_uncor_FE_data_error, forward_width_data_pt  );

////////////////////////////////////////////////////////////////////////////
//		Ref reg corrected for widths at alpha = 0.15                        //
////////////////////////////////////////////////////////////////////////////
//		I make make vectors with ratios of widths                           //
////////////////////////////////////////////////////////////////////////////

	std::vector< std::vector< double > > scales_classic, scales_fe, scales_fe_control;
	std::vector< std::vector< double > > scales_classic_error, scales_fe_error, scales_fe_control_error;

	makeScales( scales_classic, scales_classic_error, JER_data, JER_data_error, JER_MC, JER_MC_error );
	makeScales( scales_fe, scales_fe_error, JER_FE_data, JER_FE_data_error, JER_FE_MC, JER_FE_MC_error );

	makeScales( scales_fe_control, scales_fe_control_error, JER_uncor_FE_data, JER_uncor_FE_data_error, JER_uncor_FE_MC, JER_uncor_FE_MC_error );	// uncorrected for reference region width, as a cross check. (i think)


	for ( unsigned int m = 0; m < scales_fe.size(); m++)
	{
		for ( unsigned int i = 0; i < scales_fe.at(m).size(); i++ )
		{
			std::cout << "pt	" << forward_width_data_pt.at(m).at(i).at(0) << "eta	" << m << ", pt	" << i << ", data	" << JER_FE_data.at(m).at(i) << ", mc	" << JER_FE_MC.at(m).at(i) << ", ratio	" << scales_fe.at(m).at(i) << std::endl;
		}
	}

// and same thing for using-b-parameter calculations

	std::vector< std::vector< double > > scales015_classic, scales015_fe;
	std::vector< std::vector< double > > scales015_classic_error, scales015_fe_error;

	makeScales( scales015_classic, scales015_classic_error, JER015_data, JER015_data_error, JER015_MC, JER015_MC_error );
	makeScales( scales015_fe, scales015_fe_error, JER015_FE_data, JER015_FE_data_error, JER015_FE_MC, JER015_FE_MC_error );

////////////////////////////////////////////////////////////////////////////
//		I have vectors with ratios of widths                                //
////////////////////////////////////////////////////////////////////////////
//		I make histograms with  JERs and scale factors                      //
////////////////////////////////////////////////////////////////////////////

	std::vector< TH1F* > JER_MC_hist, JER_data_hist, JER_scale_hist;
	std::vector< TH1F* > JER_FE_MC_hist, JER_FE_data_hist, JER_FE_scale_hist;

	fill_hist( "MC_JER_classic", JER_MC_hist, JER_MC, JER_MC_error, asymmetries_width_pt, 0.2);
	fill_hist( "data_JER_classtc", JER_data_hist, JER_data, JER_data_error, asymmetries_width_data_pt, 0.2);
	fill_hist( "SF_classic", JER_scale_hist, scales_classic, scales_classic_error, asymmetries_width_data_pt, 2.);

	fill_hist( "MC_JER_FE", JER_FE_MC_hist, JER_FE_MC, JER_FE_MC_error, forward_width_pt, 0.5);
	fill_hist( "data_JER_FE", JER_FE_data_hist, JER_FE_data, JER_FE_data_error, forward_width_data_pt, 0.5);
	fill_hist( "SF_FE", JER_FE_scale_hist, scales_fe, scales_fe_error, forward_width_data_pt, 2.0);

	std::vector< TH1F* > JER_FE_MC_hist_control, JER_FE_data_hist_control, JER_FE_scale_hist_control;

	fill_hist( "MC_JER_FE_control", JER_FE_MC_hist_control, JER_uncor_FE_MC, JER_uncor_FE_MC_error, forward_width_pt, 0.5);
	fill_hist( "data_JER_FE_control", JER_FE_data_hist_control, JER_uncor_FE_data, JER_uncor_FE_data_error, forward_width_data_pt, 0.5);
	fill_hist( "SF_FE_control", JER_FE_scale_hist_control, scales_fe_control, scales_fe_control_error, forward_width_data_pt, 2.0);

	std::vector< TH1F* > JER015_scale_hist, JER015_FE_scale_hist;

	fill_hist( "SF_classic015", JER015_scale_hist, scales015_classic, scales015_classic_error, asymmetries_width_data_pt, 2.);
	fill_hist( "SF_FE015", JER015_FE_scale_hist, scales015_fe, scales015_fe_error, forward_width_data_pt, 2.0);

//////////////////////////////////////////////////////////////////////////
//		I divide the histograms
//////////////////////////////////////////////////////////////////////////

//	std::vector< std::vector< std::vector< TH1F* > > > asymmetries_all, asymmetries_gen_all, asymmetries_all_data;
//	std::vector< std::vector< std::vector< TH1F* > > > asymmetries_all_pt, asymmetries_gen_all_pt, asymmetries_all_data_pt;
//
//	std::vector< std::vector< std::vector< TH1F* > > > forward_hist, forward_gen_hist, forward_hist_data;
//	std::vector< std::vector< std::vector< TH1F* > > > forward_hist_pt, forward_gen_hist_pt, forward_hist_data_pt;

	TFile hprim("output/asymmetries.root","RECREATE");

	for( unsigned int m = 0; m < asymmetries_all.size(); m++ )
	{
		for( unsigned int p = 0; p < asymmetries_all.at(m).size(); p++ )
		{
			for( unsigned int r = 0; r < asymmetries_all.at(m).at(p).size(); r++ )
			{
				asymmetries_all.at(m).at(p).at(r) -> Write();
				asymmetries_gen_all.at(m).at(p).at(r) -> Write();
				asymmetries_all_data.at(m).at(p).at(r) -> Write();
			}
		}
	}

	for( unsigned int m = 0; m < forward_hist.size(); m++ )
	{
		for( unsigned int p = 0; p < forward_hist.at(m).size(); p++ )
		{
			for( unsigned int r = 0; r < forward_hist.at(m).at(p).size(); r++ )
			{
				forward_hist.at(m).at(p).at(r) -> Write();
				forward_gen_hist.at(m).at(p).at(r) -> Write();
				forward_hist_data.at(m).at(p).at(r) -> Write();
			}
		}
	}


	TFile hprimm("output/widths.root","RECREATE");

	for( unsigned int m = 0; m < widths_hist_FE.size(); m++ )
	{
		for( unsigned int p = 0; p < widths_hist_FE.at(m).size(); p++ )
		{
			widths_hist_FE.at(m).at(p) -> Write();
			widths_hist_FE_gen.at(m).at(p) -> Write();
			widths_hist_FE_data.at(m).at(p) -> Write();
		}
	}

	for( unsigned int m = 0; m < widths_hist_all.size(); m++ )
	{
		for( unsigned int p = 0; p < widths_hist_all.at(m).size(); p++ )
		{
			widths_hist_all.at(m).at(p) -> Write();
			widths_hist_all_gen.at(m).at(p) -> Write();
			widths_hist_all_data.at(m).at(p) -> Write();
		}
	}

	hprimm.Close();


	TFile gprim("output/JERs.root","RECREATE");

	for( unsigned int m = 0; m < JER_MC_hist.size(); m++ )
	{
		JER_MC_hist.at(m) -> Write();
	}

	for( unsigned int m = 0; m < JER_data_hist.size(); m++ )
	{
		JER_data_hist.at(m) -> Write();
	}

	for( unsigned int m = 0; m < JER_FE_MC_hist.size(); m++ )
	{
		JER_FE_MC_hist.at(m) -> Write();
	}

	for( unsigned int m = 0; m < JER_FE_data_hist.size(); m++ )
	{
		JER_FE_data_hist.at(m) -> Write();
	}

	for( unsigned int m = 0; m < JER_FE_MC_hist_control.size(); m++ )
	{
		JER_FE_MC_hist_control.at(m) -> Write();
	}
	for( unsigned int m = 0; m < JER_FE_data_hist_control.size(); m++ )
	{
		JER_FE_data_hist_control.at(m) -> Write();
	}

	gprim.Close();


	TFile gbis("output/SFs.root","RECREATE");

	for( unsigned int m = 0; m < JER_scale_hist.size(); m++ )
	{
		std::cout << "standard scales, eta bin " << m << std::endl;
		JER_scale_hist.at(m) -> Fit("pol0","");
		JER_scale_hist.at(m) -> Write();
		std::cout << std::endl;
		std::cout << std::endl;
	}

	for( unsigned int m = 0; m < JER_FE_scale_hist_control.size(); m++ )
	{
		std::cout << "FE control scales, eta bin " << m << std::endl;
		JER_FE_scale_hist_control.at(m) -> Fit("pol0","");
		JER_FE_scale_hist_control.at(m) -> Write();
		std::cout << std::endl;
		std::cout << std::endl;
	}

	for( unsigned int m = 0; m < JER015_scale_hist.size(); m++ )
	{
		std::cout << "standard with 0.15 scales, eta bin " << m << std::endl;
		JER015_scale_hist.at(m) -> Fit("pol0","");
		JER015_scale_hist.at(m) -> Write();
		std::cout << std::endl;
		std::cout << std::endl;
	}

	for( unsigned int m = 0; m < JER015_FE_scale_hist.size(); m++ )
	{
		std::cout << "FE with 015 scales, eta bin " << m << std::endl;
		JER015_FE_scale_hist.at(m) -> Fit("pol0","");
		JER015_FE_scale_hist.at(m) -> Write();
		std::cout << std::endl;
		std::cout << std::endl;
	}

	for( unsigned int m = 0; m < JER_FE_scale_hist.size(); m++ )
	{
		std::cout << "FE scales, eta bin " << m << std::endl;
		JER_FE_scale_hist.at(m) -> Fit("pol0","");
		JER_FE_scale_hist.at(m) -> Write();
		std::cout << std::endl;
		std::cout << std::endl;
	}

	gbis.Close();

	setTDRStyle();

	int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
	extraText  = "       Preliminary";  // default extra text is "Preliminary"
	lumi_13TeV = "2.1 fb^{-1}";
	lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

	gStyle -> SetOptFit(1);

	int W = 800;
	int H = 600;
	
	int H_ref = 600; 
	int W_ref = 800; 
			
	// references for T, B, L, R
	float T = 0.08*H_ref;
	float B = 0.12*H_ref; 
	float L = 0.12*W_ref;
	float R = 0.04*W_ref;

	TFile h_merged("output/widths_merged.root","RECREATE");

	for( unsigned int m = 0; m < widths_hist_FE.size(); m++ )
	{
		for( unsigned int p = 0; p < widths_hist_FE.at(m).size(); p++ )
		{
			TString canvName = widths_hist_FE.at(m).at(p) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			if( widths_hist_FE.at(m).at(p) -> GetEntries() != 0 )     widths_hist_FE.at(m).at(p) -> GetFunction("linfit")->SetLineColor(6);
			if( widths_hist_FE_gen.at(m).at(p) -> GetEntries() != 0 ) widths_hist_FE_gen.at(m).at(p) -> GetFunction("linfit")->SetLineColor(2);
			if( widths_hist_FE_data.at(m).at(p) -> GetEntries() != 0 )widths_hist_FE_data.at(m).at(p) -> GetFunction("linfit")->SetLineColor(4);

			widths_hist_FE.at(m).at(p) -> SetMarkerColor(6);
			widths_hist_FE_gen.at(m).at(p) -> SetMarkerColor(2);
			widths_hist_FE_data.at(m).at(p) -> SetMarkerColor(4);

			widths_hist_FE.at(m).at(p) -> SetMarkerStyle(20);
			widths_hist_FE_gen.at(m).at(p) -> SetMarkerStyle(20);
			widths_hist_FE_data.at(m).at(p) -> SetMarkerStyle(20);

			widths_hist_FE.at(m).at(p) -> Draw();

			canv->Update();
			TPaveStats *stats1 = (TPaveStats*)canv->GetPrimitive("stats");
			stats1->SetName("h1stats2");
			stats1->SetY1NDC(.14);
			stats1->SetY2NDC(.30);
			stats1->SetX1NDC(.71);
			stats1->SetX2NDC(.96);
			stats1->SetTextColor(6);

			TList *list1 = stats1->GetListOfLines();
			TLatex *myt1 = new TLatex(0,0,"MC = ");
			myt1 ->SetTextFont(42);
			myt1 ->SetTextSize(0.04);
			myt1 ->SetTextColor(6);
			list1->AddFirst(myt1);

				canv->Update();
			if ( !((p == 1) && ( m > 3)) ) 
			{
				widths_hist_FE_data.at(m).at(p) -> Draw();

				canv->Update();
				TPaveStats *stats3 = (TPaveStats*)canv->GetPrimitive("stats");
				stats3->SetName("h1stats4");
				stats3->SetY1NDC(.30);
				stats3->SetY2NDC(.46);
				stats3->SetX1NDC(.71);
				stats3->SetX2NDC(.96);
				stats3->SetTextColor(4);

				TList *list3 = stats3->GetListOfLines();
				TLatex *myt3 = new TLatex(0,0,"Data = ");
				myt3 ->SetTextFont(42);
				myt3 ->SetTextSize(0.04);
				myt3 ->SetTextColor(4);
				list3->AddFirst(myt3);
			canv->Update();
			}

			widths_hist_FE_gen.at(m).at(p) -> Draw();

			canv->Update();
			TPaveStats *stats2 = (TPaveStats*)canv->GetPrimitive("stats");
			stats2->SetName("h1stats3");
			stats2->SetY1NDC(.14);
			stats2->SetY2NDC(.30);
			stats2->SetX1NDC(.46);
			stats2->SetX2NDC(.71);
			stats2->SetTextColor(2);

			TList *list2 = stats2->GetListOfLines();
			TLatex *myt2 = new TLatex(0,0,"PLI = ");
			myt2 ->SetTextFont(42);
			myt2 ->SetTextSize(0.04);
			myt2 ->SetTextColor(2);
			list2->AddFirst(myt2);

				canv->Update();
//			canv->Update();
			widths_hist_FE_gen.at(m).at(p) -> Draw();
//			canv->Update();
			widths_hist_FE_data.at(m).at(p) -> Draw("same");

//			canv->Update();
			widths_hist_FE.at(m).at(p) -> Draw("same");


			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			canv -> Write();
		
			TString outputname = widths_hist_FE.at(m).at(p) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
		}
	}

	for( unsigned int m = 0; m < widths_hist_all.size(); m++ )
	{
		for( unsigned int p = 0; p < widths_hist_all.at(m).size(); p++ )
		{
			TString canvName = widths_hist_all.at(m).at(p) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			if( widths_hist_all.at(m).at(p) -> GetEntries() != 0 )     widths_hist_all.at(m).at(p) -> GetFunction("linfit")->SetLineColor(6);
			if( widths_hist_all_gen.at(m).at(p) -> GetEntries() != 0 ) widths_hist_all_gen.at(m).at(p) -> GetFunction("linfit")->SetLineColor(2);
			if( widths_hist_all_data.at(m).at(p) -> GetEntries() != 0 )widths_hist_all_data.at(m).at(p) -> GetFunction("linfit")->SetLineColor(4);

			widths_hist_all.at(m).at(p) -> SetMarkerColor(6);
			widths_hist_all_gen.at(m).at(p) -> SetMarkerColor(2);
			widths_hist_all_data.at(m).at(p) -> SetMarkerColor(4);

			widths_hist_all.at(m).at(p) -> SetMarkerStyle(20);
			widths_hist_all_gen.at(m).at(p) -> SetMarkerStyle(20);
			widths_hist_all_data.at(m).at(p) -> SetMarkerStyle(20);

			widths_hist_all.at(m).at(p) -> Draw();

			canv->Update();
			if( widths_hist_all.at(m).at(p) -> GetEntries() != 0 )
			{
				TPaveStats *stats1 = (TPaveStats*)canv->GetPrimitive("stats");
				stats1->SetName("h1stats2");
				stats1->SetY1NDC(.14);
				stats1->SetY2NDC(.30);
				stats1->SetX1NDC(.71);
				stats1->SetX2NDC(.96);
				stats1->SetTextColor(6);

				TList *list1 = stats1->GetListOfLines();
				TLatex *myt1 = new TLatex(0,0,"MC = ");
				myt1 ->SetTextFont(42);
				myt1 ->SetTextSize(0.04);
				myt1 ->SetTextColor(6);
				list1->AddFirst(myt1);
			}

			widths_hist_all_gen.at(m).at(p) -> Draw();

			canv->Update();
			if( widths_hist_all_gen.at(m).at(p) -> GetEntries() != 0 )
			{
				TPaveStats *stats2 = (TPaveStats*)canv->GetPrimitive("stats");
				stats2->SetName("h1stats3");
				stats2->SetY1NDC(.14);
				stats2->SetY2NDC(.30);
				stats2->SetX1NDC(.46);
				stats2->SetX2NDC(.71);
				stats2->SetTextColor(2);

				TList *list2 = stats2->GetListOfLines();
				TLatex *myt2 = new TLatex(0,0,"PLI = ");
				myt2 ->SetTextFont(42);
				myt2 ->SetTextSize(0.04);
				myt2 ->SetTextColor(2);
				list2->AddFirst(myt2);
			}

			widths_hist_all_data.at(m).at(p) -> Draw();

			canv->Update();
			if( widths_hist_all_data.at(m).at(p) -> GetEntries() != 0 )
			{
				TPaveStats *stats3 = (TPaveStats*)canv->GetPrimitive("stats");
				stats3->SetName("h1stats4");
				stats3->SetY1NDC(.30);
				stats3->SetY2NDC(.43);
				stats3->SetX1NDC(.71);
				stats3->SetX2NDC(.96);
				stats3->SetTextColor(4);

				TList *list3 = stats3->GetListOfLines();
				TLatex *myt3 = new TLatex(0,0,"Data = ");
				myt3 ->SetTextFont(42);
				myt3 ->SetTextSize(0.04);
				myt3 ->SetTextColor(4);
				list3->Add(myt3);
			}
			canv->Update();

			widths_hist_all_gen.at(m).at(p) -> Draw();

			canv->Update();

			widths_hist_all_data.at(m).at(p) -> Draw("same");
			widths_hist_all.at(m).at(p) -> Draw("same");


			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			canv -> Write();
		
			TString outputname = widths_hist_all.at(m).at(p) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
		}
	}
	h_merged.Close();


	gStyle -> SetOptStat(0);
	TFile fJERs("output/Jersalltogether.root","RECREATE");
	for( unsigned int m = 0; m < JER_data_hist.size(); m++ )
	{
			TString canvName = JER_data_hist.at(m) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			JER_data_hist.at(m) -> SetMarkerColor(4);
			JER_MC_hist.at(m) -> SetMarkerColor(2);

			JER_data_hist.at(m) -> SetMarkerStyle(20);
			JER_MC_hist.at(m) -> SetMarkerStyle(20);

			JER_data_hist.at(m) -> Draw();

			canv->Update();

			JER_MC_hist.at(m) -> Draw();

			canv->Update();
			JER_data_hist.at(m) -> Draw("same");


			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
			leg->AddEntry(JER_data_hist.at(m),"Data","lep");
			leg->AddEntry(JER_MC_hist.at(m),"MC","lep");
			leg->Draw();

			canv -> Write();
		
			TString outputname = JER_data_hist.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}



	for( unsigned int m = 0; m < JER_FE_data_hist.size(); m++ )
	{
			TString canvName = JER_FE_data_hist.at(m) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			JER_FE_data_hist.at(m) -> SetMarkerColor(4);
			JER_FE_MC_hist.at(m) -> SetMarkerColor(2);

			JER_FE_data_hist.at(m) -> SetMarkerStyle(20);
			JER_FE_MC_hist.at(m) -> SetMarkerStyle(20);

			JER_FE_data_hist.at(m) -> Draw();

			canv->Update();
			JER_FE_MC_hist.at(m) -> Draw();

			canv->Update();
			JER_FE_data_hist.at(m) -> Draw("same");


			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
			leg->AddEntry(JER_FE_data_hist.at(m),"Data","lep");
			leg->AddEntry(JER_FE_MC_hist.at(m),"MC","lep");
			leg->Draw();

			canv -> Write();
		
			TString outputname = JER_FE_data_hist.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}

	for( unsigned int m = 0; m < JER_FE_data_hist_control.size(); m++ )
	{
			TString canvName = JER_FE_data_hist_control.at(m) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			JER_FE_data_hist_control.at(m) -> SetMarkerColor(4);
			JER_FE_MC_hist_control.at(m) -> SetMarkerColor(2);

			JER_FE_data_hist_control.at(m) -> SetMarkerStyle(20);
			JER_FE_MC_hist_control.at(m) -> SetMarkerStyle(20);

			JER_FE_data_hist_control.at(m) -> Draw();

			canv->Update();

			JER_FE_MC_hist_control.at(m) -> Draw();

			canv->Update();
			JER_FE_data_hist_control.at(m) -> Draw("same");


			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
			leg->AddEntry(JER_FE_data_hist_control.at(m),"Data","lep");
			leg->AddEntry(JER_FE_MC_hist_control.at(m),"MC","lep");
			leg->Draw();

			canv -> Write();
		
			TString outputname = JER_FE_data_hist_control.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}
	fJERs.Close();

	TFile gsfoverlayed("output/SFsOver.root","RECREATE");

	gStyle -> SetOptFit(1);

	for( unsigned int m = 0; m < JER_scale_hist.size(); m++ )
	{
			TString canvName = JER_scale_hist.at(m) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			JER_scale_hist.at(m) -> GetFunction("pol0")->SetLineColor(6);
			JER015_scale_hist.at(m) -> GetFunction("pol0")->SetLineColor(4);

			JER_scale_hist.at(m) -> SetMarkerColor(6);
			JER015_scale_hist.at(m) -> SetMarkerColor(4);

			JER_scale_hist.at(m) -> SetLineColor(6);
			JER015_scale_hist.at(m) -> SetLineColor(4);

			JER_scale_hist.at(m) -> SetMarkerStyle(20);
			JER015_scale_hist.at(m) -> SetMarkerStyle(20);


			JER015_scale_hist.at(m) -> Draw();

			canv->Update();
			TPaveStats *stats2 = (TPaveStats*)canv->GetPrimitive("stats");
			stats2->SetName("h1stats3");
			stats2->SetY1NDC(.64);
			stats2->SetY2NDC(.77);
			stats2->SetX1NDC(.66);
			stats2->SetX2NDC(.91);
			stats2->SetTextColor(4);

			JER_scale_hist.at(m) -> Draw();

			canv->Update();
			TPaveStats *stats1 = (TPaveStats*)canv->GetPrimitive("stats");
			stats1->SetName("h1stats2");
			stats1->SetY1NDC(.77);
			stats1->SetY2NDC(.90);
			stats1->SetX1NDC(.66);
			stats1->SetX2NDC(.91);
			stats1->SetTextColor(6);

			JER015_scale_hist.at(m) -> Draw();
			JER_scale_hist.at(m) -> Draw("same");

			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			TLegend *leg = new TLegend(0.6,0.2,0.9,0.4);
			leg->AddEntry(JER_scale_hist.at(m),"#sigma_{JER}^{Data}/#sigma_{JER}^{MC}","lep");
			leg->AddEntry(JER015_scale_hist.at(m),"#sigma_{0.15}^{Data}/#sigma_{0.15}^{MC}","lep");
			leg->Draw();
			canv -> Write();
		
			TString outputname = JER_scale_hist.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}
	for( unsigned int m = 0; m < JER_FE_scale_hist.size(); m++ )
	{
			TString canvName = JER_FE_scale_hist.at(m) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			JER_FE_scale_hist.at(m) -> GetFunction("pol0")->SetLineColor(6);
			JER015_FE_scale_hist.at(m) -> GetFunction("pol0")->SetLineColor(4);

			JER_FE_scale_hist.at(m) -> SetMarkerColor(6);
			JER015_FE_scale_hist.at(m) -> SetMarkerColor(4);

			JER_FE_scale_hist.at(m) -> SetLineColor(6);
			JER015_FE_scale_hist.at(m) -> SetLineColor(4);

			JER_FE_scale_hist.at(m) -> SetMarkerStyle(20);
			JER015_FE_scale_hist.at(m) -> SetMarkerStyle(20);


			JER015_FE_scale_hist.at(m) -> Draw();

			canv->Update();
			TPaveStats *stats2 = (TPaveStats*)canv->GetPrimitive("stats");
			stats2->SetName("h1stats3");
			stats2->SetY1NDC(.64);
			stats2->SetY2NDC(.77);
			stats2->SetX1NDC(.66);
			stats2->SetX2NDC(.91);
			stats2->SetTextColor(4);

			JER_FE_scale_hist.at(m) -> Draw();
			canv->Update();
			TPaveStats *stats1 = (TPaveStats*)canv->GetPrimitive("stats");
			stats1->SetName("h1stats2");
			stats1->SetY1NDC(.77);
			stats1->SetY2NDC(.90);
			stats1->SetX1NDC(.66);
			stats1->SetX2NDC(.91);
			stats1->SetTextColor(6);

			JER015_FE_scale_hist.at(m) -> Draw();
			JER_FE_scale_hist.at(m) -> Draw("same");
			JER015_FE_scale_hist.at(m) -> Draw("same");

			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();

			TLegend *leg = new TLegend(0.6,0.2,0.9,0.4);
			leg->AddEntry(JER_scale_hist.at(m),"#sigma_{JER}^{Data}/#sigma_{JER}^{MC}","lep");
			leg->AddEntry(JER015_scale_hist.at(m),"#sigma_{0.15}^{Data}/#sigma_{0.15}^{MC}","lep");
			leg->Draw();
		
			canv -> Write();
		
			TString outputname = JER_FE_scale_hist.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}




	gsfoverlayed.Close();

/*
	for( unsigned int m = 0; m < forward_width_data_pt.size(); m++ )
	{
		for( unsigned int p = 0; p < forward_width_data_pt.at(m).size(); p++ )
		{
//			std::cout << m << ", " << p << ", " << forward_width_data_pt.at(m).at(p).at(4) << std::endl;
		}
	}

	for( unsigned int m = 0; m < scales_fe.size(); m++ )
	{
		for( unsigned int p = 0; p < scales_fe.at(m).size(); p++ )
		{
//			std::cout << m << ", " << p << ", " << scales_fe.at(m).at(p) << std::endl;
		}
	}





	TFile g("KFSR_vs_pt.root","RECREATE");

	for( unsigned int m = 0; m < KFSR_vs_pt_all.size(); m++ )
	{
		KFSR_vs_pt_all.at(m) -> Write();
	}

	for( unsigned int m = 0; m < KFSR_vs_pt_gen_all.size(); m++ )
	{
		KFSR_vs_pt_gen_all.at(m) -> Write();
	}

	for( unsigned int m = 0; m < KFSR_vs_pt_all_data.size(); m++ )
	{
		KFSR_vs_pt_all_data.at(m) -> Write();
	}

	for( unsigned int m = 0; m < KFSR_vs_pt_FE.size(); m++ )
	{
		KFSR_vs_pt_FE.at(m) -> Write();
	}

	for( unsigned int m = 0; m < KFSR_vs_pt_gen_FE.size(); m++ )
	{
		KFSR_vs_pt_gen_FE.at(m) -> Write();
	}

	for( unsigned int m = 0; m < KFSR_vs_pt_FE_data.size(); m++ )
	{
		KFSR_vs_pt_FE_data.at(m) -> Write();
	}
	g.Close();





//		JERb_scale_hist.at(m) -> Fit("pol0","");
//		JERb_FE_scale_hist.at(m) -> Fit("pol0","");

	TFile gbisb("SFsb.root","RECREATE");

//	std::cout << "now i'm fitting scale factors for b-par method" << std::endl;

	for( unsigned int m = 0; m < JERb_scale_hist.size(); m++ )
	{
		JERb_scale_hist.at(m) -> Fit("pol0","");
		JERb_scale_hist.at(m) -> Write();
	}

	for( unsigned int m = 0; m < JERb_FE_scale_hist.size(); m++ )
	{
		JERb_FE_scale_hist.at(m) -> Fit("pol0","");
		JERb_FE_scale_hist.at(m) -> Write();
	}

	for( unsigned int m = 0; m < JERb_FE_scale_hist_control.size(); m++ )
	{
		JERb_FE_scale_hist_control.at(m) -> Fit("pol0","");
		JERb_FE_scale_hist_control.at(m) -> Write();
	}

	gbisb.Close();

	TFile gsfboverlayed("SFbsOver.root","RECREATE");


	for( unsigned int m = 0; m < JERb_scale_hist.size(); m++ )
	{
			TString canvName = JERb_scale_hist.at(m) -> GetTitle();
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			JERb_scale_hist.at(m) -> SetMarkerColor(2);

			JERb_scale_hist.at(m) -> SetMarkerStyle(20);

			JERb_scale_hist.at(m) -> Draw();

			canv->Update();

			JERb_scale_hist.at(m) -> Draw("same");


			canv->cd();
	//		CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			canv -> Write();
		
			TString outputname = JERb_scale_hist.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}


	for( unsigned int m = 0; m < JERb_FE_scale_hist.size(); m++ )
	{
			TString canvName = JERb_FE_scale_hist.at(m) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			JERb_FE_scale_hist.at(m) -> SetMarkerColor(2);

			JERb_FE_scale_hist.at(m) -> SetMarkerStyle(20);

			JERb_FE_scale_hist.at(m) -> Draw();

			canv->Update();


			canv->Update();
			JERb_FE_scale_hist.at(m) -> Draw("same");


			canv->cd();
//			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			canv -> Write();
		
			TString outputname = JERb_FE_scale_hist.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}
	gsfboverlayed.Close();






	setTDRStyle();

	writeExtraText = true;       // if extra text
	extraText  = "       Preliminary";  // default extra text is "Preliminary"
	lumi_13TeV = "1.28 fb^{-1}";
	lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)
	
	int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
	

	gStyle -> SetOptFit(1);





























	TFile hkfsr_merged("KFSR_merged.root","RECREATE");

	for( unsigned int m = 0; m < KFSR_vs_pt_all.size(); m++ )
	{
			TString canvName = KFSR_vs_pt_all.at(m) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			if( KFSR_vs_pt_all.at(m) -> GetEntries() != 0 )     KFSR_vs_pt_all.at(m) -> GetFunction("linfit")->SetLineColor(6);
			if( KFSR_vs_pt_gen_all.at(m) -> GetEntries() != 0 ) KFSR_vs_pt_gen_all.at(m) -> GetFunction("linfit")->SetLineColor(2);
			if( KFSR_vs_pt_all_data.at(m) -> GetEntries() != 0 )KFSR_vs_pt_all_data.at(m) -> GetFunction("linfit")->SetLineColor(4);

			KFSR_vs_pt_all.at(m) -> SetMarkerColor(6);
			KFSR_vs_pt_gen_all.at(m) -> SetMarkerColor(2);
			KFSR_vs_pt_all_data.at(m) -> SetMarkerColor(4);

			KFSR_vs_pt_all.at(m) -> SetMarkerStyle(20);
			KFSR_vs_pt_gen_all.at(m) -> SetMarkerStyle(20);
			KFSR_vs_pt_all_data.at(m) -> SetMarkerStyle(20);

			KFSR_vs_pt_all.at(m) -> Draw();

			canv->Update();
			TPaveStats *stats1 = (TPaveStats*)canv->GetPrimitive("stats");
			stats1->SetName("h1stats2");
			stats1->SetY1NDC(.74);
			stats1->SetY2NDC(.90);
			stats1->SetX1NDC(.71);
			stats1->SetX2NDC(.96);
			stats1->SetTextColor(6);

			TList *list1 = stats1->GetListOfLines();
			TLatex *myt1 = new TLatex(0,0,"MC = ");
			myt1 ->SetTextFont(42);
			myt1 ->SetTextSize(0.04);
			myt1 ->SetTextColor(6);
			list1->AddFirst(myt1);

			KFSR_vs_pt_gen_all.at(m) -> Draw();

			canv->Update();
			TPaveStats *stats2 = (TPaveStats*)canv->GetPrimitive("stats");
			stats2->SetName("h1stats3");
			stats2->SetY1NDC(.74);
			stats2->SetY2NDC(.90);
			stats2->SetX1NDC(.46);
			stats2->SetX2NDC(.71);
			stats2->SetTextColor(2);

			TList *list2 = stats2->GetListOfLines();
			TLatex *myt2 = new TLatex(0,0,"PLI = ");
			myt2 ->SetTextFont(42);
			myt2 ->SetTextSize(0.04);
			myt2 ->SetTextColor(2);
			list2->AddFirst(myt2);

				KFSR_vs_pt_all_data.at(m) -> Draw();

				canv->Update();
				TPaveStats *stats3 = (TPaveStats*)canv->GetPrimitive("stats");
				stats3->SetName("h1stats4");
				stats3->SetY1NDC(.74);
				stats3->SetY2NDC(.60);
				stats3->SetX1NDC(.71);
				stats3->SetX2NDC(.96);
				stats3->SetTextColor(4);

				TList *list3 = stats3->GetListOfLines();
				TLatex *myt3 = new TLatex(0,0,"Data = ");
				myt3 ->SetTextFont(42);
				myt3 ->SetTextSize(0.04);
				myt3 ->SetTextColor(4);
				list3->AddFirst(myt3);

			KFSR_vs_pt_all_data.at(m) -> Draw();

			canv->Update();
			KFSR_vs_pt_gen_all.at(m) -> Draw("same");
			KFSR_vs_pt_all.at(m) -> Draw("same");


			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			canv -> Write();
		
			TString outputname = KFSR_vs_pt_all.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}



	for( unsigned int m = 0; m < KFSR_vs_pt_FE.size(); m++ )
	{
			TString canvName = KFSR_vs_pt_FE.at(m) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			if( KFSR_vs_pt_FE.at(m) -> GetEntries() != 0 )     KFSR_vs_pt_FE.at(m) -> GetFunction("linfit")->SetLineColor(6);
			if( KFSR_vs_pt_gen_FE.at(m) -> GetEntries() != 0 ) KFSR_vs_pt_gen_FE.at(m) -> GetFunction("linfit")->SetLineColor(2);
			if( KFSR_vs_pt_FE_data.at(m) -> GetEntries() != 0 )KFSR_vs_pt_FE_data.at(m) -> GetFunction("linfit")->SetLineColor(4);

			KFSR_vs_pt_FE.at(m) -> SetMarkerColor(6);
			KFSR_vs_pt_gen_FE.at(m) -> SetMarkerColor(2);
			KFSR_vs_pt_FE_data.at(m) -> SetMarkerColor(4);

			KFSR_vs_pt_FE.at(m) -> SetMarkerStyle(20);
			KFSR_vs_pt_gen_FE.at(m) -> SetMarkerStyle(20);
			KFSR_vs_pt_FE_data.at(m) -> SetMarkerStyle(20);

			KFSR_vs_pt_FE.at(m) -> Draw();

			canv->Update();
			TPaveStats *stats1 = (TPaveStats*)canv->GetPrimitive("stats");
			stats1->SetName("h1stats2");
			stats1->SetY1NDC(.74);
			stats1->SetY2NDC(.90);
			stats1->SetX1NDC(.71);
			stats1->SetX2NDC(.96);
			stats1->SetTextColor(6);

			TList *list1 = stats1->GetListOfLines();
			TLatex *myt1 = new TLatex(0,0,"MC = ");
			myt1 ->SetTextFont(42);
			myt1 ->SetTextSize(0.04);
			myt1 ->SetTextColor(6);
			list1->AddFirst(myt1);

			KFSR_vs_pt_gen_FE.at(m) -> Draw();

			canv->Update();
			TPaveStats *stats2 = (TPaveStats*)canv->GetPrimitive("stats");
			stats2->SetName("h1stats3");
			stats2->SetY1NDC(.74);
			stats2->SetY2NDC(.90);
			stats2->SetX1NDC(.46);
			stats2->SetX2NDC(.71);
			stats2->SetTextColor(2);

			TList *list2 = stats2->GetListOfLines();
			TLatex *myt2 = new TLatex(0,0,"PLI = ");
			myt2 ->SetTextFont(42);
			myt2 ->SetTextSize(0.04);
			myt2 ->SetTextColor(2);
			list2->AddFirst(myt2);

				KFSR_vs_pt_FE_data.at(m) -> Draw();

				canv->Update();
				TPaveStats *stats3 = (TPaveStats*)canv->GetPrimitive("stats");
				stats3->SetName("h1stats4");
				stats3->SetY1NDC(.74);
				stats3->SetY2NDC(.60);
				stats3->SetX1NDC(.71);
				stats3->SetX2NDC(.96);
				stats3->SetTextColor(4);

				TList *list3 = stats3->GetListOfLines();
				TLatex *myt3 = new TLatex(0,0,"Data = ");
				myt3 ->SetTextFont(42);
				myt3 ->SetTextSize(0.04);
				myt3 ->SetTextColor(4);
				list3->AddFirst(myt3);

			KFSR_vs_pt_FE_data.at(m) -> Draw();

			canv->Update();
			KFSR_vs_pt_gen_FE.at(m) -> Draw("same");
			KFSR_vs_pt_FE.at(m) -> Draw("same");


			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			canv -> Write();
		
			TString outputname = KFSR_vs_pt_FE.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}
	hkfsr_merged.Close();





	TFile fJERs("Jersalltogether.root","RECREATE");
	for( unsigned int m = 0; m < JER_data_hist.size(); m++ )
	{
			TString canvName = JER_data_hist.at(m) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			JER_data_hist.at(m) -> SetMarkerColor(4);
			JER_MC_hist.at(m) -> SetMarkerColor(2);

			JER_data_hist.at(m) -> SetMarkerStyle(20);
			JER_MC_hist.at(m) -> SetMarkerStyle(20);

			JER_data_hist.at(m) -> Draw();

			canv->Update();

			JER_MC_hist.at(m) -> Draw();

			canv->Update();
			JER_data_hist.at(m) -> Draw("same");


			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
			leg->AddEntry(JER_data_hist.at(m),"Data","lep");
			leg->AddEntry(JER_MC_hist.at(m),"MC","lep");
			leg->Draw();

			canv -> Write();
		
			TString outputname = JER_data_hist.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}



	for( unsigned int m = 0; m < JER_FE_data_hist.size(); m++ )
	{
			TString canvName = JER_FE_data_hist.at(m) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			JER_FE_data_hist.at(m) -> SetMarkerColor(4);
			JER_FE_MC_hist.at(m) -> SetMarkerColor(2);

			JER_FE_data_hist.at(m) -> SetMarkerStyle(20);
			JER_FE_MC_hist.at(m) -> SetMarkerStyle(20);

			JER_FE_data_hist.at(m) -> Draw();

			canv->Update();
			JER_FE_MC_hist.at(m) -> Draw();

			canv->Update();
			JER_FE_data_hist.at(m) -> Draw("same");


			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
			leg->AddEntry(JER_FE_data_hist.at(m),"Data","lep");
			leg->AddEntry(JER_FE_MC_hist.at(m),"MC","lep");
			leg->Draw();

			canv -> Write();
		
			TString outputname = JER_FE_data_hist.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}

	for( unsigned int m = 0; m < JER_FE_data_hist_control.size(); m++ )
	{
			TString canvName = JER_FE_data_hist_control.at(m) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			JER_FE_data_hist_control.at(m) -> SetMarkerColor(4);
			JER_FE_MC_hist_control.at(m) -> SetMarkerColor(2);

			JER_FE_data_hist_control.at(m) -> SetMarkerStyle(20);
			JER_FE_MC_hist_control.at(m) -> SetMarkerStyle(20);

			JER_FE_data_hist_control.at(m) -> Draw();

			canv->Update();

			JER_FE_MC_hist_control.at(m) -> Draw();

			canv->Update();
			JER_FE_data_hist_control.at(m) -> Draw("same");


			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
			leg->AddEntry(JER_FE_data_hist_control.at(m),"Data","lep");
			leg->AddEntry(JER_FE_MC_hist_control.at(m),"MC","lep");
			leg->Draw();

			canv -> Write();
		
			TString outputname = JER_FE_data_hist_control.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}
	fJERs.Close();



//	std::cout << " tutej jestsems --------------------------- jestem tutej --------------------------- jestem tutej " << std::endl;


	TFile gsfoverlayed("SFsOver.root","RECREATE");


	for( unsigned int m = 0; m < JERb_scale_hist.size(); m++ )
	{
			TString canvName = JERb_scale_hist.at(m) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			JERb_scale_hist.at(m) -> GetFunction("pol0")->SetLineColor(3);
			JER015_scale_hist.at(m) -> GetFunction("pol0")->SetLineColor(4);

			JERb_scale_hist.at(m) -> SetMarkerColor(3);
			JER015_scale_hist.at(m) -> SetMarkerColor(4);

			JERb_scale_hist.at(m) -> SetLineColor(3);
			JER015_scale_hist.at(m) -> SetLineColor(4);

			JERb_scale_hist.at(m) -> SetMarkerStyle(20);
			JER015_scale_hist.at(m) -> SetMarkerStyle(20);


			JER015_scale_hist.at(m) -> Draw();

			canv->Update();
			TPaveStats *stats2 = (TPaveStats*)canv->GetPrimitive("stats");
			stats2->SetName("h1stats3");
			stats2->SetY1NDC(.64);
			stats2->SetY2NDC(.77);
			stats2->SetX1NDC(.66);
			stats2->SetX2NDC(.91);
			stats2->SetTextColor(4);

			JERb_scale_hist.at(m) -> Draw();

			canv->Update();
			TPaveStats *stats1 = (TPaveStats*)canv->GetPrimitive("stats");
			stats1->SetName("h1stats2");
			stats1->SetY1NDC(.77);
			stats1->SetY2NDC(.90);
			stats1->SetX1NDC(.66);
			stats1->SetX2NDC(.91);
			stats1->SetTextColor(3);

			JER015_scale_hist.at(m) -> Draw();
			JERb_scale_hist.at(m) -> Draw("same");

			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();
		
			TLegend *leg = new TLegend(0.6,0.2,0.9,0.4);
			leg->AddEntry(JERb_scale_hist.at(m),"#sigma_{JER}^{Data}/#sigma_{JER}^{MC}","lep");
			leg->AddEntry(JER015_scale_hist.at(m),"#sigma_{0.15}^{Data}/#sigma_{0.15}^{MC}","lep");
			leg->Draw();
			canv -> Write();
		
			TString outputname = JERb_scale_hist.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}
	for( unsigned int m = 0; m < JERb_FE_scale_hist.size(); m++ )
	{
			TString canvName = JERb_FE_scale_hist.at(m) -> GetTitle();
			
			TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
			canv->SetFillColor(0);
			canv->SetBorderMode(0);
			canv->SetFrameFillStyle(0);
			canv->SetFrameBorderMode(0);
			canv->SetLeftMargin( L/W );
			canv->SetRightMargin( R/W );
			canv->SetTopMargin( T/H );
			canv->SetBottomMargin( B/H );
			canv->SetTickx(0);
			canv->SetTicky(0);

			JERb_FE_scale_hist.at(m) -> GetFunction("pol0")->SetLineColor(3);
			JER015_FE_scale_hist.at(m) -> GetFunction("pol0")->SetLineColor(4);

			JERb_FE_scale_hist.at(m) -> SetMarkerColor(3);
			JER015_FE_scale_hist.at(m) -> SetMarkerColor(4);

			JERb_FE_scale_hist.at(m) -> SetLineColor(3);
			JER015_FE_scale_hist.at(m) -> SetLineColor(4);

			JERb_FE_scale_hist.at(m) -> SetMarkerStyle(20);
			JER015_FE_scale_hist.at(m) -> SetMarkerStyle(20);


			JER015_FE_scale_hist.at(m) -> Draw();

			canv->Update();
			TPaveStats *stats2 = (TPaveStats*)canv->GetPrimitive("stats");
			stats2->SetName("h1stats3");
			stats2->SetY1NDC(.64);
			stats2->SetY2NDC(.77);
			stats2->SetX1NDC(.66);
			stats2->SetX2NDC(.91);
			stats2->SetTextColor(4);

			JERb_FE_scale_hist.at(m) -> Draw();
			canv->Update();
			TPaveStats *stats1 = (TPaveStats*)canv->GetPrimitive("stats");
			stats1->SetName("h1stats2");
			stats1->SetY1NDC(.77);
			stats1->SetY2NDC(.90);
			stats1->SetX1NDC(.66);
			stats1->SetX2NDC(.91);
			stats1->SetTextColor(3);

			JER015_FE_scale_hist.at(m) -> Draw();
			JERb_FE_scale_hist.at(m) -> Draw("same");
			JER015_FE_scale_hist.at(m) -> Draw("same");

			canv->cd();
			CMS_lumi( canv, iPeriod, 0 );
			
			canv->Update();
			canv->RedrawAxis();
			canv->GetFrame()->Draw();
			canv->Draw();

			TLegend *leg = new TLegend(0.6,0.2,0.9,0.4);
			leg->AddEntry(JERb_scale_hist.at(m),"#sigma_{JER}^{Data}/#sigma_{JER}^{MC}","lep");
			leg->AddEntry(JER015_scale_hist.at(m),"#sigma_{0.15}^{Data}/#sigma_{0.15}^{MC}","lep");
			leg->Draw();
		
			canv -> Write();
		
			TString outputname = JERb_FE_scale_hist.at(m) -> GetTitle();
		
			canv -> Print("pdfy/"+outputname+".pdf","pdf");
	}




	gsfoverlayed.Close();

	TFile checksformikko("CHECKs.root","RECREATE");

	for( unsigned int m = 0; m < KFSR_ratios_all.size(); m++ )
	{
		KFSR_ratios_all.at(m) -> Fit("pol0","");
		KFSR_ratios_all.at(m) -> Write();
	}
	for( unsigned int m = 0; m < KFSR_ratios_FE.size(); m++ )
	{
		KFSR_ratios_FE.at(m) -> Fit("pol0","");
		KFSR_ratios_FE.at(m) -> Write();
	}
	for( unsigned int m = 0; m < widths_015_ratios_all.size(); m++ )
	{
		widths_015_ratios_all.at(m) -> Fit("pol0","");
		widths_015_ratios_all.at(m) -> Write();
	}
	for( unsigned int m = 0; m < widths_015_ratios_FE.size(); m++ )
	{
		widths_015_ratios_FE.at(m) -> Fit("pol0","");
		widths_015_ratios_FE.at(m) -> Write();
	}

	checksformikko.Close();
*/

	return 0;
}
