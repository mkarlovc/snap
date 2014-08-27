	/////////////////////////////////////////////////
	// Community detection algorithms
	namespace TSnap {


	namespace TSnapDetail {

	void CalculatePij(PUNGraph& Graph, TIntFltH& P){
		int N = Graph->GetNodes();
		for(int i=0;i<P.Len();i++) { P[i] = P[i]/N;}
	}

	TIntFltH CalculateEij(PUNGraph& Graph, TIntIntH Cats, TIntFltH P){
		TIntFltH E;
		int e = Graph->GetEdges();
		int e_conn = 0;
		int N = P.Len();
		for(int i=0;i<P.Len();i++){
			for(int j=i;j<P.Len();j++){
				if (i!=j){
					for (TUNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++){
						int SRC = Cats.GetDat(EI.GetSrcNId());
						int DST = Cats.GetDat(EI.GetDstNId());
						int I = P.GetKey(i);
						int J = P.GetKey(j);
						if (Cats.GetDat(EI.GetSrcNId())==P.GetKey(i) && Cats.GetDat(EI.GetDstNId())==P.GetKey(j) || Cats.GetDat(EI.GetSrcNId())==P.GetKey(j) && Cats.GetDat(EI.GetDstNId())==P.GetKey(i))
							e_conn++;
					}

					E.AddKey((N*P.GetKey(i))+P.GetKey(j)); E.AddDat((N*P.GetKey(i))+P.GetKey(j),(float)e_conn/(float)e);
					E.AddKey((N*P.GetKey(j))+P.GetKey(i)); E.AddDat((N*P.GetKey(j))+P.GetKey(i),(float)e_conn/(float)e);
					e_conn = 0;
				} 
			}
		}
		return E;
	}

	float Index(PUNGraph& Graph, TIntFltH& E, TIntIntH& Cats, TIntFltH& P,TIntFltH& D, int Alpha, int Beta, int Gamma){
		int N = P.Len();
		float I = 0;
		for(int i=0;i<P.Len();i++){
			for(int j=i;j<P.Len();j++){
				if (i!=j){
					double a = D.GetDat((N*P.GetKey(i))+P.GetKey(j));
					double b = P.GetDat(P.GetKey(i));
					double c = P.GetDat(P.GetKey(j));
					double d = E.GetDat((N*P.GetKey(i))+P.GetKey(j));
					printf("\n%f,%f,%f,%f\n",a,b,c,d); //print execution time
					I += pow(1-D.GetDat((N*P.GetKey(i))+P.GetKey(j)),Alpha) * /*pow(0.5,Alpha)* */ pow(P.GetDat(P.GetKey(i))*P.GetDat(P.GetKey(j)),Beta)*pow(E.GetDat((N*P.GetKey(i))+P.GetKey(j)),Gamma);
				}
			}
		}
		return I;
	}

	TIntFltH LoadMat(PUNGraph& Graph,TStr InFNmMat, TIntFltH& D){
	  TSsParser Ss(InFNmMat, ssfWhiteSep, true, true, true);
	  TIntIntH CatNames;
  
	  int NId, Cat,j,N=0, CatName;
	  double val=0.0;
	  while (Ss.Next()) {
		j = Ss.GetLineNo()-2;
		if (j==-1){
			N = Ss.Len();
			for (int i=0; i<N; i++){
				if (Ss.GetInt(i,CatName)){
					CatNames.AddKey(i);
					CatNames.AddDat(i,CatName);
				}
			}
		}
		else{
			for (int i=0; i<N; i++){
				if (Ss.GetFlt(i,val)){
					int i_ =CatNames.GetDat(i);
					int j_=CatNames.GetDat(j);
					int ij_ = (CatNames.GetDat(j)*N)+CatNames.GetDat(i);
					D.AddKey((CatNames.GetDat(j)*N)+CatNames.GetDat(i));
					D.AddDat((CatNames.GetDat(j)*N)+CatNames.GetDat(i),(float)val);
				}
			}
		}
	  }

	  return D;
	}

	TIntIntH LoadCatList(PUNGraph& Graph,TStr InFNmMat, TIntFltH& P){

	  TSsParser Ss(InFNmMat, ssfWhiteSep, true, true, true);
	  TIntIntH Cats;

	  int NId, Cat;
	  while (Ss.Next()) {
		if (! Ss.GetInt(0, NId) || ! Ss.GetInt(1, Cat)) { continue; }
		if (Graph->IsNode(NId)) { Cats.AddDat(NId,Cat); }
		if (P.IsKey(Cat)) { int old = P.GetDat(Cat); P.DelKey(Cat); P.AddKey(Cat); P.AddDat(Cat, old+1); }
		else { P.AddKey(Cat); P.AddDat(Cat,1); }
	  }

	  return Cats;
	}

	} // namespace TSnapDetail



	double StirlingIndex(PUNGraph& Graph, TStr InFNmCat, TStr InFNmMat, int Alpha, int Beta, int Gamma){
		const int N = Graph->GetNodes();
		TIntFltH P;
		TIntIntH Cats = TSnapDetail::LoadCatList(Graph,InFNmCat,P);
		TSnapDetail::CalculatePij(Graph,P);
		TIntFltH D;
		TSnapDetail::LoadMat(Graph,InFNmMat,D);
		TIntFltH E = TSnapDetail::CalculateEij(Graph,Cats,P);
		float I = TSnapDetail::Index(Graph,E,Cats,P,D, Alpha, Beta, Gamma);
		return double(I);
		}

	}; //namespace TSnap
