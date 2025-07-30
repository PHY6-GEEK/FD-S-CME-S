void smooth(const char* filename="/media/nandini/D804-C2A4/G3_Data/Mu_Filt_Rate_2003.root") {
    TFile *file = TFile::Open(filename);
    if (!file || file->IsZombie()) {
        Error("canvas", "Could not open file %s", filename);
        return;
    }

    
    const char* profileNames[] = { 
        "Filt_Smooth_Rate_9"  
    };
    const int nProfiles = 1; 

    
    TCanvas *c1 = new TCanvas("c3", "Profile Comparison", 800, 1200); 
    c1->Divide(1, 3);

    
    Int_t colors[] = {kCyan+2, kViolet+2, kBlack};
    Int_t markers[] = {20, 21, 22}; 

    for (int i = 0; i < nProfiles; i++) {
        c1->cd(i+1); 
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.05); 
        gPad->SetGridx(); gPad->SetGridy();

        TProfile *prof = (TProfile*)file->Get(profileNames[i]);
        if (!prof) {
            Warning("canvas", "Profile %s not found", profileNames[i]);
            continue;
        }

        
        prof->SetLineColor(colors[i]);
        prof->SetMarkerColor(colors[i]);
        prof->SetMarkerStyle(markers[i]);
        prof->SetMarkerSize(1.2); 
        prof->SetLineWidth(2);

        
        prof->GetXaxis()->SetTitle("X-Axis (Units)");
        prof->GetYaxis()->SetTitle("Y-Axis (Units)");
        prof->GetYaxis()->SetTitleOffset(1.8); 

        
        prof->Draw("E");

    
        TLatex *panelTitle = new TLatex(0.15, 0.85, profileNames[i]);
        panelTitle->SetNDC();
        panelTitle->SetTextSize(0.06);
        panelTitle->SetTextColor(colors[i]);
        panelTitle->Draw();
    }

    
    c1->cd(0); 
    TLatex *mainTitle = new TLatex(0.5, 0.995, " Profile Comparison");
    mainTitle->SetNDC();
    mainTitle->SetTextAlign(22);
    mainTitle->SetTextSize(0.03);
    mainTitle->Draw();

    c1->Update();
    
}