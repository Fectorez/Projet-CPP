#include "pch.h"
#include "PhysicsManager.h"

namespace PhysicsManager
{
	void PhysicsManager::manageMarioJump(Player & player, Platform & platform)
	{
		std::vector<PlatformPart*> pparts = platform.getParts();
		for ( SimpleObject* const& ppart : pparts )
		{
			if ( Collision::BoundingBoxTest(player.getSprite(), ppart->getSprite()) )
			{
				if ( player.isGoingUp() )
					player.makeFall();
				else if ( player.isGoingDown() )
					player.stopFall();
				else
					player.setMoving(false);
			}
		}
	}
}