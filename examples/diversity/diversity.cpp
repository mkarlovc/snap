#include "stdafx.h"

int main(int argc, char* argv[]) {

  // code needed for inputing parameters
  Env = TEnv(argc, argv, TNotify::StdNotify);
  Env.PrepArgs(TStr::Fmt("Network diversity. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

  TExeTm ExeTm; // for measuring execution time
  Try
  const TStr InFNmGraph = Env.GetIfArgPrefixStr("-i:", "artificial_intelligence_pub.txt", "Input graph (undirected graph)");
  const TStr InFNmCat = Env.GetIfArgPrefixStr("-c:", "artificial_intelligence_cat_pub.txt", "Categories");
  const TStr InFNmMat = Env.GetIfArgPrefixStr("-m:", "sciences.txt", "Matrix");
  const TStr OutFNm = Env.GetIfArgPrefixStr("-o:", "diversity.txt", "Output file");
  const int DivAlg = Env.GetIfArgPrefixInt("-a:", 1, "Measure: 1:Stirling");
  const int Alpha = Env.GetIfArgPrefixInt("-alp:", 1, "alpha");
  const int Beta = Env.GetIfArgPrefixInt("-bet:", 1, "beta");
  const int Gamma = Env.GetIfArgPrefixInt("-gam:", 1, "gama");
  // defining graph
  PUNGraph Graph = TSnap::LoadEdgeList<PUNGraph>(InFNmGraph, false);

  double D = 0.0;
  TStr DivAlgStr;

  // based on input parametr -a (variable DivAlg), diversity measure is choosen
  if (DivAlg == 1) {
    DivAlgStr = "Stirling";
	D = TSnap::StirlingIndex(Graph,InFNmCat,InFNmMat, Alpha, Beta, Gamma);}
  else { Fail; }

  printf("\nDiversity: %f\nrun time: %s (%s)\n", D,ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr()); //print execution time
  
  Catch

  return 0;
}