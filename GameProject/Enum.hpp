#pragma once

namespace player {
	enum class EntityState {
		IDDLE,
		WALKING,
		ATTACKING,
		JUMPING,
		THROWING_SUBWEAPON,
		DAMAGED,
		SQUAT,
		SQUAT_ATTACK,
		SQUAT_THROWING_SUBWEAPON
	};
	enum class AnimLayer {
		BODY,
		WHIP
	};
	enum class CorrespondingBodyAnimation {
		IDDLE,
		WALKING,
		ATTACKING,
		JUMPING,
		THROWING_SUBWEAPON,
		DAMAGED,
		SQUAT,
		SQUAT_ATTACK
	};
	enum class CorrespondingWhipAnimation {
		ATTACKING
	};
}
namespace robot {
	enum class EntityState {
		WALKING,
		JUMP,
		IDDLE
	};
}

namespace crow {
	enum class EntityState {
		FLYING,
		STANDING
	};
}