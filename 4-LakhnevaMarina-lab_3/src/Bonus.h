#pragma once

#include "Gem.h"

namespace NGems {

	class TBonus {
	public:
		TBonus(int spawnPosID) : mId(spawnPosID) {}
		virtual int Activate(std::vector<std::vector<TGem>>& field) = 0;
	protected:
		int mId;
	};

	class TBoom : public TBonus {
	public:
		TBoom(int spawnPosID) : TBonus(spawnPosID) {}
		virtual int Activate(std::vector<std::vector<TGem>>& field) override;
	};

	class TPaint : public TBonus {
	public:
		TPaint(int spawnPosID) : TBonus(spawnPosID) {}
		virtual int Activate(std::vector<std::vector<TGem>>& field) override;
	};
}