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


//void fitAsym( TH1F &hist, double &width, double &error , double &centre, double &centre_error, double &chisqr, int fitType );
void fitAsym( TH1F &hist, double &width, double &error , double &centre, double &centre_error, double &chisqr, int fitType, double position = 0. , bool fix = false );
void fitConst( TH1F &hist, double &value, double &error );
void fitLin( TH1F &hist, double &width, double &error );
void fitShift( TH1F &hist, double &a, double &errora, double &b, double &errorb );
void fitMCTruth( TH1F &hist, double &width, double &error );
float GetAsymmWidth(TH1F* &htemp, double * xq_IQW, double * yq_IQW);




void histLoadMC( TFile &f, std::vector<TH1F*> &Asymmetry, std::vector<TH1F*> &GenAsymmetry, std::vector<TH1F*> &MCTruth, std::vector<TH1F*> &Alpha, std::vector<TH1F*> &AlphaGen  );
void histLoadFE1( TFile &f, bool data, TString name, std::vector< std::vector< std::vector< TH1F* > > > &forward_hist , std::vector< std::vector< std::vector< TH1F* > > > &forward_gen_hist, int ptbin , int etabin);
void histWidthAsym( std::vector<std::vector<std::vector<TH1F*> > > &Asymmetry , std::vector<std::vector<std::vector<double> > > &Widths, std::vector<std::vector<std::vector<double> > > &WidthsError  );
void def_fill_widths( TString name1, std::vector< std::vector< TH1F* > > &widths_FE1 , std::vector< std::vector< std::vector< double > > > Widths, std::vector< std::vector< std::vector< double > > > WidthsError );
void histLinFE( std::vector< std::vector< TH1F* > > widths_hist_all , std::vector< std::vector< double > > &Widths, std::vector< std::vector< double > > &WidthsError, int ptbin );
void histLinAsym( std::vector< std::vector< TH1F* > > widths_hist_all , std::vector< std::vector< double > > &Widths, std::vector< std::vector< double > > &WidthsError );

void fill_widthsFE_pt( TString name1, std::vector< TH1F* > &widths, std::vector< std::vector< double > > Widths, std::vector< std::vector< double > > WidthsError, std::vector< std::vector< double > > forward_width_pt );




void histLoadAsym( TFile &f, bool data, TString name, std::vector< std::vector< std::vector< TH1F* > > > &Asymmetry , std::vector< std::vector< std::vector< TH1F* > > > &GenAsymmetry , int ptbin, int etabin )
{
	// I load histograms

	for( int m = 0; m < etabin; m++ )
	{
		std::vector< std::vector< TH1F* > > temp2;
		std::vector< std::vector< TH1F* > > temp2gen;

		for( int p = 0; p < ptbin; p++ )
		{
			std::vector< TH1F* > temp1;
			std::vector< TH1F* > temp1gen;
			for( int r = 0; r < 5; r++ )
			{
				TString name_fw = name;
				TString name_fwgen = "gen_"; name_fwgen += name;
				name_fw += m+1; name_fw += "_pt"; name_fw += p+1; name_fw += "_alpha"; name_fw += r+1; 
				name_fwgen += m+1; name_fwgen += "_pt"; name_fwgen += p+1; name_fwgen += "_alpha"; name_fwgen += r+1; 
				temp1.push_back( ( TH1F* )f.Get( name_fw ) );
				if( data == false ) temp1gen.push_back( ( TH1F* )f.Get( name_fwgen ) );
//	std::cout << name_fw << std::endl;
			}
			temp2.push_back(temp1);
			if( data == false ) temp2gen.push_back(temp1gen);
		}
		Asymmetry.push_back(temp2);
		if( data == false ) GenAsymmetry.push_back(temp2gen);
	}
}


void histLoadFE1( TFile &f, bool data, TString name, std::vector< std::vector< std::vector< TH1F* > > > &forward_hist , std::vector< std::vector< std::vector< TH1F* > > > &forward_gen_hist , int ptbin , int etabin)
{
	// I load histograms

	int shift;
	if ( etabin == 8 )	shift = 2;
	if ( etabin == 2 )	shift = 10;

	for( int m = 0; m < etabin; m++ )
	{
		std::vector< std::vector< TH1F* > > temp2;
		std::vector< std::vector< TH1F* > > temp2gen;

		for( int p = 0; p < ptbin; p++ )
		{
			std::vector< TH1F* > temp1;
			std::vector< TH1F* > temp1gen;
			for( int r = 0; r < 5; r++ )
			{
				TString name_fw = name;
				TString name_fwgen = "gen_"; name_fwgen += name;
				name_fw += shift+m; 	name_fw += "_pt"; name_fw += p+1; name_fw += "_alpha"; name_fw += r+1; 
				name_fwgen += shift+m; 	name_fwgen += "_pt"; name_fwgen += p+1; name_fwgen += "_alpha"; name_fwgen += r+1; 
				temp1.push_back( ( TH1F* )f.Get( name_fw ) );
//				std::cout << name_fw << std::endl;
//				std::cout << name_fwgen << std::endl;
				if( data == false ) temp1gen.push_back( ( TH1F* )f.Get( name_fwgen ) );
			}
			temp2.push_back(temp1);
			if( data == false ) temp2gen.push_back(temp1gen);
		}
		forward_hist.push_back(temp2);
		if( data == false ) forward_gen_hist.push_back(temp2gen);
	}
}


void histMeanFE_Pt( std::vector< std::vector< std::vector< TH1F* > > > &Asymmetry , std::vector< std::vector< std::vector< double > > > &Widths )
{
//	std::cout << Asymmetry.at(0).size() << std::endl;
	for( unsigned int m = 0; m < Asymmetry.size(); m++ )
	{
		std::vector< std::vector< double > > temp1;
		for( unsigned int p = 0; p < Asymmetry.at(m).size(); p++ )
		{
			std::vector< double > temp2;
			for( unsigned int r = 0; r < 5; r++ )
			{
//				std::cout << "eta " << m + 1<< ", pt " << p + 1 << ", alpha " << r + 1 << ", mean pt "; std::cout << (*Asymmetry.at(m).at(p).at(r)).GetMean() << std::endl;
				temp2.push_back( (*Asymmetry.at(m).at(p).at(r)).GetMean() );
			}
			temp1.push_back(temp2);
		}
		Widths.push_back(temp1);
	}
}

