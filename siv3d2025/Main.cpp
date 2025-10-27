#include <Siv3D.hpp>
#include "Game.h"

void Main()
{
	GameCore::Game game;

	Scene::SetResizeMode(ResizeMode::Keep);
	Window::SetStyle(WindowStyle::Sizable);
	Window::Resize(640, 480);
	Window::SetTitle(U"深海ギョ戦記");

	game.RunAsync();
}
