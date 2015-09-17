
#include <string>
#include <vector>
#include <assimp/scene.h>
class Bone 
{
public:
	std::string name;
	aiMatrix4x4 offsetMatix;
	aiMatrix4x4 bindTransform;
	unsigned int childCount;
	unsigned int  child[10];

	~Bone();
};
