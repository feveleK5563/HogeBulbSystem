#include "Task_Pipe.h"
#include "DxLib.h"
#include "ImageLoader.h"
#include "InputState.h"
#include "GameDefine.h"

namespace Pipe
{
	std::weak_ptr<Resource> Resource::instance;
	//----------------------------------------------
	//���\�[�X�̃R���X�g���N�^
	Resource::Resource()
	{
		IMG::imageLoader.LoadDivImage("pipe", "data/image/pipe.png", 4, 4, 1, GDEF::imageSize, GDEF::imageSize);
		imgData = IMG::imageLoader.GetImageData("pipe");
	}
	//----------------------------------------------
	//���\�[�X�̃f�X�g���N�^
	Resource::~Resource()
	{
		IMG::imageLoader.DeleteImageData("pipe");
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
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create(const MATH::Vec2& setPos, PipeCreator::PipeType setType, int& setMapData)
	{
		std::shared_ptr<Task> task = 
			std::make_shared<Task>(setPos, setType, setMapData);
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
		mapData = (int)type;
	}

	//----------------------------------------------
	//�I������
	//----------------------------------------------
	void Task::Finalize()
	{
		mapData = (int)PipeCreator::PipeType::Non;
	}

	//----------------------------------------------
	//�X�V
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
	//�`��
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