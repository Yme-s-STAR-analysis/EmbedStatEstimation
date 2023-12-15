#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TCanvas.h"
#include "TEfficiency.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TString.h"
#include "TF1.h"
#include "Util.h"


int main(int argc, char** argv) {
    /*
        Args:
        :fname: root file name
        :save name: out put text name


        The output file will follow the format below:
        
        0       1   2       3   4       5       6       7           8
        PID,    vz, cent,   y,  pt,     eff,    err,    rel. err,   entries
    */

    auto tf = new TFile(argv[1]);
    const char* sname = argv[2];

    std::ofstream fout;
    fout.open(sname);

    fout << "PID,Vz,Centrality,y,pT,Efficiency,Error,RelativeError,Tracks\n";

    TEfficiency* teff;

    const int nVz = 5;
    const int nCent = 9;
    const int nY = 10;
    const int nPro = 2; // pro and pbar

    const double pts[3] = {
        0.40, 0.50, 0.60
    };

    const double ys[nY] = {
        -0.45,
        -0.35,
        -0.25,
        -0.15,
        -0.05,
        +0.05,
        +0.15,
        +0.25,
        +0.35,
        +0.45,
    };

    Utils* mut = new Utils();

    mut->OpenFile(tf);

    for (int pid=0; pid<nPro; pid++) {
        for (int vz=0; vz<nVz; vz++) {
            for (int cent=0; cent<nCent; cent++) {
                mut->Init(pid, vz, cent);
                for (int y=0; y<nY; y++) {
                    mut->SetRapiditySlice(ys[y]);
                    for (int pt=0; pt<3; pt++) {
                        mut->DumpIntoFile(fout, pts[pt]);
                    }
                }
            }
        }
    }



    // out put 

    fout.close();

    return 0;
}