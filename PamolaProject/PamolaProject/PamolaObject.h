#pragma once

#include "PamolaTypes.h"
#include <set>
#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include <cpplinq.hpp>


namespace Pamola
{
	class Engine;
	class Circuit;

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

	private:

		std::set<uint32_t> & getConnectedComponents(std::set<uint32_t> &);

	public:

		std::shared_ptr<Circuit> getCircuit();

		const std::shared_ptr<Engine> getEngine();
		
		uint32_t getId() const;

		bool operator<(const Pamola::Object&);

		bool operator>(const Pamola::Object&);

		bool operator<=(const Pamola::Object&);
		
		bool operator>=(const Pamola::Object&);
		
		bool operator==(const Pamola::Object&);

		bool operator!=(const Pamola::Object&);
		
		virtual std::set<std::string> getVariables() = 0;

		virtual const std::set<uint32_t> getAdjacentComponents() = 0;

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