void histWidthAsym( std::vector< std::vector< std::vector< TH1F* > > > &Asymmetry , std::vector< std::vector< std::vector< double > > > &Widths, std::vector< std::vector< std::vector< double > > > &WidthsError  )
{
   double yq_IQW[2],xq_IQW[2];
   xq_IQW[0] = 0.0;
   xq_IQW[1] = 0.985;

	for( unsigned int m = 0; m < Asymmetry.size(); m++ )
	{
		std::vector< std::vector< double > > temp2;
		std::vector< std::vector< double > > temp_error2;
		for( unsigned int p = 0; p < Asymmetry.at(m).size() ; p++ )
		{
			std::vector< double > temp1;
			std::vector< double > temp_error1;
			for( unsigned int r = 0; r < 5; r++ )
			{
//				std::cout << "eta " << m+1 << " pt " << p+1 << " alpha " << r+1 << ", " << GetAsymmWidth( Asymmetry.at(m).at(p).at(r) , xq_IQW, yq_IQW ) << std::endl;
				temp1.push_back( GetAsymmWidth( Asymmetry.at(m).at(p).at(r) , xq_IQW, yq_IQW) );
				temp_error1.push_back( GetAsymmWidth( Asymmetry.at(m).at(p).at(r) , xq_IQW, yq_IQW)/TMath::Sqrt(2*Asymmetry.at(m).at(p).at(r)->GetEffectiveEntries()));

/*								TF1 * myfit = new TF1( "myfit", "[0]*exp(-0.5*TMath::Power(((x-[1])/[2]),2))", 0, 0.15 );
							
								const int nq = 2;
								Asymmetry.at(m).at(p).at(r)->GetQuantiles(nq,yq_IQW,xq_IQW);

								double norm = Asymmetry.at(m).at(p).at(r)->Integral();
								if ( norm != 0 ) Asymmetry.at(m).at(p).at(r)->Scale( 1/norm );

								myfit -> SetParameter( 0, 0.1 );
								myfit -> SetParameter( 1, 0 );
								myfit -> SetParameter( 2, GetAsymmWidth( Asymmetry.at(m).at(p).at(r) , xq_IQW, yq_IQW) );
								myfit -> FixParameter( 2, GetAsymmWidth( Asymmetry.at(m).at(p).at(r) , xq_IQW, yq_IQW) );
								myfit -> FixParameter( 1, 0 );//I fix the mean value (center of gaus distribution) at 0
							
								myfit -> SetRange( 0, yq_IQW[1]);
							
								Asymmetry.at(m).at(p).at(r) -> Fit( "myfit", "+RQ" );

								TFile hplaprim("asymmetries.root","UPDATE");

								Asymmetry.at(m).at(p).at(r) -> Write();

								hplaprim.Close();
*/			}
			temp2.push_back(temp1);
			temp_error2.push_back(temp_error1);
		}
		Widths.push_back(temp2);
		WidthsError.push_back(temp_error2);
	}
}


void correctPLIbinbybin(std::vector< std::vector< std::vector< double > > > &Output, std::vector< std::vector< std::vector< double > > > &OutputError, std::vector< std::vector< std::vector< double > > > Widths, std::vector< std::vector< std::vector< double > > > WidthsError, std::vector< std::vector< std::vector< double > > > PLI, std::vector< std::vector< std::vector< double > > > PLIError)
{
	double temp, tempError;

	for( unsigned int i = 0; i < Widths.size(); i++ )
	{
		std::vector< std::vector< double > > temp2;
		std::vector< std::vector< double > > temp_error2;
		for( unsigned int j = 0; j < Widths.at(i).size(); j++ )
		{
			std::vector< double > temp1;
			std::vector< double > temp_error1;
			for( unsigned int k = 0; k < Widths.at(i).at(j).size(); k++ )
			{
				temp = TMath::Sqrt( Widths.at(i).at(j).at(k) * Widths.at(i).at(j).at(k) - PLI.at(i).at(j).at(k) * PLI.at(i).at(j).at(k) );
				tempError = ( Widths.at(i).at(j).at(k) * WidthsError.at(i).at(j).at(k) + PLI.at(i).at(j).at(k) * PLIError.at(i).at(j).at(k) )/temp;
				temp1.push_back( temp );
				temp_error1.push_back( tempError );
			}
			temp2.push_back(temp1);
			temp_error2.push_back(temp_error1);
		}
		Output.push_back(temp2);
		OutputError.push_back(temp_error2);
	}
}


void fill_PLI_hist( TString name1, std::vector< std::vector< TH1F* > > &widths_FE1 , std::vector< std::vector< std::vector< double > > > Widths, std::vector< std::vector< std::vector< double > > > WidthsError, std::vector< std::vector< std::vector< double > > > pt_binning)
{
	int shift;

	if (Widths.size() == 4 ) shift = 1;
	if (Widths.size() == 6 ) shift = 2;
	
	for( unsigned int m = 0; m <  Widths.size(); m++ )
	{
		std::vector< TH1F* > temp1;

		for( unsigned int r = 0; r <  Widths.at(m).at(0).size(); r++ )
		{
			TString name_width_fe1 = name1;
			name_width_fe1 += m+shift; name_width_fe1 += "_alpha"; name_width_fe1 += r+1; 
			TH1F *h1 = new TH1F( name_width_fe1, name_width_fe1, 1000, 0, 1000 );
			h1 ->GetYaxis()->SetTitle("#sigma_{A,PLI}");	h1 ->GetXaxis()->SetTitle("p_{T}");	h1 -> Sumw2();

			for( unsigned int p = 0; p < Widths.at(m).size(); p++ )
			{
				if( !(TMath::IsNaN(Widths.at(m).at(p).at(r))) ) h1 -> SetBinContent( h1 -> FindBin( pt_binning.at(m).at(p).at(r) ), Widths.at(m).at(p).at(r) );
				if( !(TMath::IsNaN(WidthsError.at(m).at(p).at(r))) ) h1 -> SetBinError( h1 -> FindBin( pt_binning.at(m).at(p).at(r) ), WidthsError.at(m).at(p).at(r) );
			}
			h1 ->GetYaxis()-> SetRangeUser( 0.8*(h1 -> GetMinimum()), 1.2*(h1 -> GetMaximum()) );
			temp1.push_back(h1);
		}
		widths_FE1.push_back(temp1);
	}
}


