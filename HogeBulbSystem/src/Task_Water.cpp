#include "Task_Water.h"
#include "DxLib.h"
#include "ImageLoader.h"
#include "GameDefine.h"
#include "InputState.h"

namespace Water
{
	std::weak_ptr<Resource> Resource::instance;
	//----------------------------------------------
	//���\�[�X�̃R���X�g���N�^
	Resource::Resource()
	{
		IMG::imageLoader.LoadDivImage("water", "data/image/water.png", 2, 2, 1, GDEF::imageSize, GDEF::imageSize);
		imgData = IMG::imageLoader.GetImageData("water");
	}
	//----------------------------------------------
	//���\�[�X�̃f�X�g���N�^
	Resource::~Resource()
	{
		IMG::imageLoader.DeleteImageData("water");
	}
	//----------------------------------------------
	//���\�[�X�̐���
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

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task(const MATH::Vec2& setPos, WaterCreator::WaterType setType, int* wmap):
		TaskAbstract(defGroupName, defTaskName, defPriority),
		res(Resource::Create()),
		map(wmap),
		isCreate(false),
		type(setType),
		pos(setPos)
	{
		imgDrawer.Initialize(res->imgData, false);
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create(const MATH::Vec2& setPos, WaterCreator::WaterType setType, int* wmap)
	{
		std::shared_ptr<Task> task = 
			std::make_shared<Task>(setPos, setType, wmap);
		TS::taskSystem.AddTask(task);

		task->Initialize();
		return task;
	}

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//����������
	//----------------------------------------------
	void Task::Initialize()
	{

	}

	//----------------------------------------------
	//�I������
	//----------------------------------------------
	void Task::Finalize()
	{

	}

	//----------------------------------------------
	//�X�V
	//----------------------------------------------
	void Task::Update()
	{
		int mx = (int)pos.x / GDEF::imageSize,
			my = (int)pos.y / GDEF::imageSize;

		if (isCreate == false)
		{
			CreateWater(mx + 1, my, 1, 0);
			CreateWater(mx - 1, my, -1, 0);
			CreateWater(mx, my + 1, 0, 1);
			CreateWater(mx, my - 1, 0, -1);
			isCreate = true;
		}
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		imgDrawer.DrawOne(pos, 1.f, 0.f, false, (int)type, Color(255, 255, 255, 255));
	}

	//----------------------------------------------
	//�����쐬����
	void Task::CreateWater(int mx, int my, int addx, int addy)
	{
		if (mx < 0 || my < 0 ||
			mx >= GDEF::mapX, my >= GDEF::mapY)
		{
			return;
		}

		if (auto pipeC = TS::taskSystem.GetTaskOne<PipeCreator::Task>
			(PipeCreator::defGroupName, PipeCreator::defTaskName))
		{
			if (auto waterC = TS::taskSystem.GetTaskOne<WaterCreator::Task>
				(WaterCreator::defGroupName, WaterCreator::defTaskName))
			{
				int& mapState = *(map + (mx + (my * GDEF::mapX)));

				if (mapState != (int)WaterCreator::WaterType::Water &&
					mapState != (int)WaterCreator::WaterType::WaterSource)
				{
					switch (PipeCreator::PipeType(pipeC->GetMapState(mx, my)))
					{
					case PipeCreator::PipeType::Pipe:
					case PipeCreator::PipeType::ValveOff:
						Create(MATH::Vec2((float)mx * GDEF::imageSize, (float)my * GDEF::imageSize),
							WaterCreator::WaterType::Water, map);
						mapState = (int)WaterCreator::WaterType::Water;
						break;

					case PipeCreator::PipeType::Cross:
						CreateWater(mx + addx, my + addy, addx, addy);
						break;
					}
				}
			}
		}
	}
}