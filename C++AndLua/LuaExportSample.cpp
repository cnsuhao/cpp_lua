/*
1�����Ÿ�lua�ĺ����У�����������߷���ֵ���ַ���������ʹ��const char*����Ҫʹ��std::string��
   ʹ��std::string���ж���Ĺ��������ɱ���
2�����ڴ�lua�����з��س������ַ��������Ҫ����Ļ���һ��Ҫ�Լ������ڴ�ռ䣬���ַ�������������
3�������һ�����󿪷ŵ�lua�����У���ö������������ҲҪ���ŵ�lua�����У�lua��GC����ʱ�����
   �Ҳ���������������ʹ��free�����ͷ��ڴ棬���δ֪bug��
*/
#include "LuaExportSample.h"

namespace LuaExport
{
	void Script_GetNumber(int& nFirst, int& nSecond)
	{
		nFirst = 10;
		nSecond = 20;
	}
}
