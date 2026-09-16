#pragma warning(disable: 6031)

#include <iostream>
#include <bitset>
#include <cstdint> // uint32_t 사용을 위한 헤더

#include <io.h>
#include <fcntl.h>

using namespace std;
 
int main()
{
	uint32_t	yearDate = 0x20260917;
	unsigned short	*pYear, *pDate; 

	_setmode(_fileno(stdout), _O_U16TEXT); // 윈도우 콘솔 창 유니코드 출력 모드

	pDate = reinterpret_cast<unsigned short*>(&yearDate);
	// ...

	pYear = pDate + 1;

	wcout << hex << *pYear;
	wcout << L"년 ";

	unsigned char* pMonth, * pdate;
	pdate = reinterpret_cast<unsigned char*>(pDate);
	pMonth = pdate + 1;

	wcout << *pMonth << L"월 " << *pdate << L"일 " << endl;

	///------------------------
	//uint32_t	yearDate2 = 0;
	unsigned long long	yearDate2 = 0;
	/// Sep 17 2026 <= 이 형태로 위 변수에 쓸 것
	/// 00536570 0017 2026 // 월-일-년 
	byte* pB = reinterpret_cast<byte*>(&yearDate2);  
	
	*pB++ = (byte)0x26;
	*pB++ = (byte)0x20;
	*pB++ = (byte)0x17;
	*pB++ = (byte)0x00;
	*pB++ = (byte)0x70;
	*pB++ = (byte)0x65;
	*pB++ = (byte)0x53;
	*pB-- = (byte)0x00; // 월 -> 3문자. 맨 앞에 00을 넣어는 주되 무시

	wcout << *reinterpret_cast<char*>(pB--);
	wcout << *reinterpret_cast<char*>(pB--);
	wcout << *reinterpret_cast<char*>(pB--) << L" ";	

	pB--;  // 0x00 skip
	wcout <<
		hex << static_cast<uint32_t>(*(reinterpret_cast<unsigned char*>(pB--))) << L" " <<	// date
		hex << static_cast<uint32_t>(*(reinterpret_cast<unsigned char*>(pB--))) <<	// year
		hex << static_cast<uint32_t>(*(reinterpret_cast<unsigned char*>(pB))) << endl;

	return 0;
}
