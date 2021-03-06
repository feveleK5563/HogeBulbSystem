#pragma once
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "Task_PipeCreator.h"

namespace Pipe
{
	const std::string	defGroupName	("パイプ");	//グループ名
	const std::string	defTaskName		("パイプ本体");	//タスク名
	const float			defPriority(1.1f);	//デフォルトの処理優先度

	//----------------------------------------------
	class Resource
	{
	private:
		static std::weak_ptr<Resource> instance;

	public:
		ImageData imgData;

		Resource();		//コンストラクタ
		~Resource();	//デストラクタ
		static std::shared_ptr<Resource> Create();	//リソースの生成
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::shared_ptr<Resource> res;	//確保したリソース

		PipeCreator::PipeType type;
		ImageDrawer imgDrawer;
		MATH::Vec2 pos;

		int& mapData;

	public:
		//コンストラクタ
		Task(const MATH::Vec2& setPos, PipeCreator::PipeType setType, int& setMapData);
		
		//デストラクタ
		~Task();
		
		//タスクの生成
		static std::shared_ptr<Task> Create(const MATH::Vec2& setPos, PipeCreator::PipeType setType, int& setMapData);

		void Initialize() override;	//初期化処理
		void Finalize() override;	//終了処理
		void Update() override;		//更新
		void Draw() override;		//描画

		const MATH::Vec2& GetPos() const;
	};
}