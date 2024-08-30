#ifndef _DEBUG_
#define _DEBUG_
	
#ifdef __cplusplus
extern "C"{
#endif

	void db_DEBUG_Init(unsigned int BaudRates);
	void db_DEBUG_Putchar(char *_varString);
	void db_DEBUG_SendChar(char _varChar);
	void db_DEBUG_Number(int _varNumber);
	int db_DEBUG_compare(char *string);
	int db_DEBUG_flag(void);
	void db_DEBUG_Putchar_RRX(void);
#ifdef __cplusplus
}
#endif

#endif
