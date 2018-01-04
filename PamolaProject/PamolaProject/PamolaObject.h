#pragma once

#include "Circuit.h"
#include "PamolaTypes.h"
#include <set>
#include <vector>
#include <memory>
#include <cassert>
#include <cpplinq.hpp>


namespace Pamola
{
	class Engine;

	class Object
	{
		friend class Engine;

		// TODO: Check enable_shared_from_thiss usage

	private:
		
		uint32_t id;

		std::weak_ptr<Engine> engine;

	protected:

		Object();

	public:

		virtual ~Object();

		std::set<uint32_t> getConnectedComponents();
		std::set<uint32_t> getConnectedComponents(std::set<uint32_t>);

		const std::shared_ptr<Engine> getEngine();
		
		uint32_t getId();

		virtual const std::vector<std::shared_ptr<Object>> getAdjacentComponents() = 0;

		virtual Type getPamolaType() = 0;

		virtual int getDegreesOfFreedom() = 0;

	};
}
