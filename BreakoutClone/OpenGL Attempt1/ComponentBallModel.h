#ifndef COMPONENT_BALL_MODEL_SIMENGINE
#define COMPONENT_BALL_MODEL_SIMENGINE

#include "GameObject.h"

class ComponentBallModel : public IComponent
{
public:
	ComponentBallModel(Vector3 inPosition);
	~ComponentBallModel();

	inline const Vector3 GetSpeed() const {return mSpeed;}
	inline void SetSpeed(Vector3 inSpeed) {mSpeed = inSpeed;}

	inline const bool IsMovementEnabled() {return mMovementEnabled;}
	inline void EnableMovement(bool inMovementEnabled) {mMovementEnabled = inMovementEnabled;}

private:
	bool mMovementEnabled;

	Vector3 mInitialPosition;
	Vector3 mSpeed;
};

#endif