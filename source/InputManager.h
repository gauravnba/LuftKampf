#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#define NUM_INPUTS	4
#define FIRE_KEY	88

class InputManager
{
public:
	static InputManager* CreateInstance();
	static InputManager* GetInstance() {return sInstance;};
	void				init() {};
	void				update(){};
	//Coord2D*			getCurrentMousePosition(){};
	void				keyProcess();
	void				playerInput();

	bool*				getInputs() { return mPlayerInputStates; };

private:
	InputManager(){};

	static	InputManager *sInstance;
	static const char mPlayerInput[NUM_INPUTS];
	bool	mPlayerInputStates[NUM_INPUTS];
};
#endif