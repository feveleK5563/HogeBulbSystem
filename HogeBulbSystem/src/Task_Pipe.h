#pragma once
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "Task_PipeCreator.h"

namespace Pipe
{
	const std::string	defGroupName	("�p�C�v");	//�O���[�v��
	const std::string	defTaskName		("�p�C�v�{��");	//�^�X�N��
	const float			defPriority(1.1f);	//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Resource
	{
	private:
		static std::weak_ptr<Resource> instance;

	public:
		ImageData imgData;

		Resource();		//�R���X�g���N�^
		~Resource();	//�f�X�g���N�^
		static std::shared_ptr<Resource> Create();	//���\�[�X�̐���
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::shared_ptr<Resource> res;	//�m�ۂ������\�[�X

		PipeCreator::PipeType type;
		ImageDrawer imgDrawer;
		MATH::Vec2 pos;

		int& mapData;

	public:
		//�R���X�g���N�^
		Task(const MATH::Vec2& setPos, PipeCreator::PipeType setType, int& setMapData);
		
		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create(const MATH::Vec2& setPos, PipeCreator::PipeType setType, int& setMapData);

		void Initialize() override;	//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��

		const MATH::Vec2& GetPos() const;
	};
}