void fit_NSC_PLI( std::vector< std::vector< TF1* > > &functions, std::vector< std::vector< TH1F* > > PLI_hists )
{
	for( unsigned int m = 0; m <  PLI_hists.size(); m++ )
	{
		std::vector< TF1* > temp1;

		for( unsigned int r = 0; r <  PLI_hists.at(m).size(); r++ )
		{
			TString name_width_fe1 = "NSCfun";
			name_width_fe1 += m+1; name_width_fe1 += "_alpha"; name_width_fe1 += r+1; 
			TF1 * NSCfun = new TF1( name_width_fe1, "TMath::Sqrt(TMath::Power(([0]/x),2)+TMath::Power([1],2)/x + TMath::Power([2],2))", 0, 1000 );
			NSCfun->SetParName(0,"N");	NSCfun->SetParName(1,"S");	NSCfun->SetParName(2,"C");

			PLI_hists.at(m).at(r)-> Fit(name_width_fe1,"");

			NSCfun ->GetYaxis()-> SetRangeUser( 0.8*(NSCfun -> GetMinimum()), 1.2*(NSCfun -> GetMaximum()) );
			temp1.push_back(NSCfun);
		}
		functions.push_back(temp1);
	}
}


void def_fill_PLI( TString name1, std::vector< std::vector< TH1F* > > &widths_FE1 , std::vector< std::vector< TF1* > > functions, std::vector< std::vector< std::vector< double > > > WidthsError, std::vector< std::vector< std::vector< double > > > pt_binning )
{
	double aMax[] = { 0.1, 0.15, 0.2, 0.25, 0.3 };

	for( unsigned int m = 0; m < pt_binning.size(); m++ )
	{
		std::vector< TH1F* > temp1;

		for( unsigned int p = 0; p < pt_binning.at(m).size(); p++ )
		{
			TString name_width_fe1 = name1;
			name_width_fe1 += "_eta"; name_width_fe1 += m+1; name_width_fe1 += "_pt"; name_width_fe1 += p+1; 
			TH1F *h1 = new TH1F( name_width_fe1, name_width_fe1, 50, 0, 0.35 );
			h1 ->GetYaxis()->SetTitle("#sigma_{A}");	h1 ->GetXaxis()->SetTitle("#alpha_{max}");
			h1 -> Sumw2();
			for( unsigned int r = 0; r < 5; r++ )
			{
				h1 -> SetBinContent( h1 -> FindBin( aMax[ r ] ), functions.at(m).at(r)->Eval( pt_binning.at(m).at(p).at(r) ) );
				h1 -> SetBinError( h1 -> FindBin( aMax[ r ] ), WidthsError.at(m).at(p).at(r) );
			}
			h1 ->GetYaxis()-> SetRangeUser( 0.8*(h1 -> GetMinimum()), 1.2*(h1 -> GetMaximum()) );
			temp1.push_back(h1);
		}
		widths_FE1.push_back(temp1);
	}
}


void def_fill_widths( TString name1, std::vector< std::vector< TH1F* > > &widths_FE1 , std::vector< std::vector< std::vector< double > > > Widths, std::vector< std::vector< std::vector< double > > > WidthsError )
{
	double aMax[] = { 0.1, 0.15, 0.2, 0.25, 0.3 };
	double temp;

	for( unsigned int m = 0; m < Widths.size(); m++ )
	{
		std::vector< TH1F* > temp1;

		for( unsigned int p = 0; p < Widths.at(m).size(); p++ )
		{
			TString name_width_fe1 = name1;
			name_width_fe1 += "_eta"; name_width_fe1 += m+1; name_width_fe1 += "_pt"; name_width_fe1 += p+1; 
			TH1F *h1 = new TH1F( name_width_fe1, name_width_fe1, 50, 0, 0.35 );
			h1 ->GetYaxis()->SetTitle("#sigma_{A}");	h1 ->GetXaxis()->SetTitle("#alpha_{max}"); h1 ->GetYaxis()->SetTitleOffset(1.);
			h1 -> Sumw2();
			for( unsigned int r = 0; r < 5; r++ )
			{
//				if ( Widths.at(m).size() > 6 && p == 0 && r < 2 ) continue;
//				if ( Widths.at(m).size() > 6 && p == 1 && r < 1 ) continue;
//				if ( Widths.at(m).size() < 8 && p == 0 && r < 1 ) continue;

				temp = Widths.at(m).at(p).at(r);
				if( !(TMath::IsNaN(temp)) && temp != 0) h1 -> SetBinContent( h1 -> FindBin( aMax[ r ] ), Widths.at(m).at(p).at(r) );
				if( !(TMath::IsNaN(temp)) && temp != 0) h1 -> SetBinError( h1 -> FindBin( aMax[ r ] ), WidthsError.at(m).at(p).at(r) );
			}
			h1 ->GetYaxis()-> SetRangeUser( 0., 0.2 );
			temp1.push_back(h1);
		}
		widths_FE1.push_back(temp1);
	}
}


