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

	int i = 7;

	TString filenames [] = {"../lists/file_list_25ns_76X.txt",
									"../lists/file_list_25ns_76X1.txt",
									"../lists/file_list_25ns_76X2.txt",
									"../lists/file_list_25ns_76X3.txt",
									"../lists/file_list_25ns_76X4.txt",
									"../lists/file_list_25ns_76X5.txt",
									"../lists/file_list_25ns_76X6.txt",
									"../lists/file_list_25ns_76X_test.txt",
									"../lists/ptbinned/file_list_5to10_76X.txt",
									"../lists/ptbinned/file_list_10to15_76X.txt",
									"../lists/ptbinned/file_list_15to30_76X.txt",
									"../lists/ptbinned/file_list_30to50_76X.txt",
									"../lists/ptbinned/file_list_50to80_76X.txt",
									"../lists/ptbinned/file_list_80to120_76X.txt",
									"../lists/ptbinned/file_list_120to170_76X.txt",
									"../lists/ptbinned/file_list_170to300_76X.txt",
									"../lists/ptbinned/file_list_300to470_76X.txt",
									"../lists/ptbinned/file_list_470to600_76X.txt",
									"../lists/ptbinned/file_list_600to800_76X.txt",
									"../lists/ptbinned/file_list_800to1000_76X.txt",
									"../lists/ptbinned/file_list_1000to1400_76X.txt",
									"../lists/ptbinned/file_list_1400to1800_76X.txt",
									"../lists/ptbinned/file_list_1800to2400_76X.txt",
									"../lists/ptbinned/file_list_2400to3200_76X.txt",
									"../lists/ptbinned/file_list_3200toInf_76X.txt"};

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
