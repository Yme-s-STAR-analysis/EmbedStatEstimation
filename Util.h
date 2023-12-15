#ifndef __UTILHH__
#define __UTILHH__

#include <fstream>

class TFile;
class TEfficiency;
class TH1D;
class TH2D;
class TF1;
class TGraphAsymmErrors;

class Utils {

    private:
        TFile* tf;
        TEfficiency* teff;
        TEfficiency* teff1D;
        TH2D *h2tot, *h2pass;
        TH1D *h1tot, *h1pass;
        TGraphAsymmErrors* tg;

        int pid, vz, cent, y;

    public:
        Utils(){}
        ~Utils(){}

        void OpenFile(TFile* tf);
        void Init(int pid, int vz, int cent);
        void SetRapiditySlice(double y);
        double GetEfficiency(double pt);
        double GetError(double pt);
        double GetEntries(double pt);
        void DumpIntoFile(std::ofstream& fout, double pt);

};

#endif