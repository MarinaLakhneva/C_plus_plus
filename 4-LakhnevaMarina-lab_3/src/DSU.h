#pragma once

#include <vector>

namespace NGems {
	namespace NTools {
		class DSU {
		public:
			DSU(int n) : root(n), size(n, 1), depth(n, 1), visited(n, false) {
				for (int i = 0; i < n; ++i) {
					root[i] = i;
				}
			}

			int Size(int x);
			int Find(int x);

			void Unite(int x, int y);
			bool VisitOnce(int x);

			std::vector<int> GetSet(int x);
		private:
			std::vector<int> root;
			std::vector<int> size;
			std::vector<int> depth;
			std::vector<bool> visited;
		};
	}
}

