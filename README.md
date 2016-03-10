#### Running histogram preapration ####

cd hist_preparation/MC/fine_eta_bin/ or different subdirectory, i.e. hist_preparation/data/fine_eta_bin/ 
make
./Analysis___.x



#### Running calculations

cd JER/fine_eta_binning/
root -l
gROOT->SetBatch(true)			if you produce a lot of pdfs and a lot of canvas, without it, it will take ages to run
.L iterFit.C++						compile the code
mainRun(false,"/afs/desy.de/user/n/niedziem/public/histograms_mc_incl_full_fine.root","/afs/desy.de/user/n/niedziem/public/histograms_data_incl_full.root")     path to root files you produced in histogram preparation part
