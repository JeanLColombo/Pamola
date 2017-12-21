#include "stdafx.h"
#include "PamolaEngine.h"

namespace Pamola
{
	const std::shared_ptr<Engine> Engine::localEngine(new Engine());

	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
	}

	const std::shared_ptr<Engine> Engine::getLocalEngine()
	{
		return localEngine;
	}

	const std::set<Object*> Engine::getLocalObjects()
	{
		return localObjects;
	}
	Object * Engine::getLocalObject(uint32_t id)
	{
		for (auto object : localObjects)
			if (object->getId() == id)
				return object;
	}
}