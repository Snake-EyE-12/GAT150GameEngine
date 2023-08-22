#pragma once
#include <list>
#include "Actor.h"
#include <vector>
#include <string>
#include "Game/Block.h"


namespace cg
{
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;
		bool Initialize();
		void Update(float dt);
		void Draw(Renderer& renderer);
		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll(bool force = false);

		bool Load(const std::string& filename);
		void Read(const json_t& value);

		std::vector<Block*> GetBlocks();

		template<typename T>
		T* GetActor();

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);
		
		
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
	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors) {
			if (actor->name == name) {
				T* result = dynamic_cast<T*>(actor.get());
				if (result) return result;
			}
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