void correctForPLI( TString name1, std::vector< std::vector< TH1F* > > widths_FE1, std::vector< std::vector< TH1F* > > &output, std::vector< std::vector< TF1* > > functions, std::vector< std::vector< std::vector< double > > > pt_binning)
{
	double aMax[] = { 0.1, 0.15, 0.2, 0.25, 0.3 };

	double temp, temp_error;
	double Ref, Ext, RefError;

	for( unsigned int m = 0; m < widths_FE1.size(); m++ )
	{
		std::vector< TH1F* > temp1;
		for( unsigned int p = 0; p < widths_FE1.at(m).size(); p++ )
		{
			TString name_width_fe1 = name1;
			name_width_fe1 += "_eta"; name_width_fe1 += m+1; name_width_fe1 += "_pt"; name_width_fe1 += p+1; 
			TH1F *h1 = new TH1F( name_width_fe1, name_width_fe1, 50, 0, 0.35 );
			h1 ->GetYaxis()->SetTitle("#sigma_{A}");	h1 ->GetXaxis()->SetTitle("#alpha_{max}");
			h1 -> Sumw2();
			for( unsigned int r = 0 ; r < 5; r++ )
			{
				Ref = widths_FE1.at(m).at(p)->GetBinContent( h1 -> FindBin( aMax[ r ] ) );
				Ext = functions.at(m).at(r)->Eval(pt_binning.at(m).at(p).at(r));

				RefError = widths_FE1.at(m).at(p)->GetBinError( h1 -> FindBin( aMax[ r ] ) );

				temp = TMath::Sqrt( Ref*Ref - Ext*Ext );
				temp_error = (2*Ext*RefError + 2*Ref*RefError )/temp;

//				if (temp != 0) std::cout << "before " << Ref << ", corrected " << temp << std::endl;

				if( !(TMath::IsNaN(temp)) && temp != 0) h1 -> SetBinContent( h1 -> FindBin( aMax[ r ] ) , temp );
				if( !(TMath::IsNaN(temp)) && temp != 0) h1 -> SetBinError( h1 -> FindBin( aMax[ r ] ) , temp_error );
			}
			h1 ->GetYaxis()-> SetRangeUser( 0.8*(h1 -> GetMinimum()), 1.2*(h1 -> GetMaximum()) );
			temp1.push_back(h1);
		}
		output.push_back(temp1);
	}
}


void histLinFit( std::vector< std::vector< TH1F* > > widths_hist_all , std::vector< std::vector< double > > &Widths, std::vector< std::vector< double > > &WidthsError  )
{
	for( unsigned int m = 0; m < widths_hist_all.size(); m++ )
	{
		std::vector<double> temp2;
		std::vector<double> temp_error2;
		for( unsigned int p = 0; p < widths_hist_all.at(m).size(); p++ )
		{
			double value, error;
			if( widths_hist_all.at(m).at(p)->GetEntries() != 0 )
			{ 
				fitLin( *( widths_hist_all.at(m).at(p) ), value, error );
				temp2.push_back(value);
				temp_error2.push_back(error);
			}
			else
			{
				temp2.push_back(0.);
				temp_error2.push_back(0.);
			}

		}
		Widths.push_back(temp2);
		WidthsError.push_back(temp_error2);
	}
}


void fill_widths_pt( TString name1, std::vector<TH1F*> &widths, std::vector<std::vector<double> > Widths, std::vector<std::vector<double> > WidthsError, std::vector<std::vector<std::vector<double> > > forward_width_pt )
{
	for( unsigned int m = 0; m < Widths.size(); m++ )
	{
		TString name_width_fe1 = name1;
		name_width_fe1 += "_eta"; name_width_fe1 += m+1;
		
		TH1F *hist = new TH1F( name_width_fe1, name_width_fe1, 1500, 0, 1500 );
		hist ->GetYaxis()->SetTitle("k_{FSR}");
		hist ->GetXaxis()->SetTitle("p_{T}");
		hist -> GetYaxis()->SetRangeUser( 0, 0.4 );

		for( unsigned int p = 0; p < Widths.at(m).size(); p++ )
		{
			if ( forward_width_pt.at(m).at(p).at(0)!= 0 )
			{
				hist -> SetBinContent( hist -> FindBin( forward_width_pt.at(m).at(p).at(0) ), Widths.at(m).at(p) );
				hist -> SetBinError( hist -> FindBin( forward_width_pt.at(m).at(p).at(0) ), WidthsError.at(m).at(p) );
			}
		}
		hist ->GetYaxis()-> SetRangeUser( 0.8*(hist -> GetMinimum()), 1.2*(hist -> GetMaximum()) );
		widths.push_back(hist);
	}
}


void KFSR_ratios( TString name1, std::vector<TH1F*> &widths, std::vector<std::vector<double> > Widths, std::vector<std::vector<double> > WidthsError, std::vector<std::vector<double> > WidthsTwo, std::vector<std::vector<double> > WidthsTwoError, std::vector<std::vector<std::vector<double> > > forward_width_pt )
{
	double temp, tempError;

	for( unsigned int m = 0; m < Widths.size(); m++ )
	{
		TString name_width_fe1 = name1;
		name_width_fe1 += "_eta"; name_width_fe1 += m+1;
		
		TH1F *hist = new TH1F( name_width_fe1, name_width_fe1, 1500, 0, 1500 );
		hist ->GetYaxis()->SetTitle("k_{FSR}^{Data}/k_{FSR}^{MC}");
		hist ->GetXaxis()->SetTitle("p_{T}");
		hist -> GetYaxis()->SetRangeUser( 0, 2. );

		for( unsigned int p = 0; p < Widths.at(m).size(); p++ )
		{
			if ( forward_width_pt.at(m).at(p).at(0)!= 0 )
			{
				temp = Widths.at(m).at(p)/WidthsTwo.at(m).at(p);
				tempError = WidthsError.at(m).at(p)/WidthsTwo.at(m).at(p) + ( Widths.at(m).at(p) * WidthsTwoError.at(m).at(p) ) / ( WidthsTwo.at(m).at(p) * WidthsTwo.at(m).at(p) ) ;

				hist -> SetBinContent( hist -> FindBin( forward_width_pt.at(m).at(p).at(0) ), temp );
				hist -> SetBinError( hist -> FindBin( forward_width_pt.at(m).at(p).at(0) ), tempError );
			}
		}
		widths.push_back(hist);
	}
}


