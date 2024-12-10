#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void) :
	m_theEarth(-47, 300, "earth.gif", 0),
	m_theMoon(830, 300, "moon.gif", 0),
	m_theRocket(125, 300, "rocket.bmp", CColor::Blue(), 0)
{
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	m_theRocket.Update(GetTime());
	if (m_theRocket.IsLandedOnEarth() || m_theRocket.IsLandedOnMoon())
		if (m_theRocket.IsCrashed())
			GameOver();
}

#pragma warning (disable:4996)
void CMyGame::OnDraw(CGraphics* g)
{
	// draw the stars
	for (int i = 0; i < NUM_START; i++)
	{
		Sint16 r = 1 + rand() * 2 / RAND_MAX;
		g->FillOval(CRectangle((Sint16)m_stars[i].m_x-r, 80 + (Sint16)m_stars[i].m_y-r, r+r, r+r), CColor::White());
	}

	// draw the sprites
	m_theEarth.Draw(g);
	m_theMoon.Draw(g);
	m_theRocket.Draw(g);
	
	*g << font(14);

	// show speed
	CColor clr = abs(m_theRocket.GetSpeed()) > 100.0 ? CColor::Red() : CColor::Green();
	*g << color(clr) << xy(405, 55) << "speed: " << (int)(m_theRocket.GetSpeed()/10);
	g->DrawLine(CVector(400, 55), CVector(400, 65), clr);
	g->DrawLine(CVector(400, 55), CVector(400 + 0.4f * m_theRocket.GetSpeed(), 55.f), clr);

	// show thrust
	*g << color(CColor::Yellow()) << xy(405, 30) << "thrust: " << (int)m_theRocket.GetThrust();
	g->DrawLine(CVector(400, 30), CVector(400, 40), CColor::Yellow());
	g->DrawLine(CVector(400, 30), CVector(400 + 40.f * m_theRocket.GetThrust(), 30.f), CColor::Yellow());

	// show fuel
	*g << color(CColor::Blue()) << xy(405, 5) << "fuel: " << (int)(m_theRocket.GetFuel());
	g->DrawLine(CVector(400, 5), CVector(400, 15), CColor::Blue());
	g->DrawLine(CVector(400, 5), CVector(400 + 4.f * m_theRocket.GetFuel(), 5.f), CColor::Blue());

	// show landing/crashing information
	int landingSpeed = (int)abs(m_theRocket.GetLandingSpeed()/10);
	if (m_theRocket.IsLandedOnEarth() || m_theRocket.IsLandedOnMoon())
	{
		*g << color(CColor::White()) << bottom << row(2) << down;
		if (m_theRocket.IsLandedOnEarth() && landingSpeed == 0)
			*g << "Use LEFT and RIGHT arrows to accelerate the rocket";
		else if (m_theRocket.IsLandedOnEarth())
			if (m_theRocket.IsCrashed()) 
				*g << "CRASHED ON EARTH";
			else 
				*g << "LANDED ON EARTH"; 
		else
			if (m_theRocket.IsCrashed()) 
				*g << "CRASHED ON THE MOON";
			else 
				*g << "LANDED ON THE MOON"; 
		
		if (landingSpeed != 0)
			*g << endl << "Speed at the Surface = " << landingSpeed;
		if (m_theRocket.IsCrashed())
			*g << endl << "PRESS F2 TO PLAY AGAIN";
	}
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
	// create stars
	for (int i = 0; i < NUM_START; i++)
		m_stars[i] = CVector((float)(800 * rand() / RAND_MAX), (float)(520 * rand() / RAND_MAX));

	m_theRocket.LoadImage("rocket.bmp", "rocket", CColor::Blue());
	m_theRocket.LoadImage("fire.gif", "fire");
}

// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	// reset the rocket and start the game
	m_theRocket.SetPosition(125, 300);
	m_theRocket.SetRotation(90);
	m_theRocket.Reset();
	m_theRocket.SetImage("rocket");
	StartGame();
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
}

// called when Game is Over
void CMyGame::OnGameOver()
{
	m_theRocket.SetImage("fire");
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();

	if (IsGameOver())
		return;
	if (sym == SDLK_LEFT)
		m_theRocket.SetThrust(m_theRocket.GetThrust() - 1);
	if (sym == SDLK_RIGHT)
		m_theRocket.SetThrust(m_theRocket.GetThrust() + 1);
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
