#include "Task_PipeCreator.h"
#include "DxLib.h"
#include "Math.h"
#include "Task_Pipe.h"
#include "InputState.h"
#include "Task_WaterCreator.h"

namespace PipeCreator
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, defTaskName, defPriority)
	{
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create()
	{
		std::shared_ptr<Task> task = 
			std::make_shared<Task>();
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
		MapClear();
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
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		
	}

	//�}�b�v�̏�Ԃ��擾����
	const PipeType Task::GetMapState(int mx, int my) const
	{
		return (PipeType)map[my][mx];
	}

	//�}�b�v��������
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

	//�p�C�v���쐬
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

	//�p�C�v���u���邩�ۂ��̔��f
	bool Task::SetCheck(int mx, int my)
	{
		return map[my][mx] == (int)PipeType::Non;
	}
}