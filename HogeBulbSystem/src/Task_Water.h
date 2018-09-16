#pragma once
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "Task_PipeCreator.h"
#include "Task_WaterCreator.h"

namespace Water
{
	const std::string	defGroupName	("��");	//�O���[�v��
	const std::string	defTaskName		("���{��");		//�^�X�N��
	const float			defPriority(1.f);			//�f�t�H���g�̏����D��x

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

		int* map;
		bool isCreate;
		WaterCreator::WaterType type;
		ImageDrawer imgDrawer;
		MATH::Vec2 pos;

	public:
		//�R���X�g���N�^
		Task(const MATH::Vec2& setPos, WaterCreator::WaterType setType, int* map);
		
		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create(const MATH::Vec2& setPos, WaterCreator::WaterType setType, int* map);

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��

	private:
		void CreateWater(int mx, int my, int addx, int addy);
	};
}