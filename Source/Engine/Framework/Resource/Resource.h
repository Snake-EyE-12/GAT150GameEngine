#pragma once
#include <string>
#include <memory>

namespace cg
{
	class Resource
	{
	public:
		virtual ~Resource() = default;

		virtual bool Create(std::string filename, ...) = 0;
	private:
	};

	template<typename T>
	using res_t = std::shared_ptr<T>;
}