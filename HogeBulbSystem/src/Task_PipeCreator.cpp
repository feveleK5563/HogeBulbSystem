#include "Task_PipeCreator.h"
#include "DxLib.h"
#include "Math.h"
#include "Task_Pipe.h"
#include "InputState.h"
#include "Task_WaterCreator.h"

namespace PipeCreator
{
	//☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★
	//★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆

	//----------------------------------------------
	//タスクのコンストラクタ
	Task::Task():
		TaskAbstract(defGroupName, defTaskName, defPriority)
	{
	}
	//----------------------------------------------
	//タスクのデストラクタ
	Task::~Task()
	{

	}
	//----------------------------------------------
	//タスクの生成
	std::shared_ptr<Task> Task::Create()
	{
		std::shared_ptr<Task> task = 
			std::make_shared<Task>();
		TS::taskSystem.AddTask(task);

		task->Initialize();
		return task;
	}

	//◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆
	//◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇

	//----------------------------------------------
	//初期化処理
	//----------------------------------------------
	void Task::Initialize()
	{
		MapClear();
	}

	//----------------------------------------------
	//終了処理
	//----------------------------------------------
	void Task::Finalize()
	{

	}

	//----------------------------------------------
	//更新
	//----------------------------------------------
	void Task::Update()
	{
		if (auto wcreator = TS::taskSystem.GetTaskOne<WaterCreator::Task>
			(WaterCreator::defGroupName, WaterCreator::defTaskName))
		{
			if (wcreator->GetIsCreateWaterSouce() == false)
			{
				CreatePipe();
			}
		}
	}

	//----------------------------------------------
	//描画
	//----------------------------------------------
	void Task::Draw()
	{
		
	}

	//マップの状態を取得する
	const PipeType Task::GetMapState(int mx, int my) const
	{
		return (PipeType)map[my][mx];
	}

	//マップを初期化
	void Task::MapClear()
	{
		for (int y = 0; y < GDEF::mapY; ++y)
		{
			for (int x = 0; x < GDEF::mapX; ++x)
			{
				map[y][x] = (int)PipeType::Non;
			}
		}
	}

	//パイプを作成
	void Task::CreatePipe()
	{
		int mx = (int)INPUT_DXL::mouse.GetPos().x,
			my = (int)INPUT_DXL::mouse.GetPos().y;
		mx /= GDEF::imageSize;
		my /= GDEF::imageSize;

		if (mx < 0 || my < 0 ||
			mx >= GDEF::mapX || my >= GDEF::mapY)
		{
			return;
		}

		MATH::Vec2 setPos((float)mx * GDEF::imageSize, (float)my * GDEF::imageSize);

		if (INPUT_DXL::mouse[MouseInput::Type::LEFT] == ON &&
			SetCheck(mx, my))
		{
			Pipe::Task::Create(setPos, PipeType::Pipe, map[my][mx]);
		}

		if (INPUT_DXL::mouse[MouseInput::Type::RIGHT] == DOWN &&
			SetCheck(mx, my))
		{
			Pipe::Task::Create(setPos, PipeType::ValveOff, map[my][mx]);
		}
	}

	//パイプが置けるか否かの判断
	bool Task::SetCheck(int mx, int my)
	{
		return map[my][mx] == (int)PipeType::Non;
	}
}