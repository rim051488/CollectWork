#pragma once
#include "../Scene/BaseScene.h"

enum class TranID
{
	Cross,
	CutainUp,
};


class TransitionScene:
	public BaseScene
{
public:
	TransitionScene(uniqueScene beforScene, uniqueScene afterScene);
	~TransitionScene();
private:
	uniqueScene Update(double delta, uniqueScene ownScene) override;
	virtual bool UpdateTransition(double delta) = 0;

protected:
	virtual TranID GetTranID(void) = 0;
	bool Init(void) override;
	Scene GetSceneID(void) override { return Scene::Transition; };
	uniqueScene beforScene_;
	uniqueScene afterScene_;
	double count_;

};