void widths_015_ratios( TString name1, std::vector<TH1F*> &widths, std::vector<std::vector<std::vector<double> > > Widths, std::vector<std::vector<std::vector<double> > > WidthsError, std::vector<std::vector<std::vector<double> > > WidthsTwo, std::vector<std::vector<std::vector<double> > > WidthsTwoError, std::vector<std::vector<std::vector<double> > > forward_width_pt )
{
	double temp, tempError;

	for( unsigned int m = 0; m < Widths.size(); m++ )
	{
		TString name_width_fe1 = name1;
		name_width_fe1 += "_eta"; name_width_fe1 += m+1;
		
		TH1F *hist = new TH1F( name_width_fe1, name_width_fe1, 1500, 0, 1500 );
		hist ->GetYaxis()->SetTitle();
		hist ->GetXaxis()->SetTitle("p_{T}");
		hist -> GetYaxis()->SetRangeUser( 0, 2. );

		for( unsigned int p = 0; p < Widths.at(m).size(); p++ )
		{
			if ( forward_width_pt.at(m).at(p).at(1)!= 0 )
			{
				temp = Widths.at(m).at(p).at(1)/WidthsTwo.at(m).at(p).at(1);
				tempError = WidthsError.at(m).at(p).at(1)/WidthsTwo.at(m).at(p).at(1) + ( Widths.at(m).at(p).at(1) * WidthsTwoError.at(m).at(p).at(1) ) / ( WidthsTwo.at(m).at(p).at(1) * WidthsTwo.at(m).at(p).at(1) ) ;

				hist -> SetBinContent( hist -> FindBin( forward_width_pt.at(m).at(p).at(1) ), temp );
				hist -> SetBinError( hist -> FindBin( forward_width_pt.at(m).at(p).at(1) ), tempError );
			}
		}
		widths.push_back(hist);
	}
}


void KNFS_line_fit( TString name1, std::vector<TH1F*> widths, std::vector< TF1* > &functions )
{
	for( unsigned int m = 0; m < widths.size(); m++ )
	{
		TString name_width_fe1 = name1;
		name_width_fe1 += "_eta"; name_width_fe1 += m+1;
		
		TF1 * linfit = new TF1( "linfit", "[0]+x*[1]", 0, 0.25 );

		widths.at(m)-> Fit("linfit","");

		functions.push_back(linfit);
	}
}


void correctKFSR( std::vector<std::vector<double> > &Output, std::vector<std::vector<double> > &OutputError, std::vector<std::vector<std::vector<double> > > Widths, std::vector<std::vector<std::vector<double> > > WidthsError, std::vector<TF1*> functions, std::vector<std::vector<std::vector<double> > > forward_width_pt )
{
	for( unsigned int i = 0; i < Widths.size(); i++ )
	{
		std::vector< double > temp2;
		std::vector< double > temp_error2;

		for( unsigned int j = 0; j < Widths.at(i).size(); j++ )
		{
			double temp1;
			double temp_error1;

			temp1 = TMath::Sqrt(2) * ( Widths.at(i).at(j).at(2) - 0.2 * functions.at(i)->Eval( forward_width_pt.at(i).at(j).at(2) ) );
			temp_error1 = TMath::Sqrt(2) * ( Widths.at(i).at(j).at(2) * WidthsError.at(i).at(j).at(2) +	0.2*functions.at(i)->Eval( forward_width_pt.at(i).at(j).at(2) )*( forward_width_pt.at(i).at(j).at(2)*functions.at(i)->GetParError(1) + functions.at(i)->GetParError(0) ) ) ;

			temp2.push_back(temp1);
			temp_error2.push_back(temp_error1);
		}
		Output.push_back(temp2);
		OutputError.push_back(temp_error2);
	}
}


void correctJERwithPLI(std::vector< std::vector< double > > &Output, std::vector< std::vector< double > > &OutputError, std::vector< std::vector< double > > Widths, std::vector< std::vector< double > > WidthsError, std::vector< std::vector< double > > PLI, std::vector< std::vector< double > > PLIError)
{
	for( unsigned int i = 0; i < Widths.size(); i++ )
	{
		std::vector< double > temp2;
		std::vector< double > temp_error2;

		for( unsigned int j = 0; j < Widths.at(i).size(); j++ )
		{
			double temp;
			double temp_error;

			if(Widths.at(i).at(j) != 0. )
			{
				temp = TMath::Sqrt( Widths.at(i).at(j) * Widths.at(i).at(j) - PLI.at(i).at(j) * PLI.at(i).at(j) );
				temp_error = ( Widths.at(i).at(j) * WidthsError.at(i).at(j) + PLI.at(i).at(j) * PLIError.at(i).at(j) )/temp;
			}
			else
			{
			   temp = 0.;
			   temp_error = 0.;
			}

//			std::cout << "reco " << Widths.at(i).at(j) << ", pli " << PLI.at(i).at(j) << ", corrected width " << temp << std::endl;

			if( TMath::IsNaN(temp) ) { temp = 0. ; temp_error = 0.; }

			temp2.push_back(temp);
			temp_error2.push_back(temp_error);
		}
		Output.push_back(temp2);
		OutputError.push_back(temp_error2);
	}
}


void correctJERwithPLI015(std::vector<std::vector<double> > &Output, std::vector<std::vector<double> > &OutputError, std::vector<std::vector<std::vector<double> > > Widths, std::vector<std::vector<std::vector<double> > > WidthsError, std::vector<std::vector<std::vector<double> > > PLI, std::vector<std::vector< std::vector< double > > > PLIError)
{
	for( unsigned int i = 0; i < Widths.size(); i++ )
	{
		std::vector< double > temp2;
		std::vector< double > temp_error2;

		for( unsigned int j = 0; j < Widths.at(i).size(); j++ )
		{
			double temp;
			double temp_error;

			temp = TMath::Sqrt( Widths.at(i).at(j).at(1) * Widths.at(i).at(j).at(1) - PLI.at(i).at(j).at(1) * PLI.at(i).at(j).at(1) );
			temp_error = ( Widths.at(i).at(j).at(1) * WidthsError.at(i).at(j).at(1) + PLI.at(i).at(j).at(1) * PLIError.at(i).at(j).at(1) )/temp;

//			std::cout << "reco " << Widths.at(i).at(j).at(1) << ", pli " << PLI.at(i).at(j).at(1) << ", corrected width " << temp << std::endl;

			if( TMath::IsNaN(temp) ) { temp = 0 ; temp_error = 0; }

			temp2.push_back(temp);
			temp_error2.push_back(temp_error);
		}
		Output.push_back(temp2);
		OutputError.push_back(temp_error2);
	}
}


