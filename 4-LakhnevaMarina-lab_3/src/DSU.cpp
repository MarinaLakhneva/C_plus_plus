#include "DSU.h"

namespace NGems::NTools {

	int DSU::Size(int x) {
		return size[Find(x)];
	}

	int DSU::Find(int x) {
		auto p = root[x];
		if (p != root[p]) {
			root[x] = Find(p);
		}
		return root[x];
	}

	void DSU::Unite(int x, int y) {
		x = Find(x);
		y = Find(y);
		if (depth[y] < depth[x]) {
			root[y] = x;
			size[x] += size[y];
		}
		else {
			root[x] = y;
			size[y] += size[x];
		}
		if (depth[x] == depth[y]) {
			++depth[y];
		}
	}

	bool DSU::VisitOnce(int x) {
		x = Find(x);
		if (visited[x]) {
			return false;
		}
		visited[x] = true;
		return true;
	}

	std::vector<int> DSU::GetSet(int x) {
		x = Find(x);
		std::vector<int> answer;
		answer.reserve(size[x]);
		for (int i = 0; i < root.size(); ++i) {
			if (root[i] == x) {
				answer.push_back(i);
			}
		}
		return answer;
	}
}
