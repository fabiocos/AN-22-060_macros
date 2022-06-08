#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TH1.h"
#include "TH1F.h"
 
TCanvas* example_plot( int iPeriod, int iPos );
 
void endcap_purity()
{
  /*gROOT->LoadMacro("tdrstyle.C");*/
  setTDRStyle();

  /*gROOT->LoadMacro("CMS_lumi.C");*/

  writeExtraText = true;       // if extra text
  extraText  = "Phase-2 Simulation Preliminary";  // default extra text is "Preliminary"
  lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
  lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
  lumi_sqrtS = "14 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

  int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)

  // second parameter in example_plot is iPos, which drives the position of the CMS logo in the plot
  // iPos=11 : top-left, left-aligned
  // iPos=33 : top-right, right-aligned
  // iPos=22 : center, centered
  // mode generally : 
  //   iPos = 10*(alignement 1/2/3) + position (1/2/3 = left/center/right)

  example_plot ( iPeriod, 0 );

  //  example_plot( iPeriod, 0 );   // out of frame (in exceptional cases)
  //  example_plot( iPeriod, 11 );  // left-aligned
  //  example_plot( iPeriod, 33 );  // right-aligned

  //  writeExtraText = false;       // remove Preliminary
  
  //  example_plot( iPeriod, 0 );   // out of frame (in exceptional cases)

  //  example_plot( iPeriod, 11 );  // default: left-aligned
  //  example_plot( iPeriod, 22 );  // centered
  //  example_plot( iPeriod, 33 );  // right-aligned  
}