void correctForRef( TString name1, std::vector<std::vector<double> > &Output, std::vector<std::vector<double> > &OutputError, std::vector<std::vector<double> > Input, std::vector<std::vector<double> > InputError, std::vector<std::vector<std::vector<double> > > width_pt  )
{
	double sqRef , sqProbe;
	double Ref, Probe, RefError, ProbeError;
	double N, S, C, sN, sS, sC, pT;

	TString name_width_fe1 = name1;
	TF1 * NSCfun = new TF1( name_width_fe1, "TMath::Sqrt(TMath::Power(([0]/x),2)+TMath::Power([1],2)/x + TMath::Power([2],2))", 0, 1000 );
	NSCfun->SetParName(0,"N");	NSCfun->SetParName(1,"S");	NSCfun->SetParName(2,"C");

	TH1F *hist = new TH1F( name1+"_hist", name1+"_hist", 1500, 0, 1500 );
	hist ->GetYaxis()->SetTitle("#sigma_{A}");
	hist ->GetXaxis()->SetTitle("p_{T}");

	for( unsigned int p = 0; p < Input.at(0).size(); p++ )
	{
		if ( Input.at(0).at(p) != 0 && !(TMath::IsNaN(Input.at(0).at(p))))
		{
			hist -> SetBinContent( hist -> FindBin( width_pt.at(0).at(p).at(4) ), Input.at(0).at(p) );
			hist -> SetBinError( hist -> FindBin( width_pt.at(0).at(p).at(4) ), InputError.at(0).at(p) );
		}
	}

	hist -> Fit(name_width_fe1,"");
			
	for( unsigned int m = 1; m < Input.size() ; m++ )
	{
		std::vector< double > temp2;
		std::vector< double > temp_error2;

		for( unsigned int p = 0; p < Input.at(m).size(); p++ )
		{
			double temp;
			double temp_error;

			if ( Input.at(m).at(p) != 0. ) 
			{
			   pT = width_pt.at(m).at(p).at(4) ;
     
			   N = NSCfun -> GetParameter(0) ;
			   sN = NSCfun -> GetParError(0) ;
			   S = NSCfun -> GetParameter(1) ;
			   sS = NSCfun -> GetParError(1) ;
			   C = NSCfun -> GetParameter(2) ;
			   sC = NSCfun -> GetParError(2) ;
    
			   Ref = NSCfun->Eval( pT );
			   Probe = Input.at(m).at(p);
			   ProbeError = InputError.at(m).at(p);
			   RefError = ( (N*sN)/(pT*pT) + ( S*sS )/pT + C*sC )/Ref;
    
			   sqRef = Ref*Ref;
			   sqProbe = Probe*Probe;
    
			   temp = TMath::Sqrt( 2*sqProbe - sqRef);
			   temp_error = ( 2*Probe*ProbeError + Ref*RefError )/temp;
    
    //			   std::cout << "probe " << Probe << ", ref " << Ref << ", corrected width " << temp << std::endl;
    
			   if( !(TMath::IsNaN(temp)) ) temp2.push_back(temp);
			   else temp2.push_back(0.);
			   if( !(TMath::IsNaN(temp)) ) temp_error2.push_back(temp_error);
			   else temp_error2.push_back(0.);
			}
			else { temp2.push_back(0.); temp_error2.push_back(0.); }
		}
		Output.push_back(temp2);
		OutputError.push_back(temp_error2);
	}
}


void makeScales( std::vector< std::vector< double > > &Output, std::vector< std::vector< double > > &OutputError, std::vector< std::vector< double > > Input1, std::vector< std::vector< double > > Input1Error, std::vector< std::vector< double > > Input2, std::vector< std::vector< double > > Input2Error )
{
	for( unsigned int i = 0; i < Input1.size(); i++ )
	{
		std::vector< double > temp2;
		std::vector< double > temp_error2;

		for( unsigned int j = 0; j < Input1.at(i).size(); j++ )
		{
			double temp;
			double temp_error;

			if( (Input1.at(i).at(j)!=0.) && (Input2.at(i).at(j)!=0.) && Input1.at(i).at(j) / Input2.at(i).at(j)>0.7 && Input1.at(i).at(j) / Input2.at(i).at(j)<2. )
			{
			   temp = Input1.at(i).at(j) / Input2.at(i).at(j);
			   temp_error = Input1Error.at(i).at(j) / Input2.at(i).at(j) + ( Input1.at(i).at(j) * Input2Error.at(i).at(j)) / ( Input2.at(i).at(j) * Input2.at(i).at(j) ) ;
			}
			else{ temp = 0.; temp_error = 0.; }


			if( TMath::IsNaN(temp) ) { temp = 0.; temp_error = 0.; }

			temp2.push_back(temp);
			temp_error2.push_back(temp_error);
		}
		Output.push_back(temp2);
		OutputError.push_back(temp_error2);
	}
}


void fill_hist( TString name1, std::vector< TH1F* > &output, std::vector< std::vector< double > > Widths, std::vector< std::vector< double > > WidthsError, std::vector< std::vector< std::vector< double > > > pt_binning, double range)
{
	int shift;

//	if (Widths.size() == 4 ) shift = 1;
//	if (Widths.size() == 5 ) shift = 2;
	
	for( unsigned int m = 0; m <  Widths.size(); m++ )
	{
		TString name_width_fe1 = name1;
		name_width_fe1 += m+shift; 
		TH1F *h1 = new TH1F( name_width_fe1, name_width_fe1, 1000, 0, 1000 );
		h1 ->GetYaxis()->SetTitle("#sigma_{JER}");	h1 ->GetXaxis()->SetTitle("p_{T}");	h1 -> Sumw2();

		for( unsigned int p = 0; p <  Widths.at(m).size(); p++ )
		{
			if( ( !(TMath::IsNaN(Widths.at(m).at(p))) ) && Widths.at(m).at(p)!= 0. ) h1 -> SetBinContent( h1 -> FindBin( pt_binning.at(m).at(p).at(4) ), Widths.at(m).at(p) );
			if( ( !(TMath::IsNaN(WidthsError.at(m).at(p))) ) && Widths.at(m).at(p)!= 0. ) h1 -> SetBinError( h1 -> FindBin( pt_binning.at(m).at(p).at(4) ), WidthsError.at(m).at(p) );
		}
		h1 ->GetYaxis()-> SetRangeUser( 0., range );
		output.push_back(h1);
	}
}













