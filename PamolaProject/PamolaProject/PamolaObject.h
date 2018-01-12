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
		
		uint32_t getId() const;

		bool operator<(const Pamola::Object&);

		bool operator>(const Pamola::Object&);

		bool operator<=(const Pamola::Object&);
		
		bool operator>=(const Pamola::Object&);
		
		bool operator==(const Pamola::Object&);

		bool operator!=(const Pamola::Object&);
		
		virtual const std::vector<std::shared_ptr<Object>> getAdjacentComponents() = 0;

		virtual Type getPamolaType() = 0;

		virtual int getDegreesOfFreedom() = 0;

	};
	
	bool operator<(const std::shared_ptr<Object>, const std::shared_ptr<Object>);
	bool operator>(const std::shared_ptr<Object>, const std::shared_ptr<Object>);
	bool operator<=(const std::shared_ptr<Object>, const std::shared_ptr<Object>);
	bool operator>=(const std::shared_ptr<Object>, const std::shared_ptr<Object>);
	bool operator==(const std::shared_ptr<Object>, const std::shared_ptr<Object>);
	bool operator!=(const std::shared_ptr<Object>, const std::shared_ptr<Object>);
}
