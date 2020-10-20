#pragma once


using namespace System;
using namespace Autodesk::AutoCAD::Geometry;
using namespace Autodesk::AutoCAD::DatabaseServices;

class ZfgkTriangle;

namespace zfgk
{
	namespace TrangleEntityDB
	{
		//����һ��Entity�̳е��й��࣬���з�װ��zfgkTriangle��Ķ������
		[Autodesk::AutoCAD::Runtime::Wrapper("zfgkTriangle")]
		public __gc class MgTriangle:public Autodesk::AutoCAD::DatabaseServices::Entity
		{
		public:
			MgTriangle(void);
			MgTriangle(Point3d pt1,Point3d pt2,Point3d pt3);

		public private:
			MgTriangle(System::IntPtr unmanagedPointer,bool autoDelete);

			//��ȡ���й�ʵ��ָ��
			inline ZfgkTriangle * GetImpObj()
			{
				//UnmangedObject() ������һ��AutoCAD�йܰ�װ���������ṩһ��ֱ�ӷ���VC++��ARXʵ�巽��
				return static_cast<ZfgkTriangle*>(UnmanagedObject.ToPointer());
			}

		public:
			//������ж���
			void GetVerts([Runtime::InteropServices::Out] Autodesk::AutoCAD::Geometry::Point3dCollection *&verts);

			//����ĳ������
			void SetVertAt(int index,Point3d point);

			//���������
			__property double get_Area();

		};
	}
}

