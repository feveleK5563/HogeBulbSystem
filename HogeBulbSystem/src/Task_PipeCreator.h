#pragma once
#include "TaskSystem.h"
#include "SystemDefine.h"
#include "GameDefine.h"

namespace PipeCreator
{
	const std::string	defGroupName	("パイプ");			//グループ名
	const std::string	defTaskName		("パイプ生成者");		//タスク名
	const float			defPriority(0.f);			//デフォルトの処理優先度

	enum struct PipeType
	{
		Pipe		= 0,
		ValveOff	= 1,
		Cross		= 2,
		ValveOn		= 3,
		Non			= 4,
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		int map[GDEF::mapY][GDEF::mapX];

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

		const PipeType GetMapState(int mx, int my) const;

	private:
		void MapClear();
		void CreatePipe();
		bool SetCheck(int mx, int my);
	};
}