#define NOMINMAX
#include <algorithm>
#include "ImageLoader.h"
#include "DxLib.h"
#include "UtilityFunctions.h"

AnimData::AnimData():
	startSheet(0),
	relativeSheet(0),
	waitTime(0),
	isLoop(false) {}

AnimData::AnimData(int startSheet, int relativeSheet, float waitTime, bool isLoop) :
	startSheet(startSheet),
	relativeSheet(relativeSheet),
	waitTime(waitTime),
	isLoop(isLoop) {}

//-----------------------------------------------------------------------------

//�f�X�g���N�^
ImageLoader::~ImageLoader()
{
	AllDeleteImageData();
}

//�摜�ǂݍ���
bool ImageLoader::LoadOneImage(const std::string& imageName, const std::string& filePath)
{
	if (imageData.find(imageName) != imageData.end())
	{
		return false;
	}

	//�ǂݍ��񂾉摜�̃f�[�^���i�[
	imageData[imageName].handle = new int[1]{ LoadGraph(filePath.c_str()) };
	imageData[imageName].sheetNum = 1;
	int xSize, ySize;
	GetGraphSize(*(imageData[imageName].handle), &xSize, &ySize);
	imageData[imageName].rect = { 0, 0, xSize, ySize };

	return true;
}

//�摜�����ǂݍ���
bool ImageLoader::LoadDivImage(const std::string& imageName, const std::string& filePath, int allNum, int xNum, int yNum, int xSize, int ySize)
{
	if (imageData.find(imageName) != imageData.end())
	{
		return false;
	}

	//�ǂݍ��񂾉摜�̃f�[�^���i�[
	imageData[imageName].handle = new int[allNum] {};
	if (LoadDivGraph(filePath.c_str(), allNum, xNum, yNum, xSize, ySize, imageData[imageName].handle) == -1)
	{
		return false;
	}
	imageData[imageName].sheetNum = allNum;
	imageData[imageName].rect = { 0, 0, xSize, ySize };

	return true;
}

//�����ǂݍ��ݍς݂̃f�[�^�ɃA�j���[�V�����f�[�^��ǉ�
void ImageLoader::AddAnimationData(const std::string& imageName, int startSheet, int endSheet, float waitTime, bool isLoop)
{
	imageData[imageName].anim.emplace_back(
		new AnimData(startSheet, endSheet - startSheet, std::max(waitTime, 1.f), isLoop)
	);
}

//�摜�f�[�^�̎擾
const ImageData& ImageLoader::GetImageData(const std::string& imageName)
{
	//�A�j���[�V�����ݒ肪�s���Ă��Ȃ������ꍇ��
	//�֋X�I�ɃA�j���[�V������ݒ肵�Ă���
	if (imageData[imageName].anim.empty())
	{
		AddAnimationData(imageName, 0, 0, 1, false);
	}

	return imageData[imageName];
}

//�摜�f�[�^�̉��
std::list<std::pair<const std::string, ImageData>, std::allocator<std::pair<const std::string, ImageData>>>::iterator ImageLoader::DeleteImageData(const std::string& imageName)
{
	if (!imageData.count(imageName))
		return imageData.end();

	for (int i = 0; i < imageData[imageName].sheetNum; ++i)
	{
		DeleteGraph(imageData[imageName].handle[i]);
	}

	if (imageData[imageName].sheetNum == 1)
	{
		UTIL::SafeDelete(imageData[imageName].handle);
	}
	else
	{
		UTIL::SafeDeleteArr(imageData[imageName].handle);
	}

	for (auto animit : imageData[imageName].anim)
	{
		UTIL::SafeDelete(animit);
	}

	return imageData.erase(imageData.lower_bound(imageName));
}

//�S�Ẳ摜�f�[�^�̉��
void ImageLoader::AllDeleteImageData()
{
	for (	auto it = imageData.begin();
			it != imageData.end();)
	{
		it = DeleteImageData(it->first);
	}
	imageData.clear();
}

//�C���X�^���X�𓾂�
ImageLoader& ImageLoader::GetInstance()
{
	static ImageLoader imageLoader;
	return imageLoader;
}