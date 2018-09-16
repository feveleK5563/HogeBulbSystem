#pragma once
#include "TaskSystem.h"
#include "SystemDefine.h"
#include "GameDefine.h"

namespace PipeCreator
{
	const std::string	defGroupName	("�p�C�v");			//�O���[�v��
	const std::string	defTaskName		("�p�C�v������");		//�^�X�N��
	const float			defPriority(0.f);			//�f�t�H���g�̏����D��x

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
		//�R���X�g���N�^
		Task();
		
		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create();

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��

		const PipeType GetMapState(int mx, int my) const;

	private:
		void MapClear();
		void CreatePipe();
		bool SetCheck(int mx, int my);
	};
}