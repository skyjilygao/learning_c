/**
 * 复制网络代码。学习c。功能：根据输入端口号，查到相应进程并kill。（比较狠，慎行）
 * Date: 20230511
 * Author: skyjilygao
*/

#include <windows.h>
// #include <tlhelp32.h>	//进程快照函数头文件
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

void killProcess(string pid);
bool GetNameByPort(int nPort, string &strResult)
{
	char pResult[128] = {0};
	const char *pPortFilePath = "c:\\~vkutmp";
	const char *pProcessFilePath = "c:\\~vvkutmp";
	sprintf(pResult, "netstat -ano|findstr %d > %s", nPort, pPortFilePath);
	system(pResult);
	FILE *pPortFile = fopen(pPortFilePath, "r");
	if (NULL != pPortFile)
	{
		fread(pResult, 1, sizeof(pResult), pPortFile);
		strResult = pResult;
		if ("" != strResult)
		{
			int off = strResult.find_last_of(0x0a);
			if (off > -1)
			{
				strResult = strResult.substr(0, off);
				off = strResult.find_last_of(0x20);
				if (off > -1)
				{
					strResult = strResult.substr(off + 1);
					string pid = strResult.c_str();
					printf("port -> %s\n", pid.c_str());
					sprintf(pResult, "tasklist|findstr %s > %s", pid.c_str(), pProcessFilePath);
					system(pResult);
					printf("process -> %s\n", pResult);
					FILE *pProcessFile = fopen(pProcessFilePath, "r");
					if (NULL != pProcessFile)
					{
						memset(pResult, 0, sizeof(pResult));
						fread(pResult, 1, sizeof(pResult), pProcessFile);

						strResult = pResult;
						printf("process -> %s\n", strResult.c_str());
						if ("" != strResult)
						{
							killProcess(pid);
							
							off = -1;
							off = strResult.find_first_of(0x20);
							if (off > -1)
							{
								strResult = strResult.substr(0, off);
								return true;
							}
						}
					}
					fclose(pProcessFile);
					pProcessFile = NULL;

					sprintf(pResult, "del %s", pProcessFilePath);
					system(pResult);
				}
			}
		}
	}
	strResult = "";
	fclose(pPortFile);
	pPortFile = NULL;

	sprintf(pResult, "del %s", pPortFilePath);
	system(pResult);
	return false;
}

int main(int argc, char *argv[])
{
	if(argc <=1){
		printf("请输入端口号");
		return 0;
	}
	printf("端口号：%s\n", argv[1]);
	string strResult = "";
	bool bo = GetNameByPort(atoi(argv[1]), strResult);
	printf("process name -> %s \n", strResult.c_str());
	// system("pause");
	return 1;
}

void killProcess(string pid)
{
	string confirm;
	cout << "请确认是否停止进程[" << pid.c_str() << "]：是[Y]，否[N]：";
	cin >> confirm;
	printf("输入结果：%s\n", confirm.c_str());
	printf("-------比较结果：%d\n", strcmp("Y", confirm.c_str()));
	if (strcmp("y", confirm.c_str()) == 0 || strcmp("Y", confirm.c_str()) == 0)
	{
		printf("++++++：%d\n", strcmp("Y", confirm.c_str()));
		printf("pid：%d\n", atoi(pid.c_str()));
		// 结束当前进程
		HANDLE hPro = OpenProcess(PROCESS_TERMINATE, FALSE, atoi(pid.c_str()));
		if (hPro != NULL)
		{
			TerminateProcess(hPro, 0);
			CloseHandle(hPro);
		}
	}
	else
	{
		printf("取消停止进程[%s]!", pid.c_str());
	}
}