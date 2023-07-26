//#include <XephEngine/include/XephEngine.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stdio.h>

//using namespace xe;
//using namespace xe::Graphics;
//using namespace xe::Math;
//
//namespace stdfs = std::filesystem;
//
//struct Arguments
//{
//	stdfs::path inputFilename;
//	stdfs::path outputFilename;
//	float scale = 1.f;
//};
//
//std::optional<Arguments> ParseArgs(int argc, char* argv[])
//{
//	if (argc < 3)
//	{
//		return std::nullopt;
//	}
//
//	Arguments args;
//	args.inputFilename = argv[argc - 2];
//	args.outputFilename = argv[argc - 1];
//
//	for (int i = 1; i + 2 < argc; ++i)
//	{
//		if (strcmp(argv[i], "-scale") == 0)
//		{
//			args.scale = atof(argv[i + 1]);
//			++i;
//		}
//	}
//
//	return args;
//}

//Vector3 ToVector3(aiVector3D v)
//{
//	return { static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z) };
//}
//
//Quaternion ToQuaternion(aiQuaternion q)
//{
//	return { static_cast<float>(q.x), static_cast<float>(q.y), static_cast<float>(q.z), static_cast<float>(q.w) };
//}
//
//Color ToColor(aiColor3D c)
//{
//	return { static_cast<float>(c.r), static_cast<float>(c.g), static_cast<float>(c.b), 1.f};
//}

//Matrix4 ToMatrix4(const aiMatrix4x4& m)
//{
//	return {
//		static_cast<float>(m.a1),static_cast<float>(m.b1),static_cast<float>(m.c1),static_cast<float>(m.d1),
//		static_cast<float>(m.a2),static_cast<float>(m.b2),static_cast<float>(m.c2),static_cast<float>(m.d2),
//		static_cast<float>(m.a3),static_cast<float>(m.b3),static_cast<float>(m.c3),static_cast<float>(m.d3),
//		static_cast<float>(m.a4),static_cast<float>(m.b4),static_cast<float>(m.c4),static_cast<float>(m.d4)
//	};
//}

int main(int argc, char* argv[])
{

	return 0;
}