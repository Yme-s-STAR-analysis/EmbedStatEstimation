#include "Util.h"

#include "TFile.h"
#include "TEfficiency.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TString.h"

void Utils::OpenFile(TFile* tf) {
    this->tf = tf;
}

void Utils::Init(int pid, int vz, int cent) {

    const char* tags[2] = {"Pro", "Pbar"};
    teff = (TEfficiency*)tf->Get(Form("TpcEff_y_pt_cent%d_vz%d_%s", cent, vz, tags[pid]));
    this->pid = pid;
    this->vz = vz;
    this->cent = cent;
    h2tot = (TH2D*)teff->GetTotalHistogram();
    h2pass = (TH2D*)teff->GetPassedHistogram();
}

void Utils::SetRapiditySlice(double y) {
    int bin = h2tot->GetXaxis()->FindBin(y);
    h1tot = h2tot->ProjectionY("tot_py", bin, bin);
    h1pass = h2pass->ProjectionY("pass_py", bin, bin);
    teff1D = new TEfficiency(*h1pass, *h1tot);
    if (-0.5 < y && y < -0.4) { this->y = 0; } 
    if (-0.4 < y && y < -0.3) { this->y = 1; } 
    if (-0.3 < y && y < -0.2) { this->y = 2; } 
    if (-0.2 < y && y < -0.1) { this->y = 3; } 
    if (-0.1 < y && y < -0.0) { this->y = 4; } 
    if (+0.0 < y && y < +0.1) { this->y = 5; } 
    if (+0.1 < y && y < +0.2) { this->y = 6; } 
    if (+0.2 < y && y < +0.3) { this->y = 7; } 
    if (+0.3 < y && y < +0.4) { this->y = 8; } 
    if (+0.4 < y && y < +0.5) { this->y = 9; } 
}

double Utils::GetEfficiency(double pt) {
    int bin = h2tot->GetYaxis()->FindBin(pt);
    return teff1D->GetEfficiency(bin);
}

double Utils::GetError(double pt) {
    int bin = h2tot->GetYaxis()->FindBin(pt);
    return (teff1D->GetEfficiencyErrorUp(bin) + teff1D->GetEfficiencyErrorLow(bin)) * 0.5;
}

double Utils::GetEntries(double pt) {
    int bin = h2tot->GetYaxis()->FindBin(pt);
    return h1tot->GetBinContent(bin);
} 

void Utils::DumpIntoFile(std::ofstream& fout, double pt) {
    fout << pid << "," << vz << "," << cent << "," << y << "," << pt << "," << GetEfficiency(pt) << "," << GetError(pt) << "," << GetError(pt) / GetEfficiency(pt) * 100  << "," << GetEntries(pt) << std::endl;
}
