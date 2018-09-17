#pragma once

#include "PamolaObject.h"
#include <set>
#include <vector>

namespace Pamola
{
	class CircuitTerminal;

	class CircuitElement : public Object, public std::enable_shared_from_this<CircuitElement>
	{

		friend class Engine;
		
	public:

		using std::enable_shared_from_this<CircuitElement>::shared_from_this;

	private:

		std::vector<std::shared_ptr<CircuitTerminal>> terminals;

		uint32_t numberOfterminals;

	protected:

		CircuitElement(uint32_t = 0);

	public:

		virtual ~CircuitElement();

	public:

		const std::vector<std::shared_ptr<CircuitTerminal>> getTerminals();

		const std::shared_ptr<CircuitTerminal> getTerminal(uint32_t);

		const std::set<uint32_t> getAdjacentComponents();

		Type getPamolaType();

		uint32_t getNumberOfTerminals();
		
		virtual varMap getVariables() = 0;

	};
	
	bool operator<(const std::shared_ptr<CircuitElement>, const std::shared_ptr<CircuitElement>);
	bool operator>(const std::shared_ptr<CircuitElement>, const std::shared_ptr<CircuitElement>);
	bool operator<=(const std::shared_ptr<CircuitElement>, const std::shared_ptr<CircuitElement>);
	bool operator>=(const std::shared_ptr<CircuitElement>, const std::shared_ptr<CircuitElement>);
	bool operator==(const std::shared_ptr<CircuitElement>, const std::shared_ptr<CircuitElement>);
	bool operator!=(const std::shared_ptr<CircuitElement>, const std::shared_ptr<CircuitElement>);

}