#include "stdafx.h"
#include "Rocket.h"

CRocket::CRocket(float x, float y, char *pFileBitmap, Uint32 time) 
	: CSprite(x, y, pFileBitmap, time)
{
	SetDirection(90);
	Reset();
}

CRocket::CRocket(float x, float y, char *pFileBitmap, CColor colorKey, Uint32 time) 
	: CSprite(x, y, pFileBitmap, colorKey, time)
{
	SetDirection(90);
	Reset();
}

CRocket::~CRocket(void)
{
}

void CRocket::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	// THIS IS WHERE YOU ARE SUPPOSED TO INSERT YOUR CODE!!!
	


	// 1. Burn your fuel
	SetFuel(GetFuel() - abs(GetThrust()) / 20);


	// 2. Calculate the Mass of the Rocket
	// It should be the rocket own mass, for example 120, plus the fuel
	// So - uncomment the next line of code and type in the formula!

	// float mass = 


	// 3. Calculate the distance Earth - rocket [ NOTE: position of the rocket is GetX() ]
	// float rEarth = 

	// 4. Calculate the distance Moon - rocket
	// float rMoon = 

	// 5. Calculate Earth's and Moon's gravitational force - use the Newton's formula

	// 6. Calculate the engine force (thrust)

	// 7. Calculate the net force (engine + gravity from the Earth + gravity from the Moon).
	//    Note: Gravity of the Earth is pulling the rocket back; gravity of the Moon is pushing it ahead.

	// 8. Find the acceleration

	// 9. Find the speed (I hope you know the formula for the speed/velocity in accelerated motion?)
	//    Names of Rocket's functions you may need here: GetSpeed to obtain the current speed, and SetSpeed to update the speed.


	// 10. Update the rocket's position.
	//     I'm nice - did this part for you:
	CSprite::OnUpdate(time, deltaTime);

	// set rotation depending on the thrust
	if (GetThrust() > 0) SetRotation(90);
	if (GetThrust() < 0) SetRotation(-90);

	// landing tweaks
	if (IsLandedOnEarth() && GetSpeed() <= 0 || IsLandedOnMoon() && GetSpeed() >= 0)
	{
		if (landingSpeed == 0)			// if just landed:
		{
			landingSpeed = GetSpeed();	// register the landing speed
			SetThrust(0);				// switch off the engines
		}
		SetSpeed(0);					// reset speed and position
		SetX(IsLandedOnEarth() ? 125.f : 720.f);
	}
	else
		landingSpeed = 0;				// we are in outer space!
}
