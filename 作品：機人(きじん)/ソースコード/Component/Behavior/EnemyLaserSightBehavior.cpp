#include "EnemyLaserSightBehavior.h"
#include "../../Object/ObjectManager.h"
#include "../Info/ObjectInfo.h"
#include "../../Common/Debug.h"

Quaternion defRot{Deg2Rad(5.0f), 0.0f,0.0f};

void EnemyLaserSightBehavior::Update(BaseScene& scene, ObjectManager& objectManager, float delta, Controller& controller)
{
	if (!enemy_.IsActive())
	{
		objectManager.GetComponent<ObjectInfo>(ownerId_)->Destory();
	}

	// 同期する敵の回転とオフセットから座標を求める
	auto vec = enemy_->GetRotation() * offset_;
	transform_->Pos() = enemy_->GetPos() + vec;

	// 回転も同期させる
	transform_->SetRotation(defRot);
	transform_->AddRotation(enemy_->GetRotation());
}

void EnemyLaserSightBehavior::Begin(ObjectManager& objectManager)
{
	transform_ = objectManager.GetComponent<Transform>(ownerId_);
	enemy_ = objectManager.GetComponent<Transform>(enemyID_);
	line_ = objectManager.GetComponent<LineRender>(ownerId_);
	line_->SetLength(700.0f);
	line_->SetDrawFlag(false);
}
