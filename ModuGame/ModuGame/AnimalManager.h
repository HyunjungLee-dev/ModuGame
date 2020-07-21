#pragma once
#include"Animal.h"
#include"JEngine.h"
#include<vector>


class AnimalManager : public	Animal
{
public:
	AnimalManager();
	virtual ~AnimalManager();

	virtual void Init(DIRECTION  Holedirct) final {};
	void Init();
	void Reset(DIRECTION dirct);
	virtual void Draw() override;
	void Update();
	void Release();


	void ExplosionDraw(float *fETime);
	bool CollisionUpdate(JEngine::POINT mpoint);
	void MotionUpdate();
	void MotionSet(int Direction);

private:
	vector<Animal*> m_pAnimalList;




};

