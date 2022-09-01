#include "Game.h"
#include <iostream>

void NGems::TGame::Start() {
	spawnGems();
	run();
}

void NGems::TGame::spawnGems() {
	field.reserve(Global::kGemsCountY);
	for (int i = 0; i < Global::kGemsCountY; ++i) {
		field.emplace_back();
		field[i].reserve(Global::kGemsCountX);
		for (int j = 0; j < Global::kGemsCountX; ++j) {
			auto pos = sf::Vector2f{
				Global::kGemsGap + (Global::kGemsGap + Global::kGemSize) * j,
				Global::kGemsGap + (Global::kGemsGap + Global::kGemSize) * i
			};

			auto color = rand() % 4;
			field[i].emplace_back(mWindow, pos, (GemColor)(color), i, j);
			if (j > 0 && field[i][j].Match(field[i][j - 1])) {
				field[i][j].SetColor((GemColor)((color + 1) % 5));
			}
			if (i > 0 && field[i][j].Match(field[i-1][j])) {
				field[i][j].SetColor((GemColor)((color + 1) % 5));
			}
		}
	}
	redraw();
}

void NGems::TGame::run() {
	
	while (mWindow.isOpen()) {
		sf::Event event;
		while (mWindow.pollEvent(event)) {
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
				mWindow.close();
				break;
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				auto mousePos = sf::Vector2i{ event.mouseButton.x, event.mouseButton.y };
				for (auto& line : field) {
					for (auto& gem : line) {
						if (gem.Contains(mousePos)) {
							swapper.Select(&gem);
						}
					}
				}
				while (updateField()) ;
				redraw();
			}
		}
	}
	std::cout << score;
}

bool NGems::TGame::updateField() {
	// Собираем кристаллы одного цвета в группы (горизонтально)
	NTools::DSU dsu(Global::kGemsCountX * Global::kGemsCountY);
	for (int i = 0; i < Global::kGemsCountY; ++i) {
		for (int j = 0; j < Global::kGemsCountX; ++j) {
			if (j > 0 && field[i][j].Match(field[i][j - 1])) {
				dsu.Unite(i * Global::kGemsCountX + j, i * Global::kGemsCountX + j - 1);
			}
		}
	}

	// Удаляем группы, в которых 3 или больше кристаллов (горизонтально)
	std::vector<int> toRemoveIDs;
	for (int i = 0; i < Global::kGemsCountY; ++i) {
		for (int j = 0; j < Global::kGemsCountX; ++j) {
			auto id = i * Global::kGemsCountX + j;
			if (dsu.Size(id) >= 3 && dsu.VisitOnce(id)) {
				auto group = dsu.GetSet(id);
				for (auto id : group) {
					toRemoveIDs.push_back(id);
				}
			}
		}
	}

	// Аналогично для вертикальных групп
	NTools::DSU dsu2(Global::kGemsCountX * Global::kGemsCountY);
	for (int i = 0; i < Global::kGemsCountY; ++i) {
		for (int j = 0; j < Global::kGemsCountX; ++j) {
			if (i > 0 && field[i][j].Match(field[i - 1][j])) {
				dsu2.Unite(i * Global::kGemsCountX + j, (i - 1) * Global::kGemsCountX + j);
			}
		}
	}

	for (int i = 0; i < Global::kGemsCountY; ++i) {
		for (int j = 0; j < Global::kGemsCountX; ++j) {
			auto id = i * Global::kGemsCountX + j;
			if (dsu2.Size(id) >= 3 && dsu.VisitOnce(id) && dsu2.VisitOnce(id)) {
				auto group = dsu2.GetSet(id);
				for (auto id : group) {
					toRemoveIDs.push_back(id);
				}
			}
		}
	}

	// Если ничего не удалено, отменяем своп
	if (toRemoveIDs.size() == 0) {
		swapper.Cancel();
		return false;
	}
	else {
		swapper.Done();
	}
	std::vector<bool> needFall(Global::kGemsCountX, false);
	std::vector<std::shared_ptr<TBonus>> bonuses;
	

	// Тут само удаление
	for (auto id : toRemoveIDs) {
		int i = id / Global::kGemsCountX;
		int j = id % Global::kGemsCountX;
		field[i][j].SetColor(GemColor::EMPTY);
		needFall[j] = true;

		// Выпадение бонусов
		if (rand() % 11 == 0) {
			// Выбираем позицию для бонуса

			// Зазор по X
			int gapXStart = std::max(0, j - 3);
			int gapXEnd = std::min(Global::kGemsCountX - 1, j + 3);

			// Зазор по Y
			int gapYStart = std::max(0, i - 3);
			int gapYEnd = std::min(Global::kGemsCountY - 1, i + 3);

			int bonusX = gapXStart + rand() % (gapXEnd - gapXStart);
			int bonusY = gapYStart + rand() % (gapYEnd - gapYStart);

			int bonusID = bonusY * Global::kGemsCountX + bonusX;

			if (rand() % 2) {
				bonuses.emplace_back(std::make_shared<TBoom>(bonusID));
			}
			else {
				bonuses.emplace_back(std::make_shared<TPaint>(bonusID));
			}
		}
	}

	// Активация бонусов
	for (auto bonus : bonuses) {
		score += bonus->Activate(field);
	}

	// Показываем, что удалили
	redraw();
	sf::sleep(sf::seconds(0.2f));

	// Иначе записываем очкм и проигрываем анимацию падения
	score += toRemoveIDs.size();
	bool keepFalling = true;
	while (keepFalling) {
		for (int i = Global::kGemsCountY - 1; i >= 0; --i) {
			for (int j = 0; j < Global::kGemsCountX; ++j) {
				if (i > 0 && field[i][j].IsEmpty() && !field[i][j].Match(field[i - 1][j])) {
					field[i][j].Swap(&field[i - 1][j]);

					field[i][j].Draw();
					field[i - 1][j].Draw();

					if (i > 1) {
						needFall[j] = true;
					}
				}
				else {
					needFall[j] = false;
				}
			}
		}
		sf::sleep(sf::seconds(0.08f));

		keepFalling = false;
		for (auto b : needFall) {
			keepFalling |= b;
		}
	}
	mWindow.display();

	// Заполняем пропуски
	for (int i = 0; i < Global::kGemsCountY; ++i) {
		for (int j = 0; j < Global::kGemsCountX; ++j) {
			if (field[i][j].IsEmpty()) {

				auto color = rand() % 5;
				field[i][j].SetColor((GemColor)color);

				if (j > 0 && field[i][j].Match(field[i][j - 1])) {
					field[i][j].SetColor((GemColor)((color + 2) % 5));
				}
				if (i > 0 && field[i][j].Match(field[i - 1][j])) {
					field[i][j].SetColor((GemColor)((color + 1) % 5));
				}
			}
		}
	}
	// Повторяем, так как могли получиться новые комбинации
	return true;
}

void NGems::TGame::redraw() {
	mWindow.clear(sf::Color::Black);
	for (auto& line : field) {
		for (auto& gem : line) {
			gem.Draw();
		}
	}
	mWindow.display();
}

void GemsGame::Run() {
	NGems::TGame game;
	game.Start();

	// Ждём нажатия для выхода
	getchar();
}
