#pragma once

//�ڴ˶�����Ҫ���õĲ��Ժ���
#define _TEST_DEMO_

/*
	Debug�÷���
		�ڰ���main�������ļ���include��ͷ�ļ���ͨ���޸�define��ͬ�ĺ�
		���ڲ�ͬ�Ĳ���main�����н����л���

		eg��
			#define _DEBUG1_

			#if defined(_DEBUG1_)
				int main() { ... }
			#elif defined(_DEBUG2_)
				int mian() { ... }
			#endif

*/