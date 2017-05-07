class BallC : public ObjectC
{
public:
    BallC();
	BallC(float32_t initPosX, float32_t initPosY, float32_t initVelX, float32_t initVelY,int id);
    ~BallC();
	void setBallColor(long color) {mBallColor = color;};
    long getBallColor() {return mBallColor;};
    void update(DWORD milliseconds);
    virtual void render();
	void DoCollisions();
    void disable() {mEnabled = false;};
    void enable() {mEnabled = true;};
    void setRadius(float32_t radius) {mCollInfo.param1 = radius;mRadius = radius;};
	void setRandomColor();
	void reduceVelocity(float32_t factor);
	void moveUp();
private:
	void CollideField();

	long mBallColor;
    bool mEnabled;
    float32_t mRadius;
	bool mAtRest;
};