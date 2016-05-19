#define MyAnalysis_cxx
// The class definition in MyAnalysis.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("MyAnalysis.C")
// Root > T->Process("MyAnalysis.C","some options")
// Root > T->Process("MyAnalysis.C+")
//

#include "MyAnalysis.h"
#include <iostream>
#include <TH1F.h>
#include <TLatex.h>

using namespace std;

void MyAnalysis::BuildEvent() {
   
   Muons.clear();
   for (int i = 0; i < NMuon; ++i) {
      MyMuon muon(Muon_Pt[i], Muon_Eta[i], Muon_Phi[i], Muon_E[i]);
      muon.SetIsolation(Muon_Iso[i]);
      muon.SetCharge(Muon_Charge[i]);
      Muons.push_back(muon);
   }
   
   Electrons.clear();
   for (int i = 0; i < NElectron; ++i) {
      MyElectron electron(Electron_Pt[i], Electron_Eta[i], Electron_Phi[i], Electron_E[i]);
      electron.SetIsolation(Electron_Iso[i]);
      electron.SetCharge(Electron_Charge[i]);
      Electrons.push_back(electron);
   }
   
   Photons.clear();
   for (int i = 0; i < NPhoton; ++i) {
      MyPhoton photon(Photon_Pt[i], Photon_Eta[i], Photon_Phi[i], Photon_E[i]);
      photon.SetIsolation(Photon_Iso[i]);
      Photons.push_back(photon);
   }
   
   Jets.clear();
   for (int i = 0; i < NJet; ++i) {
      MyJet jet(Jet_Pt[i], Jet_Eta[i], Jet_Phi[i], Jet_E[i]);
      jet.SetBTagDiscriminator(Jet_bDiscriminator[i]);
      //jet.SetJetID(Jet_ID[i]);
      Jets.push_back(jet);
   }
   
   //hadB.SetXYZM(MChadronicBottom_px, MChadronicBottom_py, MChadronicBottom_pz, 4.8);
   //lepB.SetXYZM(MCleptonicBottom_px, MCleptonicBottom_py, MCleptonicBottom_pz, 4.8);
   //hadWq.SetXYZM(MChadronicWDecayQuark_px, MChadronicWDecayQuark_py, MChadronicWDecayQuark_pz, 0.0);
   //hadWqb.SetXYZM(MChadronicWDecayQuarkBar_px, MChadronicWDecayQuarkBar_py, MChadronicWDecayQuarkBar_pz, 0.0);
   //lepWl.SetXYZM(MClepton_px, MClepton_py, MClepton_pz, 0.0);
   //lepWn.SetXYZM(MCneutrino_px, MCneutrino_py, MCneutrino_pz, 0.0);
   mymet.SetXYZM(MET_Px, MET_Py, 0., 0.);
   
   EventWeight = PUWeight*GenWeight*weight_factor*norm_scale;

}

void MyAnalysis::Begin(TTree * /*tree*/) {
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).
   
   TString option = GetOption();
   
}

