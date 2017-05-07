class StateManager
{
public:
	static StateManager* CreateInstance();
	static StateManager* GetInstance() {return sInstance;};
	~StateManager(){};

	enum 
	{
		SPLASH_SCREEN,
		GAME,
		GAME_OVER
	};

	int32_t	getState();
	void	setState(int32_t stateToSet);
	void	shutdown();

private:
	static StateManager* sInstance;
	StateManager(){};
	int32_t		mCurrentState;
};