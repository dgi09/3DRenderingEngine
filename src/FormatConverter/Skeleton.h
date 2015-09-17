#include "Bone.h"
#include <assimp/anim.h>
#include <vector>
#include <unordered_map>

class Skeleton
{
public:
	aiMatrix4x4 globalInverse;
	std::vector<Bone> bones;
	std::unordered_map<std::string,unsigned int> nameMap;
};