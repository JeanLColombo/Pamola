#pragma once

#include "CircuitElement.h"

namespace Pamola {
	
	class Dipole : public CircuitElement
	{
	public:
		Dipole();
		virtual ~Dipole();

		std::shared_ptr<Pamola::CircuitTerminal> getLeft();
		std::shared_ptr<Pamola::CircuitTerminal> getRight();
		
	protected:

		std::function<std::complex<double>(varMap)> currentCallback();

	public:

		void connectInSeriesTo(std::shared_ptr<Dipole>);

		void connectInParallelTo(std::shared_ptr<Dipole>);

		virtual std::set<std::string> getVariables() = 0;

		virtual int getDegreesOfFreedom() = 0;
		
		template<class T1, class T2>
		friend std::shared_ptr<Dipole> operator+(std::shared_ptr<T1>, std::shared_ptr<T2>);

		template<class T1, class T2>
		friend std::shared_ptr<Dipole> operator/(std::shared_ptr<T1>, std::shared_ptr<T2>);

	};

	template<class T1, class T2>
	std::shared_ptr<Dipole> operator+(std::shared_ptr<T1> firstDipole, std::shared_ptr<T2> secondDipole)
	{
		auto firstUp = std::static_pointer_cast<Dipole>(firstDipole);
		firstUp->connectInSeriesTo(secondDipole);
		return secondDipole;
	}

	template<class T1, class T2>
	std::shared_ptr<Dipole> operator/(std::shared_ptr<T1> firstDipole, std::shared_ptr<T2> secondDipole)
	{
		auto firstUp = std::static_pointer_cast<Dipole>(firstDipole);
		firstUp->connectInParallelTo(secondDipole);
		return secondDipole;
	}

}
