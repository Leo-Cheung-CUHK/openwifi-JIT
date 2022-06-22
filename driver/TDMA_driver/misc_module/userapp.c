#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

#define BEEPOFF	0
#define BEEPON 	1

#pragma  pack(push)  //保存对齐状态  
#pragma  pack(1)  
typedef struct strcChange
{
    unsigned char user_ID;
    unsigned int allo_vec;
}STRU_CHANGE;
#pragma  pack(pop)

/*
 * @description		: main主程序
 * @param - argc 	: argv数组元素个数
 * @param - argv 	: 具体参数
 * @return 			: 0 成功;其他 失败
 */
int main(int argc, char *argv[])
{
	int fd, retvalue, wr;
	char *filename;
	unsigned char databuf[10];
	
	if(argc > 5){
		printf("Error Usage!\r\n");
		return -1;
	}

	filename = argv[1];
	
	fd = open(filename, O_RDWR);	 //驱动 
	if(fd < 0){
		printf("file %s open failed!\r\n", argv[1]);
		return -1;
	}

	
	wr = atoi(argv[2]);	/* 要执行的操作：打开或关闭 */
	
	if(wr == 1)
	{
		STRU_CHANGE strChangeData1;
		strChangeData1.user_ID  = atoi(argv[3]);
    	strChangeData1.allo_vec = atoi(argv[4]);
    	memcpy(databuf, &strChangeData1, sizeof(strChangeData1));
    	printf("write databuf[0] = 0x%x\n", databuf[0]);
		retvalue = write(fd, databuf, sizeof(databuf));
		if(retvalue < 0){
		printf("Write Failed!\r\n");
		close(fd);
		return -1;
	    }	
	}else if(wr == 2){
		STRU_CHANGE * pstrChangeData1;
		printf("before read: %x\n", databuf[0]);
		retvalue = read(fd, databuf, sizeof(databuf));
		if(retvalue < 0){
		printf("Read Failed!\r\n");
		close(fd);
		return -1;
		}
		pstrChangeData1 = (STRU_CHANGE *)((char*)databuf);
		printf("Read data A: 0x%x \r\n", pstrChangeData1->user_ID); 
		printf("Read data B: 0x%08x \r\n", pstrChangeData1->allo_vec); 
		close(fd);
		return -1; 
	}
	
	retvalue = close(fd);  //关闭文件 
	if(retvalue < 0){
		printf("file %s close failed!\r\n", argv[1]);
		return -1;
	}
	
	return 0;
}