void histMeanAsym_Pt( std::vector< std::vector< std::vector< TH1F* > > > &Asymmetry , std::vector< std::vector< double > > &Widths  )
{
	for( int m = 0; m < 5; m++ )
	{
		std::vector< double > temp2;
		for( int p = 0; p < 9; p++ )
		{
//			std::cout << "eta " << m << ", pt " << p << ", mean pt " << (*Asymmetry.at(m).at(p).at(6)).GetMean() << std::endl;
			temp2.push_back( (*Asymmetry.at(m).at(p).at(6)).GetMean() );
		}
		Widths.push_back(temp2);
	}
}


void fill_widthsFE_pt( TString name1, std::vector< TH1F* > &widths, std::vector< std::vector< double > > Widths, std::vector< std::vector< double > > WidthsError, std::vector< std::vector< double > > forward_width_pt )
{
	for( int m = 0; m < 5; m++ )
	{
		TString name_width_fe1 = name1;
		name_width_fe1 += "_eta"; name_width_fe1 += m+1;
			
		TH1F *hist = new TH1F( name_width_fe1, name_width_fe1, 1500, 0, 1500 );
		hist ->GetYaxis()->SetTitle("#sigma_{A}");
		hist ->GetXaxis()->SetTitle("p_{T}");
//		hist -> GetYaxis()->SetRangeUser( 0, 0.2 );

		for( unsigned int p = 0; p < Widths.at(m).size(); p++ )
		{
			hist -> SetBinContent( hist -> FindBin( forward_width_pt.at(m).at(p) ), Widths.at(m).at(p) );
			hist -> SetBinError( hist -> FindBin( forward_width_pt.at(m).at(p) ), WidthsError.at(m).at(p) );
		}
		widths.push_back(hist);
	}
}


// fitType 0 -> gaussian fit, 1 -> RMS (100% of points), 2 -> shifted gaussian
void fitAsym( TH1F &hist, double &width, double &error , double &centre, double &centre_error, double &chisqr, int fitType, double position , bool fix )
{

	TF1 * myfit = new TF1( "myfit", "[0]*exp(-0.5*TMath::Power(((x-[1])/[2]),2))", 0, 0.15 );
//	TF1 * myfit2 = new TF1( "myfit2", "[0]* exp( -( x^2 + [1]^2 )/(2*[2]) ) * ( exp( 2*x*[1]/(2*[2]) ) + exp( -2*x*[1]/([2]*2) ) )	", 0, 0.15 );
	TF1 * myfit2 = new TF1( "myfit2", "[0]*exp( -( TMath::Power(x,2) + TMath::Power([1],2) )/(2*[2]) ) * ( exp( 2*x*[1]/(2*[2]) ) + exp( -2*x*[1]/([2]*2) ) )", 0, 0.15 );

	double norm = hist.Integral();
	if ( norm != 0 ) hist.Scale( 1/norm );

	if ( fitType == 0 )
	{
		double widthAux;
//		std::cout << hist.GetTitle() << std::endl;
//		std::cout << "bin content " << hist.GetBinContent(1) << std::endl;
		myfit -> SetParameter( 0, hist.GetBinContent(1) );
//		std::cout << "set heigth " << myfit.GetParamter(0) << std::endl;
//		myfit -> SetParameter( 0, 2*hist.GetMean(2) );
		myfit -> SetParameter( 1, 0 );
		myfit -> SetParameter( 2, hist.GetRMS() );
		myfit -> FixParameter( 1, 0 );//I fix the mean value (center of gaus distribution) at 0
	
		myfit -> SetRange( 0, 0.2);

		hist.Fit( "myfit", "NQLR" );
		widthAux = myfit -> GetParameter(2);
		myfit -> SetRange( 0, 2*TMath::Abs(widthAux));

		hist.Fit( "myfit", "RLQN" );
		widthAux = myfit -> GetParameter(2);
		myfit -> SetRange( 0, 2*TMath::Abs(widthAux));

		hist.Fit( "myfit", "LQR" );
		width = TMath::Abs(myfit -> GetParameter(2));
		error = myfit -> GetParError(2);

		centre = 0;
		centre_error = 0;

		chisqr = ( myfit -> GetChisquare() )/( myfit -> GetNDF() );

/*		if ( (myfit -> GetParameter(2)) > 1)
		{
			std::cout << "fit not converged, trying log-likelihood fit" << std::endl;
			std::cout << "chi-square fit gave: " << "width = " << width << std::endl;

			hist.Fit( "myfit", "NQLR" );
			widthAux = myfit -> GetParameter(2);
			myfit -> SetRange( 0, 2*TMath::Abs(widthAux));
   
			hist.Fit( "myfit", "RQNL" );
			widthAux = myfit -> GetParameter(2);
			myfit -> SetRange( 0, 2*TMath::Abs(widthAux));
   
			hist.Fit( "myfit", "QRL" );
			width = TMath::Abs(myfit -> GetParameter(2));
			error = myfit -> GetParError(2);

			std::cout << "fit gave:          " << "width = " << width << std::endl;
		}*/
	}

	else if ( fitType == 1 )
	{
		width = hist.GetRMS();
		error = hist.GetRMSError();

		centre = 0;
		centre_error = 0;
		chisqr = 0;
	}

	else if ( fitType == 2 )
	{
		hist.Scale(1);
		
		myfit2 -> SetParameter( 0, 0.05 );
		myfit2 -> SetParLimits( 0, 0.001, 0.2 );
		if ( position != 0. )
		{
			if ( fix == false )
			{
				myfit2 -> SetParameter( 1, position );
				myfit2 -> SetParLimits( 1, 0., 0.2 );
			}
			if ( fix == true ) myfit2 -> FixParameter( 1, position );
		}
		else 
		{
			myfit2 -> SetParameter( 1, 0.05 );
			myfit2 -> SetParLimits( 1, 0., 0.2 );
		}
		myfit2 -> SetParameter( 2, hist.GetRMS() );
		myfit2 -> SetParLimits( 2, 0.001, 0.1 );

		myfit2 -> SetRange( 0, 0.25);
		hist.Fit( "myfit2", "QR" );

//		double new_range = myfit2 -> GetParameter(1) + 2*(myfit2 -> GetParameter(2));

//		std::cout << "new range up to " << new_range << std::endl;
//		if ( new_range > 0.05 ) myfit2 -> SetRange( 0, new_range );
//		hist.Fit( "myfit2", "QR" );

		width = TMath::Abs(myfit2 -> GetParameter(2));
		error = myfit2 -> GetParError(2);

		centre = TMath::Abs(myfit2 -> GetParameter(1));
		centre_error = myfit2 -> GetParError(1);

		chisqr = ( myfit2 -> GetChisquare() )/( myfit2 -> GetNDF() );
//		std::cout << "chisqr/NDF = " << chisqr << std::endl;
//		std::cout << "normalization = " << myfit2 -> GetParameter(0) << std::endl;
	}

	else std::cout << "wrong fit type in function argument" << std::endl;
}


