#pragma 

#include "PamolaObject.h"

namespace Pamola
{
	
	class Engine;
	class CircuitTerminal;

	class Circuit : public Object
	{
		
		friend class Engine;

	private:

		std::set<std::shared_ptr<Object>> elements;

		std::set<std::shared_ptr<CircuitTerminal>> terminals;

		Circuit();

	public:

		~Circuit();
		
		const std::set<std::shared_ptr<CircuitTerminal>> getTerminals();

		const std::set<std::shared_ptr<Object>> getElements();

		std::vector<std::function<std::complex<double>(std::map<std::string, std::complex<double>>)>> getEquations();

		std::set<std::string> getVariables();
		
		const std::set<uint32_t> getAdjacentComponents();

		Type getPamolaType();

		int getDegreesOfFreedom();

		void setUp(const std::vector<std::shared_ptr<Object>> &);
	};

}