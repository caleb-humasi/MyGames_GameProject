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
	enum class CorrespondingLayer {
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
namespace dragon {
	enum class EntityState {
		FLYING,
		DASHING,
		ATTACKING,
		DAMAGED
	};
	enum class CorrespondingLayer {
		BODY,
		HEAD,
		FIRE
	};
	enum class CorrespondingHeadAnimation {
		NORMAL,
		FIRE_BREATHING,
		NONE
	};
	enum class CorrespondigFireAnimation {
		FIRING,
		NONE
	};
	enum class CorrespondingBodyAnimation {
		FLYING,
		DASHING,
		DAMAGED
	};
}