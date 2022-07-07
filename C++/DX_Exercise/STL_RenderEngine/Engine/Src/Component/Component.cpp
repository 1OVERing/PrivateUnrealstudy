#include "Core.h"
#include "Component.h"
#include "Actor.h"
//#include "TransformComponent.h"

namespace Ronnie
{
	// RTTI Á¤ÀÇ.
	RTTI_DEFINITIONS(Component)

	Component::Component()
		: ownerActor(nullptr), transform(nullptr)
	{
	}

	Component::~Component()
	{
	}

	void Component::SetActor(Actor* actor)
	{
		ownerActor = actor;
		transform = ownerActor->transform.get();
	}
}