void MyAnalysis::SlaveBegin(TTree * /*tree*/) {
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   
   TString option = GetOption();

   for(int i=0; i < 2; i++){ 
     h_NVertex[i] = new TH1F(Form("h_NVertex_S%i",i), "Number of vertex", 40 , 0, 40);
     h_NVertex[i]->SetXTitle("No. Vertexs");
     h_NVertex[i]->Sumw2();
     histograms.push_back(h_NVertex[i]);
     histograms_MC.push_back(h_NVertex[i]);
    
     h_Mmumu[i] = new TH1F(Form("h_Mmumu_S%i",i), "Invariant di-muon mass", 100, 40, 140);
     h_Mmumu[i]->SetXTitle("m_{#mu#mu}");
     h_Mmumu[i]->Sumw2();
     histograms.push_back(h_Mmumu[i]);
     histograms_MC.push_back(h_Mmumu[i]);
   
     h_NMuon[i] = new TH1F(Form("h_NMuon_S%i",i), "Number of muons", 7, 0, 7);
     h_NMuon[i]->SetXTitle("No. Muons");
     h_NMuon[i]->Sumw2();
     histograms.push_back(h_NMuon[i]);
     histograms_MC.push_back(h_NMuon[i]);
 
     h_MuonIso[i] = new TH1F(Form("h_MuonIso_S%i",i), "Relative Isolation", 80, 0, 0.4);
     h_MuonIso[i]->SetXTitle("Relative Isolation (GeV)");
     h_MuonIso[i]->Sumw2();
     histograms.push_back(h_MuonIso[i]);
     histograms_MC.push_back(h_MuonIso[i]);
 
     h_WMuon_MT[i] = new TH1F(Form("h_WMuon_MT_S%i",i), "Transverse mass", 60, 0, 120);
     h_WMuon_MT[i]->SetXTitle("MT(Gev)");
     h_WMuon_MT[i]->Sumw2();
     histograms.push_back(h_WMuon_MT[i]);
     histograms_MC.push_back(h_WMuon_MT[i]);

     h_WMuon_Phi[i] = new TH1F(Form("h_WMuon_Phi_S%i",i), "DR between muon and MET", 70, 0, 3.5);
     h_WMuon_Phi[i]->SetXTitle("DR between muon and MET");
     h_WMuon_Phi[i]->Sumw2();
     histograms.push_back(h_WMuon_Phi[i]);
     histograms_MC.push_back(h_WMuon_Phi[i]);

     h_NJet[i] = new TH1F(Form("h_NJet_S%i",i), "Number of jets", 14, 0, 14);
     h_NJet[i]->SetXTitle("No. Jets");
     h_NJet[i]->Sumw2();
     histograms.push_back(h_NJet[i]);
     histograms_MC.push_back(h_NJet[i]);

     h_NBJet[i] = new TH1F(Form("h_NBJet_S%i",i), "Number of b tagged jets", 5, 0, 5);
     h_NBJet[i]->SetXTitle("No. b Jets");
     h_NBJet[i]->Sumw2();
     histograms.push_back(h_NBJet[i]);
     histograms_MC.push_back(h_NBJet[i]);

     h_MET[i] = new TH1F(Form("h_MET_S%i",i), "MET", 100, 0, 100);
     h_MET[i]->SetXTitle("MET");
     h_MET[i]->Sumw2();
     histograms.push_back(h_MET[i]);
     histograms_MC.push_back(h_MET[i]);

   }

}

