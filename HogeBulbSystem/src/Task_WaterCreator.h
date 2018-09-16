#pragma once
#include "TaskSystem.h"
#include "GameDefine.h"

namespace WaterCreator
{
	const std::string	defGroupName	("水");	//グループ名
	const std::string	defTaskName		("水生成者");		//タスク名
	const float			defPriority(0.f);			//デフォルトの処理優先度
	
	enum struct WaterType
	{
		WaterSource	= 0,
		Water		= 1,
		Non			= 2,
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		int map[GDEF::mapY][GDEF::mapX];
		bool isCreateWaterSource;

	public:
		//コンストラクタ
		Task();
		
		//デストラクタ
		~Task();
		
		//タスクの生成
		static std::shared_ptr<Task> Create();

		void Initialize();			//初期化処理
		void Finalize() override;	//終了処理
		void Update() override;		//更新
		void Draw() override;		//描画

		bool GetIsCreateWaterSouce() const;

	private:
		void CreateWaterSource();
		void MapClear();
	};
}