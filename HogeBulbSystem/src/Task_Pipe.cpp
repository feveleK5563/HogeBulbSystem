#include "Task_Pipe.h"
#include "DxLib.h"
#include "ImageLoader.h"
#include "InputState.h"
#include "GameDefine.h"

namespace Pipe
{
	std::weak_ptr<Resource> Resource::instance;
	//----------------------------------------------
	//リソースのコンストラクタ
	Resource::Resource()
	{
		IMG::imageLoader.LoadDivImage("pipe", "data/image/pipe.png", 4, 4, 1, GDEF::imageSize, GDEF::imageSize);
		imgData = IMG::imageLoader.GetImageData("pipe");
	}
	//----------------------------------------------
	//リソースのデストラクタ
	Resource::~Resource()
	{
		IMG::imageLoader.DeleteImageData("pipe");
	}
	//----------------------------------------------
	//リソースの生成
	std::shared_ptr<Resource> Resource::Create()
	{
		auto sp = instance.lock();
		if (!sp)
		{
			sp = std::make_shared<Resource>();
			instance = sp;
		}
		return sp;
	}

	//☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★
	//★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆

	//----------------------------------------------
	//タスクのコンストラクタ
	Task::Task(const MATH::Vec2& setPos, PipeCreator::PipeType setType, int& setMapData):
		TaskAbstract(defGroupName, defTaskName, defPriority),
		res(Resource::Create()),
		pos(setPos),
		type(setType),
		mapData(setMapData)
	{
		imgDrawer.Initialize(res->imgData, false);
	}
	//----------------------------------------------
	//タスクのデストラクタ
	Task::~Task()
	{

	}
	//----------------------------------------------
	//タスクの生成
	std::shared_ptr<Task> Task::Create(const MATH::Vec2& setPos, PipeCreator::PipeType setType, int& setMapData)
	{
		std::shared_ptr<Task> task = 
			std::make_shared<Task>(setPos, setType, setMapData);
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
		mapData = (int)type;
	}

	//----------------------------------------------
	//終了処理
	//----------------------------------------------
	void Task::Finalize()
	{
		mapData = (int)PipeCreator::PipeType::Non;
	}

	//----------------------------------------------
	//更新
	//----------------------------------------------
	void Task::Update()
	{
		int mx = (int)INPUT_DXL::mouse.GetPos().x,
			my = (int)INPUT_DXL::mouse.GetPos().y,
			px, py;

		mx /= GDEF::imageSize;
		my /= GDEF::imageSize;
		px = int(pos.x / GDEF::imageSize);
		py = int(pos.y / GDEF::imageSize);

		if (px == mx && py == my)
		{
			switch (type)
			{
			case PipeCreator::PipeType::Pipe:
				if (INPUT_DXL::mouse[MouseInput::Type::RIGHT] == ON)
				{
					KillMe();
				}
				break;

			case PipeCreator::PipeType::ValveOff:
				if (INPUT_DXL::mouse[MouseInput::Type::RIGHT] == DOWN)
				{
					type = PipeCreator::PipeType::Cross;
					mapData = (int)type;
				}
				break;

			case PipeCreator::PipeType::Cross:
				if (INPUT_DXL::mouse[MouseInput::Type::RIGHT] == DOWN)
				{
					type = PipeCreator::PipeType::ValveOn;
					mapData = (int)type;
				}
				break;

			case PipeCreator::PipeType::ValveOn:
				if (INPUT_DXL::mouse[MouseInput::Type::RIGHT] == DOWN)
				{
					KillMe();
				}
				break;
			}
		}

		if (INPUT_DXL::key[KEY_INPUT_SPACE] == DOWN)
		{
			KillMe();
		}
	}

	//----------------------------------------------
	//描画
	//----------------------------------------------
	void Task::Draw()
	{
		imgDrawer.DrawOne(pos, 1.f, 0.f, false, (int)type, Color(255, 255, 255, 255));
	}


	const MATH::Vec2& Task::GetPos() const
	{
		return pos;
	}
}