Bool_t MyAnalysis::Process(Long64_t entry) {
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either MyAnalysis::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
   bool debug = false;
 
   ++TotalEvents;
   
   GetEntry(entry);

   if (TotalEvents % 100000 == 0)
      cout << "Next event -----> " << TotalEvents << endl;
   
   BuildEvent();

   double MuonPtCut = 30.;
   double MuonEtaCut = 30.;
   double MuonRelIsoCut = 0.12;
   double ElectronPtCut = 30.;
   double ElectronEtaCut = 30.;
   double ElectronRelIsoCut = 0.12;
   
   //   cout << "Jets: " << endl;
   //   for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
   //      cout << "pt, eta, phi, btag, id: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", " << it->IsBTagged() << ", " << it->GetJetID() //      << endl;
   //   }
   //   cout << "Muons: " << endl;
   //   for (vector<MyMuon>::iterator it = Muons.begin(); it != Muons.end(); ++it) {
   //      cout << "pt, eta, phi, iso, charge: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", "
   //      << it->GetIsolation() << ", " << it->GetCharge() << endl;
   //   }
   //   cout << "Electrons: " << endl;
   //   for (vector<MyElectron>::iterator it = Electrons.begin(); it != Electrons.end(); ++it) {
   //      cout << "pt, eta, phi, iso, charge: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", "
   //      << it->GetIsolation() << ", " << it->GetCharge() << endl;
   //   }
   //   cout << "Photons: " << endl;
   //   for (vector<MyPhoton>::iterator it = Photons.begin(); it != Photons.end(); ++it) {
   //      cout << "pt, eta, phi, iso: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", " << it->GetIsolation()
   //      << endl;
   //   }
   
   
   //////////////////////////////
   // Exercise 1: Invariant Di-Muon mass
    
   int N_IsoMuon = 0;

   int sel_mu = 0;
   int imu = 0;


   MyMuon *muon1, *muon2;
   for (vector<MyMuon>::iterator jt = Muons.begin(); jt != Muons.end(); ++jt) {
     if( Muon_Iso[imu] < MuonRelIsoCut){
       N_IsoMuon++;
       if( N_IsoMuon == 1 ) {
         muon1 = &(*jt); 
         sel_mu = imu; 
       }
       if( N_IsoMuon == 2 ) muon2 = &(*jt); 
     }
     imu++;
   }

   int N_IsoElectron = 0;
   
   for (int i = 0; i < NElectron; ++i) {
     if( Electron_Iso[i] < ElectronRelIsoCut){
       N_IsoElectron++;
     }
   }

   int N_VetoMuon = 0;
   
   for (int i = 0; i < NLooseMuon; ++i) {
     if( LooseMuon_Iso[i] < 0.25){
       N_VetoMuon++;
     }
   }

   int N_VetoElectron = 0;

   for (int i = 0; i < NLooseElectron; ++i) {
     if( LooseElectron_Iso[i] < 0.25){
       N_VetoElectron++;
     }
   }

   if( debug ) cout << "filling at step0..." << endl;
   //////////////////////////////
   //step 0 
   if( NMuon == 1 ){
     h_MuonIso[0]->Fill(Muon_Iso[0], EventWeight);
     h_NMuon[0]->Fill(N_IsoMuon, EventWeight);
     h_NVertex[0]->Fill(NVertex, EventWeight);
     h_WMuon_MT[0]->Fill( WMuon_MT[sel_mu], EventWeight);
     h_WMuon_Phi[0]->Fill( WMuon_Phi[sel_mu], EventWeight);
     h_NJet[0]->Fill(NJet, EventWeight);
     h_NBJet[0]->Fill(NBJet, EventWeight);
     h_MET[0]->Fill(MET, EventWeight);
   }

   if( debug ) cout << "filling at step1..." << endl;
   if(NMuon == 1 && WMuon_MT[0] < 20 && WMuon_Phi[0] < 1.5 && NJet >= 1){ //step 1
  
     h_MuonIso[1]->Fill(Muon_Iso[0], EventWeight); 
     h_NMuon[1]->Fill(N_IsoMuon, EventWeight);
     h_NVertex[1]->Fill(NVertex, EventWeight);
     h_WMuon_MT[1]->Fill( WMuon_MT[sel_mu], EventWeight);
     h_WMuon_Phi[1]->Fill( WMuon_Phi[sel_mu], EventWeight);
     h_NJet[1]->Fill(NJet, EventWeight);
     h_NBJet[1]->Fill(NBJet, EventWeight); 
     h_MET[1]->Fill(MET, EventWeight);
      
//     if (N_IsoMuon > 1 ) h_Mmumu[1]->Fill((*muon1 + *muon2).M(), EventWeight);

/*     if( debug ) cout << "filling at step2..." << endl;
     if( N_IsoMuon > 1 && ){ //step 2
       h_MuonIso[2]->Fill(Muon_Iso[sel_mu], EventWeight); 
       h_NMuon[2]->Fill(N_IsoMuon, EventWeight);
       h_NVertex[2]->Fill(NVertex, EventWeight);
       h_WMuon_MT[2]->Fill( WMuon_MT[sel_mu], EventWeight);
       h_WMuon_Phi[2]->Fill( WMuon_Phi[sel_mu], EventWeight);
       h_NJet[2]->Fill(NJet, EventWeight);
       h_NBJet[2]->Fill(NBJet, EventWeight);
       h_MET[2]->Fill(MET, EventWeight);
*//*
       if( debug ) cout << "filling at step3..." << endl;

       if( NBJet > 1 ){ //step 3
         h_MuonIso[3]->Fill(Muon_Iso[sel_mu], EventWeight); 
         h_NMuon[3]->Fill(N_IsoMuon, EventWeight);
         h_NVertex[3]->Fill(NVertex, EventWeight);
         h_WMuon_MT[3]->Fill( WMuon_MT[sel_mu], EventWeight);
         h_WMuon_Phi[3]->Fill( WMuon_Phi[sel_mu], EventWeight);
         h_NJet[3]->Fill(NJet, EventWeight);
         h_NBJet[3]->Fill(NBJet, EventWeight);
         h_MET[3]->Fill(MET, EventWeight);
       } 
*/
//     }

   }

   if( debug ) cout << "ending event..." << endl; 
   return kTRUE;
}

void MyAnalysis::SlaveTerminate() {
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
   
}

void MyAnalysis::Terminate() {
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   
}
