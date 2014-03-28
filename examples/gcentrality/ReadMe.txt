========================================================================
    Group centrality experiments
========================================================================

More one Maximum Domination Problem:
Eiji Miyano, Hirotaka Ono, Maximum Domination Problem, CATS 2011: 55-62

/////////////////////////////////////////////////////////////////////////////
Parameters:
   -g:input graph (default:'../gcentrality/cobiss.txt')
   -o:Output graph file name (default:'gc.test.tab')
   -k:size of the group(default:10)
   -c:input group nodes list

/////////////////////////////////////////////////////////////////////////////
Data:
	sicris.txt - edge list of sicris projects collaboration
	cobiss.txt - edge list of collaboration on publications
	cobiss1.txt - small test sample from cobiss
/////////////////////////////////////////////////////////////////////////////
Usage:

Determine group that has maximum group degree centrality using approximative greedy algorithm

gcentrality.exe -g:../gcentrality/cobiss.txt -o:gc.test.tab -k:10