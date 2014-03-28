========================================================================
    Group centrality experiments
========================================================================

More one Maximum Domination Problem:
Eiji Miyano, Hirotaka Ono, Maximum Domination Problem, CATS 2011: 55-62

/////////////////////////////////////////////////////////////////////////////
Parameters:
   -o:Output graph file name (default:'graph.txt')
   -n:Number of nodes (size of the generated graph) (default:10000)
   -f:Forward burning probability (default:0.35)
   -b:Backward burning probability (default:0.32)
   -s:Start graph with S isolated nodes (default:1)
   -a:Probability of a new node choosing 2 ambassadors (default:0)
   -op:Probability of a new node being an orphan (node with zero out-degree) (default:0)

/////////////////////////////////////////////////////////////////////////////
Data:
	sicris.txt - edge list of sicris projects collaboration
	cobiss.txt - edge list of collaboration on publications
	cobiss1.txt - small test sample from cobiss
/////////////////////////////////////////////////////////////////////////////
Usage:

Determine group that has maximum group degree centrality using approximate greedy algorithm

gcentrality.exe -g:../gcentrality/cobiss.txt -o:gc.test.tab -k:10