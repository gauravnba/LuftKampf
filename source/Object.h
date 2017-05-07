class BallC;
class FieldC;

typedef struct
{
	float32_t x;
	float32_t y;
}Coord2D;

class ObjectC
{
    friend class BallC;
	friend class FieldC;
public:
    ObjectC(float32_t initPosX, float32_t initPosY, float32_t initVelX, float32_t initVelY);
    ObjectC();
    ~ObjectC();
    void setPosition(Coord2D *posToSet) {mPosition.x = posToSet->x;mPosition.y = posToSet->y;};
    Coord2D *getPosition() {return &mPosition;};
    void setVelocity(Coord2D *velToSet) {mVelocity.x = velToSet->x;mVelocity.y = velToSet->y;};
    void setVelocity(float32_t x, float32_t y) {mVelocity.x = x;mVelocity.y = y;};
    Coord2D *getVelocity() {return &mVelocity;};
    void setCollInfo(CollInfoC *collInfoToSet) {mCollInfo = *collInfoToSet;};
    CollInfoC *getCollInfo() {return &mCollInfo;};
	int32_t getID() {return mID;};
	void setID(int32_t id) {mID = id;};
	virtual void render()=0;
private:
    Coord2D mPosition;
    Coord2D mVelocity;
    CollInfoC mCollInfo;
	int32_t mID;
};