TCanvas* example_plot( int iPeriod, int iPos )
{ 
  //  if( iPos==0 ) relPosX = 0.12;

  int W = 800;
  int H = 600;

  // 
  // Simple example of macro: plot with CMS name and lumi text
  //  (this script does not pretend to work in all configurations)
  // iPeriod = 1*(0/1 7 TeV) + 2*(0/1 8 TeV)  + 4*(0/1 13 TeV) 
  // For instance: 
  //               iPeriod = 3 means: 7 TeV + 8 TeV
  //               iPeriod = 7 means: 7 TeV + 8 TeV + 13 TeV 
  // Initiated by: Gautier Hamel de Monchenault (Saclay)
  // Updated by:   Dinko Ferencek (Rutgers)
  //
  int H_ref = 600; 
  int W_ref = 800; 

  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;

  TString canvName = "endcap_purity";

  TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(0);
  canv->SetTicky(0);

  int histLineColor = kOrange+7;
  int histFillColor = kOrange-2;
  float markerSize  = 1.0;

  {
    // Observed data
    TFile file_("DQM_V0001_R000000001__Global__CMSSW_X_Y_Z__RECO.root","READ");

    TH1F *data1 = static_cast<TH1F*>(file_.Get("DQMData/Run 1/MTD/Run summary/Vertices/EndcapPiPurity")->Clone());
    TH1F *data2 = static_cast<TH1F*>(file_.Get("DQMData/Run 1/MTD/Run summary/Vertices/EndcapKPurity")->Clone());
    TH1F *data3 = static_cast<TH1F*>(file_.Get("DQMData/Run 1/MTD/Run summary/Vertices/EndcapPPurity")->Clone());

    data1->SetDirectory(0);
    data1->SetMarkerStyle(20);
    data1->SetMarkerSize(markerSize);

    data1->GetXaxis()->SetTitleOffset(0);
    data1->GetXaxis()->SetNdivisions(6,5,0);
    data1->GetXaxis()->SetTitle("p_{t} (GeV)");  
    data1->GetYaxis()->SetNdivisions(6,5,0);
    data1->GetYaxis()->SetTitle("PID purity");  

    float t = canv->GetTopMargin();

    data1->GetXaxis()->SetTitleSize(cmsTextSize*t);
    data1->GetYaxis()->SetTitleSize(cmsTextSize*t);

    /*data->SetMaximum( 260 );*/
    /*if( iPos==1 ) data->SetMaximum( 300 );*/

    data1->SetMarkerColor(1);
    data1->Draw("E1");

    data2->SetDirectory(0);
    data2->SetMarkerStyle(20);
    data2->SetMarkerSize(markerSize);
    data2->SetMarkerColor(4);
    data2->Draw("E1SAME");

    data3->SetDirectory(0);
    data3->SetMarkerStyle(20);
    data3->SetMarkerSize(markerSize);
    data3->SetMarkerColor(2);
    data3->Draw("E1SAME");

    TLegend *leg1 = new TLegend(.15,.15,.35,.35);
    leg1->SetTextFont(82);
    leg1->SetTextSize(0.03);
    leg1->AddEntry(data1,"#pi","P");
    leg1->AddEntry(data2,"K","P");
    leg1->AddEntry(data3,"p","P");
    leg1->Draw();

    TLatex latex;
    latex.SetTextFont(42);
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);
    latex.SetTextSize(0.04);
    latex.SetTextAlign(12);
    latex.DrawLatexNDC(.17,.38,"1.6 < |#eta| < 3");

    file_.Close();
  }

  /*{*/
    /*TLatex latex;*/
				
    /*int n_ = 2;*/

    /*float x1_l = 0.92;*/
    /*float y1_l = 0.60;*/

    /*float dx_l = 0.30;*/
    /*float dy_l = 0.18;*/
    /*float x0_l = x1_l-dx_l;*/
    /*float y0_l = y1_l-dy_l;*/

    /*TPad* legend = new TPad("legend_0","legend_0",x0_l,y0_l,x1_l, y1_l );*/
    /*//    legend->SetFillColor( kGray );*/
    /*legend->Draw();*/
    /*legend->cd();*/
		
    /*float ar_l = dy_l/dx_l;*/
		
    /*float x_l[1];*/
    /*float ex_l[1];*/
    /*float y_l[1];*/
    /*float ey_l[1];*/
		
    /*//    float gap_ = 0.09/ar_l;*/
    /*float gap_ = 1./(n_+1);*/
		
    /*float bwx_ = 0.12;*/
    /*float bwy_ = gap_/1.5;*/
		
    /*x_l[0] = 1.2*bwx_;*/
    /*//    y_l[0] = 1-(1-0.10)/ar_l;*/
    /*y_l[0] = 1-gap_;*/
    /*ex_l[0] = 0;*/
    /*ey_l[0] = 0.04/ar_l;*/
		
    /*TGraph* gr_l = new TGraphErrors(1, x_l, y_l, ex_l, ey_l );*/
		
    /*gStyle->SetEndErrorSize(0);*/
    /*gr_l->SetMarkerSize(0.9);*/
    /*gr_l->Draw("0P");*/
		
    /*latex.SetTextFont(42);*/
    /*latex.SetTextAngle(0);*/
    /*latex.SetTextColor(kBlack);    */
    /*latex.SetTextSize(0.25);    */
    /*latex.SetTextAlign(12); */
		
    /*TLine line_;*/
    /*TBox  box_;*/
    /*float xx_ = x_l[0];*/
    /*float yy_ = y_l[0];*/
    /*latex.DrawLatex(xx_+1.*bwx_,yy_,"Data");*/
		
    /*yy_ -= gap_;*/
    /*box_.SetLineStyle( kSolid );*/
    /*box_.SetLineWidth( 1 );*/
    /*//		box_.SetLineColor( kBlack );*/
    /*box_.SetLineColor( histLineColor );*/
    /*box_.SetFillColor( histFillColor );*/
    /*box_.DrawBox( xx_-bwx_/2, yy_-bwy_/2, xx_+bwx_/2, yy_+bwy_/2 );*/
    /*box_.SetFillStyle(0);*/
    /*box_.DrawBox( xx_-bwx_/2, yy_-bwy_/2, xx_+bwx_/2, yy_+bwy_/2 );*/
    /*latex.DrawLatex(xx_+1.*bwx_,yy_,"Z #rightarrow e^{+}e^{-} (MC)");*/

    /*canv->cd();*/
  /*}*/

  // writing the lumi information and the CMS "logo"
  CMS_lumi( canv, iPeriod, iPos );

  canv->Update();
  canv->RedrawAxis();
  canv->GetFrame()->Draw();

  canv->Print(canvName+".pdf",".pdf");
  canv->Print(canvName+".png",".png");

  return canv;
}
