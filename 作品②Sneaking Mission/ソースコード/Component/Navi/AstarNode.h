#pragma once
#include <memory>
#include <list>
#include "../../common/Math.h"

// Astar探索用のノード
class AstarNode
{
public:
	AstarNode(const Math::Vector2I& pos);
	AstarNode();

	/// <summary>
	/// 内容をクリアする
	/// </summary>
	void Clear();

	/// <summary>
	/// トータルコストの取得
	/// </summary>
	/// <param name=""></param>
	/// <returns> トータルコスト </returns>
	const int GetTotalCost(void) const;

	/// <summary>
	/// トータルのコストのセット
	/// </summary>
	/// <param name="cost"> コスト </param>
	void SetTotalCost(int cost);

	/// <summary>
	/// ヒューリスティックコストの取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const int GetHeuristicCost(void) const;

	/// <summary>
	/// 指定の座標までのヒューリスティックコストを計算する
	/// </summary>
	/// <param name="pos"> 座標(マス目) </param>
	void CalculateHeuristicCost(const Math::Vector2I& pos);

	/// <summary>
	/// 座標(マス目)を取得する
	/// </summary>
	/// <param name=""></param>
	/// <returns> マス目 </returns>
	const Math::Vector2I& GetPos(void) const;

	/// <summary>
	/// 座標(マス目)をセットする
	/// </summary>
	/// <param name="pos"> マス目 </param>
	void SetPos(const Math::Vector2I& pos) { pos_ = pos; }

	/// <summary>
	/// 隣接ノードのリストを取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const std::list<AstarNode*> GetNextNode(void) const { return nextNode_; }

	/// <summary>
	/// 隣接ノードを追加する
	/// </summary>
	/// <param name="node"></param>
	void PushNext(AstarNode* node) { nextNode_.emplace_back(node); }

private:

	// 座標(マス目)
	Math::Vector2I pos_;

	// 一つ前の座標(マス目)
	Math::Vector2I beforPos_;

	// 隣接ノード
	std::list<AstarNode*> nextNode_;

	// ヒューリスティックコスト(ゴールまでの距離をコストに)
	int heuristicCost_;

	// 合計コスト
	int totalCost_;
};

