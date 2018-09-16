#pragma once
#include "TaskSystem.h"
#include "GameDefine.h"

namespace WaterCreator
{
	const std::string	defGroupName	("��");	//�O���[�v��
	const std::string	defTaskName		("��������");		//�^�X�N��
	const float			defPriority(0.f);			//�f�t�H���g�̏����D��x
	
	enum struct WaterType
	{
		WaterSource	= 0,
		Water		= 1,
		Non			= 2,
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		int map[GDEF::mapY][GDEF::mapX];
		bool isCreateWaterSource;

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

		bool GetIsCreateWaterSouce() const;

	private:
		void CreateWaterSource();
		void MapClear();
	};
}