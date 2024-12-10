#pragma once

class CRocket : public CSprite
{
	float fuel;
	float thrust;
	float landingSpeed;

public:
	CRocket(float x, float y, char *pFileBitmap, Uint32 time);
	CRocket(float x, float y, char *pFileBitmap, CColor colorKey, Uint32 time);
	~CRocket(void);

	// fuel
	float GetFuel() 						{ if (fuel < 0) return 0; else return fuel; }
	void SetFuel(float fuel)		 		{ this->fuel = fuel; }
	
	// rocket engine thrust
	float GetThrust()		 				{ if (fuel < 1) return 0; else return thrust; }
	void SetThrust(float thrust)			{ this->thrust = thrust; }
	
	void Reset()							{ SetSpeed(0); fuel = 100; thrust = 0; landingSpeed = 0; }

	// status information
	bool IsLandedOnEarth()					{ return GetX() <= 125; }
	bool IsLandedOnMoon()					{ return GetX() >= 720; }
	bool IsCrashed()						{ return abs(landingSpeed) > 100.0; }
	float GetLandingSpeed()					{ return landingSpeed; }

	// The Rocket Behaviour
	virtual void OnUpdate(Uint32 time, Uint32 deltaTime);
};
