#pragma once

#include "Gem.h"

namespace NGems {

	class TSelector {
	public:
		void Select(TGem* gem);
		void Cancel();
		void Done();
	private:
		std::pair<TGem*, TGem*> buff{ nullptr, nullptr };		
	};
}