#pragma once
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "Task_PipeCreator.h"
#include "Task_WaterCreator.h"

namespace Water
{
	const std::string	defGroupName	("水");	//グループ名
	const std::string	defTaskName		("水本体");		//タスク名
	const float			defPriority(1.f);			//デフォルトの処理優先度

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

		int* map;
		bool isCreate;
		WaterCreator::WaterType type;
		ImageDrawer imgDrawer;
		MATH::Vec2 pos;

	public:
		//コンストラクタ
		Task(const MATH::Vec2& setPos, WaterCreator::WaterType setType, int* map);
		
		//デストラクタ
		~Task();
		
		//タスクの生成
		static std::shared_ptr<Task> Create(const MATH::Vec2& setPos, WaterCreator::WaterType setType, int* map);

		void Initialize();			//初期化処理
		void Finalize() override;	//終了処理
		void Update() override;		//更新
		void Draw() override;		//描画

	private:
		void CreateWater(int mx, int my, int addx, int addy);
	};
}