void fitMCTruth( TH1F &hist, double &width, double &error )
{

	TF1 * myfit = new TF1( "myfit", "[0]*exp(-0.5*((x-[1])/[2])^2)", 0, 0.15 );

	double norm = hist.Integral();
	if ( norm != 0 ) hist.Scale( 1/norm );

	double widthAux, meanAux;
	myfit -> SetParameter( 0, hist.GetMaximum() );
	myfit -> SetParameter( 1, hist.GetMean() );
	myfit -> SetParameter( 2, hist.GetRMS() );

	myfit -> SetRange( 0, 2);

	hist.Fit( "myfit", "NQR" );
	widthAux = TMath::Abs(myfit -> GetParameter(2));
	meanAux = myfit -> GetParameter(1);
	myfit -> SetRange( meanAux - 2*widthAux, meanAux + 2*widthAux);

	hist.Fit( "myfit", "RQN" );
	widthAux = TMath::Abs(myfit -> GetParameter(2));
	meanAux = myfit -> GetParameter(1);
	myfit -> SetRange( meanAux - 2*widthAux, meanAux + 2*widthAux);

	hist.Fit( "myfit", "RQ" );
	width = TMath::Abs(myfit -> GetParameter(2));
	error = myfit -> GetParError(2);

}


void fitConst( TH1F &hist, double &value, double &error )
{
	TF1 * constfit = new TF1( "constfit", "pol0", 0, 0.25 );

	constfit -> SetParameter( 0, 0.1 );

	constfit -> SetParLimits( 0, 0., 1. );

	hist.Fit( "constfit", "Q" );
	value = constfit -> GetParameter(0);
	error = constfit -> GetParError(0);
}


void fitLin( TH1F &hist, double &width, double &error )
{
	TF1 * linfit = new TF1( "linfit", "[0]+x*[1]", 0, 0.3 );

	linfit -> SetParameter( 0, 0.1 );
	linfit -> SetParameter( 1, 0.1 );

	linfit -> SetParLimits( 0, 0., 1. );

	hist.Fit( "linfit", "Q" );
	width = linfit -> GetParameter(0);
	error = 1. * ( linfit -> GetParError(0) );
}


void fitShift( TH1F &hist, double &a, double &errora, double &b, double &errorb )
{
	TF1 * linfit = new TF1( "linfit", "[0]+x*[1]", 0, 0.25 );

	linfit -> FixParameter( 0, 0.0 );
	linfit -> SetParameter( 1, 0.1 );

//	linfit -> SetParLimits( 0, 0, 1 );

	hist.Fit( "linfit", "Q" );
	a = linfit -> GetParameter(1);
	errora = linfit -> GetParError(1);
	b = linfit -> GetParameter(0);
	errorb = linfit -> GetParError(0);
}

// Kristins code, truncated-RMS calculation. To use 
float GetAsymmWidth(TH1F* &htemp, double * xq_IQW, double * yq_IQW)
{
	const int nq = 2;

	float width = 0.;
   float temp;

//	std::cout << htemp  << std::endl;

/*	if( htemp->GetEntries() > 100 ) 
	{
		htemp->GetXaxis()->SetRange(0,-1);
		htemp->ComputeIntegral();
		htemp->GetQuantiles(nq,yq_IQW,xq_IQW);
		Int_t IQW_high_bin_i = htemp->FindBin(yq_IQW[1]);

		// cout << "Truncated Integral in %: " << htemp->Integral(1,IQW_high_bin_i)/htemp->Integral() << endl;
		// cout << "Truncated Bin: " << htemp->FindBin(yq_IQW[1]) << endl;

		for(int i=1; i <= IQW_high_bin_i; i++) 
		{
			width += htemp->GetBinContent(i) * std::pow(htemp->GetBinCenter(i), 2);
      }
		temp = TMath::Sqrt((1/(htemp->Integral(1, IQW_high_bin_i)))*width);
	}*/
	if( htemp->GetEntries() == 0 ) 
	{
		std::cout << "pusty hitogram, ale czilujemy" << std::endl;
		temp = 0;
	}

	else
	{
//		width = htemp -> GetRMS();
		int last_bin = htemp->FindLastBinAbove();
		for(int i=1; i <= last_bin; i++) 
		{
			width += htemp->GetBinContent(i) * std::pow(htemp->GetBinCenter(i), 2);
      }
		temp = TMath::Sqrt(width/(htemp->Integral()));
	}

   return temp;  
}
