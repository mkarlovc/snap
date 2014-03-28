#include "stdafx.h"

int main(int argc, char* argv[]) {
  Env = TEnv(argc, argv, TNotify::StdNotify);
  Env.PrepArgs(TStr::Fmt("Node Centrality. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
  TExeTm ExeTm, ExeTm1, ExeTm2;
  double tm1, tm2;
  Try
  const TStr InFNm = Env.GetIfArgPrefixStr("-g:", "../gcentrality/cobiss.txt", "Input un/directed graph");
  const TStr OutFNm = Env.GetIfArgPrefixStr("-o:", "gc.test.tab", "Output file");
  const TStr InGFNm = Env.GetIfArgPrefixStr("-c:", "../gcentrality/gc2.txt", "Input group nodes");
  const TStr K = Env.GetIfArgPrefixStr("-k:", "10", "k size");
  
  int k = K.GetInt64(); // size of the group
  TIntH GroupNodes; // input group nodes for calculating group centrality

  // loading graph
  printf("Loading %s...\n", InFNm.CStr());
  PNGraph Graph = TSnap::LoadEdgeList<PNGraph>(InFNm);

  // loading input group nodes
  if (InGFNm != ""){
    printf("Loading %s...\n", InGFNm.CStr());
    TIntH GroupNodes = TSnap::LoadNodeList(InGFNm);
  }

  // printing the size of node and edge lists
  printf("nodes:%d  edges:%d\n", Graph->GetNodes(), Graph->GetEdges());
  PUNGraph UGraph = TSnap::ConvertGraph<PUNGraph>(Graph); // undirected version of the graph

  // performing the search for group with greatest group degree centrality
  tm1 = ExeTm1.GetSecs();
  printf("Max k better domination...\n");  TIntH gk1 = TSnap::MaxCPGreedyBetter3(UGraph, k);
  tm2 = ExeTm2.GetSecs();

  // printing nodes belonging to group in the output file
  FILE *F = fopen(OutFNm.CStr(), "wt");
  for (THashKeyDatI<TInt,TInt> NI = gk1.BegI(); NI < gk1.EndI(); NI++){
	  fprintf(F, "%i\n", NI.GetDat());
  }

  // calculating group degree centrality for the definded group and printing results in the file
  double gdc = TSnap::GetGroupDegreeCentr(UGraph, gk1);
  fprintf(F, "#group degre centrality %f\n#group size %i\nnodes %i\n #edges %i\n#excecution time (seconds) %f\n", gdc,gk1.Len(), Graph->GetNodes(), Graph->GetEdges(), (tm2-tm1));
  printf("\ngroup degre centrality: %f\ngroup size: %i\nnodes: %i\nedges: %i\nexcecution time (seconds): %f\n", gdc,gk1.Len(), Graph->GetNodes(), Graph->GetEdges(), (tm2-tm1));
  system("pause");
  Catch
  return 0;
}
