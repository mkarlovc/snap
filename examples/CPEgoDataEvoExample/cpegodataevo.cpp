#include "stdafx.h"
#include <strstream>
int main(int argc, char* argv[]) {
  Env = TEnv(argc, argv, TNotify::StdNotify);
  Env.PrepArgs(TStr::Fmt("Node Centrality. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
  TExeTm ExeTm, ExeTm1, ExeTm2;
  double tm1, tm2;
  Try
  //const TStr InFNmNet = Env.GetIfArgPrefixStr("-i:", "networks_aggregate_res-bib-part//", "Input graph (one edge per line, tab/space separated)");
  //const TStr InFNmNet = Env.GetIfArgPrefixStr("-i:", "Ego-Networks//1493603.edg", "Input graph (one edge per line, tab/space separated)");
  //const TStr InFNmNet = Env.GetIfArgPrefixStr("-i:", "Ego-Networks//1464675.edg", "Input graph (one edge per line, tab/space separated)");
  const TStr InFNmNet = Env.GetIfArgPrefixStr("-i:", "small//", "Input graph (one edge per line, tab/space separated)");
  const TStr InFNmEgo = Env.GetIfArgPrefixStr("-i:", "Ego-Networks-Small//", "Input graph (one edge per line, tab/space separated)");
  const TStr OutFNm = Env.GetIfArgPrefixStr("-o:", "out.txt", "Output file");

  // reding folder with networks and calculating core/periphery

  TIntFltVH cp;
  //TSnap::FastCorePeripheryBatch(InFNmNet, cp);

  // reding folder with ego networks and calculating basic properties

  // declaring variables for properties to be calculated one vector for each individual. an element of the vector is a value in the timepoint
  // nn - number of nodes, ne - number of edges, edi - effective diameter, adi - average diameter, dc - degree centrality,
  // bc - betweenness centrality, cc - clustering coefficient, de - density, wcc - number of wekly connected components
  TIntFltVH nn, ne, edi, adi, dc, bc, cc, de, wcc;
  // declaring container for ids
  TIntV ids;
  // declaring map for internal int id to string id
  TIntStrH idmap;
  // declaring container for years to assoiciate the years with an individual
  TIntIntVH years;
  // do determine the range of years
  int minyear=3000, maxyear = 0;
  //TSnap::EgonetPropEvolutionBatch(InFNmEgo, nn, ne, edi, adi, dc, bc, cc, de, wcc, ids, idmap, years, minyear, maxyear);

  // community evolution

  // declaring containers for communities for individuals and for distribution of communities in years 
  TIntIntVH com, dist, edges;
  TSnap::CmtyEvolutionFolderBatch(InFNmNet,dist,com,edges,0.5,0.75,1);
  //TSnap::CmtyEvolutionFolderBatch(InFNmNet,dist,com,edges,0.5,0.75,2);
  //TSnap::CmtyEvolutionFileBatch(InFNmNet,dist,com,edges,0.5,0.75,1);

  TStr Json;
  TSnap::CmtyEvolutionJson(Json, dist, com, edges);
  FILE *F = fopen("data.json", "wt");
  fprintf(F, Json.CStr());
  

  // plotting community evolution
  /*TGnuPlot GnuPlot("com","com",true);
  for (THashKeyDatI<TInt, TIntV> it = com.BegI();  !it.IsEnd(); it++)
	  GnuPlot.AddPlot(it.GetDat());
  GnuPlot.SavePng();*/

  // plotting
  // temporal variable for current key
  /*int currid;
  for (THashKeyDatI<TInt, TFltV> it = cp.BegI();  !it.IsEnd(); it++)
  {
	currid = it.GetKey();
	if (ne.IsKey(currid)){
		// get the max value of the property and create a temporal vector for the property used for plotting - to scale the core so it is visible on the plot
		int maxval =-1;
		for (int i=0; i<ne.GetDat(currid).Len(); i++)
			if (ne.GetDat(currid)[i]>maxval) maxval = ne.GetDat(currid)[i];
	
		TFltV vec;

		for (int i=0; i<it.GetDat().Len(); i++)
			vec.Add(it.GetDat()[i]*maxval);

		TStr name = idmap.GetDat(currid); name.InsStr(name.Len(),"_cp_ne");

		TGnuPlot GnuPlot(name,name,true); GnuPlot.AddPlot(vec); GnuPlot.AddPlot(ne.GetDat(currid)); GnuPlot.SavePng();
	}
  }*/

  Catch
  return 0;
}