#pragma 

#include "PamolaObject.h"
#include "CircuitElement.h"

namespace Pamola
{
	
	class Circuit : public Object
	{
		
		friend class Engine;

	private:

		std::set<std::shared_ptr<Object>> elements;

		std::set<std::shared_ptr<CircuitTerminal>> terminals;

		Circuit();

	public:

		~Circuit();

		const std::set<std::shared_ptr<Object>> getElements();
		
		const std::set<uint32_t> getAdjacentComponents();

		Type getPamolaType();

		int getDegreesOfFreedom();

		void setUp(const std::vector<std::shared_ptr<Object>> &);
	};

}