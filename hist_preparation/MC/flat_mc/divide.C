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

int divide()
{
	TFile f1("PU.root", "READ");	// pu distribution from MC, simply sill histogram with PU, with weight = 1
	TFile f2("MyDataPileup_V6_minBiasXsec69000_pileupJSON_151102.root", "READ");	// PU distriubtions from data, need to follow instructions from twiki (or ask JEC people ;) )
//	TFile f2("MyDataPileup_V6_minBiasXsec80000_pileupJSON_151102.root", "READ");	// distriubtion calculated with 80000 minbias, for systematic uncertainty calculations

	TH1F *mc = ( TH1F* )f1.Get("PileUp");
	TH1F *data = ( TH1F* )f2.Get("pileup");

	Double_t scaleMC = 1/(mc->Integral());
	Double_t scaleDt = 1/(data->Integral());

	mc->Scale(scaleMC);
	data->Scale(scaleDt);

	data -> Divide( mc );
	data -> DrawCopy();

	data ->GetXaxis()->SetTitle("PU");
	data ->GetYaxis()->SetTitle("weight");

	TFile h( "PUscale.root" ,"new" );

	data -> Write();

	h.Close();

	unsigned    bin = 0;
	for ( int i = 0; i < 61; i++)
	{
		bin = data -> FindBin(i);
		std::cout << "pu = " << i << "scale factor = " << data -> GetBinContent(bin) << std::endl;
	}

	return 0;
}
