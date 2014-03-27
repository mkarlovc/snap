#include "stdafx.h"

int main(int argc, char* argv[]) {
  Env = TEnv(argc, argv, TNotify::StdNotify);
  Env.PrepArgs(TStr::Fmt("Node Centrality. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
  TExeTm ExeTm, ExeTm1, ExeTm2;
  double tm0, tm1, tm2;
  Try
  const TStr InFNm = Env.GetIfArgPrefixStr("-g:", "../gcentrality/cobiss.txt", "Input un/directed graph");
  const TStr OutFNm = Env.GetIfArgPrefixStr("-o:", "gc.testtab", "Output file");
  const TStr InGFNm = Env.GetIfArgPrefixStr("-c:", "../gcentrality/gc2.txt", "Input group nodes");
  const TStr K = Env.GetIfArgPrefixStr("-k:", "10000", "k size");
  
  int k = K.GetInt64();

  printf("Loading %s...", InFNm.CStr());
  PNGraph Graph = TSnap::LoadEdgeList<PNGraph>(InFNm);
  TIntH GroupNodes = TSnap::LoadNodeList(InGFNm);

  printf("nodes:%d  edges:%d\n", Graph->GetNodes(), Graph->GetEdges());
  PUNGraph UGraph = TSnap::ConvertGraph<PUNGraph>(Graph); // undirected version of the graph

  //printf(" Group centrality...");   double gdc = TSnap::GetGroupDegreeCentr(UGraph, GroupNodes);
  //printf(" Group closeness...");   double gcc = TSnap::GetGroupClosenessCentr(UGraph, GroupNodes);
  tm0 = ExeTm1.GetSecs();
  //printf(" Max k domination...");  TIntH gk = TSnap::MaxCPGreedy(UGraph, 3);
  tm1 = ExeTm1.GetSecs();
  printf(" Max k better domination...");  TIntH gk1 = TSnap::MaxCPGreedyBetter3(UGraph, k);
  tm2 = ExeTm2.GetSecs();

  //printf("%f %f", gdc, gcc);

  
  //printf("\nrun time: %s (%s)\n", ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr());
  printf("\nMaxCPGreedy: %f %f %f\n", tm0, tm1, tm2);

  FILE *F = fopen(OutFNm.CStr(), "wt");
  for (THashKeyDatI<TInt,TInt> NI = gk1.BegI(); NI < gk1.EndI(); NI++){
	  fprintf(F, "%i\n", NI.GetDat());
  }

  double gdc = TSnap::GetGroupDegreeCentr(UGraph, gk1);
  fprintf(F, "#group degre centrality %f %f\n", gdc, (tm2-tm1));

  Catch
  return 0;
}
