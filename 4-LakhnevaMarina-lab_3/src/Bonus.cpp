#include "Bonus.h"

namespace NGems {

	int TBoom::Activate(std::vector<std::vector<TGem>>& field) {
		std::vector<int> choice(Global::kGemsCountX * Global::kGemsCountY);
		for (int i = 0; i < choice.size(); ++i) {
			choice[i] = i;
		}

		std::swap(choice[mId], choice[0]);
		auto n = static_cast<int>(choice.size());
		for (int k = 1; k < 5; ++k) {
			std::swap(choice[k], choice[k + (rand() % (n - k))]);
		}

		for (int k = 0; k < 5; ++k) {
			auto id = choice[k];
			auto i = id / Global::kGemsCountX;
			auto j = id % Global::kGemsCountX;
			field[i][j].SetColor(GemColor::EMPTY);
		}
		return 5;
	}

	int TPaint::Activate(std::vector<std::vector<TGem>>& field) {
		auto mI = mId / Global::kGemsCountX;
		auto mJ = mId % Global::kGemsCountX;

		for (int k = 0; k < 2; ++k) {
			auto i = rand() % Global::kGemsCountY;
			auto j = rand() % Global::kGemsCountX;

			if (std::abs(i - mI) < 2) {
				i = (i + 1) % Global::kGemsCountY;
			}

			if (std::abs(j - mJ) < 2) {
				j = (j + 1) % Global::kGemsCountX;
			}
			field[i][j].SetColor(field[mI][mJ].GetColor());
		}
		return 0;
	}
}
