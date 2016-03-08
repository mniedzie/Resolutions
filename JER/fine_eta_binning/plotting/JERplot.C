#include "tdrstyle_mod15.C"
#include "TGraphErrors.h"
#include "TF1.h"

void JERplot() {

  setTDRStyle();

  // TWiki for 7, 8 and 13 TeV:
  // https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution#JER_Scaling_factors_and_Uncertai

  //0 - 0.5 0.5 - 1.1 1.1 - 1.7 1.7 - 2.3 2.3 - 2.8 2.8 - 3.2 3.2 - 5.0
  double eta7[] = {0, 0.5, 1.1, 1.7, 2.3, 5.0};
  const int neta7 = sizeof(eta7)/sizeof(eta7[0])-1;
  double jer7[neta7][2] = {{1.052 ,(1.115-0.990)/2}, {1.057 ,(1.114-1.001)/2}, {1.096 ,(1.161-1.032)/2}, {1.134 ,(1.228-1.042)/2}, {1.2588 ,(1.488-1.089)/2}};
  TH1D *h7 = new TH1D("h7",";#eta;JER",neta7,eta7);
  for (int i = 0; i != neta7; ++i) {
    h7->SetBinContent(i+1, jer7[i][0]);
    h7->SetBinError(i+1, jer7[i][1]);
  }

  //0 - 0.5 0.5 - 1.1 1.1 - 1.7 1.7 - 2.3 2.3 - 2.8 2.8 - 3.2 3.2 - 5.0
  double eta8[] = {0, 0.5, 1.1, 1.7, 2.3, 2.8, 3.2, 5.0};
  const int neta8 = sizeof(eta8)/sizeof(eta8[0])-1;
  double jer8[neta8][2] =
  // Statistics only?
  //{{1.079 ,0.005}, {1.099 ,0.005}, {1.121 ,0.005}, {1.208 ,0.013},
  // {1.254 ,0.026}, {1.395 ,0.036}, {1.056 ,0.048}};
  // With systematics included
    {{1.079 ,(1.105-1.053)/2}, {1.099 ,(1.127-1.071)/2},
     {1.121 ,(1.150-1.092)/2}, {1.208 ,(1.254-1.162)/2},
     {1.254 ,(1.316-1.192)/2}, {1.395 ,(1.458-1.332)/2},
     {1.056 ,(1.247-0.865)/2}};
  TH1D *h8 = new TH1D("h8",";#eta;JER",neta8,eta8);
  for (int i = 0; i != neta8; ++i) {
    h8->SetBinContent(i+1, jer8[i][0]);
    h8->SetBinError(i+1, jer8[i][1]);
  }

  //0 - 0.8 0.8 - 1.3 1.3 - 1.9 1.9 - 2.5 2.5 - 3.0 3.0 - 3.2 3.2 - 4.7
  //double eta13[] = {0, 0.8, 1.3, 1.9, 2.5, 3.0, 3.2, 4.7}; // up to Jan29
  double eta13[] = {0, 0.5, 0.8, 1.1, 1.3,
		    1.7, 1.9, 2.1, 2.3, 2.5,
		    2.8, 3.0, 3.2, 4.7}; // from Feb28
  const int neta13 = sizeof(eta13)/sizeof(eta13[0])-1;

  // Director's cut settings: 1:ST, 2:FE, 3:ST+FE weighted, 4:(ST+8)/2, 5:(FE+8)/2
  int djer13[neta13] = {1,1,1,4, 3,3,1,3,3, 2,2,2,2};

  // Standard method tables
  double jer13[neta13][2] =
  //{{1.094 ,0.003}, {1.071 ,0.006}, {1.108 ,0.007}, {1.130 ,0.014},
    // {1.309 ,0.025}, {1.294 ,0.029}, {1.428 ,0.074}};
    // Nov 13
  //{{1.090 ,0.001}, {1.063 ,0.004}, {1.099 ,0.005}, {1.115 ,0.010},
  // {1.337 ,0.018}, {1.429 ,0.022}, {1.419 ,0.039}};
  // Nov 19, b-Standard
  //{{1.061 ,0.015}, {1.088 ,0.027}, {1.092 ,0.031}, {1.126 ,0.063},
  // {1.494 ,0.198}, {0 ,0}, {0 ,0}};
  // Nov23/Jan29, Standard
  //{{1.063, 0.013}, {1.086, 0.022}, {1.118, 0.026}, {1.127, 0.052},
    // {1.281, 0.145}, {0,0}, {0,0}};
  // Feb28, Standard

   // {{1.121,0.033},{1.095,0.056},{1.07,0.06},{0.9732,0.087},{1.049,0.043},{1.142,0.136},{1.065,0.157},{1.162,0.185},{1.062,0.179},{1.185,0.164},{1.128,0.498},{0,0},{0,0}};
  
  //march 7
 // {{1.149,0.012},{1.215,0.022},{1.155,0.021},{1.143,0.034},{1.13, 0.02},{1.108,0.055},{1.21, 0.08},{1.219,0.099},{1.156,0.133},{1.223,0.12},{0.8695,0.2422},{0,0},{0,0}};
  // march 7 .15 results
  {{1.11,0.01},{1.141,0.019},{1.095,0.017},{1.086,0.028},{1.112,0.016},{1.103,0.047},{1.175,0.067},{1.168,0.075},{1.124,0.098},{1.225,0.094},{1.136,0.199},{0,0},{0,0}};
  
  // Forward extension tables
  double jer13b[neta13][2] =
  //{{1.094 ,0.003}, {1.071 ,0.006}, {1.139 ,0.014}, {1.067 ,0.021},
    // {1.309 ,0.025}, {1.294 ,0.029}, {1.428 ,0.074}};
  // Nov 13
  //{{1.090 ,0.001}, {1.081 ,0.002}, {1.080 ,0.010}, {1.013 ,0.013},
  //{1.337 ,0.018}, {1.429 ,0.022}, {1.419 ,0.039}};
  // Nov 19, b-FE (
  //{{0 ,0}, {0 ,0}, {1.139 ,0.048}, {1.062 ,0.070},
  // {1.308 ,0.095}, {1.211 ,0.062}, {1.320 ,0.110}};
  // Nov23/Jan29, Forward extension
      //{{0,0}, {0,0}, {1.166, 0.043}, {1.112, 0.062},
      //{1.329, 0.081}, {1.217, 0.055}, {1.313, 0.101}};
  // Feb28 forward extension
    //{{0,0},{0,0},{0,0},{0,0},{1.181,0.048},{1.115,0.079},{1.124,0.091},{1.102,0.102},{1.192,0.115},{1.18,0.09},{1.559,0.12},{1.207,0.049},{1.199,0.064}};
	 //march 7
    //{{0,0},{0,0},{0,0},{0,0},{1.195,0.033},{1.165,0.053},{1.253,0.073},{1.284,0.079},{1.352,0.100},{1.366,0.105},{1.725,0.137},{1.365,0.040},{1.341,0.065}};
  // march 7 .15 results
  {{0,0},{0,0},{0,0},{0,0},{1.141,0.03},{1.097,0.047},{1.152,0.059},{1.155,0.062},{1.184,0.076},{1.198,0.076},{1.626,0.076},{1.384,0.033},{1.216,0.05}};


//    {{0,0},{0,0},{0,0},{0,0},{1.114,0.043},{1.118,0.070},{0.215,0.028},{1.099,0.088},{1.153,0.098},{1.236,0.086},{1.552,0.096},{1.161,0.038},{1.17,0.05}};
  
  // Effective statistical unceratinty (smalled or STD and FE)
  double jer13s[neta13] =
  //{0.015, 0.027, 0.031, 0.063, 0.095, 0.062, 0.110}; // Nov13
  //{0.013, 0.022, 0.026,  0.052, 0.081, 0.055, 0.101}; // Nov23/Jan29
  //{0.033,0.056,0.06,0.087,0.043,0.079,0.091,0.102,0.115,0.09,0.12,0.049,0.064};
  //{0.012,0.022,0.021,0.034,0.02,0.053,0.073,0.079,0.100,0.105,0.137,0.040,0.065};
    {0.01,0.019,0.017,0.028,0.016,0.047,0.059,0.062,0.076,0.076,0.076,0.033,0.05};

  TH1D *h13 = new TH1D("h13",";#eta;JER",neta13,eta13);   // STD
  TH1D *h13b = new TH1D("h13b",";#eta;JER",neta13,eta13); // FE
  TH1D *h13c = new TH1D("h13c",";#eta;JER",neta13,eta13); // STD+FE
  TH1D *h13d = new TH1D("h13d",";#eta;JER",neta13,eta13); // custom STD+FE
  TH1D *h13ds = new TH1D("h13ds",";#eta;JER",neta13,eta13); // w/ stat only

  TGraphErrors *gtmp = new TGraphErrors(2);
  TF1 *ftmp = new TF1("fmpt","[0]",0,3);
  for (int i = 0; i != neta13; ++i) {
    if (h13->GetBinCenter(i+1)<3.0) {
      h13->SetBinContent(i+1, jer13[i][0]);
      h13->SetBinError(i+1, jer13[i][1]);
    }
    //if (h13b->GetBinCenter(i+1)>0.8) { // up to Jan29
    if (h13b->GetBinCenter(i+1)>1.3) { // Feb28
      h13b->SetBinContent(i+1, jer13b[i][0]);
      h13b->SetBinError(i+1, jer13b[i][1]);
    }

    // combo
    double eta = h13->GetBinCenter(i+1);
    if (eta<1.3) { // STD
      h13c->SetBinContent(i+1, jer13[i][0]);
      h13c->SetBinError(i+1, jer13[i][1]);
    }
    if (eta>3.0) { // FE
      h13c->SetBinContent(i+1, jer13b[i][0]);
      h13c->SetBinError(i+1, jer13b[i][1]);
    }
    if (eta>1.3 && eta<3.0) { // weighted average of STD+FE
      gtmp->SetPoint(0,1,jer13[i][0]);
      gtmp->SetPointError(0,0,jer13[i][1]);
      gtmp->SetPoint(1,2,jer13b[i][0]);
      gtmp->SetPointError(1,0,jer13b[i][1]);
      gtmp->Fit(ftmp,"QRN");
      h13c->SetBinContent(i+1, ftmp->GetParameter(0));
      h13c->SetBinError(i+1, ftmp->GetParError(0));
    }
    
    // For comparing to 8 TeV results as part of systematics
    int j = h8->FindBin(h13b->GetBinCenter(i+1));

    // Director's cut
    if (djer13[i]==1) { // ST
      h13d->SetBinContent(i+1, h13->GetBinContent(i+1));
      h13d->SetBinError(i+1, h13->GetBinError(i+1));
    } // st
    if (djer13[i]==2) { // FE
      h13d->SetBinContent(i+1, h13b->GetBinContent(i+1));
      h13d->SetBinError(i+1, h13b->GetBinError(i+1));
    } // st
    if (djer13[i]==3) { // ST+FE weighted
      h13d->SetBinContent(i+1, h13c->GetBinContent(i+1));
      h13d->SetBinError(i+1, h13c->GetBinError(i+1));
    } // st
    if (djer13[i]==4) { // (ST+8)/2
      h13d->SetBinContent(i+1, 0.5*(h13->GetBinContent(i+1)+
				    h8->GetBinContent(j)));
      h13d->SetBinError(i+1, sqrt(pow(h13->GetBinError(i+1),2) +
				  pow(h13d->GetBinContent(i+1)-
				      h8->GetBinContent(j),2)));
    }
    if (djer13[i]==5) { // (FE+8)/2
      h13d->SetBinContent(i+1, 0.5*(h13b->GetBinContent(i+1)+
				    h8->GetBinContent(j)));
      h13d->SetBinError(i+1, sqrt(pow(h13b->GetBinError(i+1),2) +
				  pow(h13d->GetBinContent(i+1)-
				      h8->GetBinContent(j),2)));
    }

    /*
    //if (eta<1.9 || (eta>2.5 && eta<3.0) || (eta>3.2 && eta<4.7)) { // Nov19
    if (eta<3.0 || eta>3.2) { // Jan29
      h13d->SetBinContent(i+1, h13c->GetBinContent(i+1));
    }
    //if (eta>1.9 && eta<2.5) { // Nov 19
    //h13d->SetBinContent(i+1, h13->GetBinContent(i+1));
    //}
    if (eta>3.0 && eta<3.2) { // replace HE-HF bin (Nov19, Nov23/Jan29)
      h13d->SetBinContent(i+1, 0.5*(h13b->GetBinContent(i+1)+
				    h8->GetBinContent(j)));
    }
    h13d->SetBinError(i+1, sqrt(pow(h13c->GetBinError(i+1),2) +
				pow(h13d->GetBinContent(i+1)-
				    h8->GetBinContent(j),2)));
    */

    h13ds->SetBinContent(i+1, h13d->GetBinContent(i+1));
    h13ds->SetBinError(i+1, jer13s[i]);
  }

  lumi_13TeV = "Run2015D - 25 ns - 1.3 fb^{-1}";
  TH1D *h = new TH1D("h",";|#eta|;JER",52,0,5.2);
  //h->SetMinimum(1.00);
  //h->SetMaximum(1.50);
  h->SetMinimum(0.85);
  h->SetMaximum(1.60);
  TCanvas *c1 = tdrCanvas("c1",h,4,11,kSquare);
  
  tdrDraw(h7, "PE2", kFullSquare, kBlue, kSolid, kBlue, 1001, kBlue-9);
  //tdrDraw(h8, "PE2", kFullSquare, kGreen+2, kSolid, kGreen+2, 1001, kGreen-9);
  tdrDraw(h8, "PE2", kFullSquare, kGreen+2, kSolid, kGreen+2, 3001, kGreen-9);
  //tdrDraw(h13b, "PE2", kFullCircle, kRed, kSolid, kRed, 3001, kRed-9);
  //tdrDraw(h13,  "PE2", kFullCircle, kBlue, kSolid, kBlue, 3002, kCyan);//kBlue-9);
  //tdrDraw(h13c, "P", kFullStar, kMagenta+2);//, kSolid, kMagenta+1, 3001, kMagenta-9);
  //h13c->SetMarkerSize(1.3);
  tdrDraw(h13d, "Pz", kFullStar, kBlack);
  h13d->SetLineWidth(2);
  h13d->SetMarkerSize(1.5);
  tdrDraw(h13ds, "PE1", kFullStar, kBlack);
  h13ds->SetLineWidth(3);
  h13ds->SetMarkerSize(1.5);
  /*
  TH1D *h13cc = (TH1D*)h13c->Clone("h13cc");
  tdrDraw(h13c, "PE2", kFullCircle, kRed, kSolid, kRed, 3001, kRed-9);
  tdrDraw(h13cc, "P", kFullCircle, kRed);
  */

  TLegend *leg = tdrLeg(0.20,0.60,0.50,0.80);
  //TLegend *leg = tdrLeg(0.20,0.65,0.50,0.80); // Nov19
  //TLegend *leg = tdrLeg(0.20,0.70,0.50,0.80);
  leg->AddEntry(h7, " 7 TeV","FP");
  leg->AddEntry(h8, " 8 TeV","FP");
  //leg->AddEntry(h13c,"13 TeV","FPL");
  //leg->AddEntry(h13,"13 TeV - ST","FP");
  //leg->AddEntry(h13b,"13 TeV - FE","FP");
  //leg->AddEntry(h13c,"13 TeV","PL");
  //leg->AddEntry(h13d,"13 TeV - DC","PL");
  leg->AddEntry(h13ds,"13 TeV","PL");

  gPad->RedrawAxis();

  for (int i = 1; i != h13d->GetNbinsX()+1; ++i) {
    cout << Form("%1.1f - %1.1f: %1.3f +/- %1.3f\n",
		 h13d->GetBinLowEdge(i), h13d->GetBinLowEdge(i+1),
		 h13d->GetBinContent(i), h13d->GetBinError(i));
  }

  gPad->SaveAs("pdf/JERplot.pdf");
  gPad->SaveAs("pdfC/JERplot.C");
}
