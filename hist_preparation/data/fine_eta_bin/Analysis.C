#include "MySelector.h"
#include <iostream>
#include <TChain.h>
#include <TMinuit.h>
#include <TF1.h>
#include <TLatex.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <string>
#include <TCanvas.h>
#include <TFileCollection.h>


int main() 
{
   MySelector *A = new MySelector();

   TChain* ch = new TChain("AK4PFCHS/t");
	TChain* c1 = new TChain("hlt/t");

 	FILE *input;
	char filename[300];
 
	input = fopen("../lists/file_25ns_full.txt","r");

	if (input != NULL)
	{ // lets read each line and get the filename from it
		while (fscanf(input,"%s\n",filename) != EOF)
		{
			printf("%s\n",filename);
			ch->Add(filename);
			ch->AddFriend(c1,filename);
		}
	}

	ch->Process(A);

}
