#include "Selector.h"

namespace NGems {

	void TSelector::Select(TGem* gem) {
		if (buff.first == nullptr) {
			gem->Select();
			buff.first = gem;
			return;
		}
		if (buff.first && buff.first->IsNeighbor(*gem)) {
			buff.first->Swap(gem);
			buff.second = gem;
			return;
		}
		buff.first->Unselect();
		buff.first = nullptr;
	}

	void TSelector::Cancel() {
		if (!buff.second || !buff.first) {
			return;
		}
		buff.first->Swap(buff.second);
		buff.first = nullptr;
		buff.second = nullptr;
	}

	void TSelector::Done() {
		if (!buff.second || !buff.first) {
			return;
		}
		buff.first = nullptr;
		buff.second = nullptr;
	}
}