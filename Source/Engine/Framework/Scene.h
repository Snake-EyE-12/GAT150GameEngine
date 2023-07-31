#pragma once
#include <list>
#include "Actor.h"
#include <vector>
#include <string>
#include "Game/Block.h"


namespace cg
{
	class Renderer; //Avoids #include

	class Scene
	{
	public:
		Scene() = default;
		void Update(float dt);
		void Draw(Renderer& renderer);
		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll();

		std::vector<Block*> GetBlocks();

		template<typename T>
		T* GetActor();
		
		
		friend class Actor;

	private:
		std::list<std::unique_ptr<Actor>> m_actors;
	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors) {
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}
		return nullptr;
	}
	//This Should Be More Dynamic For All Types - Could Not Get That To Work
	inline std::vector<Block*> Scene::GetBlocks()
	{
		std::vector<Block*> allBlocks;
		for (auto& actor : m_actors) {
			Block* result = dynamic_cast<Block*>(actor.get());
			if (result && result->m_placed) allBlocks.push_back(result);
		}
		//std::cout << "Block Count = " << allBlocks.size() << std::endl;
		return allBlocks;
	}
}