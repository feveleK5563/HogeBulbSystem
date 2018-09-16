#include "Task_WaterCreator.h"
#include "DxLib.h"
#include "Task_Water.h"
#include "InputState.h"
#include "Task_PipeCreator.h"

namespace WaterCreator
{
	//☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★
	//★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆

	//----------------------------------------------
	//タスクのコンストラクタ
	Task::Task():
		TaskAbstract(defGroupName, defTaskName, defPriority),
		isCreateWaterSource(false)
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
		TS::taskSystem.KillTask(Water::defGroupName, Water::defTaskName);
	}

	//----------------------------------------------
	//更新
	//----------------------------------------------
	void Task::Update()
	{
		if (INPUT_DXL::mouse[MouseInput::Type::MIDDLE] == DOWN)
		{
			if (isCreateWaterSource == false)
			{
				CreateWaterSource();
			}
			else
			{
				TS::taskSystem.KillTask(Water::defGroupName, Water::defTaskName);
				MapClear();
				isCreateWaterSource = false;
			}
		}

		if (INPUT_DXL::key[KEY_INPUT_SPACE] == DOWN)
		{
			TS::taskSystem.KillTask(Water::defGroupName, Water::defTaskName);
			MapClear();
			isCreateWaterSource = false;
		}
	}

	//----------------------------------------------
	//描画
	//----------------------------------------------
	void Task::Draw()
	{
		
	}

	//水源を生成する
	void Task::CreateWaterSource()
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

		if (auto mapd = TS::taskSystem.GetTaskOne<PipeCreator::Task>
			(PipeCreator::defGroupName, PipeCreator::defTaskName))
		{
			if (mapd->GetMapState(mx, my) == PipeCreator::PipeType::Pipe)
			{
				Water::Task::Create(MATH::Vec2((float)mx * GDEF::imageSize, (float)my * GDEF::imageSize),
					WaterType::WaterSource, &map[0][0]);

				map[my][mx] = (int)WaterType::WaterSource;
				isCreateWaterSource = true;
			}
		}
	}

	bool Task::GetIsCreateWaterSouce() const
	{
		return isCreateWaterSource;
	}

	//マップを初期化
	void Task::MapClear()
	{
		for (int y = 0; y < GDEF::mapY; ++y)
		{
			for (int x = 0; x < GDEF::mapX; ++x)
			{
				map[y][x] = (int)WaterType::Non;
			}
		}
	}
}