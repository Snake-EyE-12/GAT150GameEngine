#include "AstroidFighter.h"
#include "GameIncludes.h"
#include <cassert>
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "Core/Core.h"
#include "Core/Json.h"
#include "Physics/PhysicsSystem.h"


using namespace std;



int main(int argc, char* argv[])
{
	
	//cg::Text bob;
	
	//Initialization
 	cg::MemoryTracker::Initialize();
	cg::seedRandom((unsigned int)time(nullptr));
	cg::setFilePath("assets");
	cg::g_renderer.Initialize();
	cg::g_renderer.CreateWindow("Window", 800, 600);
	cg::g_inputSystem.Initialize();
	cg::g_audioSystem.Initialize();
	cg::PhysicsSystem::Instance().Initialize();

	unique_ptr<AstroidFighter> game = make_unique<AstroidFighter>();
	game->Initialize();

	bool quit = false;
	while (!quit) {
		//Update
		cg::g_time.Tick();
		cg::g_audioSystem.Update();
		cg::g_inputSystem.Update();
		cg::g_particleSystem.Update(cg::g_time.GetDeltaTime());
		game->Update(cg::g_time.GetDeltaTime());

		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) quit = true;


		//Draw
		cg::g_renderer.SetColor(0, 0, 0, 0);
		cg::g_renderer.BeginFrame();

		cg::g_particleSystem.Draw(cg::g_renderer);
		game->Draw(cg::g_renderer);

		cg::g_renderer.EndFrame();
	}
	
	return 0;
}
