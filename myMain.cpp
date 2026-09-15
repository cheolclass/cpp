#include <iostream>
#include <bitset>
#include <cstdint>

using namespace std;
 
int main()
{
	//int i = 0x12345678;
	uint32_t	i = 0x12345678;

	//unsigned char* pC = (unsigned char*) &i;
	unsigned char* pC = reinterpret_cast<unsigned char*> (&i);

	// Big-endian vs. Little-endian
	//cout << hex << (int)(*pC) << ", " << dec << (int)*pC << ", " << bitset<8>(*pC) << endl;
	cout << hex << static_cast<int>(*pC) << ", " << 
		dec << static_cast<int>(*pC) << ", " << bitset<8>(*pC) << endl;
	cout << bitset<8>(*(pC+1))  << endl;
	cout << bitset<8>(*(pC + 2)) << endl;
	cout << hex << static_cast<int>(*(pC + 3)) << ", " << 
		dec << static_cast<int>(*(pC + 3)) << ", " << bitset<8>(*(pC + 3)) << endl; // 18, 0001 0010

	return 0;
}
