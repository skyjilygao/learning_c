#include <windows.h>
#include <tlhelp32.h>	//���̿��պ���ͷ�ļ�
#include <stdio.h>


int main()
{

	// ������ǰ����
      HANDLE hPro = OpenProcess(PROCESS_TERMINATE, FALSE, 24540);
      if (hPro != NULL)
      {
      TerminateProcess(hPro, 0);
      CloseHandle(hPro);
      }
	  
//    int countProcess=0;									//��ǰ����������������
// 	PROCESSENTRY32 currentProcess;						//��ſ��ս�����Ϣ��һ���ṹ��
// 	currentProcess.dwSize = sizeof(currentProcess);		//��ʹ������ṹ֮ǰ�����������Ĵ�С
// 	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//��ϵͳ�ڵ����н�����һ������
	
// 	if (hProcess == INVALID_HANDLE_VALUE)
// 	{
// 		printf("CreateToolhelp32Snapshot()����ʧ��!\n");
// 		return -1;
// 	}
// 	BOOL bMore=Process32First(hProcess,&currentProcess);	//��ȡ��һ��������Ϣ
// 	while(bMore)
// 	{
// 		int pid = currentProcess.th32ProcessID;

// 		printf("PID=%5u    PName= %s\n",currentProcess.th32ProcessID,currentProcess.szExeFile);	//�������̿��գ�������ʾÿ��������Ϣ
		
	

// 		bMore=Process32Next(hProcess,&currentProcess);	//������һ��
// 		countProcess++;
// 	}
	
// 	CloseHandle(hProcess);	//���hProcess���
// 	printf("��������%d������������\n",countProcess);
// 	system("pause");
    
    return 0;
}