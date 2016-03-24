/*
 * JS89.h
 *
 *  Created on: Nov 18, 2014
 *      Author: rechner
 */

#ifndef JS89_CHAIN_H_
#define JS89_CHAIN_H_

#include <queue>

#include "../../MarkovChain.h"
#include "BipartiteMatching.h"
#include "SparseBipartiteGraph.h"

namespace marathon {
namespace chain {
namespace matching {

class Broder86: public MarkovChain {

	friend class JS89Path;

protected:

	SparseBipartiteGraph *g = nullptr;

	/**
	 * Instances have the form "110101011".
	 * Such a 0-1-String is interpreted as a biadjacency matrix of a bipartite graph, flattened to a single line.
	 * Thus, the input string above corresponds to the biadjacency  matrix
	 *
	 *  1 1 0
	 *  1 0 1
	 *  0 1 1
	 *
	 *  which is the graph
	 *
	 *  u1  u2  u3
	 *  |\ / \ /|
	 *  | X   X |
	 *  |/ \ / \|
	 *  v1  v2  v3
	 * .
	 */
	void parseInstance(const std::string& inst);

public:

	Broder86(const std::string& instance);
	~Broder86();

	virtual State* computeArbitraryState();
	virtual void computeNeighbours(const State* s,
			std::vector<std::pair<State*, rational>>& neighbors) const;

};

}

}

}
#endif /* JS89_H_ */
