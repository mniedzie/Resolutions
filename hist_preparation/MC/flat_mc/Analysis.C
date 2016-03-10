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
#include <TLorentzVector.h>

int main() 
{
   MySelector *A = new MySelector();

   TChain* ch = new TChain("AK4PFCHS/t");
	TChain* c1 = new TChain("event/t");

 	FILE *input;
	char filename[300];

	int i = 0;

	TString filenames [] = {"../lists/file_list_25ns.txt",
									"../lists/file_list_25ns_test.txt",
									"../lists/file_list_5to10.txt",
									"../lists/file_list_10to15.txt",
									"../lists/file_list_15to30.txt",
									"../lists/file_list_30to50.txt",
									"../lists/file_list_50to80.txt",
									"../lists/file_list_80to120.txt",
									"../lists/file_list_120to170.txt",
									"../lists/file_list_170to300.txt",
									"../lists/file_list_300to470.txt",
									"../lists/file_list_470to600.txt",
									"../lists/file_list_600to800.txt",
									"../lists/file_list_800to1000.txt",
									"../lists/file_list_1000to1400.txt",
									"../lists/file_list_1400to1800.txt",
									"../lists/file_list_1800to2400.txt",
									"../lists/file_list_2400to3200.txt",
									"../lists/file_list_3200toInf.txt"};

	input = fopen( filenames[i], "r" );

	if (input != NULL)
	{ // lets read each line and get the filename from it
		while (fscanf(input,"%s\n",filename) != EOF) 
		{
			printf("%s\n",filename); 
			ch->Add(filename);
			ch->AddFriend(c1,filename);
		}
	}

//	std::cout << "number of events is " << ch->GetEntries() << std::endl;

	ch -> Process(A);

//	std::cout <<"			Analyzed events #" <<  A -> TotalEvents << std::endl;

}
